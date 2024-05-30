#include <iostream>

using namespace std;

void initial(double& x0, double& vy0, double& dt) {
    cout << "Enter initial x0, vy0, dt (separated by spaces): ";
    cin >> x0 >> vy0 >> dt;
}
