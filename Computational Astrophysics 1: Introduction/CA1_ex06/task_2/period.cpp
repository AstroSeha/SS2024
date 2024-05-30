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
        if (abs(x[i] - reference_x)/abs(reference_x) < 1e-5) {
            return dt * i;
        }
    }

    return -1.0; // when not found
}
// Kepler's third law T^2 ~ a^3
double theoretical_period(double x[], double y[], int N, double dt) {
    double r1 = abs(x[0]);
    double r2 = 0.0;

    for (int i = 1; i < N; ++i) {
        if (y[i] * y[i-1] < 0) {
            r2 = sqrt(x[i] * x[i] + y[i] * y[i]);
            break;
        }
    }
    if (r1 > r2) {
        return pow(r1, 1.5);
    } else {
        return pow(r2, 1.5);
    }
}

// save the results
void log_results(double x0, double y0, double vx0, double vy0, double dt, int nout, double experimental_period, double theoretical_period) {
    ofstream logfile("period_log.txt", ios_base::app);
    if (!logfile.is_open()) {
        cerr << "Unable to open log file" << endl;
        return;
    }

    // get current time
    time_t now = time(0);
    char* dt_now = ctime(&now);

    logfile << "Timestamp: " << dt_now;
    logfile << "Initial conditions: x0 = " << x0 << ", y0 = " << y0 << ", vx0 = " << vx0 << ", vy0 = " << vy0 << endl;
    logfile << "Time step: " << dt << ", nout: " << nout << endl;
    logfile << "Experimental period: " << experimental_period << " years" << endl;
    logfile << "Theoretical period: " << theoretical_period << " years" << endl;
    logfile << "-----------------------------------------" << endl;

    logfile.close();
}
