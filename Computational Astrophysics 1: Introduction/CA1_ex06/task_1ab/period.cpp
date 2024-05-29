#include <cmath>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

const double GM = 4 * M_PI * M_PI; 

double compute_period(double x[], double y[], int N, double dt) {

    for (int i = 1; i < N; ++i) {
        if (y[i-1] < 0 && y[i] >= 0) { 
            return dt * i;
        }
    }
    return -1.0; //when not found 
}

double theoretical_period(double r) {
    return 2 * M_PI * sqrt(pow(r, 3) / GM);
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
