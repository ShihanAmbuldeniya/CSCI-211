// square.cpp
// Embuldeniya, Shihan
// cembuldeniyaarachch

#include "square.h"
#include "grid.h" 

Square::Square(int x, int y, int size) : Shape(x, y) 
{
    m_size = size;
}

void Square::draw(Grid &grid)
{
    //Need to draw a square of size m_size using '*'

    for (int row = 0; row < m_size; row++)
    {
        for (int col = 0; col < m_size; col++)
        {
            bool top_or_bottom = (row == 0) || (row == m_size - 1);
            bool left_or_right = (col == 0) || (col == m_size - 1);

            if (top_or_bottom || left_or_right)
            {
                int x = m_x + col; // moving col steps to the right from m_x
                int y = m_y + row; // moving row steps down from m_y
                grid.set(x, y, '*');
            }
            // if it's not on the border, we do nothing 
        }
    }
}
