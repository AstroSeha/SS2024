#include <cmath>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// period: time taken to complete one orbit
double experimental_period(double x[], double y[], int N, double dt) {
    double reference_x = x[0]; // Reference position

    // find the next position where x = reference_x
    for (int i = 100; i < N; ++i) {
        if (abs(x[i] - reference_x) / abs(reference_x) < 1e-5) {
            return dt * i;
        }
    }

    return -1.0; // when not found
}

// Kepler's third law T^2 ~ a^3
double theoretical_period(double x0, double vy0) {
    return pow(x0, 1.5);
}
