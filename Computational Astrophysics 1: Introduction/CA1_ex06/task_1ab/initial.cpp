#include <iostream>
#include <cmath>

using namespace std;

void initial(double& x0, double& y0, double& vx0, double& vy0, double& dt, int& nout) {
    y0 = 0.0;
    vx0 = 0.0;
    
    cout << "Size of the time step (dt): ";
    cin >> dt;
    
    cout << "Number of time steps between two consecutive draw actions (nout): ";
    cin >> nout;
    
    cout << "Initial value x(t = 0): ";
    cin >> x0;
    
    cout << "Initial value vy(t = 0): ";
    cin >> vy0;
}
