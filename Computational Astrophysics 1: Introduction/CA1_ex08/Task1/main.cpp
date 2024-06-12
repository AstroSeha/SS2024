#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

double f(double t) {
    return exp(-t);
}

double trapezoid_rule(double (*func)(double), double a, double b, int N) {
    double h = (b - a) / N;
    double sum = 0.5 * (func(a) + func(b));
    for (int i = 1; i < N; ++i) {
        sum += func(a + i * h);
    }
    return h * sum;
}

double simpson_rule(double (*func)(double), double a, double b, int N) {
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

int main() {
    double a = 0.0;
    double b = 1.0;
    double C_exact = 1.0 - exp(-1.0);
    const int num_N_values = 5;
    int N_values[num_N_values] = {2, 10, 20, 100, 1000};
    double errors_trapezoid[num_N_values];
    double errors_simpson[num_N_values];

    ofstream outfile("results.txt");

    for (int i = 0; i < num_N_values; ++i) {
        int N = N_values[i];
        double C_trapezoid = trapezoid_rule(f, a, b, N);
        double C_simpson = simpson_rule(f, a, b, N);
        errors_trapezoid[i] = (C_trapezoid - C_exact)/C_exact;
        errors_simpson[i] = (C_simpson - C_exact)/C_exact;
        outfile << N <<" " << errors_trapezoid[i] << " " << errors_simpson[i] << endl;
    }
    outfile.close();
    return 0;
}
