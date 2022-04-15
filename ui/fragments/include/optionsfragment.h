//
// Created by vladimir on 15.04.22.
//

#ifndef NULL_OPTIONSFRAGMENT_H
#define NULL_OPTIONSFRAGMENT_H

#include "abstractfragment.h"
#include "screensfactory.h"
#include <QPushButton>

class OptionsFragment: public AbstractFragment {
    Q_OBJECT
public:
    OptionsFragment();
    ~OptionsFragment();

public slots:
    void onBackPressed();

private:
    QPushButton *backButton;
};

#endif //NULL_OPTIONSFRAGMENT_H
