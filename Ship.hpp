#pragma once
#include <iostream>
using namespace std ;
class Ship
{
private:
    char* name;
    int size;
    int hitsTaken;
public:
    Ship(const char* shipName, int shipSize);
    ~Ship();
    virtual void takeHit();
    bool isSunk()const;
    int getSize()const;
    char* getName()const;
    
};
class Carrier : public Ship
{
    public:
            Carrier();
};
class Battleship : public Ship
{
    public:
            Battleship();
};
class Cruiser  : public Ship
{
    public:
            Cruiser();
};
class Submarine   : public Ship
{
    public:
            Submarine();
};
class Destroyer   : public Ship
{
    public:
            Destroyer();
};