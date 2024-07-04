#include <iostream>
#include <X11/Xlib.h>
#include <unistd.h>

using namespace std;
    
const int neutrons_count = 10000;
const double pc = 0.33;
const double ps = 0.67;
const double t = 1.;

void initial(double& f);
void scatter(int neutrons, double pc, double ps, double f, double t, int& captured, int& reflected, int& transmitted, double* x_positions, double* y_positions, bool* captured_flags, bool* reflected_flags, bool* transmitted_flags);
void output(int captured, int reflected, int transmitted, int neutrons);
void draw(int neutrons, double* x_positions, double* y_positions, bool* captured_flags, bool* reflected_flags, bool* transmitted_flags, double pc, double ps, double f, double t, double fc, double fr, double ft);

int main() {
    double f;
    initial(f);

    double* x_positions = new double[neutrons_count];
    double* y_positions = new double[neutrons_count-1];
    bool* captured_flags = new bool[neutrons_count];
    bool* reflected_flags = new bool[neutrons_count];
    bool* transmitted_flags = new bool[neutrons_count];

    int captured, reflected, transmitted;

    scatter(neutrons_count, pc, ps, f, t, captured, reflected, transmitted, x_positions, y_positions, captured_flags, reflected_flags, transmitted_flags);

    double fc = (double) captured / neutrons_count;
    double fr = (double) reflected / neutrons_count;
    double ft = (double) transmitted / neutrons_count;

    cout << "Fraction of captured neutrons: " << fc << endl;
    cout << "Fraction of reflected neutrons: " << fr << endl;
    cout << "Fraction of transmitted neutrons: " << ft << endl;

    draw(neutrons_count, x_positions, y_positions, captured_flags, reflected_flags, transmitted_flags, pc, ps, f, t, fc, fr, ft);

    delete[] x_positions;
    delete[] captured_flags;
    delete[] reflected_flags;
    delete[] transmitted_flags;

    return 0;
}
