#include "Player.h"
#include "Car.h"
#include "TaxiCar.h"
#include "DeliveryCar.h"
#include "util.h"
#include "constants.h"
#include<iostream>
using namespace std;

Player::Player() :
		name("Player"), 
		score(0), 
		money(0.0f), 
		currentRole(MODE_TAXI), 
		car(NULL) {}

Player::Player(string _name) :
		name(_name), 
		score(0), 
		money(0.0f), 
		currentRole(MODE_TAXI), 
		car(NULL) {}

void Player::changeRole(int role) {
	cout << "Changing role to: " << (role == MODE_TAXI ? "Taxi" : "Delivery") << " of " << name << endl;

	// store current position and fuel
	float currentFuel = (car != nullptr) ? car->fuelLevel : 100.0f;
	int currentX = (car != nullptr) ? car->x : 0;
	int currentY = (car != nullptr) ? car->y : 0;

	if (car != nullptr) {
		delete car;
		car = nullptr;
	}

	//new car
	if (role == MODE_TAXI) {
		car = new TaxiCar(currentX, currentY, this);
		currentRole = MODE_TAXI;
	} else {
		car = new DeliveryCar(currentX, currentY, this);
		currentRole = MODE_DELIVERY;
	}

	car->fuelLevel = currentFuel;
	car->x = currentX;
	car->y = currentY;
	car->isPlayerControlled = true;
	car->isActive = true;

	currentRole = role;
}

void Player::updateScore(int points) {
	score += points;
}

void Player::updateMoney(float amount) {
	money += amount;
}

Car* Player::getCar() {
	return car;
}

float Player::getMoney() {
	return money;
}

void Player::resetPlayer() {
	score = 0;
	money = 0.0f;

	// reset or create car
	if (car != NULL) {
		car->resetCar();
	} else {
		if (currentRole == MODE_TAXI) {
			car = new TaxiCar();
		} else {
			car = new DeliveryCar();
		}
		car->isPlayerControlled = true;
	}
}

