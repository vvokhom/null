#include "client.hpp"

using namespace boost::asio;
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
    get_client_input();
}

void Client::get_client_input() {
    switch (state) {
        case State::Login: {
            std::cout << "Enter your login\n";
            break;
        }
        case State::Echo: {
            break;
        }
    }
    async_read_until(input_stream, read_buf, '\n', IO_BIND(do_write));
}

void Client::do_write(boost_error &error, size_t bytes) {
    if (error || bytes == 0) {
        std::cerr << "ERROR READING FROM CLIENT: " << error.message() << "\n";
        return;
    }

    std::string check = to_string(read_buf);
    if (check == "end\n") {
        std::cout << "ENDING\n";
        write(socket_, buffer(check));
        socket_.shutdown(ip::tcp::socket::shutdown_both);
        socket_.close();
        state = State::End;
        return;
    }

    std::function<void(boost_error, size_t)> callback;
        
    switch (state) {
        case State::Login: {
            callback = IO_BIND(on_login);
            break; 
        }
        case State::Echo: {
            callback = IO_BIND(on_echo);
            break; 
        } 
    }

    async_write(socket_, buffer(check), callback);
}

void Client::on_login(boost_error &error, size_t bytes) {
    if (error || bytes == 0) {
        std::cerr << "WRITE ERROR: " << error.message() << "\n";
        return;
    }
    
    state = State::Echo;
    get_client_input();
}

void Client::on_echo(boost_error &error, size_t bytes) {
    if (error || bytes == 0) {
        std::cerr << "WRITE ERROR: " << error.message() << "\n";
        return;
    }
    do_read(IO_BIND(got_response));
    get_client_input();
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

    do_read(IO_BIND(got_response));
}
