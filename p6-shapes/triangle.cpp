// triangle.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include "triangle.h"
#include "grid.h"

Triangle::Triangle(int x, int y) : Shape(x, y) {}

void Triangle::draw(Grid &grid)
{
    // Pattern 
    // Row 0: "  +"
    // Row 1: " + +"
    // Row 2: "+++++"

    // Row 0: "  +"
    grid.set(m_x + 2, m_y + 0, '+');

    // Row 1: " + +"
    grid.set(m_x + 1, m_y + 1, '+');
    grid.set(m_x + 3, m_y + 1, '+');

    // Row 2: "+++++"
    for (int col = 0; col < 5; col++)
    {
        grid.set(m_x + col, m_y + 2, '+');
    }
}