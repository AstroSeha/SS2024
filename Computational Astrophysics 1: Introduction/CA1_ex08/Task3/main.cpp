#include <iostream>

double f1(double x, double y1, double y2);
double f2(double x, double y1, double y2);
double shooting(double a, double b, double alpha, double beta, double h, int n, double tol);
void ode_euler(double (*f1)(double, double, double), double (*f2)(double, double, double), double y1[], double y2[], double x[], double h, int n);

int main() {
    double a = 0.0;
    double b = 1.0;
    double alpha = 0.0;
    double beta = 1.0;
    double h = 0.01;
    int n = static_cast<int>((b - a) / h) + 1;
    double tol = 1e-6;

    shooting(a, b, alpha, beta, h, n, tol);

    return 0;
}
