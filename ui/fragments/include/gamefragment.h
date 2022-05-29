#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

#include "abstractfragment.h"
#include "screensfactory.h"

//#include <client.hpp>

#include <QPushButton>
#include <QLabel>
#include <QPixmap>



class GameFragment: public AbstractFragment {
    Q_OBJECT
public:
    GameFragment();
    ~GameFragment();


public slots:

    void update(const QString state);


private:
QLabel *mapContainer;
    QPixmap *map;
    QVector<QLabel*> playerLabels;
    QLabel *funds; 
};

#endif // GAMEFRAGMENT_H
