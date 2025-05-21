#include "Board.h"
#include "Building.h"
#include "Road.h"
#include "FuelStation.h"
#include "NPCCar.h"
#include "Station.h"
#include "Obstacle.h"
#include "Package.h"
#include "Passenger.h"
#include "GameEngine.h"
#include "Game.h"        
#include "Player.h"       
#include "TaxiCar.h"      
#include "DeliveryCar.h"  
#include "util.h"
#include "constants.h"

#include <GL/glut.h> 
#include<iostream>
using namespace std;

Board::Board(GameEngine *engine, const int grid[GRID_SIZE][GRID_SIZE]) :
		gameEngine(engine), 
		width(GRID_SIZE * CELL_SIZE), 
		height(GRID_SIZE * CELL_SIZE), 
		cityGrid(grid), 
		buildingCount(0), 
		roadCount(0), 
		fuelStationCount(0), 
		carCount(0), 
		obstacleCount(0),
		passengerCount(0), 
		packageCount(0), 
		roleChangeStation(nullptr) {
	generateBoard();
}

void Board::generateBoard() {
	cleanup();

	// seed random number generator
	srand(time(0));

	// reset counters
	buildingCount = 0;
	roadCount = 0;

	// roads and buildings
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (cityGrid[i][j] == 1 && buildingCount < MAX_BUILDINGS) {
				buildings[buildingCount++] = new Building(i, j);
			} else if (roadCount < MAX_ROADS) {
				roads[roadCount++] = new Road(i, j);
			}
		}
	}

	// role changing station at bottom left
	roleChangeStation = new Station(0, GRID_SIZE - 1, this->gameEngine);
	roleChangeStation->isActive = true;

	// fuel stations at random road locations
	for (int i = 0; i < 3 && fuelStationCount < MAX_STATIONS; i++) {
		int x, y;
		do {
			x = rand() % GRID_SIZE;
			y = rand() % GRID_SIZE;
		} while (cityGrid[x][y] != 0 || (x == 0 && y == 0)); // i don't want that all the cars start from 0,0 cell

		fuelStations[fuelStationCount++] = new FuelStation(x, y);
	}

	for (int i = 0; i < fuelStationCount; i++) {
		fuelStations[i]->isActive = true;
	}

	// 3-4 obstacles at random locations
	for (int i = 0; i < 3 + rand() % 2 && obstacleCount < MAX_OBSTACLES; i++) {
		addObstacle();
	}

	// mode according object
	Game *game = gameEngine->getGame();
	if (game && game->gameMode == MODE_TAXI) {
		for (int i = 0; i < 2; i++) {
			addPassenger();
		}
	} else if (game) { 
		for (int i = 0; i < 2; i++) {
			addPackage();
		}
	}

	//other cars
	for (int i = 0; i < 3 && carCount < MAX_CARS; i++) {
		addCar();
	}
}

void Board::updateBoard() {
	// other cars movement
	for (int i = 0; i < carCount; i++) {
		if (cars[i]->isActive) {
			cars[i]->updateMovement(this);
		}
	}

	// clean up inactive objects
	if (gameEngine->getGame()->gameMode == MODE_TAXI) {
		for (int i = 0; i < passengerCount;) {
			if (passengers[i]->readyForDeletion) { 
				delete passengers[i];
				for (int j = i; j < passengerCount - 1; j++) {
					passengers[j] = passengers[j + 1];
				}
				passengerCount--;
			} else {
				i++;
			}
		}
	} else {
		for (int i = 0; i < packageCount;) {
			if (packages[i]->readyForDeletion) { 
				delete packages[i];
				for (int j = i; j < packageCount - 1; j++) {
					packages[j] = packages[j + 1];
				}
				packageCount--;
			} else {
				i++;
			}
		}
	}

	// fuel station refueling 
	if (gameEngine->getPlayer() && gameEngine->getPlayer()->car) {
		Car *playerCar = gameEngine->getPlayer()->car;

		for (int i = 0; i < fuelStationCount; i++) {
			FuelStation *station = fuelStations[i];

			if (station->isActive && station->x == playerCar->x && station->y == playerCar->y) {

				float maxFuelCanBuy = gameEngine->getPlayer()->getMoney() / station->fuelPrice;
				float fuelNeeded = playerCar->maxFuel - playerCar->fuelLevel;
				float fuelToBuy = min(maxFuelCanBuy, fuelNeeded);

				if (fuelToBuy > 0) {
					station->refuelCar(playerCar, gameEngine->getPlayer(), fuelToBuy);
				}
			}
		}
	}

	// collisions
	if (gameEngine->getPlayer() && gameEngine->getPlayer()->car) {
		Car *playerCar = gameEngine->getPlayer()->car;

		// checking with obstacles
		for (int i = 0; i < obstacleCount; i++) {
			if (obstacles[i]->isActive && playerCar->checkCollision(obstacles[i])) {
				playerCar->handleCollision(obstacles[i]);
			}
		}

		// checking with other cars
		for (int i = 0; i < carCount; i++) {
			if (cars[i] != playerCar && cars[i]->isActive && playerCar->checkCollision(cars[i])) {
				playerCar->handleCollision(cars[i]);
			}
		}

		// checking with passenger/package
		if (gameEngine->getGame()->gameMode == MODE_TAXI) {
			TaxiCar *taxi = dynamic_cast<TaxiCar*>(playerCar);
			if (taxi) {
				for (int i = 0; i < passengerCount; i++) {
					if (passengers[i]->isActive && playerCar->checkCollision(passengers[i])) {
						taxi->handleCollision(passengers[i]);
					}
				}
			}
		} else { 
			DeliveryCar *delivery = dynamic_cast<DeliveryCar*>(playerCar);
			if (delivery) {
				for (int i = 0; i < packageCount; i++) {
					if (packages[i]->isActive && playerCar->checkCollision(packages[i])) {
						delivery->handleCollision(packages[i]);
					}
				}
			}
		}
	}

}

void Board::addCar() {
	if (carCount >= MAX_CARS)
		return;

	int gridX, gridY;
	bool validPosition = false;
	int attempts = 0;

	while (!validPosition && attempts < 100) {
		gridX = rand() % GRID_SIZE;
		gridY = rand() % GRID_SIZE;

		if (cityGrid[gridX][gridY] == 0 && !(gridX < 2 && gridY < 2)) { // keep away from player start area
			validPosition = true;

			for (int i = 0; i < carCount; i++) {
				if (cars[i]->x == gridX && cars[i]->y == gridY) {
					validPosition = false;
					break;
				}
			}
		}
		attempts++;
	}

	if (validPosition) {
		cars[carCount] = new NPCCar(gridX, gridY);
		carCount++;
	}
}

void Board::addPassenger() {
	if (passengerCount >= MAX_PASSENGERS)
		return;

	int x, y;
	int attempts = 0;
	const int maxAttempts = 100;

	do {
		x = rand() % GRID_SIZE;
		y = rand() % GRID_SIZE;
		attempts++;
	} while ((!isPositionClear(x, y) || cityGrid[x][y] != 0) && attempts < maxAttempts);

	if (attempts < maxAttempts) {
		passengers[passengerCount] = new Passenger(x, y, 0, 0);
		passengers[passengerCount]->generateDestination(this);
		passengerCount++;
	}
}

void Board::addPackage() {
	if (packageCount >= MAX_PACKAGES)
		return;

	int x, y;
	int attempts = 0;
	const int maxAttempts = 100;

	do {
		x = rand() % GRID_SIZE;
		y = rand() % GRID_SIZE;
		attempts++;
	} while ((!isPositionClear(x, y) || cityGrid[x][y] != 0) && attempts < maxAttempts);

	if (attempts < maxAttempts) {
		packages[packageCount] = new Package(x, y, 0, 0);
		packages[packageCount]->generateDestination(this);
		packageCount++;
	}
}

void Board::increaseDifficulty() {
	// increase speed to max of 5
	for (int i = 0; i < carCount; i++) {
		cars[i]->speed = min(cars[i]->speed + 0.2f, 5.0f); 
	}

	//add one more car
	if (carCount < MAX_CARS) {
		addCar();
	}
}

void Board::addObstacle() {
	if (obstacleCount >= MAX_OBSTACLES)
		return;

	int x, y;
	bool validPosition = false;
	int attempts = 0;
	const int maxAttempts = 100;

	while (!validPosition && attempts < maxAttempts) {
		x = rand() % GRID_SIZE;
		y = rand() % GRID_SIZE;

		if (isPositionClear(x, y)) {
			validPosition = true;
		}
		attempts++;
	}

	if (validPosition) {
		obstacles[obstacleCount++] = new Obstacle(x, y, rand() % 2);// random for tree / box
	} else {
		cout << "Failed to place obstacle after " << maxAttempts << " attempts" << endl;
	}
}

bool Board::isPositionClear(int gridX, int gridY) {
	//  building
	if (cityGrid[gridX][gridY] != 0) {
		return false;
	}

	// role change station 
	if (roleChangeStation && gridX == roleChangeStation->x && gridY == roleChangeStation->y) {
		return false;
	}

	// obstacles
	for (int i = 0; i < obstacleCount; i++) {
		if (!obstacles[i]->isActive)
			continue;

		if (obstacles[i]->x == gridX && obstacles[i]->y == gridY) {
			return false;
		}
	}

	//  buildings (just in case)
	for (int i = 0; i < buildingCount; i++) {
		if (!buildings[i]->isActive)
			continue;

		if (buildings[i]->x == gridX && buildings[i]->y == gridY) {
			return false;
		}
	}
        
        // fuel station
	for (int i = 0; i < fuelStationCount; i++) {
		if (!fuelStations[i]->isActive)
			continue;

		if (fuelStations[i]->x == gridX && fuelStations[i]->y == gridY) {
			return false;
		}
	}

	return true;
}

void Board::drawBoard() {
	if (!gameEngine)
		return;

	glPushMatrix();
	glTranslatef(0, HUD_HEIGHT, 0);

	// 1. Draw roads first (background)
	for (int i = 0; i < roadCount; i++) {
		if (roads[i]->isActive)
			roads[i]->draw();
	}

	// 2. Draw buildings
	for (int i = 0; i < buildingCount; i++) {
		if (buildings[i]->isActive)
			buildings[i]->draw();
	}
        
        // 3. Draw role changing station
	if (roleChangeStation->isActive)
		roleChangeStation->draw();

	// 4. Draw objects (fuel stations, obstacles)
	for (int i = 0; i < fuelStationCount; i++) {
		if (fuelStations[i]->isActive)
			fuelStations[i]->draw();
	}

	for (int i = 0; i < obstacleCount; i++) {
		if (obstacles[i]->isActive)
			obstacles[i]->draw();
	}

	//5. Draw mode-specific objects 
	if (gameEngine->getGame()->gameMode == MODE_TAXI) {
		Player *player = gameEngine->getPlayer();
		TaxiCar *taxi = nullptr;
		if (player && player->car) {
			taxi = dynamic_cast<TaxiCar*>(player->car);
		}

		for (int i = 0; i < passengerCount; i++) {
			if (passengers[i]->isActive) {
				passengers[i]->draw();
			}
		}
               
                //destination
		if (taxi && taxi->hasPassenger && taxi->currentPassenger) {
			glPushMatrix();
			glLoadIdentity();

			glDisable(GL_DEPTH_TEST);
			taxi->currentPassenger->highlightDestination();
			glEnable(GL_DEPTH_TEST);

			glPopMatrix();
		}
	} else {
		Player *player = gameEngine->getPlayer();
		DeliveryCar *delivery = nullptr;
		if (player && player->car) {
			delivery = dynamic_cast<DeliveryCar*>(player->car);
		}

		for (int i = 0; i < packageCount; i++) {
			if (packages[i]->isActive) {
				packages[i]->draw();
			}
		}

		// destination
		if (delivery && delivery->hasPackage && delivery->currentPackage) {
			glPushMatrix();
			glLoadIdentity();

			glDisable(GL_DEPTH_TEST);
			delivery->currentPackage->highlightDestination();
			glEnable(GL_DEPTH_TEST);

			glPopMatrix();
		}
	}

	// 6. Draw NPC cars
	for (int i = 0; i < carCount; i++) {
		if (cars[i]->isActive)
			cars[i]->draw();
	}

	// 7. Draw player car LAST (so it's on top)
	if (gameEngine->getPlayer() && gameEngine->getPlayer()->car) {
		gameEngine->getPlayer()->car->draw();
	}

	glPopMatrix();
}

void Board::cleanup() {
	for (int i = 0; i < buildingCount; i++) {
		delete buildings[i];
	}
	buildingCount = 0;

	for (int i = 0; i < roadCount; i++) {
		delete roads[i];
	}
	roadCount = 0;

	for (int i = 0; i < fuelStationCount; i++) {
		delete fuelStations[i];
	}
	fuelStationCount = 0;

	for (int i = 0; i < carCount; i++) {
		delete cars[i];
	}
	carCount = 0;

	if (roleChangeStation != NULL) {
		delete roleChangeStation;
		roleChangeStation = NULL;
	}

	for (int i = 0; i < obstacleCount; i++) {
		delete obstacles[i];
	}
	obstacleCount = 0;

	for (int i = 0; i < passengerCount; i++) {
		if (passengers[i]) {
			for (int j = 0; j < carCount; j++) {
				TaxiCar *taxi = dynamic_cast<TaxiCar*>(cars[j]);
				if (taxi && taxi->currentPassenger == passengers[i]) {
					taxi->currentPassenger = nullptr;
					taxi->hasPassenger = false;
				}
			}
			delete passengers[i];
		}
	}
	passengerCount = 0;

	for (int i = 0; i < packageCount; i++) {
		if (packages[i]) {
			for (int j = 0; j < carCount; j++) {
				DeliveryCar *deliver = dynamic_cast<DeliveryCar*>(cars[j]);
				if (deliver && deliver->currentPackage == packages[i]) {
					deliver->currentPackage = nullptr;
					deliver->hasPackage = false;
				}
			}
			delete packages[i];
		}
	}
	packageCount = 0;

	if (roleChangeStation) {
		delete roleChangeStation;
		roleChangeStation = nullptr;
	}
}

void Board::clearModeObjects() {
	for (int i = 0; i < passengerCount; i++) {
		delete passengers[i];
	}
	passengerCount = 0;

	for (int i = 0; i < packageCount; i++) {
		delete packages[i];
	}
	packageCount = 0;

	if (gameEngine->getGame()->gameMode == MODE_TAXI) {
		for (int i = 0; i < 2; i++) {
			addPassenger();
		}
	} else {
		for (int i = 0; i < 2; i++) {
			addPackage();
		}
	}
}

