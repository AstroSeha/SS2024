#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void initial(double& x0, double& y0, double& vx0, double& vy0, double& dt, int& nout);
void euler_richardson(double x[], double y[], double vx[], double vy[], double r[], int N, double dt);
void euler_cromer(double x[], double y[], double vx[], double vy[], double r[], int N, double dt);
float energy(double x, double y, double vx, double vy);
void output();

int main() {
    double x0, y0, vx0, vy0, dt;
    int nout;

    initial(x0, y0, vx0, vy0, dt, nout);

    double period = 2 * M_PI;
    int N = static_cast<int>(period / dt);

    double* t = new double[N];
    double* x_euler = new double[N];
    double* y_euler = new double[N];
    double* vx_euler = new double[N];
    double* vy_euler = new double[N];
    double* r_euler = new double[N];
    double* x_cromer = new double[N];
    double* y_cromer = new double[N];
    double* vx_cromer = new double[N];
    double* vy_cromer = new double[N];
    double* r_cromer = new double[N];

    t[0] = 0.0;
    x_euler[0] = x_cromer[0] = x0;
    y_euler[0] = y_cromer[0] = y0;
    vx_euler[0] = vx_cromer[0] = vx0;
    vy_euler[0] = vy_cromer[0] = vy0;

    euler_richardson(x_euler, y_euler, vx_euler, vy_euler, r_euler, N, dt);
    euler_cromer(x_cromer, y_cromer, vx_cromer, vy_cromer, r_cromer, N, dt);

    for (int i = 1; i < N; ++i) {
        t[i] = t[i-1] + dt;
    }

    ofstream energyfile("energy_data.txt");
    for (int i = 0; i < N; i += nout) {
        double E_euler = energy(x_euler[i], y_euler[i], vx_euler[i], vy_euler[i]);
        double E_cromer = energy(x_cromer[i], y_cromer[i], vx_cromer[i], vy_cromer[i]);
        energyfile << t[i] << " " << E_euler << " " << E_cromer << endl;
    }
    energyfile.close();

    output();

    delete[] t;
    delete[] x_euler;
    delete[] y_euler;
    delete[] vx_euler;
    delete[] vy_euler;
    delete[] r_euler;
    delete[] x_cromer;
    delete[] y_cromer;
    delete[] vx_cromer;
    delete[] vy_cromer;
    delete[] r_cromer;

    return 0;
}
