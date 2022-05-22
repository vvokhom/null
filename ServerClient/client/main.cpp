#include <string>
#include <thread>
#include <iostream>
#include <stdio.h>

#include <sstream>

#include "client.hpp"

int main(int argc, char const *argv[]) {
    std::string ip = argc > 1 ? argv[1] : default_ip;
    unsigned int port = argc > 2 ? std::stol(argv[2]) : default_port;

    Client client(ip, port);

    // std::thread thread([&](){context.run();});
    // thread.detach();

    std::cout << "Login" << std::endl;
    client.Login("Leroy");
    sleep(5);
    std::cout << "GetInLine" << std::endl;
    client.GetInLine();

    for(int i = 0; i < 10; ++i) {
            sleep(5);
            client.MakeMove();
            std::cout << client.GetGameInfo() << std::endl;
        }
    client.CloseConnect();
}