//
// Created by vladimir on 21.05.22.
//

#include "street.h"

#include "cstring"

Street::Street(int regionID, int price, int housePrice, const int rentArr[7]): regionID(regionID), price(price), housePrice(housePrice)  {
  //this->rent = {rent[0], rent[1], rent[2], rent[3], rent[4], rent[5], rent[6]};
  memcpy( rent,rentArr, sizeof(int)*7);
}

int Street::getRent(){
  return  rent[houses];
}
int Street::getPrice(){
  return  price;
}
int Street::getRegionID(){
  return  regionID;
}
int Street::getHouses(){
  return  houses;
}