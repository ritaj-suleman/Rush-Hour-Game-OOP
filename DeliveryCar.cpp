#include "DeliveryCar.h"
#include "Player.h"
#include "Package.h"
#include "GameObject.h"
#include "util.h"
#include <string>
#include "sound.h"
#include "constants.h"

DeliveryCar::DeliveryCar(Player *p) :
		Car(), 
		currentPackage(NULL), 
		hasPackage(false), 
		player(p) {
	color[0] = 0;
	color[1] = 0;
	color[2] = 255; // Blue
}

DeliveryCar::DeliveryCar(int _x, int _y, Player *p) :
		Car(_x, _y, 5.0f), 
		currentPackage(NULL), 
		hasPackage(false), 
		player(p) {
	color[0] = 0;
	color[1] = 0;
	color[2] = 255; // Blue
}

bool DeliveryCar::pickupPackage(Package *p) {
	if (!hasPackage && p != NULL) {
		currentPackage = p;
		hasPackage = true;
		p->setPickedUp(true);
		return true;
	}
	return false;
}

bool DeliveryCar::deliverPackage() {
	if (!hasPackage || !currentPackage)
		return false;

	if (x == currentPackage->destinationX && y == currentPackage->destinationY) {
		float fare = currentPackage->getDeliveryFee();

		if (player) {
			playSound("dropped.wav");
			player->updateMoney(fare);
			player->updateScore(20);
		}

		// only mark for deletion (abhi delete nahi krna)
		currentPackage->readyForDeletion = true; 
		hasPackage = false;
		jobsCompleted++;
		cout << jobsCompleted << endl;

		currentPackage = nullptr;

		return true;
	}
	return false;
}

void DeliveryCar::draw() {
	if (!isActive)
		return;
	int pixelX = x * CELL_SIZE + CELL_SIZE / 2;
	int pixelY = y * CELL_SIZE + CELL_SIZE / 2 + HUD_HEIGHT;

	float deliveryColor[3] = { 0.0f, 0.0f, 1.0f }; // Blue
	DrawCar(pixelX, pixelY, 30, deliveryColor);

	//indicator
	if (hasPackage) {
		float packageIndicator[3] = { 0.6f, 0.3f, 0.0f }; // Brown
		DrawSquare(pixelX - 5, pixelY - 15, 10, packageIndicator);
	}
}

void DeliveryCar::handleCollision(GameObject *obj) {
	static GameObject *lastCollided = nullptr;
	static int cooldown = 0;

	if (!player || !obj || obj == lastCollided)
		return;

	string type = obj->getType();
	int penalty = 0;

	if (type == "Package") {
		Package *p = dynamic_cast<Package*>(obj);
		if (p && p->isActive && hasPackage && currentPackage != p) {
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

void DeliveryCar::resetCar() {
	Car::resetCar();
	hasPackage = false;
	currentPackage = nullptr;
}

void DeliveryCar::move(int dir) {
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

	if (withinBounds && cityGrid[newGX][newGY] == 0) { // road
		x = newGX;
		y = newGY;
		decreaseFuel();
	}

}

string DeliveryCar::getType() const {
	return "DeliveryCar";
}


