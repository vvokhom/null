//
// Created by vladimir on 21.05.22.
//

#include "game.h"

#include <cstdlib>
#include <ctime>

void Game::initialiseMap(json GameState) { //todo: парсить карту в отдельном классе
  map = (Tile*)malloc(sizeof(Tile) * 40);
  for(int i = 0; i < 40; ++i) {
    map[i] = Tile(GameState["Map"][i]["Type"], GameState["Map"][i]["Price"], GameState["Map"][i]["StreetId"], GameState["Map"][i]["OwnerId"]);
  }
}
Game::Game(json GameState) {
  // устанвить сид игры:
  srand(time(nullptr));

  playersNum = GameState["PlayersNumber"];
  for(int i = 0; i < playersNum; ++i) {
    std::string login = GameState["Players"][i];
    players[i] = Player(login, i, GameState[login]["Position"], GameState[login]["Funds"], GameState[login]["InPrison"], GameState[login]["Alive"]);
  }

  initialiseMap(GameState);
}
int Game::startGame() {
  return turn(0);
}
int Game::turn(int activeID) {
  Player* activePlayer = &(players[activeID]);
  if (activePlayer && activePlayer->isAlive()) {
    if (activePlayer->isInPrison()) {
      prisonTurn(activeID);
    } else {
      standardTurn(activeID);
    }
  }
  if (checkEndGame()) {
    endGame();
    return 0;
  }else return turn((activeID + 1)%playersNum);


}

bool Game::checkEndGame() {
  int livingPlayers = 0;
  for (int i = 0; i < playersNum; i++) {
    if (players[i].isAlive()) livingPlayers++;
  }
  if (livingPlayers <= 1) {
    return true;
  }
  return false;
}

void Game::prisonTurn(int activeID) {

}

void Game::standardTurn(int activeID) {
  Player* activePlayer = &(players[activeID]);

  int doubles = 0;
  int roll0 = rand() % 6 + 1;
  int roll1 = rand() % 6 + 1;
  int result = roll0 + roll1;
  while(roll0 == roll1) {
    if (doubles < 2) {
      doubles++;
      roll0 = rand() % 6 + 1;
      roll1 = rand() % 6 + 1;
      result += roll0 + roll1;
    } else {
      imprisonPlayer(activeID);
      //отправить инфу о броске
      return;
    }

  }
  activePlayer->move(result);
  resolveTile(activeID);
}

void Game::imprisonPlayer(int activeID){
  Player* activePlayer = &(players[activeID]);
  activePlayer->imprison();
}

void Game::endGame(){

}

void Game::resolveTile(int activeID){
  Player* activePlayer = &(players[activeID]);
  Tile* tile = &(map[activePlayer->getPosition()]);
  switch (tile->getType()) {
    case TileType::tax:
      activePlayer->pay(100);
      break;
  }

}

json Game::ToJson() {
  json GameState;

  GameState["PlayersNumber"] = playersNum;
  GameState["Active"] = 0; // Нужно Id активного игрока

  GameState["Players"] = {};
  for(int i = 0; i < playersNum; ++i) {
    GameState["Players"][i] = players[i].getName();
    GameState[players[i].getName()] = {{"Funds", players[i].getFunds()}, {"Position", players[i].getPosition()}, {"InPrison", players[i].isInPrison()}, {"Alive", players[i].isAlive()}};
  }

  for(int i = 0; i < 40; ++i) {
    GameState["Map"][i] = {{"Type", map[i].getType()}, {"Price", map[i].getPrice()}, {"StreetId", map[i].getStreetID()}, {"OwnerId", map[i].getOwnerID()}};
  }

  return GameState;
}