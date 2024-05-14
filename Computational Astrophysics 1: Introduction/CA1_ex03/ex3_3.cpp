#include <iostream>
#include <cmath>
#include <limits> 
using namespace std;

int main() {
    const double tempSun = 5778;
    double logLsun;
    double Teff;

    cout << "Enter log(L*/Lsun): ";
    cin >> logLsun;
    cout << "Enter Teff (in Kelvin): ";
    cin >> Teff;
    while (Teff <= 0) {
        cout << "Invalid input. Please enter a positive value for Teff: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cin >> Teff;
    }
    double radius = sqrt(pow(10, logLsun) * pow(tempSun / Teff, 4));
    cout << "The radius is: " << radius << " R_sun" << endl;
    return 0;
}