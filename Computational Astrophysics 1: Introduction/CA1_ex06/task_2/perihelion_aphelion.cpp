#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void perihelion_aphelion(double x[], double y[], double vx[], double vy[], double r[], double a, double T, int N, double dt) {
    double v_perihelion;
    double v_aphelion;
    double r1, r2;
    double perihelion, aphelion;

    r1 = r[0];
    r2 = 2*a - r1;

    // bigger value is aphelion
    if (r1 < r2) {
        perihelion = r1;
        aphelion = r2;
    } else {
        perihelion = r2;
        aphelion = r1;
    }

    //from vis-viva eq.
    v_perihelion = 2*M_PI * sqrt(2./perihelion - 1./a);
    v_aphelion = 2*M_PI * sqrt(2./aphelion - 1./a);

    // convert to km/s
    v_perihelion *= 4.74372; 
    v_aphelion *= 4.74372;

    cout << "Perihelion: " << perihelion << " AU" << endl;
    cout << "Aphelion: " << aphelion << " AU" << endl;
    cout << "Velocity at perihelion: " << v_perihelion << " km/s" << endl;
    cout << "Velocity at aphelion: " << v_aphelion << " km/s" << endl;

    // save to log file
    ofstream log_file("peri_ap_log.txt", ios::out);
    time_t now = time(0);
    log_file << "--------Timestamp: " << ctime(&now)<< endl;
    log_file << "Perihelion distance: " << perihelion << " AU" << endl;
    log_file << "Aphelion distance: " << aphelion << " AU" << endl;
    log_file << "Velocity at perihelion: " << v_perihelion << " km/s" << endl;
    log_file << "Velocity at aphelion: " << v_aphelion << " km/s" << endl;
    log_file.close();
}
