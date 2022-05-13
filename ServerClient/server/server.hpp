#include <boost/asio.hpp>
#include <boost/system.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <json.hpp>

using namespace boost::asio;
using json = nlohmann::json;
typedef const boost::system::error_code boost_error;

enum class State {
    Login,
    Menu,
    Ready,
    Play,
    End
};

constexpr unsigned int default_port = 49001;

class Client: public boost::enable_shared_from_this<Client> {
public:
    typedef boost::shared_ptr<Client> ptr;
    typedef std::unordered_map<std::string, Client::ptr> clients_map;

private:
    char read_buff[256];
    std::string login;
    std::string write_buff;
    size_t id = 0;
    ip::tcp::socket socket_;
    clients_map* map_;
    clients_map* playroom;
    State state;

    Client(io_context &io_context_) : socket_(io_context_) {}
    void do_read();
    void do_write(ip::tcp::socket &destination, std::function<void(boost_error, size_t)> callback);    
    void input_analysis(boost_error &error, size_t bytes);
    void on_login();
    void connection_close();
    void ready_to_play();
    json create_game_info();
    json update_game_info(json info);

    void dummy(boost_error &error, size_t bytes) {}

public:
    static ptr create(io_context &io_context_);
    ip::tcp::socket& socket();
    size_t get_id();
    std::string get_state();
    void run(clients_map *map, clients_map *_playroom, size_t num);
};



class Server {
private:
    io_context &io_context_;
    ip::tcp::acceptor acceptor_;
    Client::clients_map clients;
    Client::clients_map playroom;
    steady_timer timer;
    size_t client_num = 0;

    void start_accept();
    void on_accept(Client::ptr new_client, boost_error &error);
    void clients_status(boost_error &error);

public:
    Server(boost::asio::io_context &context, unsigned int port): io_context_(context),
      acceptor_(context, ip::tcp::endpoint(ip::tcp::v4(), port)), timer(context, std::chrono::seconds(3)) {};
    void run();
};
