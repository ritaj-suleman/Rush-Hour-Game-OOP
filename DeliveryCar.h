#ifndef DELIVERYCAR_H
#define DELIVERYCAR_H

#include "Car.h"
#include <string>  
using std::string;

class Player;
class Package;
class GameObject;

class DeliveryCar : public Car {
private:
Player* player;
    int lastCollisionX = -1;
    int lastCollisionY = -1;
public:
    Package* currentPackage;  
    bool hasPackage;        
    
    DeliveryCar(Player* p = nullptr); 
    DeliveryCar(int _x, int _y,Player *p) ;
    
    bool pickupPackage(Package* p) ;
    bool deliverPackage() ;
    void draw() override;
    void handleCollision(GameObject* obj) override;
    void resetCar();
    void move(int dir) ;
    string getType() const;
};

#endif
