#include "client.hpp"

using namespace boost::asio;
using json = nlohmann::json;
#define IO_BIND(a)  boost::bind(&Client::a, this, placeholders::error, placeholders::bytes_transferred)
#define CL_BIND(a)  boost::bind(&Client::a, this, placeholders::error)


std::string to_string(streambuf &buf) {
    std::ostringstream out;
    out << &buf;
    return out.str();
}

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
}

void Client::on_login(boost_error &error, size_t bytes, std::string login) {
    if (error || bytes == 0) {
        std::cerr << "WRITE ERROR: " << error.message() << "\n";
        return;
    }
    state = State::Menu;
    std::string check = login;
    async_write(socket_, buffer(check), IO_BIND(dummy));
}

void Client::ready_to_play(boost_error &error, size_t bytes) {
    if (error || bytes == 0) {
        std::cerr << "WRITE ERROR: " << error.message() << "\n";
        return;
    }
    state = State::Ready;
    std::string check = "play";
    async_write(socket_, buffer(check), IO_BIND(dummy));
}

void Client::send_game_info(boost_error &error, size_t bytes) {
    if (error || bytes == 0) {
        std::cerr << "WRITE ERROR: " << error.message() << "\n";
        return;
    }

    std::string check = GameInfo.dump();
    async_write(socket_, buffer(check), IO_BIND(dummy));
    do_read(IO_BIND(got_response));
}

void Client::dummy(boost_error &error, size_t bytes) {
    if (error || bytes == 0) {
        std::cerr << "WRITE ERROR: " << error.message() << "\n";
        return;
    }
    do_read(IO_BIND(got_response));
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
    std::cout << response << '\n';

    if ( state == State::Play ) {
        GameInfo = json::parse(response);
        std::cout << std::setw(4) << GameInfo << "\n\n";
    }

    if ( response != "Sorry, the game has started" && state == State::Ready ) {
        GameInfo = json::parse(response);
        state = State::Play;
    }

    do_read(IO_BIND(got_response));
}

void Client::close_connect() {
    std::cout << "ENDING\n";
    std::string check = "end";
    write(socket_, buffer(check));
    socket_.shutdown(ip::tcp::socket::shutdown_both);
    socket_.close();
    state = State::End;
}

json Client::get_game_info() {
    return GameInfo;
}