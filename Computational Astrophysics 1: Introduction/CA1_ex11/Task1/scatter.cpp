#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

void scatter(int neutrons, double pc, double ps, double f, double t, int& captured, int& reflected, int& transmitted, double* x_positions, bool* captured_flags, bool* reflected_flags, bool* transmitted_flags) {
    captured = 0;
    reflected = 0;
    transmitted = 0;

    srand(time(0));
    double E = 1.;

    ofstream outFile("results.txt");

    for (int i = 0; i < neutrons; ++i) {
        double x = 0.0;
    
        x_positions[i] = x;
        captured_flags[i] = false;
        reflected_flags[i] = false;
        transmitted_flags[i] = false;

        while (true) {
            double r = (double) rand() / RAND_MAX;

            if (r < pc) {
                ++captured;
                captured_flags[i] = true;
                break;
            } else if (r < pc + ps) {
                double cos_theta = 1 - 2 * ((double) rand() / RAND_MAX);
                double lambda = sqrt(E);
                double step_length = -lambda * log((double) rand() / RAND_MAX);

                x += step_length * cos_theta;
                x_positions[i] = x;
                
                outFile << step_length << endl;

                if (x < 0) {
                    ++reflected;
                    reflected_flags[i] = true;
                    break;
                } else if (x > t) {
                    ++transmitted;
                    transmitted_flags[i] = true;
                    break;
                }
            }
            E = E * (1. - f);


        }
    }
    outFile.close();
}