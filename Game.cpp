#include "Game.h"
#include "Player.h"
#include "Car.h"
#include "util.h"
#include "constants.h"
#include <GL/glut.h> 

Game::Game() :
		startTime(0), 
		currentTime(0), 
		isGameOver(false), 
		gameMode(MODE_TAXI), 
		gameState(STATE_MENU), 
		timeLimit(180), 
		scoreAddedToLeaderboard(false) {}

void Game::startGame() {
	currentTime = 0;
	isGameOver = false;
	gameState = STATE_PLAYING;
	startTime = glutGet(GLUT_ELAPSED_TIME);
	cout << "Game started in state: " << gameState << endl;
}

void Game::endGame() {
	isGameOver = true;
	gameState = STATE_GAMEOVER;
}

void Game::pauseGame() {
	if (gameState == STATE_PLAYING)
		gameState = STATE_PAUSED;
}

void Game::resumeGame() {
	if (gameState == STATE_PAUSED)
		gameState = STATE_PLAYING;
}

void Game::checkScore(Player *player) {
	if (player->score < 0) {
		isGameOver = true;
		gameState = STATE_GAMEOVER;
	}
}

void Game::checkFuel(Player *player) {
	if (player->car->fuelLevel <= 0) {
		isGameOver = true;
		gameState = STATE_GAMEOVER;
	}
}

void Game::switchGameMode() {
	gameMode = (gameMode == MODE_TAXI) ? MODE_DELIVERY : MODE_TAXI;
}

void Game::checkWinConditions(Player *player) {
	if (player->score >= 100) {
		isGameOver = true;
		gameState = STATE_GAMEOVER;
	}
}

void Game::checkTimeLimit() {
	if (currentTime >= timeLimit) {
		isGameOver = true;
		gameState = STATE_GAMEOVER;
	}
}


