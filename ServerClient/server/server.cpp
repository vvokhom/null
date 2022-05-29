#include "server.hpp"
#include <iostream>

#define SV_BIND(a)  boost::bind(&Server::a, this, new_client, placeholders::error)
#define NOCL_BIND(a)  boost::bind(&Server::a, this, placeholders::error)
#define IO_BIND(a)  boost::bind(&Client::a, shared_from_this(), placeholders::error, placeholders::bytes_transferred)
#define GAME_LOBBY_SIZE 1
#define MAPP_SIZE 39

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
    timer.expires_from_now(std::chrono::seconds(5));

    if (clients.empty()) {
        std::cout << "NO CLIENTS LOGGED IN\n";
    } else {
        std::cout << "CLIENTS LOGGED IN ARE:\n";
        for (auto &it : clients) {
            std::cout << it.second->get_id() << ": " << it.first << " - " << it.second->get_state() << '\n';
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

    if (check == "end") {
        connection_close();
        return;
    }
    switch (state) {
        case State::Login: {
            login = check;
            on_login();
            break;
        }
        case State::Menu: {
            if(check == "play") {
                if ((*playroom).size() == GAME_LOBBY_SIZE) {
                    write_buff = "Sorry, the game has started";
                    do_write(socket_, IO_BIND(dummy));
                } else {
                    ready_to_play();
                }
            }
            break;
        }
        case State::Play: {
            json GameInfo = json::parse(check);

            int ActivePlayer = GameInfo["Active"];
            if( login == GameInfo["Players"][ActivePlayer]) {
                int Players = GameInfo["PlayersNumber"];
                for(int i = 0; i < Players; ++i) {
                    if((*playroom).find(GameInfo["Players"][i]) == (*playroom).end()) {
                        std::string login = GameInfo["Players"][i];
                        GameInfo[login]["Alive"] = false;
                    }
                }

                int count = 0;
                while(true) {
                    ActivePlayer = (++ActivePlayer) % Players;
                    ++count;
                    std::string login = GameInfo["Players"][ActivePlayer];
                    if(GameInfo[login]["Alive"] == true) {
                        break;
                    }
                    if ( count == Players) {
                        break;
                    }
                }
                GameInfo["Active"] = ActivePlayer;

                for(auto it = (*map_).begin(); it != (*map_).end(); ++it) {
                    if((*map_)[it->first]->state == State::Play || (*map_)[it->first]->state == State::Ready) {
                        write_buff = GameInfo.dump();
                        do_write((*map_)[it->first]->socket(), IO_BIND(dummy));
                    }
                 }
            }
            break;
        }
    }
    do_read();
}

void Client::connection_close() {
    if ((*map_).find(login) == (*map_).end()) {
        return;
    }
    std::cout << login << " - " << "CLIENT HAS EXITED\n";
    state = State::End;
    socket_.shutdown(ip::tcp::socket::shutdown_both);
    socket_.close();
    (*map_).erase(login);
    (*playroom).erase(login);
}

void Client::ready_to_play() {
    (*playroom)[login] = shared_from_this();

    if((*playroom).size() == GAME_LOBBY_SIZE) {
        json GameInfo = create_game_info();
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

std::string Client::get_state() {
    std::string result;
    switch (state)
    {
    case State::Login : {
        result = "Login";
        break;
    }
    case State::Menu : {
        result = "Menu";
        break;
    }
    case State::Ready : {
        result = "Ready";
        break;
    }
    case State::Play : {
        result = "Play";
        break;
    }
    case State::End : {
        result = "End";
        break;
    }
    }
    return result;
}

json Client::create_game_info() {
    srand(time(NULL));
    json GameInfo;

    GameInfo["Players"] = {};

    for(auto it = (*playroom).begin(); it != (*playroom).end(); ++it) {
        GameInfo["Players"].push_back(it->first);
        GameInfo[it->first] = {{"Funds", 1500}, {"Position", 0}, {"InPrison", false}, {"Alive", true}};
    }
        
    GameInfo["Active"] = 0;
    GameInfo["PlayersNumber"] = GAME_LOBBY_SIZE;

    GameInfo["Map"] = {};
    GameInfo["Map"][0] = {{"Type", 0}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][1] = {{"Type", 1}, {"Price", 60}, {"StreetId", 0}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][2] = {{"Type", 7}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][3] = {{"Type", 1}, {"Price", 60}, {"StreetId", 1}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][4] = {{"Type", 2}, {"Price", 200}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][5] = {{"Type", 3}, {"Price", 200}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][6] = {{"Type", 1}, {"Price", 100}, {"StreetId", 2}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][7] = {{"Type", 7}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][8] = {{"Type", 1}, {"Price", 100}, {"StreetId", 3}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][9] = {{"Type", 1}, {"Price", 120}, {"StreetId", 4}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][10] = {{"Type", 7}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][11] = {{"Type", 1}, {"Price", 140}, {"StreetId", 5}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][12] = {{"Type", 5}, {"Price", 150}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][13] = {{"Type", 1}, {"Price", 140}, {"StreetId", 6}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][14] = {{"Type", 1}, {"Price", 160}, {"StreetId", 7}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][15] = {{"Type", 3}, {"Price", 200}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][16] = {{"Type", 1}, {"Price", 180}, {"StreetId", 8}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][17] = {{"Type", 7}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][18] = {{"Type", 1}, {"Price", 180}, {"StreetId", 9}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][19] = {{"Type", 1}, {"Price", 200}, {"StreetId", 10}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][20] = {{"Type", 7}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][21] = {{"Type", 1}, {"Price", 220}, {"StreetId", 11}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][22] = {{"Type", 7}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][23] = {{"Type", 1}, {"Price", 220}, {"StreetId", 12}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][24] = {{"Type", 1}, {"Price", 240}, {"StreetId", 13}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][25] = {{"Type", 3}, {"Price", 200}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][26] = {{"Type", 1}, {"Price", 260}, {"StreetId", 14}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][27] = {{"Type", 1}, {"Price", 260}, {"StreetId", 15}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][28] = {{"Type", 4}, {"Price", 150}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][29] = {{"Type", 1}, {"Price", 280}, {"StreetId", 16}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][30] = {{"Type", 6}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][31] = {{"Type", 1}, {"Price", 300}, {"StreetId", 17}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][32] = {{"Type", 1}, {"Price", 300}, {"StreetId", 18}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][33] = {{"Type", 7}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][34] = {{"Type", 1}, {"Price", 320}, {"StreetId", 19}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][35] = {{"Type", 3}, {"Price", 200}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][36] = {{"Type", 7}, {"Price", 0}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][37] = {{"Type", 1}, {"Price", 350}, {"StreetId", 20}, {"OwnerId", -1}, {"HouseCount", 0}};
    GameInfo["Map"][38] = {{"Type", 2}, {"Price", 100}, {"StreetId", -1}, {"OwnerId", -1}};
    GameInfo["Map"][39] = {{"Type", 1}, {"Price", 400}, {"StreetId", 21}, {"OwnerId", -1}, {"HouseCount", 0}};

    for(auto it = (*playroom).begin(); it != (*playroom).end(); ++it) {
        (*playroom)[it->first]->state = State::Play;
    }

    for(auto it = (*map_).begin(); it != (*map_).end(); ++it) {
        if((*map_)[it->first]->state == State::Play || (*map_)[it->first]->state == State::Ready) {
            write_buff = GameInfo.dump();
            do_write((*map_)[it->first]->socket(), IO_BIND(dummy));
        }
    }

    return GameInfo;
}

