#ifndef NPCCAR_H
#define NPCCAR_H

#include "Car.h"

class Board;

class NPCCar : public Car {
public:
    int movementType;
    int stuckFrames; // counter for how long the car has been stuck
    int lastDirectionChange; // track when direction last changed
    
    NPCCar(int _x, int _y);
    
    void updateMovement(Board* board);
    void moveOneBlock(int dir, Board* board) ; 
    bool isValidPosition(int checkX, int checkY, Board* board) ;
    void findNewDirection(Board* board) ;
    bool attemptEscape(Board* board);
    void resetCar(); 
    void draw() override;
    string getType() const;
};

#endif
