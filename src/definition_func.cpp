#include "definition_func.h"

grid_t initFunction(double x)
{
    return   exp(250 * (-(x-0.2)*(x-0.2))) * 2 * x;
    //return exp(-0.5 * 100 * x * x);
    //return x;
    //return sin(x * M_PI);
}

grid_t leftBoundaryFunction(double t)
{
    return 0;
    //return t;
    //return sin(t);
}

grid_t rightBoundaryFunction(double t)
{
    //return t;
    //return t;
    return 0;
    //return cos(t * 2 * M_PI);
}

double schrodingerFunction(double x, double t)
{
    return (x - 0.2) * (x - 0.2);
    //return x * x / 2;  //-15 * x * sin(t);
    //return x * cos(t * 2 * M_PI - M_PI / 2);
    //return 0.0;
    //return (-(x - 0.5) * (x - 0.5) + 1) * sin(-M_PI + t * 2 * M_PI);
}
