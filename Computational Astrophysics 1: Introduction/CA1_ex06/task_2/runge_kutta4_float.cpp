#include <cmath>
#include "constants.h"

using namespace std;

// float variables
void runge_kutta4_float(float x[], float y[], float vx[], float vy[], float r[], int N, float dt) {
    for (int i = 0; i < N-1; i++) {
        r[i] = sqrt(x[i]*x[i] + y[i]*y[i]);
        float ax = -GM * x[i] / pow(r[i], 3);
        float ay = -GM * y[i] / pow(r[i], 3);
        float k1x = vx[i];
        float k1y = vy[i];
        float k1vx = ax;
        float k1vy = ay;
        float k2x = vx[i] + 0.5 * dt * k1vx;
        float k2y = vy[i] + 0.5 * dt * k1vy;
        float k2vx = -GM * (x[i] + 0.5 * dt * k1x) / pow(sqrt(pow(x[i] + 0.5 * dt * k1x, 2) + pow(y[i] + 0.5 * dt * k1y, 2)), 3);
        float k2vy = -GM * (y[i] + 0.5 * dt * k1y) / pow(sqrt(pow(x[i] + 0.5 * dt * k1x, 2) + pow(y[i] + 0.5 * dt * k1y, 2)), 3);
        float k3x = vx[i] + 0.5 * dt * k2vx;
        float k3y = vy[i] + 0.5 * dt * k2vy;
        float k3vx = -GM * (x[i] + 0.5 * dt * k2x) / pow(sqrt(pow(x[i] + 0.5 * dt * k2x, 2) + pow(y[i] + 0.5 * dt * k2y, 2)), 3);
        float k3vy = -GM * (y[i] + 0.5 * dt * k2y) / pow(sqrt(pow(x[i] + 0.5 * dt * k2x, 2) + pow(y[i] + 0.5 * dt * k2y, 2)), 3);
        float k4x = vx[i] + dt * k3vx;
        float k4y = vy[i] + dt * k3vy;
        float k4vx = -GM * (x[i] + dt * k3x) / pow(sqrt(pow(x[i] + dt * k3x, 2) + pow(y[i] + dt * k3y, 2)), 3);
        float k4vy = -GM * (y[i] + dt * k3y) / pow(sqrt(pow(x[i] + dt * k3x, 2) + pow(y[i] + dt * k3y, 2)), 3);
        x[i+1] = x[i] + dt/6. * (k1x + 2*k2x + 2*k3x + k4x);
        y[i+1] = y[i] + dt/6. * (k1y + 2*k2y + 2*k3y + k4y);
        vx[i+1] = vx[i] + dt/6. * (k1vx + 2*k2vx + 2*k3vx + k4vx);
        vy[i+1] = vy[i] + dt/6. * (k1vy + 2*k2vy + 2*k3vy + k4vy);
    }
}
