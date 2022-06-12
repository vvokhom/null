#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include "json.hpp"

using namespace boost::asio;
using json = nlohmann::json;

typedef const boost::system::error_code boost_error;

constexpr unsigned int default_port = 49001;
constexpr char default_ip[20] = "127.0.0.1";

enum class State {
    Login,
    Menu,
    Ready,
    Play,
    End
};

class Client {
private:
    State state = State::Login;
    io_context context;
    ip::tcp::socket socket_;
    char output[1024 * 5];
    json GameInfo;
    bool StartPlay = false;
    std::string login;
    bool ActualGameInfo = false;

    void connect(std::string &ip, unsigned int &port);
    void on_connect(boost_error &error);
    void do_read(std::function<void(boost_error, size_t)> callback);
    void on_login(boost_error &error, size_t bytes);
    void on_move(boost_error &error, size_t bytes);
    void got_response(boost_error &error, size_t bytes);
    void ready_to_play(boost_error &error, size_t bytes);

public:
    Client(std::string &ip, unsigned int &port) :  socket_(context) {
        connect(ip, port);
    }
    json GetGameInfo();
    void Login(std::string login);
    void GetInLine();
    bool IsPlay();
    bool IsActive();
    bool IsActualGameInfo();
    void MakeMove(json GameState);
    void CloseConnect();
};
