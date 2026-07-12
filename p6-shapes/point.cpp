// point.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include "point.h"
#include "grid.h"

Point::Point(int x, int y, char c) : Shape(x, y)
{
    m_c = c;
}

void Point::draw(Grid &grid)
{
    grid.set(m_x, m_y, m_c);
}