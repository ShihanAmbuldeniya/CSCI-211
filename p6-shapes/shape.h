// shape.h
// Embuldeniya, Shihan
// cembuldeniyaarachch

#ifndef SHAPE_H
#define SHAPE_H

class Grid;   

class Shape
{
  protected:
    int m_x; // x coordinate of top left corner 
    int m_y; // y coordinate of top left corner

  public:
    Shape(int x, int y);
    virtual void draw(Grid &grid) = 0;
};

#endif