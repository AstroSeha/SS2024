#include <cmath>

double trapezoid(double (*func)(double), double a, double b, int N) {
    double h = (b - a) / N;
    double sum = 0.5 * (func(a) + func(b));
    for (int i = 1; i < N; ++i) {
        sum += func(a + i * h);
    }
    return h * sum;
}