#ifndef HUD_H
#define HUD_H

class Game;
class Player;
class Car;

class HUD {
public:
    Game* game;  
    Player* player; 

HUD(Game* g, Player* p) ;
    
void draw() ;
void showScore(int x, int y);
void showMoney(int x, int y);
void showFuel(int x, int y);
void showGameMode(int x, int y);
void showTime(int x, int y);
void showGameOver();
};

#endif
