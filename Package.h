#ifndef PACKAGE_H
#define PACKAGE_H

class Board;

#include "GameObject.h"  

class Package : public GameObject {
public:
    int pickupX, pickupY;
    int destinationX, destinationY;
    float deliveryFee;
    bool isPickedUp;
    bool readyForDeletion = false; 

    Package();
    Package(int _x, int _y, int _destX, int _destY);

    void generateDestination(Board* board);  
    void setPickedUp(bool status);
    float getDeliveryFee();
    void draw() override;
    void highlightDestination();
    string getType() const;
    ~Package();
    
};

#endif 
