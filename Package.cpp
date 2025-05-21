#include "Package.h"
#include "Board.h" 
#include "util.h"
#include "constants.h"

#include <cstdlib>  // for rand()

Package::Package() :
		GameObject(), 
		pickupX(0), 
		pickupY(0), 
		destinationX(0), 
		destinationY(0), 
		deliveryFee(0.0f), 
		isPickedUp(false) {
	cout << "package made" << x << " " << y << endl;
}

Package::Package(int _x, int _y, int _destX, int _destY) :
		GameObject(_x, _y, 15, 15), 
		pickupX(_x), 
		pickupY(_y), 
		destinationX(_destX), 
		destinationY(_destY), 
		deliveryFee(15.0f + rand() % 25), // fee between 15–40
		isPickedUp(false) {
	cout << "package made" << x << " " << y << endl;
}

void Package::generateDestination(Board *board) {
	if (!board)
		return;

	int attempts = 0;
	const int maxAttempts = 100;
	bool validPosition = false;

	do {
		destinationX = rand() % GRID_SIZE;
		destinationY = rand() % GRID_SIZE;
		attempts++;

		validPosition = board->isPositionClear(destinationX, destinationY);

	} while ((!validPosition || cityGrid[destinationX][destinationY] != 0) && attempts < maxAttempts);

	if (attempts >= maxAttempts) {
		destinationX = 0;
		destinationY = 0;
	}
}

void Package::setPickedUp(bool status) {
	isPickedUp = status;
}

float Package::getDeliveryFee() {
	return deliveryFee;
}

void Package::draw() {
	if (!isActive)
		return;
	int pixelX = x * CELL_SIZE + CELL_SIZE / 2;
	int pixelY = y * CELL_SIZE + CELL_SIZE / 2;

	DrawSquare(pixelX - width / 2, pixelY - height / 2, width, PACKAGE_COLOR);
}

void Package::highlightDestination() {
	if (this == nullptr) {
		return;
	}

	int pixelX = destinationX * CELL_SIZE + CELL_SIZE / 2;
	int pixelY = destinationY * CELL_SIZE + CELL_SIZE / 2 + HUD_HEIGHT;

	if (pixelX <= 0 || pixelX >= GRID_SIZE * CELL_SIZE || pixelY <= HUD_HEIGHT || pixelY >= TOTAL_HEIGHT) {
		return;
	}

	float highlightColor[] = { 0.0f, 1.0f, 0.0f };
	DrawCircle(pixelX, pixelY, 15, highlightColor);
}

string Package::getType() const {
	return "Package";
}

Package::~Package() {
	cout << "package deleted" << endl;
}

