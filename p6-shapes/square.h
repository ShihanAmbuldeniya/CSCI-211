// square.h
// Embuldeniya, Shihan
// cembuldeniyaarachch

#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape
{
  private:
    int m_size; // side length of the square

  public:
    //x, y = top left of bounding box, size = side length
    Square(int x, int y, int size);

    //drawing this square into the given grid
    virtual void draw(Grid &grid);
};

#endif