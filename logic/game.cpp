//
// Created by vladimir on 21.05.22.
//

#include "game.h"

#include <cstdlib>
#include <ctime>

int* ArrayFilling(int* array, int first, int second, int third, int fourth, int fifth, int sixth) {
  array[0] = first;
  array[1] = second;
  array[2] = third;
  array[3] = fourth;
  array[4] = fifth;
  array[5] = sixth;

  return array;
}

void Game::initialiseMap(json GameState) { //todo: парсить карту в отдельном классе
  map = (Tile*)malloc(sizeof(Tile) * 40);
  streets = (Street*)malloc(sizeof(Street) * 22);

  for(int i = 0; i < 40; ++i) {
    map[i] = Tile(GameState["Map"][i]["Type"], GameState["Map"][i]["Price"], GameState["Map"][i]["StreetId"], GameState["Map"][i]["OwnerId"]);
  }
  
  int* rent = (int*)malloc(sizeof(int)*6);
  rent = ArrayFilling(rent, 2, 10, 30, 90, 160, 250);
  streets[0] = Street(0, GameState["Map"][1]["Price"], 50, GameState["Map"][1]["HouseCount"], rent);

  rent = ArrayFilling(rent, 4, 20, 60, 180, 320, 450);
  streets[1] = Street(0, GameState["Map"][3]["Price"], 50, GameState["Map"][3]["HouseCount"], rent);

  rent = ArrayFilling(rent, 6, 30, 90, 270, 400, 550);
  streets[2] = Street(1, GameState["Map"][6]["Price"], 50, GameState["Map"][6]["HouseCount"], rent);
  streets[3] = Street(1, GameState["Map"][8]["Price"], 50, GameState["Map"][8]["HouseCount"], rent);

  rent = ArrayFilling(rent, 8, 40, 100, 300, 450, 600);
  streets[4] = Street(1, GameState["Map"][9]["Price"], 50, GameState["Map"][9]["HouseCount"], rent);

  rent = ArrayFilling(rent, 10, 50, 150, 450, 625, 750);
  streets[5] = Street(2, GameState["Map"][11]["Price"], 100, GameState["Map"][11]["HouseCount"], rent);
  streets[6] = Street(2, GameState["Map"][13]["Price"], 100, GameState["Map"][13]["HouseCount"], rent);

  rent = ArrayFilling(rent, 12, 60, 180, 500, 700, 900);
  streets[7] = Street(2, GameState["Map"][14]["Price"], 100, GameState["Map"][14]["HouseCount"], rent);

  rent = ArrayFilling(rent, 14, 70, 200, 550, 750, 950);
  streets[8] = Street(3, GameState["Map"][16]["Price"], 100, GameState["Map"][16]["HouseCount"], rent);
  streets[9] = Street(3, GameState["Map"][18]["Price"], 100, GameState["Map"][18]["HouseCount"], rent);

  rent = ArrayFilling(rent, 16, 80, 220, 600, 800, 1000);
  streets[10] = Street(3, GameState["Map"][19]["Price"], 100, GameState["Map"][19]["HouseCount"], rent);

  rent = ArrayFilling(rent, 18, 90, 250, 700, 875, 1050);
  streets[11] = Street(4, GameState["Map"][21]["Price"], 150, GameState["Map"][21]["HouseCount"], rent);
  streets[12] = Street(4, GameState["Map"][23]["Price"], 150, GameState["Map"][23]["HouseCount"], rent);

  rent = ArrayFilling(rent, 20, 100, 300, 750, 925, 1100);
  streets[13] = Street(4, GameState["Map"][24]["Price"], 150, GameState["Map"][24]["HouseCount"], rent);

  rent = ArrayFilling(rent, 22, 110, 330, 800, 975, 1150);
  streets[14] = Street(5, GameState["Map"][26]["Price"], 150, GameState["Map"][26]["HouseCount"], rent);
  streets[15] = Street(5, GameState["Map"][27]["Price"], 150, GameState["Map"][27]["HouseCount"], rent);

  rent = ArrayFilling(rent, 24, 120, 360, 850, 1025, 1200);
  streets[16] = Street(5, GameState["Map"][29]["Price"], 150, GameState["Map"][29]["HouseCount"], rent);

  rent = ArrayFilling(rent, 26, 130, 390, 900, 1100, 1275);
  streets[17] = Street(6, GameState["Map"][31]["Price"], 200, GameState["Map"][31]["HouseCount"], rent);
  streets[18] = Street(6, GameState["Map"][32]["Price"], 200, GameState["Map"][32]["HouseCount"], rent);

  rent = ArrayFilling(rent, 28, 150, 450, 1000, 1200, 1400);
  streets[19] = Street(6, GameState["Map"][34]["Price"], 200, GameState["Map"][34]["HouseCount"], rent);

  rent = ArrayFilling(rent, 35, 175, 500, 1100, 1300, 1500);
  streets[20] = Street(7, GameState["Map"][37]["Price"], 200, GameState["Map"][37]["HouseCount"], rent);

  rent = ArrayFilling(rent, 50, 200, 600, 1400, 1700, 2000);
  streets[21] = Street(7, GameState["Map"][39]["Price"], 200, GameState["Map"][39]["HouseCount"], rent);

}

Game::Game(const Game&) {
  
}
Game::Game(json GameState) {
  // устанвить сид игры:
  srand(time(nullptr));


  playersNum = GameState["PlayersNumber"];

  for(int i = 0; i < playersNum; ++i) {
    std::string login = GameState["Players"][i];
    players.push_back(Player(login, i, GameState[login]["Position"], GameState[login]["Funds"], GameState[login]["InPrison"], GameState[login]["Alive"]));
  }

  initialiseMap(GameState);
}
int Game::startGame() {
  return turn(0);
}

int Game::takeTurn() {
  return turn(activeID)
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
    case TileType::tax: {
      activePlayer->pay(activeTile->getPrice());
      break;
    }
    case TileType::rail: {
      if (activeTile->getOwnerID() < 0) {
        std::string message = "Would you like to buy this railway for ";
        message += activeTile->getPrice();
        message += "$ ?";

        if (response(activeID, message) && activePlayer->pay(activeTile->getPrice())) {
          activeTile->setOwnerID(activeID);
        }
      }
      if (activeTile->getOwnerID() != -1 && activeTile->getOwnerID() != activeID) {
        int railsInPossession = 0;
        int recieverID = activeTile->getOwnerID();
        for (int i = 0; i < mapSize; i++) {
          Tile tile  = map[i];

          if (tile.getType() == TileType::rail && tile.getOwnerID() == recieverID) {
            railsInPossession++;
          }
        }
        activePlayer->pay(50*railsInPossession);
      }
      break;
    }
    case TileType::start: {
      break;
    }
    case TileType::empty: {
      break;
    }
    case TileType::prison: {
      break;
    }
    case TileType::hydro ... TileType::electro: {
      if (activeTile->getOwnerID() < 0) {
        std::string message;
        if(activeTile->getType() == 4) {
          message = "Would you like to buy this hydro station for ";
        } else {
          message = "Would you like to buy this electro station for ";
        }
        message += activeTile->getPrice();
        message += "$ ?";

        if (response(activeID, message) && activePlayer->pay(activeTile->getPrice())) {
          activeTile->setOwnerID(activeID);
        }
      }

      if (activeTile->getOwnerID() != -1 && activeTile->getOwnerID() != activeID) {
        int roll0 = rand() % 6 + 1;
        int roll1 = rand() % 6 + 1;
        int resultPay = roll0 + roll1;
        if(map[12].getOwnerID() == map[28].getOwnerID()) {
          activePlayer->pay(10 * resultPay);
        } else {
          activePlayer->pay(4 * resultPay);
        }
      }
      break;
    }
    case TileType::street: {
      if (activeTile->getOwnerID() < 0) {
        std::string message = "Would you like to buy this street for ";
        message += activeTile->getPrice();
        message += "$ ?";

        if (response(activeID, message) && activePlayer->pay(activeTile->getPrice())) {
          activeTile->setOwnerID(activeID);
        }
      }

      if (activeTile->getOwnerID() != -1 && activeTile->getOwnerID() != activeID) {
        Street activeStreet = streets[activeTile->getStreetID()];
         activePlayer->pay(activeStreet.getRent());
      }
    
      break;
    }
  }

}

json Game::ToJson() {
  json GameState;

  GameState["PlayersNumber"] = playersNum;

  GameState["Players"] = {};
  for(int i = 0; i < playersNum; ++i) {
    GameState["Players"][i] = players[i].getName();
    GameState[players[i].getName()] = {{"Funds", players[i].getFunds()}, {"Position", players[i].getPosition()}, {"InPrison", players[i].isInPrison()}, {"Alive", players[i].isAlive()}};
  }

  for(int i = 0; i < 40; ++i) {
    if (map[i].getType() == TileType::street) {
      GameState["Map"][i] = {{"Type", map[i].getType()}, {"Price", map[i].getPrice()}, {"StreetId", map[i].getStreetID()}, {"OwnerId", map[i].getOwnerID()}, {"HouseCount", streets[map[i].getStreetID()].getHouses()}};
    } else {
      GameState["Map"][i] = {{"Type", map[i].getType()}, {"Price", map[i].getPrice()}, {"StreetId", map[i].getStreetID()}, {"OwnerId", map[i].getOwnerID()}};
    }
  }

  return GameState;
}

Game::~Game() {
  delete map;
  delete streets;
}