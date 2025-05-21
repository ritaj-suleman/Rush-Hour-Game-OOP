#include "Leaderboard.h"
#include "constants.h"
#include "util.h"
#include "Score.h"
#include <fstream>
#include <string>  
#include <iostream>
using namespace std;

Leaderboard::Leaderboard() : filename("highscores.dat") {
	loadHighScores();
}

void Leaderboard::loadHighScores() {
	ifstream file(filename, ios::binary);
	if (file.is_open()) {
		file.read(reinterpret_cast<char*>(highScores), sizeof(highScores));
		file.close();
	} else {
		//  default scores
		for (int i = 0; i < MAX_ENTRIES; i++) {
			highScores[i] = Score("Player", 0);
		}
	}
}

void Leaderboard::saveHighScores() {
	ofstream file(filename, ios::binary);
	if (file.is_open()) {
		file.write(reinterpret_cast<const char*>(highScores),sizeof(highScores));
		file.close();
	} else {
		cout << "failed" << endl;
	}
}

bool Leaderboard::addScore(string name, int score) {
	if (!isHighScore(score))
		return false;

	int insertIndex = MAX_ENTRIES - 1;
	while (insertIndex > 0 && score > highScores[insertIndex - 1].getScore()) {
		insertIndex--;
	}
	
	if (insertIndex < MAX_ENTRIES - 1) {
		for (int i = MAX_ENTRIES - 1; i > insertIndex; i--) {
			highScores[i] = highScores[i - 1];
		}
	}
	
	highScores[insertIndex] = Score(name, score);
	saveHighScores();
	return true;
}

void Leaderboard::displayLeaderboard() {
	// background
	DrawRectangle(GRID_SIZE * CELL_SIZE / 2 - 150, GRID_SIZE * CELL_SIZE / 2 - 200, 300, 400, MENU_BG_COLOR);

	// title
	DrawString(GRID_SIZE * CELL_SIZE / 2 - 80, GRID_SIZE * CELL_SIZE / 2 - 150, "HIGH SCORES", MENU_TEXT_COLOR);

	//  scores
	for (int i = 0; i < MAX_ENTRIES; i++) {
		string entry = to_string(i + 1) + ". " + highScores[i].getName() + " - " + to_string(highScores[i].getScore());
		DrawString(GRID_SIZE * CELL_SIZE / 2 - 140, GRID_SIZE * CELL_SIZE / 2 - 100 + i * 30, entry, HUD_TEXT_COLOR);
	}
}

bool Leaderboard::isHighScore(int score) {
	return score > highScores[MAX_ENTRIES - 1].getScore();
}

