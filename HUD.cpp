#include "HUD.h"
#include "Game.h"
#include "Car.h"
#include "Player.h"
#include "util.h"
#include "constants.h"
#include <iostream>
using namespace std;

HUD::HUD(Game *g, Player *p) :
		game(g), player(p) {
}

void HUD::draw() {
	if (game->gameState != STATE_PLAYING)
		return;

	// background
	DrawRectangle(0, 0, GRID_SIZE * CELL_SIZE, HUD_HEIGHT, HUD_BG_COLOR);

	int segments = 5; // Score, Money, Fuel, Time, Mode
	int segmentWidth = GRID_SIZE * CELL_SIZE / segments;
	int textY = HUD_HEIGHT / 2 + 5;

	showScore(10, textY);
	showMoney(segmentWidth, textY);
	showFuel(segmentWidth * 2, textY);
	showTime(segmentWidth * 3, textY);
	showGameMode(segmentWidth * 4 + 10, textY);
}

void HUD::showScore(int x, int y) {
	string scoreText = "SCORE: " + to_string(player->score);
	DrawString(x, y, scoreText, HUD_TEXT_COLOR);
}

void HUD::showMoney(int x, int y) {
	string moneyText = "MONEY: $" + to_string((int) player->money);
	DrawString(x, y, moneyText, HUD_TEXT_COLOR);
}

void HUD::showFuel(int x, int y) {
	if (player->car == NULL)
		return;

	string fuelText = "FUEL: " + to_string((int) player->car->fuelLevel) + "%";
	DrawString(x, y, fuelText, HUD_TEXT_COLOR);

	//fuel line (shifts from green to red when less than 20)
	float fuelPercent = player->car->fuelLevel / 100.0f;
	DrawRectangle(x, y + 10, 50 * fuelPercent, 5,(fuelPercent < 0.2f) ? colors[RED] : colors[GREEN]);
}

void HUD::showGameMode(int x, int y) {
	string modeText = (game->gameMode == MODE_TAXI) ? "TAXI" : "DELIVERY";
	DrawString(x, y, modeText, HUD_TEXT_COLOR);
}

void HUD::showTime(int x, int y) {
	int remaining = game->timeLimit - game->currentTime;
	string timeText = "TIME: " + to_string(remaining / 60) + ":" + ((remaining % 60 < 10) ? "0" : "") + to_string(remaining % 60);
	DrawString(x, y, timeText, HUD_TEXT_COLOR);
}

void HUD::showGameOver() {
	// Draw game over overlay (offset by HUD_HEIGHT)
	DrawRectangle(0, HUD_HEIGHT, GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE, HUD_BG_COLOR);

	// Center text in the game area
	int centerY = HUD_HEIGHT + GRID_SIZE * CELL_SIZE / 2;

	string gameOverText = "GAME OVER";
	string scoreText = "FINAL SCORE: " + to_string(player->score);

	DrawString(GRID_SIZE * CELL_SIZE / 2 - 80, centerY - 30, gameOverText, colors[RED]);
	DrawString(GRID_SIZE * CELL_SIZE / 2 - 100, centerY + 20, scoreText, HUD_TEXT_COLOR);
}

