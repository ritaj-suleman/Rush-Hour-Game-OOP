#include "NPCCar.h"
#include "Board.h"
#include "util.h"
#include "constants.h"

NPCCar::NPCCar(int _x, int _y) :
		Car(_x, _y, 3.0f), 
		movementType(rand() % 3), 
		stuckFrames(0), 
		lastDirectionChange(0) {
	// random color
	color[0] = 100 + rand() % 155;
	color[1] = 100 + rand() % 155;
	color[2] = 100 + rand() % 155;

	// random initial direction
	direction = rand() % 4;
	isPlayerControlled = false;
}

void NPCCar::updateMovement(Board *board) {
	if (!isActive)
		return;

	// move only every 2 frames
	static int moveCounter = 0;
	if (++moveCounter < 2)
		return;
	moveCounter = 0;

	int oldGridX = x, oldGridY = y;// save krlo previous position
	moveOneBlock(direction, board);
	
      
	if (x == oldGridX && y == oldGridY) {// meaning stuck
		stuckFrames++;

		if (stuckFrames > 2) {
			findNewDirection(board);
		}

		if (stuckFrames > 5) {
			if (attemptEscape(board)) {
				stuckFrames = 0;
			}
		}

		if (stuckFrames > 15) {
			resetCar();
			stuckFrames = 0;
		}
	} else {
		stuckFrames = 0;
		lastDirectionChange = 0;
	}

	// random direction changes
	if (rand() % 20 == 0 && stuckFrames == 0) {
		findNewDirection(board);
	}
}

void NPCCar::moveOneBlock(int dir, Board *board) {
	int newGridX = x, newGridY = y;

	switch (dir) {
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
	}
}

bool NPCCar::isValidPosition(int checkGridX, int checkGridY, Board *board) {
	if (checkGridX < 0 || checkGridX >= GRID_SIZE || checkGridY < 0 || checkGridY >= GRID_SIZE) {
		return false;
	}

	if (cityGrid[checkGridX][checkGridY] != 0) {
		return false;
	}

	for (int i = 0; i < board->carCount; i++) {
		if (board->cars[i] != this && board->cars[i]->isActive) {
			if (board->cars[i]->x == checkGridX && board->cars[i]->y == checkGridY) {
				return false;
			}
		}
	}

	return true;
}

void NPCCar::findNewDirection(Board *board) {
	if (lastDirectionChange < 10) {
		lastDirectionChange++;
		return;
	}

	// try all directions in random order
	int dirs[4] = { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
	for (int i = 0; i < 4; i++) {
		int j = rand() % 4;
		int temp = dirs[i];
		dirs[i] = dirs[j];
		dirs[j] = temp;
	}

	for (int i = 0; i < 4; i++) {
		int testDir = dirs[i];
		int testX = x, testY = y;

		switch (testDir) {
		case DIR_UP:
			testY -= 1;
			break;
		case DIR_DOWN:
			testY += 1;
			break;
		case DIR_LEFT:
			testX -= 1;
			break;
		case DIR_RIGHT:
			testX += 1;
			break;
		}

		if (isValidPosition(testX, testY, board)) {
			direction = testDir;
			lastDirectionChange = 0;
			return;
		}
	}

	// if all directions blocked, try opposite direction
	direction = (direction + 2) % 4;
	lastDirectionChange = 0;
}

bool NPCCar::attemptEscape(Board *board) {
	for (int i = 0; i < 4; i++) {
		int testDir = (direction + i) % 4;
		int testX = x, testY = y;

		switch (testDir) {
		case DIR_UP:
			testY -= 1;
			break;
		case DIR_DOWN:
			testY += 1;
			break;
		case DIR_LEFT:
			testX -= 1;
			break;
		case DIR_RIGHT:
			testX += 1;
			break;
		}

		if (isValidPosition(testX, testY, board)) {
			direction = testDir;
			moveOneBlock(direction, board);
			return true;
		}
	}
	return false;
}

void NPCCar::resetCar() {
	Car::resetCar();
	direction = rand() % 4;
	lastDirectionChange = 0;
}

void NPCCar::draw() {
	if (!isActive)
		return;

	float pixelX = x * CELL_SIZE + CELL_SIZE / 2;
	float pixelY = y * CELL_SIZE + CELL_SIZE / 2 + HUD_HEIGHT;

	float carColor[3] = { color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f };
	DrawCar(pixelX, pixelY, 30, carColor);
}

string NPCCar::getType() const {
	return "NPCCar";
}

