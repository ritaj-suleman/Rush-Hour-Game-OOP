#include "Building.h"
#include "util.h"
#include "constants.h"


Building::Building(int _x, int _y) :   GameObject(_x, _y, 30, 30) {}
    
void Building::draw() {
    if (!isActive) return;
    float drawX = x * CELL_SIZE + CELL_SIZE / 2;
    float drawY = y * CELL_SIZE + CELL_SIZE / 2 ;
    
    float buildingColor[] = {0.0f, 0.0f, 0.0f};  // Pure black
    DrawSquare(drawX - width/2, drawY - height/2, width, buildingColor);
    
    float windowColor[] = {0.7f, 0.7f, 0.9f};//blue
    int windowSize = width / 4;
    DrawSquare(drawX - width/3, drawY - height/3, windowSize, windowColor);
    DrawSquare(drawX + width/6, drawY - height/3, windowSize, windowColor);
    DrawSquare(drawX - width/3, drawY+ height/6, windowSize, windowColor);
    DrawSquare(drawX + width/6, drawY + height/6, windowSize, windowColor);
}

string Building::getType() const { return "Building"; }
