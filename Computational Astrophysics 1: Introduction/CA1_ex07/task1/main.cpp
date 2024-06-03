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
    return (4 * central(f, x, h/2) - central(f, x, h)) / 3;
}

int main() {
    double data[16][4];
    double x = 100.0;
    double h = 1.0;
    double epsilon = numeric_limits<double>::epsilon();
    double exact = exp(x);

    ofstream file("data.txt");

    cout << setw(15) << "h" 
             << setw(20) << "Forward_Error" 
             << setw(20) << "Central_Error" 
             << setw(25) << "Extrapolated_Error" << endl;

    int i = 0;

    while (h > epsilon){
        data[i][0] = h;
        
        double fwd_diff = forward(exp, x, h);
        double cen_diff = central(exp, x, h);
        double ext_diff = extrapolated(exp, x, h);

        double fwd_error = abs(fwd_diff - exact) / exact;
        double cen_error = abs(cen_diff - exact) / exact;
        double ext_error = abs(ext_diff - exact) / exact;

        data[i][1] = fwd_error;
        data[i][2] = cen_error;
        data[i][3] = ext_error;

        cout << scientific << setprecision(5) 
             << setw(15) << h 
             << setw(20) << fwd_error 
             << setw(20) << cen_error 
             << setw(25) << ext_error << endl;

        file << scientific << setprecision(5) 
             << h 
             << " " << fwd_error 
             << " " << cen_error 
             << " " << ext_error << endl;

        h /= 10.0;
        i++;
    }
    file.close();

    ofstream file_s("slope.txt");

    for (int i = 1; i < 16; i++){
        double fwd_slope = (log(data[i][1]) - log(data[i-1][1])) / (log(data[i][0]) - log(data[i-1][0]));
        double cen_slope = (log(data[i][2]) - log(data[i-1][2])) / (log(data[i][0]) - log(data[i-1][0]));
        double ext_slope = (log(data[i][3]) - log(data[i-1][3])) / (log(data[i][0]) - log(data[i-1][0]));
        
        file_s << scientific << setprecision(5) 
         << data[i][0]
         << " " << fwd_slope 
         << " " << cen_slope 
         << " " << ext_slope << endl;
        
    
    }
    file_s.close();

    return 0;

}
