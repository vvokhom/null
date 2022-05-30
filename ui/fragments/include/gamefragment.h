#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

#include "abstractfragment.h"
#include "screensfactory.h"

#include "game.h"
#include "gamemap.h"

#include <QPushButton>
#include <QLabel>
#include <QPixmap>

#include  <QTimer>



class GameFragment: public AbstractFragment {
    Q_OBJECT
public:
    GameFragment();
    ~GameFragment();


public slots:

  void onTick();

private:
    QPushButton* makeTurn;
    GameMap *mapContainer;
    Game* gameState;
    QPixmap *map;
    QVector<QLabel*> playerLabels;
    QLabel *funds;
    QTimer* tickTimer;
    int myID;
    int tickCounter;

};

#endif // GAMEFRAGMENT_H
