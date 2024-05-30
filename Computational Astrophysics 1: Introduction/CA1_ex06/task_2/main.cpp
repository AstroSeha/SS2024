#include <iostream>
#include <cmath>
#include "euler.cpp"
#include "euler_cromer.cpp"
#include "euler_richardson.cpp"
#include "rk4.cpp"
#include "energy.cpp"
#include "initial.cpp"
#include "period.cpp"

using namespace std;

void run_simulation(void (*method)(double[], double[], double[], double[], double[], int, double), double& rel_change, double x0, double vy0, double dt, double T) {
    int N = 100 * T / dt;
    double* x = new double[N];
    double* y = new double[N];
    double* vx = new double[N];
    double* vy = new double[N];
    double* r = new double[N];
    double* rel_change_array = new double[N];

    x[0] = x0;
    y[0] = 0.0;
    vx[0] = 0.0;
    vy[0] = vy0;

    double E_initial = energy(x[0], y[0], vx[0], vy[0]);

    method(x, y, vx, vy, r, N, dt);

    for (int i = 0; i < N; i++) {
        rel_change_array[i] = abs(energy(x[i], y[i], vx[i], vy[i]) - E_initial) / E_initial;
    }  
    rel_change = rel_change_array[N-1];


    delete[] x;
    delete[] y;
    delete[] vx;
    delete[] vy;
    delete[] r;
}

int main() {
    double x0 = 1.0;
    double vy0 = 2 * M_PI;
    double dt = 1e-3;

    initial(x0, vy0, dt);
    double T = theoretical_period(x0, vy0);

    double rel_change_euler, rel_change_euler_cromer, rel_change_euler_richardson, rel_change_rk4;

    run_simulation(euler, rel_change_euler, x0, vy0, dt, T);
    run_simulation(euler_cromer, rel_change_euler_cromer, x0, vy0, dt, T);
    run_simulation(euler_richardson, rel_change_euler_richardson, x0, vy0, dt, T);
    run_simulation(runge_kutta, rel_change_rk4, x0, vy0, dt, T);

    cout << "Relative change in energy after 100 orbits:" << endl;
    cout << "Euler: " << rel_change_euler << endl;
    cout << "Euler-Cromer: " << rel_change_euler_cromer << endl;
    cout << "Euler-Richardson: " << rel_change_euler_richardson << endl;
    cout << "RK4: " << rel_change_rk4 << endl;

    return 0;
}
