#include <iostream>

using namespace std;

void initial(int& neutrons, double& pc, double& ps, double& lambda, double& t) {
    cout << "Enter the number of neutrons: ";
    cin >> neutrons;

    cout << "Enter the capture probability (pc): ";
    cin >> pc;

    cout << "Enter the scattering probability (ps): ";
    cin >> ps;

    cout << "Enter the mean free path (lambda): ";
    cin >> lambda;

    cout << "Enter the thickness of the plate (t): ";
    cin >> t;
}
