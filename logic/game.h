//
// Created by vladimir on 21.05.22.
//

#ifndef LOGIC__GAME_H_
#define LOGIC__GAME_H_

#include<vector>
#include <string>
#include"player.h"
#include "tile.h"
#include "street.h"
#include "json.hpp"

using json = nlohmann::json;

class Game {
 public:
  Game(json GameState);
  Game(const Game&);
  ~Game();
  int startGame(); //  Возвращает код исполнения

  json ToJson();

  void takeTurn();
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
  virtual bool response(int playerID, std::string message);
  void initialiseMap(json GameState);



};

#endif //LOGIC__GAME_H_
