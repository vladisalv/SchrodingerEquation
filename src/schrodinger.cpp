#include "schrodinger.h"

Schrodinger::Schrodinger(double new_left, double new_right,
    double new_time, double new_time_step, double new_coor_step)
    : Grid(new_left, new_right, new_time, new_time_step, new_coor_step)
{
}

Schrodinger::~Schrodinger()
{
}

void Schrodinger::solveEquation()
{
    initGrid();

    /*
    if (type == 'e') {
        cout << "explicit_scheme" << endl;
        double gamma = time_step / (10 * coor_step * coor_step);
        for (int t = 1; t < gridRow; t++) {
            (*grid)[t][0] = leftBoundaryFunction(t * time_step);
            (*grid)[t][gridCol - 1] = rightBoundaryFunction(t * time_step);
            for (int x = 1; x < gridCol - 1; x++)
                (*grid)[t][x] = (*grid)[t-1][x]
                              + gamma * ((*grid)[t-1][x-1] - 2 * (*grid)[t-1][x] + (*grid)[t-1][x+1])
                              + gamma * time_step * heatFunction(left + x * coor_step, t * time_step);
        }
    } else if (type == 'i') {
        cout << "implicit_scheme" << endl;
        double gamma = time_step / (coor_step * coor_step);
        for (int t = 1; t < gridRow; t++) {
            (*grid)[t][0] = leftBoundaryFunction(t * time_step);
            (*grid)[t][gridCol - 1] = rightBoundaryFunction(t * time_step);

            vector< grid_t > a(gridCol - 2, 0), b(gridCol - 2, 1 + 2 * gamma);

            a[0] = gamma * (*grid)[t][0];
            a[gridCol - 3] = gamma * (*grid)[t][gridCol - 1];
            for (int x = 0; x < gridCol - 2; x++)
                a[x] += (*grid)[t - 1][x + 1]
                     + time_step * heatFunction(left + (x + 1) * coor_step,
                                                            t * time_step);

            for (int x = 1; x < gridCol - 2; x++) {
                b[x] -= gamma * gamma / b[x - 1];
                a[x] -= -gamma * a[x - 1] / b[x - 1];
            }

            (*grid)[t][gridCol - 2] = a[gridCol - 3] / b[gridCol - 3];
            for (int x = gridCol - 3; x > 0; x--)
                (*grid)[t][x] = (a[x - 1] + gamma * (*grid)[t][x + 1]) / b[x - 1];
        }
    }
    */
}

void Schrodinger::writePlot()
{
    grid_t min, max;
    min = max = (*grid)[0][0];

    ofstream data("result/data");
    for (int x = 0; x < gridCol; x++) {
        data << left + x * coor_step << " ";
        for (int t = 0; t < gridRow; t++) {
            grid_t tmp = (*grid)[t][x];
            if (tmp > max)
                max = tmp;
            if (tmp < min)
                min = tmp;
            data << tmp << " ";
        }
        data << endl;
    }
    data.close();

    cout << "gridRow = " << gridRow << endl;
    cout << "gridCol = " << gridCol << endl;
    cout << "min = " << min << endl;
    cout << "max = " << max << endl;

    ofstream plot("result/plot");
    plot << "set term gif animate enhanced" << endl;
    plot << "set nokey" << endl;
    plot << "set output 'result/graphic.gif'" << endl;
    plot << "set xrange [" << left << ":" << right << "]" << endl;
    plot << "set yrange [" << min  << ":" << max << "]" << endl;
    plot << "progress = 0" << endl;
    plot << "total = " << gridRow + 1 << endl;
    plot << "do for [i = 2 : total] {" << endl;
    plot << "    plot 'result/data' using 1:i w li lw 3 lt rgb 'purple'" << endl;
    plot << "}" << endl;
    plot.close();

    system("gnuplot result/plot");
}
