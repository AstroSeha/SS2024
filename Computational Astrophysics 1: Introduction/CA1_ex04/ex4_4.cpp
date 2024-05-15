#include <iostream>
#include <iomanip>
#include <cmath>
#include <initializer_list>


using namespace std;

double exp_series(double x, double epsilon) {
    double term = 1.0; // the 1st term
    double sum = 1.0;
    int n = 1;
    while (fabs(term / sum) >= epsilon) {
        term *= (-x / n);
        sum += term;
        n++;
    }
    return sum;
}

void print_table(double x, double epsilon) {
    double exact = exp(-x);
    double term = 1.0;
    double sum = 1.0;
    int n = 1;
    cout << "N\tSum(N)\t\tRelative Error" << endl;
    cout << "0\t" << fixed << setprecision(10) << sum << "\t" << fabs(sum - exact) / exact << endl;
    while (fabs(term / sum) >= epsilon) {
        term *= (-x / n);
        sum += term;
        n++;
    }
    cout << n << "\t" << fixed << setprecision(10) << sum << "\t" << fabs(sum - exact) / exact << endl;
}

void check_convergence(double x, double epsilon) {
    double calculated = exp_series(x, epsilon);
    double exact = exp(-x);
    cout << "x = " << x << endl;
    cout << "Calculated: " << fixed << setprecision(10) << calculated << endl;
    cout << "Exact: " << exact << endl;
    cout << "Relative Error: " << fabs(calculated - exact) / exact << endl;
    cout << endl;
}

int main() {
    double epsilon = 1e-8;
    cout << "--Good algorithm:" << endl;
    for (double x : {0.1, 1., 10., 100., 1000.}) {
        cout << "x = " << x << endl;
        print_table(x, epsilon);
        check_convergence(x, epsilon);
    }
    cout << "--Checking convergence for small negative x:" << endl;
    for (double x : {-0.01, -0.1, -1.}) {
        cout << "x = " << x << endl;

        check_convergence(x, epsilon);
    }
    cout << "--Checking convergence for increasing |x|:" << endl;
    for (double x : {-10., -100.}) {
        cout << "x = " << x << endl;
        print_table(x, epsilon);
        check_convergence(x, epsilon);
    }
    cout << "--Bad algorithm:" << endl;
    for (double x : {-100., -10., -1., -0.1, -0.01, 0.1, 1., 10., 100., 1000.}) {
        cout << "x = " << x << endl;
        double sum = 0.0;
        double term = 1.0;
        for (int n = 0; n < 1000; n++) {
            sum += term;
            term = pow(-x, n + 1) / tgamma(n + 2);
            if (fabs(term / sum) < epsilon) break;
        }
        double exact = exp(-x);
        cout << "Sum = " << sum << "\tRelative Error = " << fabs(sum - exact) / exact << endl;
    }
    return 0;
}
