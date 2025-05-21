#include "Obstacle.h"
#include "util.h"
#include "constants.h"

Obstacle::Obstacle() :
		GameObject(), type(0) {}

Obstacle::Obstacle(int _x, int _y, int _type) :
		GameObject(_x, _y, 20, 20), 
		type(_type) {
	cout << "obstacle created at" << x << " " << y << endl;
}

int Obstacle::getObstacleType() {
	return type;
}

void Obstacle::draw() {
	if (!isActive)
		return;

	int pixelX = x * CELL_SIZE + CELL_SIZE / 2;
	int pixelY = y * CELL_SIZE + CELL_SIZE / 2;

	if (type == 0) {
		//  tree
		float trunkColor[] = { 0.5, 0.3, 0.1 }; // Brown
		float leavesColor[] = { 0, 0.6, 0.1 }; // Dark green

		// trunk
		DrawRectangle(pixelX - 3, pixelY - 10, 6, 10, trunkColor);

		// leaves
		DrawCircle(pixelX, pixelY - 15, 10, leavesColor);
	} else {
		// box
		DrawSquare(pixelX - width / 2, pixelY - height / 2, width,
				OBSTACLE_COLOR);
	}
}

string Obstacle::getType() const {
	return "Obstacle";
}

