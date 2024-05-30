#include <iostream>
#include <cmath>
#include <fstream>
#include "euler.cpp"
#include "euler_cromer.cpp"
#include "euler_richardson.cpp"
#include "rk4.cpp"
#include "energy.cpp"
#include "initial.cpp"
#include "period.cpp"

using namespace std;

void run_simulation(void (*method)(double[], double[], double[], double[], double[], int, double), double rel_change[], double t[], double x0, double vy0, double dt, double T) {
    int N = 100 * T / dt;
    double* x = new double[N];
    double* y = new double[N];
    double* vx = new double[N];
    double* vy = new double[N];
    double* r = new double[N];

    x[0] = x0;
    y[0] = 0.0;
    vx[0] = 0.0;
    vy[0] = vy0;

    double E_initial = energy(x[0], y[0], vx[0], vy[0]);

    method(x, y, vx, vy, r, N, dt);

    for (int i = 0; i < N; i++) {
        rel_change[i] = abs((energy(x[i], y[i], vx[i], vy[i]) - E_initial) / E_initial);
        t[i] = i * dt;
    }

    delete[] x;
    delete[] y;
    delete[] vx;
    delete[] vy;
    delete[] r;
}

int main() {
    double x0, vy0, dt;

    initial(x0, vy0, dt);
    double T = theoretical_period(x0, vy0, N, dt);
    int N = 100 * T / dt;

    double* rel_change_euler = new double[N];
    double* rel_change_euler_cromer = new double[N];
    double* rel_change_euler_richardson = new double[N];
    double* rel_change_rk4 = new double[N];
    double* t = new double[N];

    run_simulation(euler, rel_change_euler, t, x0, vy0, dt, T);
    run_simulation(euler_cromer, rel_change_euler_cromer, t, x0, vy0, dt, T);
    run_simulation(euler_richardson, rel_change_euler_richardson, t, x0, vy0, dt, T);
    run_simulation(runge_kutta, rel_change_rk4, t, x0, vy0, dt, T);

    ofstream outfile;
    outfile.open("accuracy.dat");
    for (int i = 0; i < N; i++) {
        outfile << t[i] << " " << rel_change_euler[i] << " " << rel_change_euler_cromer[i] << " " << rel_change_euler_richardson[i] << " " << rel_change_rk4[i] << endl;
    }
    outfile.close();

    delete[] rel_change_euler;
    delete[] rel_change_euler_cromer;
    delete[] rel_change_euler_richardson;
    delete[] rel_change_rk4;
    delete[] t;

    cout << "Data saved to accuracy.dat" << endl;

    return 0;
}
