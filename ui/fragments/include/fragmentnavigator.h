   #ifndef FRAGMENTNAVIGATOR_H
#define FRAGMENTNAVIGATOR_H

#include "abstractfragment.h"
#include "abstractscreensfactory.h"

#include <QStackedWidget>
#include <list>

class FragmentNavigator: public QObject {
    Q_OBJECT

public:
    FragmentNavigator() = delete;
    FragmentNavigator(QStackedWidget *container, AbstractScreensFactory *screensFactory, Client* client);
    ~FragmentNavigator();
    AbstractFragment* getStartScreen();


public slots:
    void navigateTo(QString tag);

    void back();

    void newRootScreen(QString tag);

    AbstractFragment* Front();

  Client* getClient();

private:
    QStackedWidget *currentContainer;

    AbstractScreensFactory *screensFactory;
    std::list<AbstractFragment*> stack;

    AbstractFragment* createAndConnect(QString tag);

    Client* client;

    void connectFragment(AbstractFragment *fragment);
    void disconnectFragment(AbstractFragment *fragment);
};

#endif // FRAGMENTNAVIGATOR_H
