#include <iostream>
using namespace std;

int main() {
    double x[100], y[100];
    int n;

    // input data 
    cout << "How many data pairs?(max 100) ";
    cin >> n;
    if(n > 100) return 1;

    cout << "Enter your pairs (x,y) " << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "], y[" << i << "]: ";
        cin >> x[i] >> y[i];
    }

    cout << "Imported Pairs" << endl;
    cout << "x\t-\ty" << endl;
    for (int i = 0; i < n; i++) {
        cout << x[i] << "\t-\t" << y[i] << endl;
    }

     double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;
    // line of best fit
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += x[i] * x[i];
    }
    double mean_x = sum_x / n;
    double mean_y = sum_y / n;
    double b = (sum_xy - n * mean_x * mean_y) / (sum_xx - n * mean_x * mean_x);
    double a = mean_y - b * mean_x;

    cout << "a = " << a << ", b = " << b << endl;
    return 0;
}
