//
// Created by vladimir on 29.05.22.
//

#ifndef NULL_UI_FRAGMENTS_INCLUDE_GAMEMAP_H_
#define NULL_UI_FRAGMENTS_INCLUDE_GAMEMAP_H_

#include <QLabel>

#include "game.h"

class GameMap: public QLabel {
  Game* gameState = nullptr;

 public:
  using QLabel::QLabel;
  void setState(Game* newState);
 protected:
  void paintEvent(QPaintEvent *event) override;
};

#endif //NULL_UI_FRAGMENTS_INCLUDE_GAMEMAP_H_
