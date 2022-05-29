//
// Created by vladimir on 21.05.22.
//

#include "tile.h"
Tile::Tile(TileType type, int price, int streetID):ownerID(-1), price(price), streetID(streetID), type(type) {

}

Tile::~Tile()=default;

TileType Tile::getType() {
  return  type;

}

int Tile::getOwnerID() {
  return ownerID;

}

int Tile::setOwnerID(int id) {
  ownerID = id;

}

int Tile::getPrice() {
  return price;

}

int Tile::getStreetID() {
  return streetID;
}