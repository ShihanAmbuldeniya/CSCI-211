// grid.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include "grid.h"
#include <iostream>
using namespace std;

Grid::Grid(){
    //Initializing the whole grid with spaces ' '
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            m_grid[y][x] = ' ';
        }
    }
}

void Grid::set(int x, int y, char c){
    //checking bounds first
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        m_grid[y][x] = c;
    }
    //if it's outside the grid, do nothing
}

void Grid::print(){
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            cout << m_grid[y][x];
        }
        cout << endl;  
    }
}