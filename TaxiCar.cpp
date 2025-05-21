#include "TaxiCar.h"
#include "Player.h"
#include "Passenger.h"
#include "GameObject.h"
#include "util.h"
#include "constants.h"
#include<string>
#include "sound.h" 

TaxiCar::TaxiCar(Player *p) : Car(), currentPassenger(NULL), hasPassenger(false), player(p) {
	color[0] = 255;
	color[1] = 255;
	color[2] = 0; // Yellow
}

TaxiCar::TaxiCar(int _x, int _y, Player *p) : Car(_x, _y, 5.0f), currentPassenger(NULL), hasPassenger(false), player(p) {
	color[0] = 255;
	color[1] = 255;
	color[2] = 0; // Yellow
}

bool TaxiCar::pickupPassenger(Passenger *p) {
	if (!hasPassenger && p != NULL) {
		currentPassenger = p;
		hasPassenger = true;
		p->setPickedUp(true);
		return true;
	}
	return false;
}

bool TaxiCar::dropPassenger() {
	if (!hasPassenger || !currentPassenger)
		return false;

	if (x == currentPassenger->destinationX && y == currentPassenger->destinationY) {
		float fare = currentPassenger->getFare();

		if (player) {
			playSound("dropped.wav");
			player->updateMoney(fare);
			player->updateScore(10);
		}

		// mark for delete (right now do not delete)
		currentPassenger->readyForDeletion = true; 
		hasPassenger = false;
		jobsCompleted++;

		currentPassenger = nullptr;

		return true;
	}
	return false;
}

void TaxiCar::draw() {
	if (!isActive)
		return;

	int pixelX = x * CELL_SIZE + CELL_SIZE / 2;
	int pixelY = y * CELL_SIZE + CELL_SIZE / 2 + HUD_HEIGHT;

	float taxiColor[3] = { 1.0f, 1.0f, 0.0f };
	DrawCar(pixelX, pixelY, 30, taxiColor);

	if (hasPassenger) {
		float passengerIndicator[3] = { 0.0f, 1.0f, 0.0f };
		DrawCircle(pixelX, pixelY - 15, 5, passengerIndicator);
	}
}

void TaxiCar::handleCollision(GameObject *obj) {
	static GameObject *lastCollided = nullptr;
	static int cooldown = 0;

	if (!player || !obj || obj == lastCollided)
		return;

	string type = obj->getType();
	int penalty = 0;

	if (type == "Passenger") {
		Passenger *p = dynamic_cast<Passenger*>(obj);
		if (p && p->isActive && hasPassenger && currentPassenger != p) {
			penalty = -5;
		}
	} else if (type == "Obstacle") {
		penalty = -2;
	} else if (type == "NPCCar") {
		penalty = -3;
	}

	if (penalty != 0) {
		player->updateScore(penalty);
		lastCollided = obj;
		cooldown = 10; // frames
		playSound("collision.wav");
	}

	if (cooldown > 0)
		cooldown--;
	else
		lastCollided = nullptr;
}

void TaxiCar::resetCar() {
	Car::resetCar();
	hasPassenger = false;
	currentPassenger = nullptr;
}

void TaxiCar::move(int dir) {
	direction = dir;

	int newGX = x;
	int newGY = y;

	switch (direction) {
	case DIR_UP:
		newGY--;
		break;
	case DIR_DOWN:
		newGY++;
		break;
	case DIR_LEFT:
		newGX--;
		break;
	case DIR_RIGHT:
		newGX++;
		break;
	}

	bool withinBounds = (newGX >= 0 && newGX < GRID_SIZE && newGY >= 0 && newGY < GRID_SIZE);

	if (withinBounds && cityGrid[newGX][newGY] == 0) {
		x = newGX;
		y = newGY;
		decreaseFuel();
	}

}

string TaxiCar::getType() const {
	return "TaxiCar";
}

TaxiCar::~TaxiCar() {
	cout << "taxi car deleted" << endl;
}


