#include "Player.hpp"
#include <cstring>
 Player::Player(const char* name)
 {
    if (name)
    {
        this->playerName =  new char [strlen(name) +1];
        strcpy(this->playerName, name);
    }
    else
    {
        playerName = nullptr;
    }
    
    this->ships[0] = new Carrier();
    this->ships[1] = new Battleship();
    this->ships[2] = new Cruiser();
    this->ships[3] = new Submarine();
    this->ships[4] = new Destroyer();
}
 Player::~Player()
{
    if (this->playerName)
    {
        delete [] this->playerName ;
    }
    for (int i = 0; i < 5; i++)
    {
        if (ships[i] != nullptr) 
        {
            delete ships[i];
        }
    }
}
bool Player::allShipsSunk() const
{
    for (int i = 0; i < 5; i++)
    {
        if (!ships[i]->isSunk())
        {
            return false ;
        }  
    }
    return true ;
}
Grid* Player ::getGrid() {return &grid;}
Ship* Player ::getShips(int index)const { return ships[index];}
const char* Player::getPlayerName() const { return playerName; }
