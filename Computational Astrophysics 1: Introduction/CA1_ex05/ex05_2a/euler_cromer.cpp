#include <cmath>

using namespace std;

const double GM = 4 * M_PI * M_PI;

// Euler-Cromer method
// update the velocities first and then the positions
void euler(double x[], double y[], double vx[], double vy[], double r[], int N, double dt) {
    for (int i = 0; i < N-1; i++) {
        r[i] = sqrt(x[i]*x[i] + y[i]*y[i]);
        vx[i+1] = vx[i] - (GM / pow(r[i], 3)) * x[i] * dt;
        vy[i+1] = vy[i] - (GM / pow(r[i], 3)) * y[i] * dt;
        x[i+1] = x[i] + vx[i+1] * dt; 
        y[i+1] = y[i] + vy[i+1] * dt;
    }
}
