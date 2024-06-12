#include <cmath>

double simpson(double (*func)(double), double a, double b, int N) {
    double h = (b - a) / N;
    double sum = func(a) + func(b);
    for (int i = 1; i < N; i += 2) { // Odd terms
        sum += 4 * func(a + i * h);
    }
    for (int i = 2; i < N; i += 2) { // Even terms
        sum += 2 * func(a + i * h);
    }
    return h * sum / 3.0;
}