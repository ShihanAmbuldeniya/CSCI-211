// point.h
// Embuldeniya, Shihan
// cembuldeniyaarachch

#ifndef POINT_H
#define POINT_H

#include "shape.h"

class Point : public Shape
{
  private:
    char m_c; 

  public:
    //x, y = location, c = character to place there
    Point(int x, int y, char c);

    virtual void draw(Grid &grid);
};

#endif
