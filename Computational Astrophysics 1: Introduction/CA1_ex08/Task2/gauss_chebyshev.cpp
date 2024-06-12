#include <cmath>

double gauss_chebyshev(double (*func)(double), double a, double b, int N) {
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        double x = cos((2.0 * i - 1.0) * M_PI / (2.0 * N));
        double w = M_PI / N * (b - a) / 2.0;
        sum += func(x*(b-a)/2.0 + (a+b)/2.0) * w*sqrt(1.0 - x*x);
    }
    return sum;
}
