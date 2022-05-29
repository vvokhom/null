#include "mainwindow.h"
#include "screensfactory.h"

#include <QScreen>
#include <QApplication>
#include <QException>
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    try {
        this->setWindowTitle("Monopolia by Null Team");

        container = new QStackedWidget;
        container->setObjectName("GUI");

        QString mainStyle = "QWidget#window {"
                            "background-color:rgb(243, 243, 211);"
                            "}";
        container->setStyleSheet(mainStyle);
        container->setObjectName("window");

        //start client
      std::string ip =  default_ip;
      unsigned int port = default_port;

      client = new Client(ip, port);

        //


        this->factory = new ScreensFactory;
        this->navigator = new FragmentNavigator(this->container, this->factory, this->client);

        this->resize(QApplication::screens().at(0)->availableGeometry().size() * 0.7);
        this->setCentralWidget(container);

    } catch (std::exception& e) {
        qDebug("%s", e.what());
    }

}

MainWindow::~MainWindow() {
  client->CloseConnect();
  delete client;
    delete navigator;
    delete container;
    delete factory;
}

#include "moc_mainwindow.cpp"
