#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void initial(double& x0, double& y0, double& vx0, double& vy0, double& dt, int& nout);
void euler(double x[], double y[], double vx[], double vy[], double r[], int N, double dt);
void output();

int main() {
    double x0, y0, vx0, vy0, dt;
    int nout;

    initial(x0, y0, vx0, vy0, dt, nout);

    double three_periods = 3* 2 * M_PI;
    int N = static_cast<int>(three_periods / dt);

    double* t = new double[N];
    double* x = new double[N];
    double* y = new double[N];
    double* vx = new double[N];
    double* vy = new double[N];
    double* r = new double[N];

    t[0] = 0.0;
    x[0] = x0;
    y[0] = y0;
    vx[0] = vx0;
    vy[0] = vy0;

    euler(x, y, vx, vy, r, N, dt);

    for (int i = 1; i < N; ++i) {
        t[i] = t[i-1] + dt;
    }

    ofstream outfile("orbit_data.txt");
    for (int i = 0; i < N; i += nout) {
        outfile << t[i] << " " << x[i] << " " << y[i] << " " << vx[i] << " " << vy[i] << endl;
    }
    outfile.close();

    output();

    delete[] t;
    delete[] x;
    delete[] y;
    delete[] vx;
    delete[] vy;
    delete[] r;

    return 0;
}
