#ifndef STATION_H
#define STATION_H

class Player;
class Car;
class Game;
class Menu;

#include "GameObject.h"
#include "GameEngine.h"

class Station : public GameObject {
    GameEngine* gameEngine; 
public:
    bool isAvailable;
    
    Station();
    Station(int _x, int _y);
    Station(int _x, int _y, GameEngine* engine);
    void changePlayerRole(Player* player);  
    void draw();
    bool isPlayerNear(Player* player); 
    string getType() const ;
    void setGameEngine(GameEngine* engine); 
    
    virtual ~Station(){};
};

#endif
