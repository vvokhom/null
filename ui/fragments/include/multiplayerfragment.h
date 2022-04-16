//
// Created by vladimir on 15.04.22.
//

#ifndef NULL_MULTIPLAYERFRAGMENT_H
#define NULL_MULTIPLAYERFRAGMENT_H

#include "abstractfragment.h"


#include <QPushButton>

class WaitingFragment: public AbstractFragment {
    Q_OBJECT
public:
    WaitingFragment();
    ~WaitingFragment();
    void refresh();

public slots:
    void onBackPressed();
    void onConnectPressed(int roomID);
    void onRefreshPressed();

private:
    QPushButton *backButton;
    QPushButton *continueButton;
    QPushButton *refreshButton;
    QVBoxLayout *list;
    QVector<QGroupBox> roomLis;

};

#endif //NULL_MULTIPLAYERFRAGMENT_H
