#ifndef SCORE_H
#define SCORE_H

#include<string>
using std::string;

class Score {
public:
    static const int NAME_LENGTH = 32; 
    char playerName[NAME_LENGTH]; //char array for binary
    int score;

    Score();
    Score(string name, int s);

    int getScore();
    string getName();
    void setScore(int newScore);
    void setName(string newName);
};

#endif
