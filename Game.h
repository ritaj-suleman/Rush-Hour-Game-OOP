#ifndef GAME_H
#define GAME_H

#include <string>  
using std::string;

class Player;
class Car;

class Game {
public:
    int startTime;
    int currentTime;      
    bool isGameOver;  
    int gameMode; // 0 for taxi, 1 for delivery
    int gameState;  // 0 for menu, 1 for playing, 2 for paused, 3 for game over, 4 for leader board
    int timeLimit;       
    bool scoreAddedToLeaderboard; 
    
    Game();
    
    void startGame() ;
    void endGame() ;
    void pauseGame() ;
    void resumeGame() ;
    void checkScore(Player *player) ;
    void checkFuel(Player* player) ;
    void switchGameMode() ;
    void checkWinConditions(Player *player) ;
    void checkTimeLimit() ;
};

#endif
