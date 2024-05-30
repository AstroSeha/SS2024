#include <cmath>
#include "constants.h"

using namespace std;

double energy(double x, double y, double vx, double vy) {
    double r = sqrt(x * x + y * y);
    double v2 = vx * vx + vy * vy;
    return 0.5 * v2 - GM / r;
}
