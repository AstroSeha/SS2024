#include <cmath>
#include "constants.h"
using namespace std;

// Euler method (explicit method)
// update the positions first and then the velocities
void euler(double x[], double y[], double vx[], double vy[], double r[], int N, double dt) {
    for (int i = 0; i < N-1; i++) {
        r[i] = sqrt(x[i]*x[i] + y[i]*y[i]);
        double ax = -GM * x[i] / pow(r[i], 3);
        double ay = -GM * y[i] / pow(r[i], 3);
        x[i+1] = x[i] + vx[i] * dt; 
        y[i+1] = y[i] + vy[i] * dt;
        vx[i+1] = vx[i] + ax * dt;
        vy[i+1] = vy[i] + ay * dt;
    }
}
