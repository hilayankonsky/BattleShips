#pragma once
#include "Player.hpp"

class Game
{
private:
    Player* player1;
    Player* player2;

public:
    Game(Player* p1, Player* p2);

    void setup();
    void start();
    bool isGameOver() const;
};
