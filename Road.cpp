#include "Road.h"
#include "util.h"
#include "constants.h"

    Road::Road() : GameObject(){}
    
    Road::Road(int _x, int _y) : 
        GameObject(_x, _y, CELL_SIZE, CELL_SIZE){}
    
    void Road::draw() {
        if (!isActive) return;
        
    int screenX = x * CELL_SIZE;
    int screenY = y * CELL_SIZE ;

    DrawSquare(screenX, screenY, CELL_SIZE, ROAD_COLOR);
    }
    
    string Road::getType() const  { return "Road"; }
    
 

