//
// Created by vladimir on 29.05.22.
//
#include "gamemap.h"
#include <QPainter>


void GameMap::setState(Game* newState) {
  gameState = newState ;
}

void GameMap::paintEvent(QPaintEvent* event) {
  QLabel::paintEvent(event);
  /*if (gameState == nullptr) {
    return;
  }*/
  QPainter painter(this);
  painter.setBrush(QBrush(Qt::green));
  painter.setPen(QPen(Qt::blue));
  painter.drawRect(0, 0, 500, 500);

}

#include "moc_gamemap.cpp"