#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

double trapezoid(double (*func)(double), double a, double b, int N);
double simpson(double (*func)(double), double a, double b, int N);
double gauss_chebyshev(double (*func)(double), double a, double b, int N);
double gauss_legendre(double (*func)(double), double a, double b, int N);
double romberg(double (*func)(double), double a, double b, int max_steps, double tol);

double f1(double t) {
    return sin(100*t);
}

double f2(double t) {
    return pow(sin(100*t), t);
}

int main() {
    double a = 0.0;
    double b = 2*M_PI;
    const int num_N_values = 8;
    int N_values[num_N_values] = {2, 10, 20, 100, 200, 1000, 2000, 10000};

    ofstream outfile1("results_F1.txt");
    for (int i = 0; i < num_N_values; ++i) {
        int N = N_values[i];

        double calc_trapezoid = trapezoid(f1, a, b, N);
        double calc_simpson = simpson(f1, a, b, N);
        double calc_gauss_chebyshev = gauss_chebyshev(f1, a, b, N);
        double calc_gauss_legendre = gauss_legendre(f1, a, b, N);
        double calc_romberg = romberg(f1, a, b, 14, 1e-8);

        outfile1 << N << " " << calc_trapezoid << " " << calc_simpson << " " << calc_gauss_chebyshev << " " << calc_gauss_legendre << " " << calc_romberg << endl;
    }
    outfile1.close();


    ofstream outfile2("results_F2.txt");
    for (int i = 0; i < num_N_values; ++i) {
        int N = N_values[i];

        double calc_trapezoid = trapezoid(f2, a, b, N);
        double calc_simpson = simpson(f2, a, b, N);
        double calc_gauss_chebyshev = gauss_chebyshev(f2, a, b, N);
        double calc_gauss_legendre = gauss_legendre(f2, a, b, N);
        double calc_romberg = romberg(f2, a, b, 10, 1e-8);

        outfile2 << N << " " << calc_trapezoid << " " << calc_simpson << " " << calc_gauss_chebyshev << " " << calc_gauss_legendre << " " << calc_romberg << endl;
    }
    outfile2.close();
    return 0;
}
