// triangle.h
// Embuldeniya, Shihan
// cembuldeniyaarachch

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape
{
  public:
    Triangle(int x, int y);
    virtual void draw(Grid &grid);
};

#endif
