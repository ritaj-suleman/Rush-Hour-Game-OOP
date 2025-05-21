#include "GameObject.h"
#include "util.h"

GameObject::GameObject() : x(0), y(0), width(0), height(0), isActive(true) {}

GameObject::GameObject(int _x, int _y, int _w, int _h) : x(_x), y(_y), width(_w), height(_h), isActive(true) {}

void GameObject::draw() {
    DrawRectangle(x, y, width, height, colors[RED]);
}

void GameObject::update() {
}

bool GameObject::checkCollision(GameObject* other) {
    if (!other) return false;
    return (x == other->x && y == other->y);
}
