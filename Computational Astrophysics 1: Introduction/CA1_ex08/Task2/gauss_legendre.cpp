#include <cmath>

// calculate nodes and weights 
void legendre_roots_weights(int N, double *roots, double *weights) {
    for (int i = 0; i < N; ++i) {
        double x = cos(M_PI * (i + 0.75) / (N + 0.5));
        double p1 = 1.0, p2 = 0.0;

        for (int j = 0; j < N; ++j) {
            double p3 = p2;
            p2 = p1;
            p1 = ((2.0 * j + 1.0) * x * p2 - j * p3) / (j + 1);
        }

        double pp = N * (x * p1 - p2) / (x * x - 1.0);
        x -= p1 / pp;
        roots[i] = x;

        p1 = 1.0, p2 = 0.0;
        for (int j = 0; j < N; ++j) {
            double p3 = p2;
            p2 = p1;
            p1 = ((2.0 * j + 1.0) * x * p2 - j * p3) / (j + 1);
        }
        pp = N * (x * p1 - p2) / (x * x - 1.0);
        weights[i] = 2.0 / ((1.0 - x * x) * pp * pp);
    }
}

double gauss_legendre(double (*func)(double), double a, double b, int N) {
    double roots[N];
    double weights[N];
    legendre_roots_weights(N, roots, weights);
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        double x = 0.5 * (b - a) * roots[i] + 0.5 * (a + b);
        sum += weights[i] * func(x);
    }
    return 0.5 * (b - a) * sum;
}
