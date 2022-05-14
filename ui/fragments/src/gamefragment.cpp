#include "gamefragment.h"
#include "screensfactory.h"


using namespace screens;

GameFragment::GameFragment() {
    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QFrame *centerContainer = new QFrame;

    QVBoxLayout *gameMainLayout = new QVBoxLayout;
    QHBoxLayout *gameContent = new QHBoxLayout;


    //QVBoxLayout *backContainer = new QVBoxLayout;

    QVBoxLayout *buttonContainer = new QVBoxLayout;
    QHBoxLayout *loadingButtonContainer = new QHBoxLayout;

    mapContainer = new QLabel("map");
    map = new QPixmap(":/map.jpg");
    mapContainer->setPixmap(*map);

    funds = new QLabel("100 M");

    gameContent->addWidget(mapContainer);
    //backButton = new QPushButton("Back");
    //backButton->setStyleSheet("color:#242424;font-size:24px");
    //connect(backButton, &QPushButton::clicked, this, &GameFragment::onBackPressed);

    //buttonContainer->addWidget(backButton);
    //loadingButtonContainer->addWidget(backButton);


    buttonContainer->addLayout(loadingButtonContainer);

    gameMainLayout->addLayout(buttonContainer);
    gameContent->setContentsMargins(46,46,46,46);

    centerContainer->setStyleSheet("color:#242424;font-size:24px");
    centerContainer->setLayout(gameContent);

    //backContainer->setAlignment(Qt::AlignTop);
    //startContent->addLayout(backContainer);

    gameContent->addLayout(gameMainLayout);

    mainHLayout->addWidget(centerContainer);
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);

    this->setLayout(mainVLayout);
}


GameFragment::~GameFragment() {
    //delete backButton;
}

/*void GameFragment::onBackPressed() {
    back();
}*/


void GameFragment::update(const QString state) {
}

#include "moc_gamefragment.cpp"
