#include "grid.h"

Grid::Grid(double new_left, double new_right,
    double new_time, double new_time_step, double new_coor_step)
    : time(new_time), time_step(new_time_step), coor_step(new_coor_step),
    left(new_left), right(new_right)
{
    gridCol = (int)((right - left) / coor_step);
    gridRow = (int)((time - 0) / time_step);

    grid = new grid_vec (gridRow, vector<grid_t>(gridCol, 0));
}

Grid::~Grid()
{
    delete grid;
}

void Grid::initGrid()
{
    (*grid)[0][0] = leftBoundaryFunction(0);
    (*grid)[0][gridCol - 1] = rightBoundaryFunction(0);
    for (int x = 1; x < gridCol - 1; x++)
        (*grid)[0][x] = initFunction(left + x * coor_step);
}
