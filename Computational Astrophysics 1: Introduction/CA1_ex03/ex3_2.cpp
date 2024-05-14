#include <iostream>
using namespace std;

int main() {
    double radius;
    double &diameterReference = radius;
    double *diameterPointer = &radius;
    cout << "Radius? ";
    cin >> radius;
    *diameterPointer *= 2;
    cout << "Diameter = " << diameterReference << endl;
}
