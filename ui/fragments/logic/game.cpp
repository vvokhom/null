//
// Created by vladimir on 21.05.22.
//

#include "game.h"

#include <cstdlib>
#include <ctime>

void Game::initialiseMap() { //todo: парсить карту в отдельном классе (Отвратительно)


  map = (Tile*)malloc(sizeof(Tile) * 40);
  map[0] = Tile(start, 0, 0);
  map[1] = Tile(street, 60, 0);
  map[2] = Tile(blue, 0, 0);
  map[3] = Tile(street, 60, 1);
  map[4] = Tile(tax, 200, 0);
  map[5] = Tile(rail, 200, 0);
  map[6] = Tile(street, 100, 2);
  map[7] = Tile(orange, 0, 0);
  map[8] = Tile(street, 100, 3);
  map[9] = Tile(street, 120, 4);
  map[10] = Tile(prison, 0, 0);
  map[11] = Tile(street, 140, 5);
  map[12] = Tile(electro, 150, 0);
  map[13] = Tile(street, 140, 6);
  map[14] = Tile(street, 160, 7);
  map[15] = Tile(rail, 200, 0);
  map[16] = Tile(street, 180, 8);
  map[17] = Tile(blue, 0, 0);
  map[18] = Tile(street, 180, 9);
  map[19] = Tile(street, 200, 10);
  map[20] = Tile(empty, 0, 0);
  map[21] = Tile(street, 220, 11);
  map[22] = Tile(orange, 0, 0);
  map[23] = Tile(street, 220, 12);
  map[24] = Tile(street, 240, 13);
  map[25] = Tile(rail, 200, 0);
  map[26] = Tile(street, 260, 14);
  map[27] = Tile(street, 260, 15);
  map[28] = Tile(hydro, 150, 0);
  map[29] = Tile(street, 260, 16);
  map[30] = Tile(goToJail, 0, 0);
  map[31] = Tile(street, 300, 17);
  map[32] = Tile(street, 300, 18);
  map[33] = Tile(blue, 0, 0);
  map[34] = Tile(street, 320, 19);
  map[35] = Tile(rail, 200, 0);
  map[36] = Tile(orange, 0, 0);
  map[37] = Tile(street, 350, 20);
  map[38] = Tile(tax, 100, 0);
  map[39] = Tile(street, 400, 21);
}

void Game::initialiseStreets() { // todo:
  streets = (Street*)malloc(sizeof(Street) * 22);
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});
  streets[0] = Street(0, 60, 50, {2, 10, 30, 90, 160, 250});

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
  Tile* tile = &(map[activePlayer->getPosition()]);
  switch (tile->getType()) {
    case TileType::tax:
      activePlayer->pay(100);
      break;
  }

}