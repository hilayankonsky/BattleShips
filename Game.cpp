#include "Game.hpp"
#include <iostream>

Game::Game(Player* p1, Player* p2) : player1(p1), player2(p2) {}

void Game::setup()
{
    std::cout << "\n=== Setup: Player 1 placing ships ===\n";
    player1->placeAllShips();

    std::cout << "\n=== Setup: Player 2 placing ships ===\n";
    player2->placeAllShips();
}

bool Game::isGameOver() const
{
    return player1->allShipsSunk() || player2->allShipsSunk();
}

void Game::start()
{
    std::cout << "\n=== Game Start ===\n";

    while (!isGameOver())
    {
        player1->makeMove(player2);
        if (player2->allShipsSunk())
        {
            std::cout << "\n*** " << player1->getPlayerName() << " WINS! ***\n";
            return;
        }

        player2->makeMove(player1);
        if (player1->allShipsSunk())
        {
            std::cout << "\n*** " << player2->getPlayerName() << " WINS! ***\n";
            return;
        }
    }
}
