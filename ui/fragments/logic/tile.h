//
// Created by vladimir on 21.05.22.
//

#ifndef LOGIC__TILE_H_
#define LOGIC__TILE_H_

enum TileType {
  start,
  street,
  blue,
  orange,
  tax,
  rail,
  hydro,
  electro,
  prison,
  goToJail,
  empty,
};

class Tile {
 public:
  Tile(TileType type, int price, int streetID);
  ~Tile();
  TileType getType();
  int getStreetID();
  int getOwnerID();
  int getPrice();
  void setOwnerID();
 private:
  TileType type;
  int streetID;
  int price;

  int ownerID;
};

#endif //LOGIC__TILE_H_
