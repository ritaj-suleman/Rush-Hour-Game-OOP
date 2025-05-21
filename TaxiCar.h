#ifndef TAXICAR_H
#define TAXICAR_H

#include "Car.h"
#include <string>  
using std::string;

class Player;
class Passenger;
class GameObject;

class TaxiCar : public Car {
private: 
    Player* player;
    int lastCollisionX = -1;
    int lastCollisionY = -1;
public:
    Passenger* currentPassenger= nullptr;;
    bool hasPassenger;

    TaxiCar(Player *p = nullptr);
    TaxiCar(int _x, int _y, Player* p);
    
    bool pickupPassenger(Passenger* p);
    bool dropPassenger();
    void draw() override;
    void handleCollision(GameObject* obj) override;
    void resetCar() ;
    void move(int dir);
    string getType() const;
    ~TaxiCar();
};

#endif
