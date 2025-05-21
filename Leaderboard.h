#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "Score.h"
#include <string>  
using std::string;


class Leaderboard {
public:
    string filename;  
    static const int MAX_ENTRIES = 10;        
    Score highScores[MAX_ENTRIES];  
   
    Leaderboard();

    void loadHighScores() ;
    void saveHighScores();
    bool addScore(string name, int score);
    void displayLeaderboard() ;
    bool isHighScore(int score) ;
};

#endif
