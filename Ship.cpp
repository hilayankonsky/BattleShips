#include"Ship.hpp"
#include <cstring>
Ship::Ship(const char* shipName, int shipSize):size(shipSize), hitsTaken(0)
{
    if (shipName)
    {
        this->name = new char[strlen(shipName)+1];
        strcpy(this->name, shipName);
        this->hitsTaken = 0;
    }
    else
    {
        this->name = nullptr;
    }   
}
 Ship::~Ship()
 {
    if (this->name)
    {
        delete[] this->name;
    }
 }
 void Ship::takeHit ()
 {
    this->hitsTaken++;
    if (isSunk())
    {
        cout << this->name << " has been sunk!" << endl;
    }
    
 }
 bool Ship::isSunk ()const
 {
     return this->hitsTaken >= this->size ;
 }
int Ship::getSize()const 
{
    return this->size;
}
char* Ship::getName()const
{
    return this->name;
}

Carrier::Carrier() : Ship("Carrier", 5) {}
Battleship::Battleship() : Ship("Battleship",4) {}
Cruiser::Cruiser() : Ship("Cruiser",3) {}
Submarine::Submarine() : Ship("Submarine",3) {}
Destroyer::Destroyer() :Ship("Destroyer",2) {}
