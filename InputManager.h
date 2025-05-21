#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class GameEngine;
class Car;
class Game;
class Player;

class InputManager {
private:
    bool keyState[256];  //256 of the keyboard buttons
    GameEngine* gameEngine;        

public:
    InputManager(GameEngine* gameEng);

    void handleKeyPress(int key);
    void handleKeyRelease(int key);
    bool isKeyPressed(int key) ;
};

#endif
