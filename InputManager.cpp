#include "InputManager.h"
#include "GameEngine.h"
#include "Car.h"
#include "Game.h"
#include "Player.h"
#include "util.h"
#include "constants.h"
#include <GL/glut.h> 

#include<iostream>
using namespace std;

InputManager::InputManager(GameEngine *gameEng) :
		gameEngine(gameEng) {
	// Initialize all keys to not pressed
	for (int i = 0; i < 256; i++) {
		keyState[i] = false;
	}
}

void InputManager::handleKeyPress(int key) {
	cout << "working key press" << endl;
	keyState[key] = true;
}

void InputManager::handleKeyRelease(int key) {
	cout << "working key released" << endl;
	keyState[key] = false;
}

bool InputManager::isKeyPressed(int key) {
	return keyState[key];
}



