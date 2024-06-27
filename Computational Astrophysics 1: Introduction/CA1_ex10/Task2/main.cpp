#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const int INITIAL_NEUTRONS = 100;
const double T = 1.0;

void initial(int& neutrons, double& pc, double& ps, double& lambda) {
    neutrons = INITIAL_NEUTRONS;
    pc = PC;
    ps = PS;
    lambda = 0.1;  // Example value, adjust as necessary
}

void scatter(int& captured, int& reflected, int& transmitted, int neutrons, double pc, double ps, double lambda) {
    captured = 0;
    reflected = 0;
    transmitted = 0;

    srand(time(0));
    
    for (int i = 0; i < neutrons; ++i) {
        double x = 0.0;

        while (true) {
            double step = -lambda * log((double) rand() / RAND_MAX);
            x += step;

            double rand_val = (double) rand() / RAND_MAX;

            if (rand_val < pc) {
                ++captured;
                break;
            } else if (rand_val < pc + ps) {
                if (x > T) {
                    ++transmitted;
                    break;
                } else if (x < 0) {
                    ++reflected;
                    break;
                }
            } else {
                ++reflected;
                break;
            }
        }
    }
}

void output(int captured, int reflected, int transmitted, int neutrons) {
    double fc = (double) captured / neutrons;
    double fr = (double) reflected / neutrons;
    double ft = (double) transmitted / neutrons;

    cout << "Fraction of captured neutrons: " << fc << endl;
    cout << "Fraction of reflected neutrons: " << fr << endl;
    cout << "Fraction of transmitted neutrons: " << ft << endl;
}

int main() {
    int neutrons;
    double pc, ps, lambda;

    initial(neutrons, pc, ps, lambda);

    int captured, reflected, transmitted;

    scatter(captured, reflected, transmitted, neutrons, pc, ps, lambda);

    output(captured, reflected, transmitted, neutrons);

    return 0;
}
