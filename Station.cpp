#include "Station.h"
#include "Player.h"
#include "Car.h"
#include "Game.h"
#include "Menu.h"
#include "util.h"
#include "constants.h"
#include <iostream>
using namespace std;

Station::Station() :GameObject(), isAvailable(true) {}

Station::Station(int _x, int _y) :GameObject(_x, _y, 40, 40), isAvailable(true) {}

Station::Station(int _x, int _y, GameEngine *engine) :GameObject(_x, _y, 40, 40), gameEngine(engine), isAvailable(true) {}

void Station::setGameEngine(GameEngine *engine) {
	gameEngine = engine;
}

void Station::draw() {
	if (!isActive)
		return;

	float drawX = x * CELL_SIZE + CELL_SIZE / 2;
	float drawY = y * CELL_SIZE + CELL_SIZE / 2;

	DrawSquare(drawX - width / 2, drawY - height / 2, width, STATION_COLOR);

	float doorColor[] = { 0.4, 0.4, 0.4 }; // Darker gray
	DrawRectangle(drawX - width / 3, drawY - height / 3, width * 2 / 3, height * 2 / 3, doorColor);
}

string Station::getType() const {
	return "Station";
}

void Station::changePlayerRole(Player *player) {
	if (!player || !gameEngine)
		return;
	gameEngine->getMenu()->showRoleChangeMenu(true);
	gameEngine->getGame()->pauseGame();
}

bool Station::isPlayerNear(Player *player) {
	if (!player || !player->car)
		return false;
	return (player->car->x == x && player->car->y == y);
}

