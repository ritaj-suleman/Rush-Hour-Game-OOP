#ifndef FUELSTATION_H
#define FUELSTATION_H

class Car;
class Player;
class Game;

#include "GameObject.h"

class FuelStation : public GameObject {
public:
    float fuelPrice;
    
    FuelStation();
    FuelStation(int _x, int _y);
    
    bool refuelCar(Car* car, Player* player, float amount);  
    float calculateCost(float amount);
    void draw();
    string getType() const;
};

#endif
