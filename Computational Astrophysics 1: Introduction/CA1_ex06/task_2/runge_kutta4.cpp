#include <cmath>
#include "constants.h"

using namespace std;

void runge_kutta4(double x[], double y[], double vx[], double vy[], double r[], int N, double dt) {
    for (int i = 0; i < N - 1; i++) {
        r[i] = sqrt(x[i] * x[i] + y[i] * y[i]);

        double ax1 = -GM * x[i] / pow(r[i], 3);
        double ay1 = -GM * y[i] / pow(r[i], 3);
        double vx1 = vx[i];
        double vy1 = vy[i];

        double x2 = x[i] + vx1 * dt / 2;
        double y2 = y[i] + vy1 * dt / 2;
        double r2 = sqrt(x2 * x2 + y2 * y2);
        double ax2 = -GM * x2 / pow(r2, 3);
        double ay2 = -GM * y2 / pow(r2, 3);
        double vx2 = vx[i] + ax1 * dt / 2;
        double vy2 = vy[i] + ay1 * dt / 2;

        double x3 = x[i] + vx2 * dt / 2;
        double y3 = y[i] + vy2 * dt / 2;
        double r3 = sqrt(x3 * x3 + y3 * y3);
        double ax3 = -GM * x3 / pow(r3, 3);
        double ay3 = -GM * y3 / pow(r3, 3);
        double vx3 = vx[i] + ax2 * dt / 2;
        double vy3 = vy[i] + ay2 * dt / 2;

        double x4 = x[i] + vx3 * dt;
        double y4 = y[i] + vy3 * dt;
        double r4 = sqrt(x4 * x4 + y4 * y4);
        double ax4 = -GM * x4 / pow(r4, 3);
        double ay4 = -GM * y4 / pow(r4, 3);
        double vx4 = vx[i] + ax3 * dt;
        double vy4 = vy[i] + ay3 * dt;

        vx[i + 1] = vx[i] + dt * (ax1 + 2 * ax2 + 2 * ax3 + ax4) / 6;
        vy[i + 1] = vy[i] + dt * (ay1 + 2 * ay2 + 2 * ay3 + ay4) / 6;
        x[i + 1] = x[i] + dt * (vx1 + 2 * vx2 + 2 * vx3 + vx4) / 6;
        y[i + 1] = y[i] + dt * (vy1 + 2 * vy2 + 2 * vy3 + vy4) / 6;
    }
}
