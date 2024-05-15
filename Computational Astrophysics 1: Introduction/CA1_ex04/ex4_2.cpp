#include <iostream>
#include <iomanip>

using namespace std;

void kahan(int n, float inc, float &sum, float &c) {
    for (int i = 0; i < n; ++i) {
        float y = inc - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
}

void regular(int n, float inc, float &sum) {
    for (int i = 0; i < n; ++i) {
        sum += inc;
    }
}

int main() {
    int n = 1e+7;
    float inc = 1e-7f;
    float x = 7.0f;

    float regularSum = x;
    regular(n, inc, regularSum);

    float kahanSum = x, cFloat = 0.0f;
    kahan(n, inc, kahanSum, cFloat);

    // double
    double regularDoubleSum = x;
    for (int i = 0; i < n; ++i) {
        regularDoubleSum += static_cast<double>(inc);
    }

    // Kahan summation for double
    double kahanDoubleSum = x, cDouble = 0.0;
    for (int i = 0; i < n; ++i) {
        double y = static_cast<double>(inc) - cDouble;
        double t = kahanDoubleSum + y;
        cDouble = (t - kahanDoubleSum) - y;
        kahanDoubleSum = t;
    }

    // Display results
    cout<<"number of iterations: "<<n<<endl;
    cout<<"arithmetic answer= "<<x + n * inc<<endl;
    cout << fixed << setprecision(10);
    cout << "Regular summation (float): " << regularSum << endl;
    cout << "Kahan summation (float): " << kahanSum << endl;
    cout << "Regular summation (double): " << regularDoubleSum << endl;
    cout << "Kahan summation (double): " << kahanDoubleSum << endl;

    return 0;
}
