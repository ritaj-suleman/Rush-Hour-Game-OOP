#include "constants.h"
#include "util.h"

const float ROAD_COLOR[] = {1, 1, 1}; // White
const float BUILDING_COLOR[] = {0, 0, 0}; // Black
const float TAXI_COLOR[] = {1, 0, 0}; // Red
const float DELIVERY_COLOR[] = {0, 0, 1}; // Blue
const float PASSENGER_COLOR[] = {0.7f, 0.5f, 0.9f}; // Purple
const float PACKAGE_COLOR[] = {0.6f, 0.3f, 0.0f}; // Brown
const float FUELSTATION_COLOR[] = {1, 0.5, 0.0f}; // Orange
const float STATION_COLOR[] = {0.5, 0.5, 0.5}; // Gray
const float OBSTACLE_COLOR[] = {1.0f, 0.0f, 0.5f}; // Hot Pink
const float MENU_BG_COLOR[] = {0.957f, 0.675f, 0.718f}; // pink
const float MENU_TEXT_COLOR[] = {1, 1, 1}; // White
const float HUD_BG_COLOR[] = {0.898f, 0.596f, 0.608f, 0.7f}; // Semi-transparent pink
const float HUD_TEXT_COLOR[] = {1, 1, 1}; // White

const int cityGrid[GRID_SIZE][GRID_SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 0 (all road)
    {0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0}, // Row 1
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0}, // Row 2
    {0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0}, // Row 3
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // Row 4
    {0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0}, // Row 5
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // Row 6
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0}, // Row 7
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // Row 8
    {0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0}, // Row 9
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // Row 10
    {0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0}, // Row 11
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 12
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0}, // Row 13
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0}, // Row 14
    {0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0}, // Row 15
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}, // Row 16
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0}, // Row 17
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 18
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // Row 19 (all road)
};

void DrawCar(int x, int y, int size, float* color) {
    // Convert game-world Y to screen Y (subtract HUD_HEIGHT)
    int screenY = y - HUD_HEIGHT;
    
    // Car body (all coordinates now use screenY)
    int carWidth = size;
    int carHeight = size * 0.6;
    
    // Main body (using screenY)
    DrawRoundRect(x - carWidth/2, screenY - carHeight/2, 
                carWidth, carHeight, color, 5);
    
    // Windows (using same screenY conversion)
    float windowColor[] = {0.8, 0.8, 0.9};
    DrawRoundRect(x - carWidth/3, screenY - carHeight/4, 
                carWidth*0.66, carHeight/3, windowColor, 3);
    
    // Wheels (using same screenY conversion)
    int wheelSize = size/5;
    DrawCircle(x - carWidth/3, screenY + carHeight/2 + 2, wheelSize, colors[BLACK]);
    DrawCircle(x + carWidth/3, screenY + carHeight/2 + 2, wheelSize, colors[BLACK]);

    // Roof light (if taxi)
    if (color == TAXI_COLOR) {
        float lightColor[] = {1, 1, 0.5};
        DrawRoundRect(x - 5, screenY - carHeight/2 + 5, 10, 8, lightColor, 3);
    }
}
