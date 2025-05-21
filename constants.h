#ifndef CONSTANTS_H
#define CONSTANTS_H

#define HUD_HEIGHT 40
#define TOTAL_HEIGHT (GRID_SIZE * CELL_SIZE + HUD_HEIGHT)

// Constants
#define MAX_BUILDINGS 500
#define MAX_ROADS 600
#define MAX_STATIONS 5
#define MAX_CARS 15
#define MAX_OBSTACLES 15
#define MAX_PASSENGERS 10
#define MAX_PACKAGES 10

// Direction constants
#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

// Game mode constants
#define MODE_TAXI 0
#define MODE_DELIVERY 1

// Game state constants
#define STATE_MENU 0
#define STATE_PLAYING 1
#define STATE_PAUSED 2
#define STATE_GAMEOVER 3
#define STATE_LEADERBOARD 4

// Grid and cell constants
#define GRID_SIZE 20
#define CELL_SIZE 40

void DrawCar(int x, int y, int size, float* color);

extern const float ROAD_COLOR[3];
extern const float BUILDING_COLOR[3];
extern const float TAXI_COLOR[3];
extern const float DELIVERY_COLOR[3];
extern const float PASSENGER_COLOR[3];
extern const float PACKAGE_COLOR[3];
extern const float FUELSTATION_COLOR[3];
extern const float STATION_COLOR[3];
extern const float OBSTACLE_COLOR[3];
extern const float MENU_BG_COLOR[3];
extern const float MENU_TEXT_COLOR[3];
extern const float HUD_BG_COLOR[4];
extern const float HUD_TEXT_COLOR[3];

extern const int cityGrid[GRID_SIZE][GRID_SIZE];

#endif

