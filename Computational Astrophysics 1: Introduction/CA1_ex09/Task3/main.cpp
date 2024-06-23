#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double a = 5.204491; 
const double M = 199.7855 * M_PI / 180.0; 
const double tol = 1e-5 / 180. /M_PI;

double fixedPointIteration(double M, double e) {
    double E = M;
    double E_next;
    int i = 0;
    do {
        i++;
        E_next = M + e * sin(E);
        if (fabs(E_next - E) < tol) break;
        E = E_next;
    } while (true);

    double phi = 2 * atan2(sqrt(1 + e) * tan(E / 2), sqrt(1 - e));
    double r = a * (1 - e * cos(E));
    if (phi < 0) phi += 2 * M_PI;
    cout << "fixed point iteration: " << i << " iterations" << endl;
    cout << "eccentric anomaly E: " << E << endl;
    cout << "true anomaly phi: " << phi << endl;
    cout << "distance to the Sun r: " << r << endl;
    return E;
}

double newtonsMethod(double M, double e) {
    double E = M;
    double E_next;
    int i = 0;
    do {
        i++;
        E_next = E - (E - e * sin(E) - M) / (1 - e * cos(E));
        if (fabs(E_next - E) < tol) break;
        E = E_next;
    } while (true);

    double phi = 2 * atan2(sqrt(1 + e) * tan(E / 2), sqrt(1 - e));
    double r = a * (1 - e * cos(E));
    if (phi < 0) phi += 2 * M_PI;
    cout << "newton method: " << i << " iterations" << endl;
    cout << "eccentric anomaly E: " << E <<endl;
    cout << "true anomaly phi: " << phi << endl;
    cout << "distance to the Sun r: " << r << endl;
    return E;
}

int main() {
    double e = 0.047837;  
    cout<< "-----eccentricity: "<<e<<endl;
    fixedPointIteration(M, e);
    newtonsMethod(M, e);
    e=0.1;  
    cout<< "-----eccentricity: "<<e<<endl;
    fixedPointIteration(M, e);
    newtonsMethod(M, e);
    e=0.3;  
    cout<< "-----eccentricity: "<<e<<endl;
    fixedPointIteration(M, e);
    newtonsMethod(M, e);
    return 0;
}

