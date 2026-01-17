#include <iostream>
#include "Grid.hpp"
using namespace std;

Grid::Grid()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cells[i][j] = '~';
        } 
    }
}

bool Grid::isTileOccupied(int row, int col)const
{
    return cells[row][col] != '~';
}

bool Grid::inBounds(int row, int col, int shipSize, bool horizontal) const
{
    if (row < 0 || row >= 10 || col < 0 || col >= 10)
        return false;

    if (horizontal)
    {
        if (col + shipSize > 10) return false;
    }
    else
    {
        if (row + shipSize > 10) return false;   
    }

    return true;
}

void Grid::placeShip(int row, int col, int shipSize, bool horizontal, char symbol)
{
    if (!inBounds(row, col, shipSize, horizontal)) return;
    if (horizontal)
    {
        for (int i = 0; i < shipSize; i++)
        {
            cells[row][col + i] = symbol;
        }
    }
        else
        {
            for (int i = 0; i < shipSize; i++)
            {
                cells[row + i][col] = symbol;
            }   
        }
}

void Grid::markHit(int row, int col)
{
    if (row < 0 || row >= 10 || col < 0 || col >= 10)
    {
       return ;
    }
    cells[row][col] = 'X'; 
}

void Grid::markMiss(int row, int col)
{
    if (row < 0 || row >= 10 || col < 0 || col >= 10)
    {
       return ;
    }
    cells[row][col] = 'M'; 
}

char Grid::getCell(int row, int col)const
{
    if (row < 0 || row >= 10 || col < 0 || col >= 10)
    {
       return '?';
    }
    return cells[row][col];
}

void Grid::printGrid()const
{
    cout<<"  0 1 2 3 4 5 6 7 8 9"<<endl;
    for (int i = 0; i < 10; i++)
    {
        cout<<(char)('A'+ i) << " ";
        for (int j = 0; j < 10; j++)
        {
            cout << cells[i][j] << " ";
        }
    cout << endl;
    }
}

void Grid::printOpponentView() const
{
    cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << (char)('A' + i) << " ";
        for (int j = 0; j < 10; j++)
        {
            char c = cells[i][j];

            // מציגים רק מידע "מותר" על יריב:
            // X = פגיעה, M = פספוס, וכל השאר ~
            if (c == 'X' || c == 'M')
                cout << c << " ";
            else
                cout << "~ ";
        }
        cout << endl;
    }
}

Grid::~Grid() {}
