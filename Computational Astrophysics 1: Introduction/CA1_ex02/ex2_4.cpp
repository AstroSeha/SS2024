#include <iostream>
#include <cmath>

int main() {
    const double tempSun = 5778;

    double logLsun;
    double Teff;

    std::cout << "Enter log(L*/Lsun): ";
    std::cin >> logLsun;
    std::cout << "Enter Teff (in Kelvin): ";
    std::cin >> Teff;

    double radius = sqrt(pow(10, logLsun) * pow(tempSun / Teff, 4));

    std::cout << "The radius is: " << radius << " R_sun" << std::endl;

    return 0;
}
