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
    posix::stream_descriptor input_stream;
    State state = State::Login;
    ip::tcp::socket socket_;
    char output[256];
    streambuf read_buf;
    json GameInfo;

    void connect(std::string &ip, unsigned int &port);
    void on_connect(boost_error &error);
    void get_client_input();
    void do_write(boost_error &error, size_t bytes);
    void do_read(std::function<void(boost_error, size_t)> callback);
    void on_login(boost_error &error, size_t bytes);
    void got_response(boost_error &error, size_t bytes);
    void ready_to_play(boost_error &error, size_t bytes);
    void dummy(boost_error &error, size_t bytes);
    void close_connect();

public:
    Client(io_context &context, std::string &ip, unsigned int &port) : input_stream(context, STDIN_FILENO), socket_(context) {
        connect(ip, port);
    }
};
