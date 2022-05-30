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
#include <QPainter>



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
    QPixmap *map;
    QVector<QLabel*> playerLabels;
    QLabel *funds;
    QTimer* tickTimer;
    int myID;
    int tickCounter;
    QPainter* painter;
  void update(json state);
  void takeTurn(json state);
  void redraw(Game game);

};

#endif // GAMEFRAGMENT_H
