#include <iostream>

using namespace std;

void output(int captured, int reflected, int transmitted, int neutrons) {
    double fc = (double) captured / neutrons;
    double fr = (double) reflected / neutrons;
    double ft = (double) transmitted / neutrons;

    cout << "Fraction of captured neutrons: " << fc << endl;
    cout << "Fraction of reflected neutrons: " << fr << endl;
    cout << "Fraction of transmitted neutrons: " << ft << endl;
}
