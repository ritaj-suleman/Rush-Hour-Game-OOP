#ifndef PASSENGER_H
#define PASSENGER_H

class Board;

#include "GameObject.h"  

class Passenger : public GameObject {
public:
    int destinationX=0, destinationY=0;  
    float fare;                      
    bool isPickedUp;         
    bool readyForDeletion = false; 
    
    Passenger();
    Passenger(int _x, int _y, int _destX, int _destY) ;
  
    void generateDestination(Board* board) ;
    void setPickedUp(bool status);
    float getFare();
    void draw();
    void highlightDestination();
    string getType() const ;
    
    ~Passenger();
};

#endif
