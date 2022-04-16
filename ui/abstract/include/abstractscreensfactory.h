//
// Created by vladimir on 15.04.22.
//

#ifndef NULL_ABSTRACTSCREENSFACTORY_H
#define NULL_ABSTRACTSCREENSFACTORY_H

#include <QString>

namespace screens {
    enum class Tag{
        kOptions,
        kGame,
        kMain,
        kWaiting,
        kCreating
    };
}

class AbstractScreensFactory {
public:
    AbstractScreensFactory();
    virtual ~AbstractScreensFactory();

    virtual AbstractFragment* create(QString tag) = 0;
    virtual QString createStart() = 0;

#endif //NULL_ABSTRACTSCREENSFACTORY_H
