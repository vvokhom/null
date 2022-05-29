#include "gamefragment.h"
#include "screensfactory.h"

//#include "../../logic/game.h"


#include <QDebug>
#include <QMessageBox>
#include <string>

using namespace screens;

bool Game::response(int playerID/* std::string*/) {
  QMessageBox message;
  message.setText("Yes?");
  message.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  message.setDefaultButton(QMessageBox::Yes);
  if(message.exec() == QMessageBox::Yes) return true;
  return false;
}



GameFragment::GameFragment():tickCounter(0) {
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


    tickTimer = new QTimer;
    tickTimer->setInterval(100);
  connect(tickTimer, &QTimer::timeout, this, &GameFragment::onTick);
  tickTimer->start();


  mapContainer = new QLabel("map");
    map = new QPixmap(":/map.jpg");
    mapContainer->setPixmap(map->scaled(700, 700));//centerContainer->size()));

    painter = new QPainter(map);

  painter->setBrush(QBrush(Qt::green));
  painter->setPen(QPen(Qt::blue));
  painter->drawRect(tickCounter, tickCounter, 500, 500);


    funds = new QLabel(QString("Your funds: 0" ));
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


void GameFragment::onTick() {
  Client* client = getClient();
  //todo:
  std::string msg = "Ticks: " + std::to_string(tickCounter);
  funds->setText(QString::fromStdString(msg));
  painter->setBrush(QBrush(Qt::green));
  painter->setPen(QPen(Qt::blue));
  painter->drawRect(tickCounter, tickCounter, 50, 50);

  tickCounter++;

}

void GameFragment::redraw(Game game) {

}

#include "moc_gamefragment.cpp"
