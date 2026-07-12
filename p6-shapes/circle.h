// circle.h
// Embuldeniya, Shihan
// cembuldeniyaarachch

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
  public:
    Circle(int x, int y);
    virtual void draw(Grid &grid);
};

#endif