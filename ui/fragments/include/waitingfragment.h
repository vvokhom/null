#ifndef WAITINGFRAGMENT_H
#define WAITINGFRAGMENT_H

#include <client.hpp>

#include "abstractfragment.h"


#include <QPushButton>



class WaitingFragment: public AbstractFragment {
    Q_OBJECT
public:
    WaitingFragment();
    ~WaitingFragment();

public slots:
    void onBackPressed();
    void onReadyPressed();
    //void onDisconnectPressed();

private:
    QPushButton *backButton;
    QPushButton *readyButton;
    //QLabel *Players;
    //QPushButton *DisconnectButton;
};

#endif // WAITINGFRAGMENT_H
