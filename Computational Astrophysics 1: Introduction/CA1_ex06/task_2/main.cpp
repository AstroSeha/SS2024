#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void initial(double& x0, double& T, double& a_initial);
void euler_richardson(double x[], double y[], double vx[], double vy[], double r[], int N, double dt);
void perihelion_aphelion(double x[], double y[], double vx[], double vy[], double r[], double a, double T, int N, double dt);

int main() {
    double x0, y0, vx0, vy0, a_initial, T, a;
    y0 = 0.0;
    vx0 = 0.0;
    double dt = 1e-3;
    const int N = 1e+5;

    initial(x0, T, a_initial);

    double* x = new double[N];
    double* y = new double[N];
    double* vx = new double[N];
    double* vy = new double[N];
    double* r = new double[N];
    a = a_initial;

    x[0] = x0;
    y[0] = y0;
    vx[0] = vx0;
    vy[0] = vy0;

    euler_richardson(x, y, vx, vy, r, N, dt);
    perihelion_aphelion(x, y, vx, vy, r, a, T, N, dt);


    delete[] x;
    delete[] y;
    delete[] vx;
    delete[] vy;
    delete[] r;

    return 0;
}
