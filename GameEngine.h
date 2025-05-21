#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class Game;
class Board;
class InputManager;
class Menu;
class HUD;
class Leaderboard;
class Player;
class Car;

class GameEngine {
public:
    Game* game;            
    Board* board;          
    InputManager* inputManager; 
    Menu* menu;           
    HUD* hud;           
    Leaderboard* leaderboard; 
    Player* player;  

    GameEngine();

    void initialize();
    void render() ;
    void update() ;
    void cleanup() ;
    void switchGameState(int newState);
    InputManager* getInputManager() const ;
    Game* getGame() const;
    Menu* getMenu() const ;
    Board* getBoard() const ;
    HUD* getHUD() const;
    Leaderboard* getLeaderboard() ;
    Player* getPlayer() const;
};

#endif
