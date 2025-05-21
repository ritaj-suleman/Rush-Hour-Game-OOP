#ifndef MENU_H
#define MENU_H

#include<string>
using std:: string;

class GameEngine;
class Game;
class Player;
class Car;
class Board;

class Menu {
public:
    int currentSelection;   
    int menuState;         
    bool isActive;         
   GameEngine* gameEngine;  
   int modeSelection; 
   bool showRoleChange = false;
   bool nameInputMode;
   string nameInput;
   bool leaderboardSelected = false;
   
    Menu() ;
   Menu(GameEngine* engine) ;
   
    void draw() ;
    void showStartMenu();
    void showModeSelectionMenu();
    void drawNameInputScreen();
    void handleInput(int key) ;
    void selectOption();
    void startGame();
    void showRoleChangeMenu(bool show);
    bool isShowingRoleChange() const;
    void drawRoleChangeMenu();
    void drawLeaderboardOption();
};

#endif
