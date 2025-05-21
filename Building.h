#ifndef BUILDING_H
#define BUILDING_H

#include "GameObject.h"
#include <string>
using std::string;

class Building : public GameObject {
public:
     Building(int _x, int _y);
    
    void draw();
    string getType() const;
};

#endif
