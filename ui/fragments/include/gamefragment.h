#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

#include "abstractfragment.h"
#include "screensfactory.h"

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
    QVector<QImage*> players;
    QLabel *funds; 
};

#endif // GAMEFRAGMENT_H
