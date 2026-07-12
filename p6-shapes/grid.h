// grid.h
// Embuldeniya, Shihan
// cembuldeniyaarachch

#ifndef GRID_H
#define GRID_H

class Grid
{
  private:
    static const int WIDTH = 60;
    static const int HEIGHT = 24;
    // m_grid[row][col] = m_grid[y][x]
    char m_grid[HEIGHT][WIDTH];

  public:
    Grid();
    void set(int x, int y, char c);
    void print();
};

#endif