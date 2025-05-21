#include "Score.h"
#include <string>
#include <cstring>
#include"constants.h"
using std::string;

Score::Score() : score(0) {
	setName("");
}
Score::Score(string name, int s) : score(s) {
	setName(name);
}

int Score::getScore() {
	return score;
}
string Score::getName() {
	return playerName;
}
void Score::setScore(int newScore) {
	score = newScore;
}
void Score::setName(string newName) {
	strncpy(playerName, newName.c_str(), NAME_LENGTH - 1);
	playerName[NAME_LENGTH - 1] = '\0';
}

