#pragma once
#include "Player.hpp"

class AiPlayer : public Player
{
private:
    bool alreadyTried[10][10]{};  // לא לירות פעמיים על אותו תא

    int rand0to9() const;
    bool canPlaceShip(int row, int col, int size, bool horizontal) const;

public:
    AiPlayer(const char* name) : Player(name) {}

    void placeAllShips() override;
    void makeMove(Player* opponent) override;
};
