#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const int np = 2; 
const int nd = 2; 
const float GM = 4 * M_PI * M_PI; 
// // for a)
// const float mass_ratio[2] = {static_cast<float>(0.04 * GM), static_cast<float>(0.001 * GM)};

// for b), the Earth and Jupiter
const float mass_ratio[2] = {static_cast<float>(0.000003 * GM), static_cast<float>(0.0009545 * GM)};

void compute_acceleration(float pos[np][nd], float acc[np][nd]) {
    float dx, dy, r3, dr3;

    for (int i = 0; i < np; ++i) {
        acc[i][0] = -GM * pos[i][0] / pow(sqrt(pos[i][0] * pos[i][0] + pos[i][1] * pos[i][1]), 3);
        acc[i][1] = -GM * pos[i][1] / pow(sqrt(pos[i][0] * pos[i][0] + pos[i][1] * pos[i][1]), 3);

        for (int j = 0; j < np; ++j) {
            if (i != j) {
                dx = pos[j][0] - pos[i][0];
                dy = pos[j][1] - pos[i][1];
                dr3 = pow(dx * dx + dy * dy, 1.5);
                acc[i][0] += mass_ratio[j] * dx / dr3;
                acc[i][1] += mass_ratio[j] * dy / dr3;
            }
        }
    }
}

void euler_richardson(float pos[np][nd], float vel[np][nd], float dt) {
    float pos_half[np][nd], vel_half[np][nd], acc[np][nd];

    compute_acceleration(pos, acc);
    for (int i = 0; i < np; ++i) {
        for (int d = 0; d < nd; ++d) {
            vel_half[i][d] = vel[i][d] + 0.5 * acc[i][d] * dt;
            pos_half[i][d] = pos[i][d] + 0.5 * vel[i][d] * dt;
        }
    }

    compute_acceleration(pos_half, acc);
    for (int i = 0; i < np; ++i) {
        for (int d = 0; d < nd; ++d) {
            vel[i][d] += acc[i][d] * dt;
            pos[i][d] += vel_half[i][d] * dt;
        }
    }
}

int main() {
    // // for a)
    // float pos[np][nd] = {{2.52, 0}, {5.24, 0}}; 
    // float vel[np][nd] = {{0, 7.5}, {0, 2.63}}; 

    // for b), the Earth and Jupiter
    float pos[np][nd] = {{1, 0}, {5.2, 0}};
    float vel[np][nd] = {{0, 6.28}, {0, 2.75}};
    
    float dt = 1e-3; 
    int steps = 1e+5; 
    ofstream output("trajectories.txt");

    for (int step = 0; step < steps; ++step) {
        euler_richardson(pos, vel, dt);
        output << pos[0][0] << " " << pos[0][1] << " " << pos[1][0] << " " << pos[1][1] << endl;
    }

    output.close();
    return 0;
}
