#include <iostream>
#include <cmath>
#include <fstream>

#include "constants.h"

using namespace std;
 
void initial(double& x0, double& vy0, double& dt);
double theoretical_period(double x0, double vy0);
void run_simulation(void (*method)(double[], double[], double[], double[], double[], int, double), double rel_change[], double t[], double x0, double vy0, double dt, double T);
void run_simulation_float(void (*method)(float[], float[], float[], float[], float[], int, float), float rel_change[], double t[], double x0, double vy0, float dt, double T);
void euler(double x[], double y[], double vx[], double vy[], double r[], int N, double dt);
void euler_cromer(double x[], double y[], double vx[], double vy[], double r[], int N, double dt);
void euler_richardson(double x[], double y[], double vx[], double vy[], double r[], int N, double dt);
void runge_kutta4(double x[], double y[], double vx[], double vy[], double r[], int N, double dt);
void runge_kutta4_float(float x[], float y[], float vx[], float vy[], float r[], int N, float dt);
double energy(double x, double y, double vx, double vy);

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

void run_simulation_float(void (*method)(float[], float[], float[], float[], float[], int, float), float rel_change[], double t[], double x0, double vy0, float dt, double T) {
    int N = 100 * T / dt;
    float* x = new float[N];
    float* y = new float[N];
    float* vx = new float[N];
    float* vy = new float[N];
    float* r = new float[N];

    x[0] = x0;
    y[0] = 0.0;
    vx[0] = 0.0;
    vy[0] = vy0;

    float E_initial = energy(x[0], y[0], vx[0], vy[0]);

    method(x, y, vx, vy, r, N, dt);

    for (int i = 0; i < N; i++) {
        rel_change[i] = fabs((energy(x[i], y[i], vx[i], vy[i]) - E_initial) / E_initial);
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

    // orbital period
    double T = theoretical_period(x0, vy0);
   
    // duration = 100 orbits
    int N = 100 * T / dt;

    double* rel_change_euler = new double[N];
    double* rel_change_euler_cromer = new double[N];
    double* rel_change_euler_richardson = new double[N];
    double* rel_change_rk4 = new double[N];
    float* rel_change_rk4_f = new float[N];
    double* t = new double[N];

    run_simulation(euler, rel_change_euler, t, x0, vy0, dt, T);
    run_simulation(euler_cromer, rel_change_euler_cromer, t, x0, vy0, dt, T);
    run_simulation(euler_richardson, rel_change_euler_richardson, t, x0, vy0, dt, T);
    run_simulation(runge_kutta4, rel_change_rk4, t, x0, vy0, dt, T);
    run_simulation_float(runge_kutta4_float, rel_change_rk4_f, t, x0, vy0, dt, T);

    ofstream outfile("accuracy.dat");
    if (!outfile) {
        cerr << "Error opening file accuracy.dat" << endl;
        return 1;
    }
    for (int i = 0; i < N; i++) {
        t[i] = dt * i;
        outfile << t[i] << " " << rel_change_euler[i] << " " << rel_change_euler_cromer[i] << " " << rel_change_euler_richardson[i] << " " << rel_change_rk4[i] << " " << rel_change_rk4_f[i] << endl;
    }
    outfile.close();

    delete[] rel_change_euler;
    delete[] rel_change_euler_cromer;
    delete[] rel_change_euler_richardson;
    delete[] rel_change_rk4;
    delete[] rel_change_rk4_f;
    delete[] t;

    return 0;
}
