#include "server.hpp"
#include <iostream>

#define SV_BIND(a)  boost::bind(&Server::a, this, new_client, placeholders::error)
#define NOCL_BIND(a)  boost::bind(&Server::a, this, placeholders::error)
#define IO_BIND(a)  boost::bind(&Client::a, shared_from_this(), placeholders::error, placeholders::bytes_transferred)


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
    new_client->run(&clients, client_num);
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

void Client::run(clients_map *map, size_t num) {
    id = num;
    map_ = map;
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

    std::string check(read_buff, bytes - 1);
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
        case State::Echo: {
            write_buff = check;
            do_write(socket_, IO_BIND(dummy));
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

void Client::on_login() {
    (*map_)[login] = shared_from_this();
    state = State::Echo;
    do_read();
}

void Client::do_write(ip::tcp::socket &destination, std::function<void(boost_error, size_t)> callback) {
    async_write(destination, buffer(write_buff), callback);
    write_buff.clear();
}

size_t Client::get_id() {
    return id;
}