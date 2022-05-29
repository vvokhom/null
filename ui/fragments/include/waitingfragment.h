#ifndef WAITINGFRAGMENT_H
#define WAITINGFRAGMENT_H

#include <client.hpp>

#include "abstractfragment.h"


#include <QPushButton>
#include <QTimer>



class WaitingFragment: public AbstractFragment {
    Q_OBJECT
public:
    WaitingFragment();
    ~WaitingFragment();

public slots:
    void onBackPressed();
    void onReadyPressed();
    //void onDisconnectPressed();
    void onGameStartCheck();
    void onForceStartPressed();

 private:
    QPushButton *backButton;
    QPushButton *readyButton;
  QPushButton *forceStartButton;
    //QLabel *Players;
    //QPushButton *DisconnectButton;
    QTimer* retryTimer;



};

#endif // WAITINGFRAGMENT_H
