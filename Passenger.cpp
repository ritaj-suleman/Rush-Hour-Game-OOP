#include "Passenger.h"
#include "Board.h" 
#include "util.h"
#include "constants.h"

#include <cstdlib>  // for rand()

Passenger::Passenger() :
		GameObject(), 
		destinationX(0), 
		destinationY(0), 
		fare(0.0f), 
		isPickedUp(false) {}

Passenger::Passenger(int _x, int _y, int _destX, int _destY) :
		GameObject(_x, _y, 10, 10),
		destinationX(_destX), 
		destinationY(_destY), 
		fare(10.0f + rand() % 20),  // random fare between 10-30
		isPickedUp(false) {}

void Passenger::generateDestination(Board *board) {
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

void Passenger::setPickedUp(bool status) {
	isPickedUp = status;
}

float Passenger::getFare() {
	return fare;
}

void Passenger::draw() {
	int pixelX = x * CELL_SIZE + CELL_SIZE / 2;
	int pixelY = y * CELL_SIZE + CELL_SIZE / 2;

	if (!isActive)
		return;
	// head
	DrawCircle(pixelX, pixelY, 5, PASSENGER_COLOR);

	// body
	DrawLine(pixelX, pixelY + 5, pixelX, pixelY + 15, 2, PASSENGER_COLOR);

	// arms
	DrawLine(pixelX - 5, pixelY + 10, pixelX + 5, pixelY + 10, 2, PASSENGER_COLOR);

	// legs
	DrawLine(pixelX, pixelY + 15, pixelX - 5, pixelY + 25, 2, PASSENGER_COLOR);
	DrawLine(pixelX, pixelY + 15, pixelX + 5, pixelY + 25, 2, PASSENGER_COLOR);
}

void Passenger::highlightDestination() {
	if (this == nullptr)
		return;

	int pixelX = destinationX * CELL_SIZE + CELL_SIZE / 2;
	int pixelY = destinationY * CELL_SIZE + CELL_SIZE / 2 + HUD_HEIGHT;

	float highlightColor[] = { 0.0f, 1.0f, 0.0f };
	DrawCircle(pixelX, pixelY, 15, highlightColor);
}

string Passenger::getType() const {
	return "Passenger";
}

Passenger::~Passenger() {
	cout << "Passenger deleted"<< endl;
}

