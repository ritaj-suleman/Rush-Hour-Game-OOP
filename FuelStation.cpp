#include "FuelStation.h"
#include "Car.h"
#include "Player.h"
#include "util.h"
#include "constants.h"

    FuelStation::FuelStation() : GameObject(), fuelPrice(2.0f) {}
    
    FuelStation::FuelStation(int _x, int _y) : GameObject(_x, _y, 30, 30), fuelPrice(2.0f) {}
    
    float FuelStation::calculateCost(float amount) {
        return amount * fuelPrice;
    }
    
    void FuelStation::draw() {
        if (!isActive) return;
        
    float drawX = x * CELL_SIZE + CELL_SIZE / 2;
    float drawY = y * CELL_SIZE + CELL_SIZE / 2 ;
        DrawSquare(drawX - width/2, drawY - height/2, width, FUELSTATION_COLOR);
        
        float pumpColor[] = {0.8, 0.8, 0.8}; // Light gray
        DrawRectangle(drawX - 5, drawY - 15, 10, 20, pumpColor);
    }
    
bool FuelStation::refuelCar(Car* car, Player* player, float amount) {
    
    float cost = this->calculateCost(amount);
    
    if (player->getMoney() >= cost) {
        float newFuel = min(car->fuelLevel + amount, car->maxFuel);
        
        car->fuelLevel = newFuel;
        player->updateMoney(-cost);
        return true;
    }
    return false;
}

string FuelStation::getType() const { return "FuelStation"; }

