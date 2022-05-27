#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  //Web:
  /*  io_context context;
    std::string ip = argc > 1 ? argv[1] : default_ip;
    unsigned int port = argc > 2 ? std::stol(argv[2]) : default_port;
    Client client(context, ip, port);
    context.run();
*/
  //GUI:
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    w.show();
    return a.exec();
}
