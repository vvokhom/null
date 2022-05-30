#include "client.hpp"

using namespace boost::asio;
using json = nlohmann::json;
#define IO_BIND(a)  boost::bind(&Client::a, this, placeholders::error, placeholders::bytes_transferred)
#define CL_BIND(a)  boost::bind(&Client::a, this, placeholders::error)


void clear(char* arr) {
    std::fill(arr, arr + sizeof(arr), 0);
}

void Client::connect(std::string &ip, unsigned int &port) {
    ip::tcp::endpoint endpoint(ip::address::from_string(ip), port);
    socket_.async_connect(endpoint, CL_BIND(on_connect));
}

void Client::on_connect(boost_error &error) {
    if (error) {
        std::cerr << "CONNECTION ERROR: " << error.message() << "\n";
        return;
    }

    std::thread thread([&](){context.run();});
    thread.detach();
    do_read(IO_BIND(got_response));
}

void Client::on_login(boost_error &error, size_t bytes) {
    if (error || bytes == 0) {
        std::cerr << "WRITE ERROR: " << error.message() << "\n";
        return;
    }
    state = State::Menu;
}

void Client::ready_to_play(boost_error &error, size_t bytes) {
    if (error || bytes == 0) {
        std::cerr << "WRITE ERROR: " << error.message() << "\n";
        return;
    }
    state = State::Ready;
}

void Client::MakeMove(json GameState) {
    std::string check = GameState.dump();
    async_write(socket_, buffer(check), IO_BIND(on_move));
    context.reset();
    context.poll();
}

void Client::on_move(boost_error &error, size_t bytes) {
    if (error || bytes == 0) {
        std::cerr << "WRITE ERROR: " << error.message() << "\n";
        return;
    }
}

void Client::do_read(std::function<void(boost_error, size_t)> callback) {
    clear(output);
    socket_.async_read_some(buffer(output, sizeof(output)), callback);
}

void Client::got_response(boost_error &error, size_t bytes) {
    if (error) {
        if (error != boost::system::errc::operation_canceled) {
            std::cerr << "MESSAGE READ ERROR: " << error.message() << "\n";
        }
        return;
    }

    if (bytes == 0) {
        std::cerr << "NO MESSAGE GOT\n";
        return;
    }

    if (state == State::End) {
            return;
    }

    std::string response(output, bytes);

    if ( state == State::Play ) {
        GameInfo = json::parse(response);
        ActualGameInfo = true;
    }

    if ( response != "Sorry, the game has started" && state == State::Ready ) {
        GameInfo = json::parse(response);
        ActualGameInfo = true;
        state = State::Play;
        StartPlay = true;
    }
    do_read(IO_BIND(got_response));
}

void Client::CloseConnect() {
    std::string check = "end";
    write(socket_, buffer(check));
    socket_.shutdown(ip::tcp::socket::shutdown_both);
    socket_.close();
    state = State::End;
}

json Client::GetGameInfo() {
    ActualGameInfo = false;
    return GameInfo;
}

void Client::Login(std::string login) {
    this->login = login;
    async_write(socket_, buffer(login), IO_BIND(on_login));
    context.reset();
    context.poll();
}

void Client::GetInLine() {
    std::string buff = "play";
    async_write(socket_, buffer(buff), IO_BIND(ready_to_play));
    context.reset();
    context.poll();
}

bool Client::IsPlay() {
    return StartPlay;
}

bool Client::IsActive() {
    if(GameInfo.empty()) {
        return false;
    }

    int ActiveId = GameInfo["Active"];
    if (login != GameInfo["Players"][ActiveId]) {
        return false;
    }

    return true;
}

bool Client::IsActualGameInfo() {
    return ActualGameInfo;
}