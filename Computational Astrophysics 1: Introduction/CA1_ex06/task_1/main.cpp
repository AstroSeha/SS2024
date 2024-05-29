#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

void initial(double& x0, double& y0, double& vx0, double& vy0, double& dt, int& nout);
void euler_richardson(double x[], double y[], double vx[], double vy[], double r[], int N, double dt);
void output(const string& filename);
double experimental_period(double x[], double y[], int N, double dt);
double theoretical_period(double x[], double y[], int N, double dt);
void log_results(double x0, double y0, double vx0, double vy0, double dt, int nout, double experimental_period, double theoretical_period);

int main() {
    double x0, y0, vx0, vy0, dt;
    int nout;

    initial(x0, y0, vx0, vy0, dt, nout);

    // set N to be a constant
    const int N = 1E+4;

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

    euler_richardson(x, y, vx, vy, r, N, dt);

    for (int i = 1; i < N; ++i) {
        t[i] = t[i-1] + dt;
    }

    // Create the filename 
    ostringstream filename;
    filename << "dt=" << dt << "_nout=" << nout << "_x=" << x0 << "_vy=" << vy0 << ".txt";

    ofstream outfile(filename.str());
    for (int i = 0; i < N; i += nout) {
        outfile << t[i] << " " << x[i] << " " << y[i] << " " << vx[i] << " " << vy[i] << endl;
    }
    outfile.close();



    double experimental_period_val = experimental_period(x, y, N, dt);
    double theoretical_period_val = theoretical_period(x, y, N, dt);

    cout << "Experimental period: " << experimental_period_val << " years" << endl;
    cout << "Theoretical period: " << theoretical_period_val << " years" << endl;

    log_results(x0, y0, vx0, vy0, dt, nout, experimental_period_val, theoretical_period_val);

    output(filename.str());

    delete[] t;
    delete[] x;
    delete[] y;
    delete[] vx;
    delete[] vy;
    delete[] r;

    return 0;
}
