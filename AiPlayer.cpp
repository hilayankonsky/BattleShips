#include "AiPlayer.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>


int AiPlayer::rand0to9() const
{
    return std::rand() % 10;
}

bool AiPlayer::canPlaceShip(int row, int col, int size, bool horizontal) const
{
    // getGrid() אצלכם לא const, אז עושים cast עדין
    Grid* g = const_cast<AiPlayer*>(this)->getGrid();

    // לא סומכים 100% על inBounds (כי יש באגים ב-Grid שלכם),
    // אז עושים בדיקה בסיסית שלנו:
    if (row < 0 || row >= 10 || col < 0 || col >= 10) return false;
    if (horizontal)
    {
        if (col + size > 10) return false;
    }
    else
    {
        if (row + size > 10) return false;
    }

    // בדיקת חפיפה:
    for (int i = 0; i < size; i++)
    {
        int r = row + (horizontal ? 0 : i);
        int c = col + (horizontal ? i : 0);
        if (g->isTileOccupied(r, c)) return false;
    }

    return true;
}

void AiPlayer::placeAllShips()
{
    Grid* g = getGrid();

    for (int i = 0; i < 5; i++)
    {
        bool placed = false;
        int size = getShips(i)->getSize();

        while (!placed)
        {
            int row = rand0to9();
            int col = rand0to9();
            bool horizontal = (std::rand() % 2 == 0);

            if (!canPlaceShip(row, col, size, horizontal))
                continue;

            // בדיוק כמו HumanPlayer: שומרים אינדקס ספינה כתו '0'..'4'
            char symbol = '0' + i;
            g->placeShip(row, col, size, horizontal, symbol);
            placed = true;
        }
    }

    std::cout << getPlayerName() << " placed all ships.\n";
}

void AiPlayer::makeMove(Player* opponent)
{
    int row, col;
    do
    {
        row = rand0to9();
        col = rand0to9();
    } while (alreadyTried[row][col]);

    alreadyTried[row][col] = true;

    char target = opponent->getGrid()->getCell(row, col);

    std::cout << "\n--- " << getPlayerName() << " attacks " << (char)('A' + row) << " " << col << " ---\n";

    if (target != '~' && target != 'X' && target != 'M')
    {
        std::cout << "HIT!\n";
        opponent->getGrid()->markHit(row, col);

        int shipIndex = target - '0';
        if (shipIndex >= 0 && shipIndex < 5)
        {
            opponent->getShips(shipIndex)->takeHit();
        }
    }
    else if (target == '~')
    {
        std::cout << "MISS!\n";
        opponent->getGrid()->markMiss(row, col);
    }
    else
    {
        // אמור לא לקרות בגלל alreadyTried, אבל שיהיה בטוח
        std::cout << "Already shot there.\n";
    }

    std::cout << "--- Opponent's Board (Status) ---\n";
    opponent->getGrid()->printGrid();

    std::cout << "--- AI Board ---\n";
    this->getGrid()->printOpponentView();
}
