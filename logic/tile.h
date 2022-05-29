//
// Created by vladimir on 21.05.22.
//

#ifndef LOGIC__TILE_H_
#define LOGIC__TILE_H_

enum TileType {
  start,
  street,
  tax,
  rail,
  hydro,
  electro,
  prison,
  empty,
};

class Tile {
 public:
  Tile(TileType type, int price, int streetID, int ownerID);
  ~Tile();
  TileType getType();
  int getStreetID();
  int getOwnerID();
  int getPrice();
  void setOwnerID(int id);
 private:
  TileType type;
  int streetID;
  int price;

  int ownerID;
};

#endif //LOGIC__TILE_H_
