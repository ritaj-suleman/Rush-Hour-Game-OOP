#include "GameEngine.h"
#include "constants.h"
#include <GL/glut.h>  

#include "Game.h"         
#include "Board.h"
#include "InputManager.h"
#include "Menu.h"
#include "HUD.h"
#include "Leaderboard.h"
#include "Player.h"
#include "Car.h"
#include "util.h"
#include <iostream>
#include "sound.h"
using namespace std;

GameEngine::GameEngine() {
	initialize();
}

void GameEngine::initialize() {
	game = new Game();
	player = new Player();

	player->changeRole(game->gameMode);
	if (player->car) {
		player->car->x = 0;
		player->car->y = 0;
		player->car->isActive = true;
		player->car->isPlayerControlled = true;
	}

	board = new Board(this, cityGrid);
	inputManager = new InputManager(this);
	hud = new HUD(game, player);
	leaderboard = new Leaderboard();
	menu = new Menu(this);
}

void GameEngine::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (game->gameState) {
	case STATE_MENU:
		menu->draw();
		break;

	case STATE_PLAYING:
	case STATE_PAUSED:
		board->drawBoard();
		hud->draw();
		if (menu->isShowingRoleChange()) {
			menu->draw();
		} else if (game->gameState == STATE_PAUSED) {
			DrawRectangle(0, 0, GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE, HUD_BG_COLOR);
			DrawString(GRID_SIZE * CELL_SIZE / 2 - 50, GRID_SIZE * CELL_SIZE / 2, "PAUSED", colors[WHITE]);
		}
		break;

	case STATE_GAMEOVER:
		board->drawBoard();
		hud->showGameOver();
		playSound("gameover.wav");
		// add score to leader board once
		if (!game->scoreAddedToLeaderboard && leaderboard->isHighScore(player->score)) {
			leaderboard->addScore(player->name, player->score);
			game->scoreAddedToLeaderboard = true; 
		}
		break;

	case STATE_LEADERBOARD:  
		menu->draw();  // menu background
		leaderboard->displayLeaderboard();
		break;
	}
	glutSwapBuffers();
}

void GameEngine::update() {
	if (game->gameState != STATE_PLAYING)
		return;

	game->currentTime++;
	board->updateBoard();
	game->checkTimeLimit();
	game->checkWinConditions(player);
	game->checkScore(player);
	game->checkFuel(player);

	// increase difficulty when 2 jobs are done and reset 
	if (player->car->jobsCompleted == 2) {
		board->increaseDifficulty();
		player->car->jobsCompleted = 0;
	}
}

void GameEngine::cleanup() {
	delete game;
	delete board;
	delete inputManager;
	delete menu;
	delete hud;
	delete leaderboard;
}

void GameEngine::switchGameState(int newState) {
	game->gameState = newState;

	if (newState == STATE_PLAYING) {
		menu->isActive = false;
		if (!player) {
			player = new Player();
			hud = new HUD(game, player);
		}
		player->resetPlayer();
		board->generateBoard();
		game->scoreAddedToLeaderboard = false;
	}
}

InputManager* GameEngine::getInputManager() const {
	return inputManager;
}
Game* GameEngine::getGame() const {
	return game;
}
Menu* GameEngine::getMenu() const {
	return menu;
}
Board* GameEngine::getBoard() const {
	return board;
}
HUD* GameEngine::getHUD() const {
	return hud;
}
Leaderboard* GameEngine::getLeaderboard() {
	return leaderboard;
}
Player* GameEngine::getPlayer() const {
	return player;
}

