//
// Created by vladimir on 15.04.22.
//

#ifndef NULL_GAMEFRAGMENT_H
#define NULL_GAMEFRAGMENT_H

#include "abstractfragment.h"
#include "screensfactory.h"

#include <QPushButton>
#include <QLabel>

class GameFragment: public AbstractFragment {
    Q_OBJECT
public:
    GameFragment();
    ~GameFragment();

    void startPlaying();
    void takeTurn();
    void exitGame();

public slots:
    void onMyTurn();
    void walk(int ID, int distance);
    void tileEffect(int ID);
    void update();
    void updateMoney();
    void updateMoney(int ID);
    void updateHouses();
    void onPlayerExit(int playerID)
    void endGame(int winnerID);

    void onRollPressed();
    void onExit();


private:
    std::vector<Player> vector;
    QBoxLayout *layout;
    QPixmap *map;
    std::vector<QPixmap> houses;
    std::vector<QPixmap> dice;
    QBoxLayout *diceLayout;
    int activePlayerID;
    int myPlayerID;
    QLabel *effectLabel;
    QBoxLayout *buttons;
    QPushButton *roll;
    AuctionWindow *auction;




};

#endif //NULL_GAMEFRAGMENT_H
