#include "Car.h"
#include "Board.h"
#include "NPCCar.h";
#include "util.h"
#include "constants.h"
#include <GL/glut.h>  

Car::Car() :
		GameObject(0, 0, 30, 20), 
		speed(5.0f), 
		direction(DIR_RIGHT), 
		fuelLevel(100.0f), 
		maxFuel(100.0f), 
		isPlayerControlled(false), 
		jobsCompleted(0) {
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
}

Car::Car(int _x, int _y, float _speed) :
		GameObject(_x, _y, 30, 20), 
		speed(_speed), 
		direction(DIR_RIGHT), 
		fuelLevel(100.0f), 
		maxFuel(100.0f), 
		isPlayerControlled(false),
		jobsCompleted(0) {
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
}

void Car::move(int dir, Board *board) {
	direction = dir;
	
	int newGridX = x;
	int newGridY = y;

	switch (direction) {
	case DIR_UP:
		newGridY -= 1;
		break;
	case DIR_DOWN:
		newGridY += 1;
		break;
	case DIR_LEFT:
		newGridX -= 1;
		break;
	case DIR_RIGHT:
		newGridX += 1;
		break;
	}

	if (isValidPosition(newGridX, newGridY, board)) {
		x = newGridX;
		y = newGridY;
		decreaseFuel();
	}
}

bool Car::isValidPosition(int checkGridX, int checkGridY, Board *board) {
	if (checkGridX < 0 || checkGridX >= GRID_SIZE || checkGridY < 0
			|| checkGridY >= GRID_SIZE) {
		return false;
	}

	if (cityGrid[checkGridX][checkGridY] != 0) {
		return false;
	}
	
	for (int i = 0; i < board->carCount; i++) {
		if (board->cars[i]->isActive) {
			if (board->cars[i]->x == checkGridX
					&& board->cars[i]->y == checkGridY) {
				return false;
			}
		}
	}

	return true;
}

void Car::draw() {
	if (!isActive)
		return;

	float carColor[3] = { color[0] / 255.f, color[1] / 255.f, color[2] / 255.f };
	float drawX = x * CELL_SIZE + CELL_SIZE / 2;
	float drawY = y * CELL_SIZE + CELL_SIZE / 2 + HUD_HEIGHT;

	glPushMatrix();

	glTranslatef(drawX, drawY, 0);

	DrawCar(drawX, drawY, 30, carColor);

	glPopMatrix();
}

void Car::decreaseFuel() {
	if (isPlayerControlled) {
		fuelLevel -= 0.5f;
	}
}

void Car::resetCar() {
	x = 0;
	y = 0;
	direction = DIR_RIGHT;
	fuelLevel = 100.0f;
	jobsCompleted = 0;
}

string Car::getType() const {
	return "Car";
}

void Car::handleCollision(GameObject *obj) {
}

Car::~Car() {
	cout << "car deleted" << endl;
}

