#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

class Obstacle : public GameObject {
public:
    int type;  // 0 for tree, 1 for box
    
    Obstacle();
    Obstacle(int _x, int _y, int _type);
    
    int getObstacleType() ;
    void draw();
    string getType() const;
};

#endif
