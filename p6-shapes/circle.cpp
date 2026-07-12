// circle.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include "circle.h"
#include "grid.h"

Circle::Circle(int x, int y) : Shape(x, y) {}

void Circle::draw(Grid &grid)
{
    // Circle pattern

    // Row 0: " oo"
    // Row 1: "o  o"
    // Row 2: "o  o"
    // Row 3: " oo"

    // Row 0
    grid.set(m_x + 1, m_y + 0, 'o');
    grid.set(m_x + 2, m_y + 0, 'o');

    // Row 1
    grid.set(m_x + 0, m_y + 1, 'o');
    grid.set(m_x + 3, m_y + 1, 'o');

    // Row 2
    grid.set(m_x + 0, m_y + 2, 'o');
    grid.set(m_x + 3, m_y + 2, 'o');

    // Row 3
    grid.set(m_x + 1, m_y + 3, 'o');
    grid.set(m_x + 2, m_y + 3, 'o');
}