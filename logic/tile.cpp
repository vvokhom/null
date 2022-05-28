//
// Created by vladimir on 21.05.22.
//

#include "tile.h"
Tile::Tile(TileType type, int price, int streetID, int ownerID): ownerID(ownerID), price(price), streetID(streetID), type(type) {

}

TileType Tile::getType() {
  return  type;

}

int Tile::getOwnerID() {
  return ownerID;

}

int Tile::getPrice() {
  return price;

}

int Tile::getStreetID() {
  return streetID;
}