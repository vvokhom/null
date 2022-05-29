//
// Created by vladimir on 21.05.22.
//

#include "player.h"

Player::Player(std::string name, int id):name(name), id(id), position(0), funds(1500), inPrison(false), alive(true) {

}

int Player::getId() {
  return id;

}
std::string Player::getName() {
  return name;
}

int Player::getFunds() {
  return funds;
}
int Player::getPosition() {
  return position;

}
bool Player::pay(int price) {
  if (funds < price){
    alive = false;
    return false;
  }
  funds -= price;
  return true;
}

void Player::earn(int earning) {
  funds += earning;
}

void Player::moveTo(int newPosition) {
  if (newPosition < 40) {
    position = newPosition;
  }
}
void Player::move(int distance) {
  int laps = (position + distance)/40;
  position = (position + distance) % 40;
  earn(100 * laps);

}

bool Player::isAlive() {
  return alive;
}
void Player::imprison(){
  inPrison = true;
  moveTo(10);
}
bool Player::isInPrison() {
  return inPrison;
}
void Player::free(){
  inPrison = true;
}
