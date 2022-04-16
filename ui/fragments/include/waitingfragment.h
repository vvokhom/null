//
// Created by vladimir on 15.04.22.
//

#ifndef NULL_WAITINGFRAGMENT_H
#define NULL_WAITINGFRAGMENT_H

#include "abstractfragment.h"


#include <QPushButton>
#include <QMovie>

class WaitingFragment: public AbstractFragment {
    Q_OBJECT
public:
    WaitingFragment();
    ~WaitingFragment();

    void disconnect();



public slots:
    void onBackPressed();
    void playerConnects();
    void startGame();

private:
    QGroupBox *layout;
    QLabel *roomName;
    QLabel *players;
    QPushButton *backButton;
    QMovie waitingMovie;


};

#endif //NULL_WAITINGFRAGMENT_H
