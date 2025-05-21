#ifndef PLAYER_H
#define PLAYER_H

#include <string>  
using std::string;

class Car;
class TaxiCar;
class DeliveryCar;

class Player {
public:
    string name;     
    int score;       
    float money;   
    int currentRole;    // 0 for taxi, 1 for delivery
    Car* car;  //current car
    
    Player();
    Player(string _name);
    
    void changeRole(int role) ;
    void updateScore(int points);
    void updateMoney(float amount);
    Car* getCar() ;
    float getMoney();
    void resetPlayer() ;
    void setName(const string& newName) ;
};

#endif
