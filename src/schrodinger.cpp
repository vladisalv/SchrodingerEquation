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

    cout << "schrodinger equation" << endl;

    double gamma = time_step / (coor_step * coor_step);
    grid_t g(0, -gamma / 2);
    grid_t im_time(0, time_step), im_gamma(1, gamma);

    for (int t = 1; t < gridRow; t++) {
        (*grid)[t][0] = leftBoundaryFunction(t * time_step);
        (*grid)[t][gridCol - 1] = rightBoundaryFunction(t * time_step);

        vector< grid_t > c(gridCol - 2, 0), f(gridCol - 2, 0);

        for (int x = 0; x < gridCol - 2; x++)
            c[x] = im_gamma - im_time * schrodingerFunction(left + (x + 1) * coor_step,
                                                                       t   * time_step);
        f[0] = -g * (*grid)[t][0];
        f[gridCol - 3] = -g * (*grid)[t][gridCol - 1];

        for (int x = 0; x < gridCol - 2; x++)
            f[x] += (*grid)[t - 1][x + 1];

        for (int x = 1; x < gridCol - 2; x++) {
            c[x] -= g * g / c[x - 1];
            f[x] -= g * f[x - 1] / c[x - 1];
        }

        (*grid)[t][gridCol - 2] = f[gridCol - 3] / c[gridCol - 3];
        for (int x = gridCol - 3; x > 0; x--)
            (*grid)[t][x] = (f[x - 1] - g * (*grid)[t][x + 1]) / c[x - 1];
    }
}

void Schrodinger::writePlot()
{
    double min, max;
    min = max = (*grid)[0][0].real();

    ofstream data("result/data");
    for (int x = 0; x < gridCol; x++) {
        data << left + x * coor_step << " ";
        for (int t = 0; t < gridRow; t++) {
            grid_t tmp = (*grid)[t][x];
            if (tmp.real() > max)
                max = tmp.real();
            if (tmp.imag() > max)
                max = tmp.imag();
            if (abs(tmp) > max)
                max = abs(tmp);
            if (tmp.real() < min)
                min = tmp.real();
            if (tmp.imag() < min)
                min = tmp.imag();
            if (abs(tmp) < min)
                min = abs(tmp);
            data << tmp.real() << " ";
            data << tmp.imag() << " ";
            data << abs(tmp)   << " ";
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
    plot << "    real = 3 * (i - 2) + 2" << endl;
    plot << "    imag = 3 * (i - 2) + 3" << endl;
    plot << "    abs  = 3 * (i - 2) + 4" << endl;
    plot << "    plot 'result/data' using 1:real w li lw 3 lt rgb 'blue', ";
    plot <<     "'result/data' using 1:imag w li lw 3 lt rgb 'green', ";
    plot <<     "'result/data' using 1:abs  w li lw 3 lt rgb 'red'" << endl;
    plot << "}" << endl;
    plot.close();

    system("gnuplot result/plot");
}
