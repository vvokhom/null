//
// Created by vladimir on 21.05.22.
//

#ifndef LOGIC__STREET_H_
#define LOGIC__STREET_H_

class Street { //Информация о владельце указана только в тайле. Не знаю насколько это правильно
 public:
  Street(int regionID, int price, int housePrice, int houseCount, const int rent[7]);
  ~Street();
  int getRent();
  int getPrice();
  int getRegionID();
  int getHouses();
  bool buyHouse(int playerMoney);
 private:
  int rent[6];
  int price;
  int housePrice;
  int houses;
  int regionID;

};

#endif //LOGIC__STREET_H_
