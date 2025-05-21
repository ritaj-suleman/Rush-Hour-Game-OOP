#ifndef ROAD_H
#define ROAD_H

#include "GameObject.h"
#include<string>
using std::string;

class Road : public GameObject {
public:
    
    Road();
    Road(int _x, int _y);
    
    void draw();
    string getType() const;
};

#endif
