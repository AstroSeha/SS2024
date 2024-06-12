#include <iostream>
#include <cmath>

void ode_euler(double (*f1)(double, double, double), double (*f2)(double, double, double), double y1[], double y2[], double x[], double h, int n) {
    for (int i = 0; i < n - 1; ++i) {
        y1[i + 1] = y1[i] + h * f1(x[i], y1[i], y2[i]);
        y2[i + 1] = y2[i] + h * f2(x[i], y1[i], y2[i]);
        x[i + 1] = x[i] + h;
    }
}

double f1(double x, double y1, double y2) {
    return y2;
}

double f2(double x, double y1, double y2) {
    return -M_PI * M_PI / 4 * (y1 + 1);
}
