#include <cmath>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

double compute_period(double x[], double y[], int N, double dt) {
    // when crossing x-axis (y = 0) is half the period
    for (int i = 1; i < N; ++i) {
        if (y[i] * y[i-1] < 0) {
            cout << " i: " << i << endl;
            cout << "x[i]: " << x[i] << endl;
            return 2 * dt * i;
        }
    }
    return -1;
}

double theoretical_period(double x[], double y[], int N, double dt){
    // when crossing x-axis, it is either semi-major or semi-minor axis
    double r1 = x[0];
    double r2 = 0.;
    for (int i = 1; i < N; ++i) {
        if (y[i] * y[i-1] < 0) {
            r2 = sqrt(x[i] * x[i] + y[i] * y[i]);
            break;
        }
    }
    cout << "r1: " << r1 << endl;
    cout << "r2: " << r2 << endl;
    if (r1 > r2) {
        return pow(r1, 1.5);
    } else 
        return pow(r2, 1.5);
    
}


void log_results(double x0, double y0, double vx0, double vy0, double dt, int nout, double experimental_period, double theoretical_period) {
    ofstream logfile("period_log.txt", ios_base::app);
    if (!logfile.is_open()) {
        cerr << "Unable to open log file" << endl;
        return;
    }

    // Get current time
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
