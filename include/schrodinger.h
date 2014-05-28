#ifndef __SCHRODINGER_HEADER__
#define __SCHRODINGER_HEADER__

#include "types.h"
#include "grid.h"
#include "definition_func.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Schrodinger : public Grid {
public:
    Schrodinger(double left, double right, double time, double time_step, double coor_step);
    ~Schrodinger();

    void solveEquation();
    void writePlot();
};

#endif /* __SCHRODINGER_HEADER__ */
