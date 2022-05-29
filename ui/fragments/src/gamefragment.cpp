#include "gamefragment.h"
#include "screensfactory.h"

//#include "../../logic/game.h"

#include "game.h"
#include "QDebug"

using namespace screens;

GameFragment::GameFragment() {
  Client* client = getClient();

    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QFrame *centerContainer = new QFrame;

    QVBoxLayout *gameMainLayout = new QVBoxLayout;
    QHBoxLayout *gameContent = new QHBoxLayout;
    QVBoxLayout *gameInfo = new QVBoxLayout;
  QVBoxLayout *playersStats = new QVBoxLayout;


    //QVBoxLayout *backContainer = new QVBoxLayout;

    QVBoxLayout *buttonContainer = new QVBoxLayout;
    QHBoxLayout *loadingButtonContainer = new QHBoxLayout;

    mapContainer = new QLabel("map");
    map = new QPixmap(":/map.jpg");
    mapContainer->setPixmap(map->scaled(700, 700));//centerContainer->size()));

    funds = new QLabel("Your funds: 1500 M");
    gameInfo->addWidget(funds);

    playerLabels.push_back(new QLabel("<font color=\"green\">Player 1</font>: 1500 M"));
  playerLabels.push_back(new QLabel("<font color=\"blue\">Player 2</font>: 1500 M"));
    for (QLabel* label : playerLabels) {
      playersStats->addWidget(label);
    }
    gameContent->addWidget(mapContainer);
  gameInfo->addLayout(playersStats);
  gameContent->addLayout(gameInfo);

    buttonContainer->addLayout(loadingButtonContainer);

    gameMainLayout->addLayout(buttonContainer);
    gameContent->setContentsMargins(46,46,46,46);

    centerContainer->setStyleSheet("color:#242424;font-size:24px");
    centerContainer->setLayout(gameContent);


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
  //Game* game = new Game();
}

#include "moc_gamefragment.cpp"
