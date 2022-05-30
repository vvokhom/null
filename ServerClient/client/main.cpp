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
    std::string str;

    std::cin >> str;
    client.Login(str);

    int i;
    while(std::cin >> i) {
        switch(i) {
            case 1: {
                client.GetInLine();
                break;
            }
            case 2: {
                if (client.IsActive()) {
                    client.MakeMove(client.GetGameInfo());
                } else {
                    std::cout << "You are not active" << std::endl;
                }
                break;
            }
            case 3: {
                client.CloseConnect();
                break;
            }
            case 4: {
                if(client.IsActualGameInfo()) {
                    std::cout << "ActualGameInfo" << std::endl;
                } else {
                    std::cout << " NOT ActualGameInfo" << std::endl;
                }

                std::cout << client.GetGameInfo() << std::endl;
                break;
            }
        }
    }
}