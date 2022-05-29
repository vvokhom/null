//
// Created by vladimir on 21.05.22.
//

#ifndef LOGIC__PLAYER_H_
#define LOGIC__PLAYER_H_

#include <string>

class Player {
 public:
  Player(std::string name, int id_, int position_, int funds_, bool inPrison_, bool alive_);
  ~Player();
  int getId();
  std::string getName();
  bool pay(int price);
  void earn (int earning);
  int getPosition();
  int getFunds();
  void moveTo(int position);
  void move(int distance);
  bool isAlive();
  void imprison();
  bool isInPrison();
  void free();

 private:
  int id;
  std::string name;
  int position;
  int funds;
  bool inPrison;
  bool alive;
};

#endif //LOGIC__PLAYER_H_
