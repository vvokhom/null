//
// Created by vladimir on 21.05.22.
//

#ifndef LOGIC__GAME_H_
#define LOGIC__GAME_H_

#include<vector>
#include"player.h"
#include "tile.h"
#include "street.h"

class Game {
 public:
  Game();
  ~Game();
  int startGame(); //  Возвращает код исполнения

 private:
  int turn(int activeID);
  bool checkEndGame();
  void prisonTurn(int activeID);
  void standardTurn(int activeID);
  void imprisonPlayer(int activeID);
  void resolveTile(int activeID);
  void endGame();


  int playersNum;
  std::vector<Player> players;
  Tile* map;
  int mapSize;
  Street* streets;
  int turnCount;
  bool response(int playerID);
  void initialiseMap();



};

#endif //LOGIC__GAME_H_
