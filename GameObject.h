#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
using std::string;

class GameObject {
public:
    int x, y;           // Position coordinates
    int width, height;  // Dimensions
    bool isActive;      // Active status flag

    GameObject();
    GameObject(int _x, int _y, int _w, int _h);
    
    virtual void draw();
    virtual void update();
    virtual bool checkCollision(GameObject* other);
    virtual string getType() const = 0;
};

#endif
