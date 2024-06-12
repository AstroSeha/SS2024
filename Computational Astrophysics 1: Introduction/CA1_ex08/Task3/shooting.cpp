#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void ode_euler(double (*f1)(double, double, double), double (*f2)(double, double, double), double y1[], double y2[], double x[], double h, int n);
double f1(double x, double y1, double y2);
double f2(double x, double y1, double y2);

double shooting(double a, double b, double alpha, double beta, double h, int n, double tol) {
    double x[n], y1_a[n], y2_a[n], y1_b[n], y2_b[n], y1_c[n], y2_c[n];
    double z_a = (beta - alpha) / (b - a);
    double z_b = z_a + 0.01;

    x[0] = a;
    y1_a[0] = alpha;
    y2_a[0] = z_a;

    y1_b[0] = alpha;
    y2_b[0] = z_b;

    ode_euler(f1, f2, y1_a, y2_a, x, h, n);
    ode_euler(f1, f2, y1_b, y2_b, x, h, n);

    double F_a = y1_a[n - 1] - beta;
    double F_b = y1_b[n - 1] - beta;

    while (fabs(F_b - F_a) > tol) {
        double z_c = z_b - F_b * (z_b - z_a) / (F_b - F_a);

        y1_c[0] = alpha;
        y2_c[0] = z_c;

        ode_euler(f1, f2, y1_c, y2_c, x, h, n);

        double F_c = y1_c[n - 1] - beta;

        z_a = z_b;
        z_b = z_c;

        F_a = F_b;
        F_b = F_c;
    }

    ofstream file("results.txt");
    for (int i = 0; i < n; ++i) {
        file << x[i] << " " << y1_b[i] << endl;
    }
    file.close();

    return z_b;
}
