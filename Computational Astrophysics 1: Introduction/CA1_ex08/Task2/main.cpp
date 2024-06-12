#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

double f1(double t) {
    return sin(100*t);
}

double f1(double t) {
    return (sin(100*t))**t;
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
    double b = 2*M_PI;
    const int num_N_values = 5;
    int N_values[num_N_values] = {2, 10, 20, 100, 1000};

    ofstream outfile("results_F1.txt");
    for (int i = 0; i < num_N_values; ++i) {
        int N = N_values[i];
        double C_trapezoid = trapezoid_rule(f1, a, b, N);
        double C_simpson = simpson_rule(f1, a, b, N);
        outfile << N <<" " << C_trapezoid << " " << C_simpson << endl;
    }
    outfile.close();

    ofstream outfile("results_F2.txt");
    for (int i = 0; i < num_N_values; ++i) {
        int N = N_values[i];
        double C_trapezoid = trapezoid_rule(f2, a, b, N);
        double C_simpson = simpson_rule(f2, a, b, N);
        outfile << N <<" " << C_trapezoid << " " << C_simpson << endl;
 \   }
    outfile.close();

    return 0;
}
