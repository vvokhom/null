#include "server.hpp"
#include <iostream>
#include <json.hpp>

#define SV_BIND(a)  boost::bind(&Server::a, this, new_client, placeholders::error)
#define NOCL_BIND(a)  boost::bind(&Server::a, this, placeholders::error)
#define IO_BIND(a)  boost::bind(&Client::a, shared_from_this(), placeholders::error, placeholders::bytes_transferred)

using json = nlohmann::json;

void clear(char* arr) {
    std::fill(arr, arr + sizeof(arr), 0);
}



void Server::run() {
    start_accept();
    boost_error err;
    clients_status(err);
}

void Server::start_accept() {
    Client::ptr new_client = Client::create(io_context_);
    acceptor_.async_accept(new_client->socket(), SV_BIND(on_accept));
}

void Server::on_accept(Client::ptr new_client, boost_error &error) {
    if (error) {
        std::cerr << "CONNECTION ERROR " << error.message() << "\n";
        return;
    }
    std::cout << "CLIENT CONNECTED\n";
    ++client_num;
    new_client->run(&clients, &playroom, client_num);
    start_accept();
}

void Server::clients_status(boost_error &error) {
    if (error) {
        std::cerr << "WAIT ERROR " << error.message() << "\n";
    }
    timer.expires_from_now(std::chrono::seconds(3));

    if (clients.empty()) {
        std::cout << "NO CLIENTS LOGGED IN\n";
    } else {
        std::cout << "CLIENTS LOGGED IN ARE:\n";
        for (auto &it : clients) {
            std::cout << it.second->get_id() << ": " << it.first << '\n';
        }
    }

    timer.async_wait(NOCL_BIND(clients_status));
}



Client::ptr Client::create(io_context &io_context_) {
    return ptr(new Client(io_context_));
}

ip::tcp::socket& Client::socket() {
    return socket_;
}

void Client::run(clients_map *map, clients_map *_playroom, size_t num) {
    id = num;
    map_ = map;
    playroom = _playroom;
    state = State::Login;
    do_read();
}

void Client::do_read() {
    clear(read_buff);
    socket_.async_read_some(buffer(read_buff, sizeof(read_buff)), IO_BIND(input_analysis));
}

void Client::input_analysis(boost_error &error, size_t bytes) {
    if (error) {
        switch(error.value()) {
            case boost::asio::error::eof: {
                connection_close();
                break;
            }
            default: {
                std::cerr << id << ": INPUT READ ERROR: " << error.message() << "\n";
                break;
            }
        }
        return;
    }

    if (bytes == 0) {
        std::cerr << id << ": NO INPUT GOT\n";
        return;
    }

    std::string check(read_buff, bytes);
    if (check == "end\n") {
        connection_close();
        return;
    }

    switch (state) {
        case State::Login: {
            login = std::string(read_buff, bytes - 1);
            on_login();
            break;
        }
        case State::Menu: {
            if(check == "play\n") {
                if ((*playroom).size() == 2) {
                    write_buff = "Sorry, the game has started";
                    do_write(socket_, IO_BIND(dummy));
                } else {
                    ready_to_play();
                }
                do_read();
            }
            break;
        }
        case State::Echo: {
            write_buff = check;
            do_write(socket_, IO_BIND(dummy));
            do_read();
            break;
        }
        case State::Play: {
            json GameInfo = json::parse(check);
            int player = GameInfo["Active"];
            if( login == GameInfo["Players"][player]) {
                int shift = 2 + rand() % (12);
                int pos = GameInfo[login]["Position"];
                GameInfo[login]["Position"] = pos + shift;
                int num = GameInfo["PlayersNumber"];
                GameInfo["Active"] = (player + 1) % num;

                for(auto it = (*playroom).begin(); it != (*playroom).end(); ++it) {
                    write_buff = GameInfo.dump();
                    do_write((*playroom)[it->first]->socket(), IO_BIND(dummy));
                }
            }
            do_read();
            break;
        }
    }
}

void Client::connection_close() {
    std::cout << "CLIENT HAS EXITED\n";
    state = State::End;
    socket_.shutdown(ip::tcp::socket::shutdown_both);
    socket_.close();
    (*map_).erase(login);
}

void Client::ready_to_play() {
    (*playroom)[login] = shared_from_this();
    if((*playroom).size() == 2) {
        srand(time(NULL));

        json GameInfo;
        GameInfo["Players"] = {};
        for(auto it = (*playroom).begin(); it != (*playroom).end(); ++it) {
            GameInfo["Players"].push_back(it->first);
            GameInfo[it->first] = {{"Money", 0}, {"Position", 0}, {"Property", { {"Position", 0}, {"HouseCount", 0} }}};
        }
        GameInfo["Active"] = 0;
        GameInfo["PlayersNumber"] = 2;

        for(auto it = (*playroom).begin(); it != (*playroom).end(); ++it) {
            (*playroom)[it->first]->state = State::Play;
            write_buff = GameInfo.dump();
            do_write((*playroom)[it->first]->socket(), IO_BIND(dummy));
        }

        json j = json::parse(GameInfo.dump());
        std::cout << j.dump() << std::endl;

    } else {
        state = State::Ready;
    }
}

void Client::on_login() {
    (*map_)[login] = shared_from_this();
    state = State::Menu;
    do_read();
}

void Client::do_write(ip::tcp::socket &destination, std::function<void(boost_error, size_t)> callback) {
    async_write(destination, buffer(write_buff), callback);
    write_buff.clear();
}

size_t Client::get_id() {
    return id;
}