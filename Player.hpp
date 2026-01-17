#pragma once
#include "Grid.hpp"
class Player
{
private:
    char* playerName;
    Ship* ships[5];
    Grid grid;
public:
    Player(const char* name);
    virtual ~Player();
    virtual void placeAllShips() = 0;
    virtual void makeMove(Player* opponent) = 0;
    bool allShipsSunk() const;
    Grid* getGrid(); 
    Ship* getShips(int index)const;
    const char* getPlayerName() const;
};
class HumanPlayer : public Player
{
    public:
            HumanPlayer(const char* name) : Player(name){}
            virtual void placeAllShips();
            virtual void makeMove(Player* opponent);
};

