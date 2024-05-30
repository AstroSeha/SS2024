#include <iostream>
#include <cmath>

using namespace std;

void initial(double& x0, double& T, double& a_initial) {
 
    cout << "Orbital period[year]: ";
    cin >> T;
    
    // semi-major axis from Kepler's third law, au and year
    a_initial = pow(T, 2./3);

    cout << "Initial value of x[au], when t=y=0: ";
    cin >> x0;

    // vis viva equation when GM=4*pi^2
    double vy0 = 2*M_PI *sqrt(2./x0 - 1./a_initial); 
    
}
