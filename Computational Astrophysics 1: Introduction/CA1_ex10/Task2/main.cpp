#include <iostream>
#include <X11/Xlib.h>
#include <unistd.h>

using namespace std;

void initial(int& neutrons, double& pc, double& ps, double& lambda, double& t);
void scatter(int neutrons, double pc, double ps, double lambda, double t, int& captured, int& reflected, int& transmitted, double* x_positions, bool* captured_flags, bool* reflected_flags, bool* transmitted_flags);
void output(int captured, int reflected, int transmitted, int neutrons);
void draw(int neutrons, double* x_positions, bool* captured_flags, bool* reflected_flags, bool* transmitted_flags, double pc, double ps, double lambda, double t, double fc, double fr, double ft);

int main() {
    int neutrons_count;
    double pc, ps, lambda, t;

    initial(neutrons_count, pc, ps, lambda, t);

    double* x_positions = new double[neutrons_count];
    bool* captured_flags = new bool[neutrons_count];
    bool* reflected_flags = new bool[neutrons_count];
    bool* transmitted_flags = new bool[neutrons_count];

    int captured, reflected, transmitted;

    scatter(neutrons_count, pc, ps, lambda, t, captured, reflected, transmitted, x_positions, captured_flags, reflected_flags, transmitted_flags);

    double fc = (double) captured / neutrons_count;
    double fr = (double) reflected / neutrons_count;
    double ft = (double) transmitted / neutrons_count;

    cout << "Fraction of captured neutrons: " << fc << endl;
    cout << "Fraction of reflected neutrons: " << fr << endl;
    cout << "Fraction of transmitted neutrons: " << ft << endl;

    draw(neutrons_count, x_positions, captured_flags, reflected_flags, transmitted_flags, pc, ps, lambda, t, fc, fr, ft);

    delete[] x_positions;
    delete[] captured_flags;
    delete[] reflected_flags;
    delete[] transmitted_flags;

    return 0;
}
