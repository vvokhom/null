//
// Created by vladimir on 15.04.22.
//

#ifndef NULL_MAINFRAGMENT_H
#define NULL_MAINFRAGMENT_H

#include "abstractfragment.h"
#include "screensfactory.h"

#include <QPushButton>
#include <QInputDialog>
#include <QPixmap       >

class MainFragment: public AbstractFragment {
    Q_OBJECT

public:
    MainFragment();
    ~MainFragment();
public slots:
    void onCreatePressed();
    void onPlayPressed();
    void onOptionsPressed();

private:
    QPushButton *createButton;
    QPushButton *playButton;
    QPushButton *optionsButton;
    QButtonGroup *layout;
    QPIxmap *logo;
};

#endif //NULL_MAINFRAGMENT_H
