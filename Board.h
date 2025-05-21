#ifndef BOARD_H
#define BOARD_H

#include "constants.h"

class Building;
class Road;
class FuelStation;
class NPCCar;
class Station;
class Obstacle;
class Passenger;
class Package;
class Game;
class Player;
class TaxiCar;
class DeliveryCar;
class GameEngine;

class Board {
public:
	GameEngine *gameEngine;
	int width, height; //dimensions of board
	const int (*cityGrid)[GRID_SIZE];  

	Building *buildings[200];      
	Road *roads[500];           
	FuelStation *fuelStations[3]; 
	NPCCar *cars[10];            
	Obstacle *obstacles[10];    
	Passenger *passengers[20];   
	Package *packages[20];    
	Station *roleChangeStation;    

	int buildingCount;
	int roadCount;
	int fuelStationCount;
	int carCount;
	int obstacleCount;
	int passengerCount;
	int packageCount;

	Board(GameEngine *engine, const int grid[GRID_SIZE][GRID_SIZE]);
	void generateBoard();
	void updateBoard();
	void addCar();
	void addPassenger();
	void addPackage();
	void increaseDifficulty();
	void addObstacle();
	bool isPositionClear(int gridX, int gridY);
	void drawBoard();
	void cleanup();
	void clearModeObjects();
};

#endif

