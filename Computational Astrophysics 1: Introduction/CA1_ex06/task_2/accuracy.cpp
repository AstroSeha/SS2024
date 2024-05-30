#include <cmath>
#include <iostream>
#include "euler.cpp"
#include "euler_cromer.cpp"
#include "euler_richardson.cpp"
#include "rk4.cpp"
#include "energy.cpp"

using namespace std;

const int N = 100000;
const double dt = 1e-3;
const double T = 1.0; // Assuming a period of 1 year

void run_simulation(void (*method)(double[], double[], double[], double[], double[], int, double), double& rel_change) {
    double x[N], y[N], vx[N], vy[N], r[N];
    x[0] = 1.0;
    y[0] = 0.0;
    vx[0] = 0.0;
    vy[0] = 2 * M_PI;

    double E_initial = energy(x[0], y[0], vx[0], vy[0]);

    method(x, y, vx, vy, r, N, dt);

    double E_final = energy(x[N-1], y[N-1], vx[N-1], vy[N-1]);

    rel_change = abs((E_final - E_initial) / E_initial);
}

int main() {
    double rel_change_euler, rel_change_euler_cromer, rel_change_euler_richardson, rel_change_rk4;

    run_simulation(euler, rel_change_euler);
    run_simulation(euler_cromer, rel_change_euler_cromer);
    run_simulation(euler_richardson, rel_change_euler_richardson);
    run_simulation(runge_kutta, rel_change_rk4);

    cout << "Relative change in energy after 100 orbits:" << endl;
    cout << "Euler: " << rel_change_euler << endl;
    cout << "Euler-Cromer: " << rel_change_euler_cromer << endl;
    cout << "Euler-Richardson: " << rel_change_euler_richardson << endl;
    cout << "RK4: " << rel_change_rk4 << endl;

    return 0;
}
