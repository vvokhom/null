#include "server.hpp"
#include <iostream>

#define SV_BIND(a)  boost::bind(&Server::a, this, new_client, placeholders::error)
#define NOCL_BIND(a)  boost::bind(&Server::a, this, placeholders::error)
#define IO_BIND(a)  boost::bind(&Client::a, shared_from_this(), placeholders::error, placeholders::bytes_transferred)
#define GAME_LOBBY_SIZE 2
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
            login = std::string(read_buff, bytes - 1);
            on_login();
            break;
        }
        case State::Menu: {
            if(check == "play\n") {
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
                GameInfo = update_game_info(GameInfo);

                for(auto it = (*playroom).begin(); it != (*playroom).end(); ++it) {
                    write_buff = GameInfo.dump();
                    do_write((*playroom)[it->first]->socket(), IO_BIND(dummy));
                }
            }
            break;
        }
    }
    do_read();
}

void Client::connection_close() {
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
        GameInfo[it->first] = {{"Money", 1500}, {"Position", 0}, {"Property", { {"Position", 0}, {"HouseCount", 0} }}};
    }
        
    GameInfo["Active"] = 0;
    GameInfo["PlayersNumber"] = GAME_LOBBY_SIZE;

    for(auto it = (*playroom).begin(); it != (*playroom).end(); ++it) {
        (*playroom)[it->first]->state = State::Play;
        write_buff = GameInfo.dump();
        do_write((*playroom)[it->first]->socket(), IO_BIND(dummy));
    }

    return GameInfo;
}

json Client::update_game_info(json info) {
    int shift = 2 + rand() % (12);
    int pos = info[login]["Position"];
    if (pos + shift > MAPP_SIZE) {
        int money = info[login]["Money"];
        info[login]["Money"] = money + 200;
    }
    info[login]["Position"] = (pos + shift) % MAPP_SIZE;

    // Анализ позиции куда наступил игрок:
    // 1) Если пустая клетка, послать сообщение с предложение покупки. Если купил изменить состояние ячейки
    // 2) Если ячейка занята, вычесть ренту из денег
    // 3) Если ячейка игрока и собрано все семейство, послать сообщение с предложение постройки дома. Если построил изменить состояние ячейки
    // 4) Если особая ячейка (шанс, общественная казна, тюрьма) - вызвать соотвествеющую функцию

    // Анализ состояния денег игрока
    // 1) Если денег больше нуля, продолжаем
    // 2) Если денег 0 или меньше, удаляем игрока из списка, уменьшаем колличество игроков.
    // Если отстался один игрок возвращяем логин победителя

    // Меняем активного игрока
    int num = info["PlayersNumber"];
    int ActivePlayer = info["Active"];
    info["Active"] = (ActivePlayer + 1) % num;

    return info;
}