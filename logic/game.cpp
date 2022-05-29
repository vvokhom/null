//
// Created by vladimir on 21.05.22.
//

#include "game.h"

#include <cstdlib>
#include <ctime>

void Game::initialiseMap() { //todo: парсить карту в отдельном классе


  map = (Tile*)malloc(sizeof(Tile) * 40);
  map[0] = Tile(start, 0, 0);
  map[0] = Tile(street, 0, 0);
  map[0] = Tile(start, 0, 0);
  map[0] = Tile(start, 0, 0);
  map[0] = Tile(start, 0, 0);
  map[0] = Tile(start, 0, 0);
  map[0] = Tile(start, 0, 0);
  map[0] = Tile(start, 0, 0);
  map[0] = Tile(start, 0, 0);
}
Game::Game() {
  // устанвить сид игры:
  srand(time(nullptr));
  initialiseMap();
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
  Tile* activeTile = &(map[activePlayer->getPosition()]);
  switch (activeTile->getType()) {
    case TileType::tax:
      activePlayer->pay(100);
      break;
      case TileType::rail:
      if (activeTile->getOwnerID() < 0 && response(activeID) && activePlayer->pay(activeTile->getPrice())) {
        activeTile->setOwnerID(activeID);
      } else if(activeTile->getOwnerID() != activeID) {
        int railsInPossession = 0;
        int recieverID = activeTile->getOwnerID();
        for (int i = 0; i < mapSize; i++) {
          Tile* tile  = map[i];

          if (tile->getType() = TileType::rail && tile->getOwnerID( = recieverID)) {
            railsInPossession++;
          }
          activePlayer->pay(50*railsInPossession);
        }
      }
      break;
  }

}