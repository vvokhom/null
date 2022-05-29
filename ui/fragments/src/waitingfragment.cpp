#include "waitingfragment.h"
#include "screensfactory.h"


using namespace screens;

WaitingFragment::WaitingFragment() {
    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QFrame *centerContainer = new QFrame;

    QVBoxLayout *startMainLayout = new QVBoxLayout;
    QHBoxLayout *startContent = new QHBoxLayout;

    QVBoxLayout *backContainer = new QVBoxLayout;

    QVBoxLayout *buttonContainer = new QVBoxLayout;
    QHBoxLayout *loadingButtonContainer = new QHBoxLayout;


retryTimer = new QTimer;
retryTimer->setInterval(100);
  connect(retryTimer, &QTimer::timeout, this, &WaitingFragment::onGameStartCheck);
    backButton = new QPushButton("Back");
    backButton->setStyleSheet("color:#242424;font-size:24px");
    connect(backButton, &QPushButton::clicked, this, &WaitingFragment::onBackPressed);

    readyButton = new QPushButton("Ready");
    readyButton->setStyleSheet("color:#242424;font-size:24px");
    connect(readyButton, &QPushButton::clicked, this, &WaitingFragment::onReadyPressed);

  forceStartButton = new QPushButton("Force start");
  forceStartButton->setStyleSheet("color:#242424;font-size:24px");
  connect(forceStartButton, &QPushButton::clicked, this, &WaitingFragment::onForceStartPressed);

    buttonContainer->addWidget(backButton);
    loadingButtonContainer->addWidget(backButton);

    buttonContainer->addWidget(readyButton);
    loadingButtonContainer->addWidget(readyButton);

  buttonContainer->addWidget(forceStartButton);
  loadingButtonContainer->addWidget(forceStartButton);

//    buttonContainer->addWidget(continueButton);
//    loadingButtonContainer->addWidget(continueButton);

    buttonContainer->addLayout(loadingButtonContainer);

    startMainLayout->addLayout(buttonContainer);
    startContent->setContentsMargins(46,46,46,46);

    centerContainer->setStyleSheet("color:#242424;font-size:24px");
    centerContainer->setLayout(startContent);

    backContainer->setAlignment(Qt::AlignTop);
    startContent->addLayout(backContainer);

    startContent->addLayout(startMainLayout);

    mainHLayout->addWidget(centerContainer);
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);


    this->setLayout(mainVLayout);
}


WaitingFragment::~WaitingFragment() {
    delete backButton;
    delete readyButton;

}

void WaitingFragment::onBackPressed() {
    back();
}

void WaitingFragment::onForceStartPressed() {
  retryTimer->stop();
  navigateTo(GAME_TAG);
}


void WaitingFragment::onReadyPressed() {
  Client* client = getClient();
  client->GetInLine();

  readyButton->setText("Wait");
  readyButton->setEnabled(false);



  retryTimer->start();




}

void WaitingFragment::onGameStartCheck() {
  Client* client = getClient();

  if (client->IsPlay()) {
    retryTimer->stop();
    navigateTo(GAME_TAG);
  }
}

//void WaitingFragment::onContinuePressed() {
//    navigateTo(GAME_TAG);
//}

#include "moc_waitingfragment.cpp"
