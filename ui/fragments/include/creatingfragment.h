//
// Created by vladimir on 15.04.22.
//

#ifndef NULL_CREATINGFRAGMENT_H
#define NULL_CREATINGFRAGMENT_H

#include "abstractfragment.h"
#include "screensfactory.h"

#include <QPushButton>
#include <QLabel>


class CreatingFragment: public AbstractFragment {
    Q_OBJECT
public:
    CreatingFragment();
    ~CreatingFragment();

    void createGame(int playerMax, QString roomName)

public slots:
    void onBackPressed();
    void onCreatePressed();

private:
    QGroupBox *layout;
    QLineEdit *roomName;
    QLineEdit *playerMax;
    QPushButton *backButton;
    QLabel *roomID;
    QPushButton *createButton

};

#endif //NULL_CREATINGFRAGMENT_H
