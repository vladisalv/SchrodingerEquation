#include "options.h"
#include "schrodinger.h"

int main(int argc, char *argv[])
{
    Options options(argc, argv);
    if (options.isErrorMode())
        options.helpAndExit();

    Schrodinger schrodingerEquation(options.getLeftBoundary(),
                      options.getRightBoundary(),
                      options.getTime(),
                      options.getTimeStep(),
                      options.getCoordStep()
                     );

    if (options.isExplicitScheme()) {
        schrodingerEquation.solveEquation();
        schrodingerEquation.writePlot();
    }
    if (options.isImplicitScheme()) {
        schrodingerEquation.solveEquation();
        schrodingerEquation.writePlot();
    }

    return 0;
}
