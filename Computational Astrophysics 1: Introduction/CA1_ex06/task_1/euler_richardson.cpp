#include <cmath>

using namespace std;

const double GM = 4 * M_PI * M_PI;

// Euler-Richardson method (midpoint method)
void euler_richardson(double x[], double y[], double vx[], double vy[], double r[], int N, double dt) {
    for (int i = 0; i < N-1; i++) {
        r[i] = sqrt(x[i] * x[i] + y[i] * y[i]);
        double ax = -GM * x[i] / pow(r[i], 3);
        double ay = -GM * y[i] / pow(r[i], 3);

        // midpoint values
        double x_mid = x[i] + 0.5 * vx[i] * dt;
        double y_mid = y[i] + 0.5 * vy[i] * dt;
        double r_mid = sqrt(x_mid * x_mid + y_mid * y_mid);
        double ax_mid = -GM * x_mid / pow(r_mid, 3);
        double ay_mid = -GM * y_mid / pow(r_mid, 3);
        double vx_mid = vx[i] + 0.5 * ax * dt;
        double vy_mid = vy[i] + 0.5 * ay * dt;

        // Update using midpoint values
        x[i+1] = x[i] + vx_mid * dt;
        y[i+1] = y[i] + vy_mid * dt;
        vx[i+1] = vx[i] + ax_mid * dt;
        vy[i+1] = vy[i] + ay_mid * dt;
    }
}
