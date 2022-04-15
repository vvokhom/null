//
// Created by vladimir on 15.04.22.
//

#ifndef NULL_SCREENSFACTORY_H
#define NULL_SCREENSFACTORY_H

#include "abstractscreensfactory.h"

#include "optionsfragment.h"
#include "gamefragment.h"
#include "mainfragment.h"
#include "waitingfragment.h"
#include "creatingfragment.h"


namespace screens {
    enum Tag{
         kOptions,
         kGame,
         kMain,
         kWaiting,
         kCreating
     };


}

class ScreensFactory : public AbstractScreensFactory {
public:
    ScreensFactory();
    ~ScreensFactory();

    AbstractFragment* create(screens::Tag tag) override;
    QString createStart() override;
};

#endif //NULL_SCREENSFACTORY_H
