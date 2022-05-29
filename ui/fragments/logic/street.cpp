//
// Created by vladimir on 21.05.22.
//

#include "street.h"

#include "cstring"

Street::Street(int regionID, int price, int housePrice, const  std::initializer_list<int> rentList): regionID(regionID), price(price), housePrice(housePrice), houses(0)  {
  memcpy( rent,rentList.begin(), sizeof(int)*6);
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