#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// Set k = m = 1
int main() {
    int n = 101, nout = 5; //changes made here
    double t, v, v_old, x;
    double const dt = 2. * M_PI / double(n - 1);
    x = 1.; t = 0.; v = 0.;

    ofstream euler_file, analytic_file;
    euler_file.open("ex05_1b_euler.dat");
    analytic_file.open("ex05_1b_analytic.dat");

    for (int i = 0; i < n; ++i) {
        t = t + dt;
        v_old = v;
        v = v - x * dt;
        x = x + v_old * dt;
        double x_analytic = cos(t);  // Analytic solution for x(t)
        double v_analytic = -sin(t); // Analytic solution for v(t)
        if (i % nout == 0) // Print out only each nout step
            euler_file << t << " " << x << " " << v << endl;
        analytic_file << t << " " << x_analytic << " " << v_analytic << endl;
    }

    euler_file.close();
    analytic_file.close();
    return 0;
}
