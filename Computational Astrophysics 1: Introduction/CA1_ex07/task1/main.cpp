#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

double forward(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x)) / h;
}

double central(double (*f)(double), double x, double h) {
    return (f(x + h/2) - f(x - h/2)) / h;
}

double extrapolated(double (*f)(double), double x, double h) {
    return (8 * (f(x + h/4) - f(x - h/4)) / (h/2) - (f(x + h/2) - f(x - h/2)) / h) / 3;
}

double slope(const vector<double> &x, const vector<double> &y) {
    int n = x.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    return (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
}

int main() {
    double x = 100.0;
    double h = 1.0;
    double epsilon = numeric_limits<double>::epsilon();
    double exact = exp(x);
    
    
    vector<double> log_h, log_fwd_error, log_cen_error, log_ext_error;

    ofstream file("data.txt");
    cout << setw(15) << "h" 
         << setw(20) << "Forward_Error" 
         << setw(20) << "Central_Error" 
         << setw(25) << "Extrapolated_Error" << endl;

    while (h > epsilon) {
        double fwd_diff = forward(exp, x, h);
        double cen_diff = central(exp, x, h);
        double ext_diff = extrapolated(exp, x, h);

        double fwd_error = abs(fwd_diff - exact) / exact;
        double cen_error = abs(cen_diff - exact) / exact;
        double ext_error = abs(ext_diff - exact) / exact;

        file << scientific << setprecision(5) 
             << h 
             << " " << fwd_error 
             << " " << cen_error 
             << " " << ext_error << endl;

        log_h.push_back(log10(h));
        log_fwd_error.push_back(log10(fwd_error));
        log_cen_error.push_back(log10(cen_error));
        log_ext_error.push_back(log10(ext_error));

        cout << scientific << setprecision(5) 
             << setw(15) << h 
             << setw(20) << fwd_error 
             << setw(20) << cen_error 
             << setw(25) << ext_error << endl;

        h /= 10.0;
    }

    file.close();

    double slope_fwd = slope(log_h, log_fwd_error);
    double slope_cen = slope(log_h, log_cen_error);
    double slope_ext = slope(log_h, log_ext_error);

    cout << "Slope of log10(|E|) over log10(h):" << endl;
    cout << "Forward Difference: " << slope_fwd << endl;
    cout << "Central Difference: " << slope_cen << endl;
    cout << "Extrapolated Difference: " << slope_ext << endl;

    return 0;
}
