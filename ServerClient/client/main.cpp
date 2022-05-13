#include <string>

#include "client.hpp"

int main(int argc, char const *argv[]) {
    io_context context;
    std::string ip = argc > 1 ? argv[1] : default_ip;
    unsigned int port = argc > 2 ? std::stol(argv[2]) : default_port;
    Client client(context, ip, port);
    context.run();

    boost_error error;
    size_t bytes;
    client.on_login(error, bytes, "Leroy");
    return 0;
}