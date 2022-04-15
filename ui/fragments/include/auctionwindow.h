//
// Created by vladimir on 15.04.22.
//

#ifndef NULL_AUCTIONWINDOW_H
#define NULL_AUCTIONWINDOW_H

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    GameFragment *parentFragment;
    QBoxLayout *layout;
    QPushButton *raiseBet;
    int itemID;
    QPixmap *itemImage;
    QLabel *currentBet;
    QTimer *betTimer; //не зависит от логики
    QLabel *buyer;
    QLabel *timeLeft;



public:
    AuctionWindow();
    ~AuctionWindow();

    void raizeBet();
public slots:
    void onRaisePressed();
    endAuction(int buyerID);
    betRaised(int buyerID, int newBet);



};

#endif //NULL_AUCTIONWINDOW_H
