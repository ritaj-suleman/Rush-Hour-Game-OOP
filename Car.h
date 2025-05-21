#ifndef CAR_H
#define CAR_H

#include "GameObject.h"
#include <string>
using std::string;

class Board;
class NPCCar;

class Car : public GameObject {
public:
    float speed;
    int color[3];
    int direction;
    float fuelLevel;
    float maxFuel;
    bool isPlayerControlled;
    int jobsCompleted;

    Car();
    Car(int _x, int _y, float _speed);
    
    virtual void move(int dir, Board* board);
    virtual void draw();
    void decreaseFuel();
    void resetCar();
    bool  isValidPosition(int checkGridX, int checkGridY, Board* board);
    virtual string getType() const;
    virtual void handleCollision(GameObject* obj);
    virtual~Car();
};

#endif
