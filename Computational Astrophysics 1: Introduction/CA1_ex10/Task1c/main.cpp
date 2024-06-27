#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void generate_norm_dist(int n, double mu, double sigma, vector<double>& numbers) {
    srand(time(0));
    for (int i = 0; i < n; i += 2) {
        double u1 = rand() / (double)RAND_MAX;
        double u2 = rand() / (double)RAND_MAX;
        double x = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
        double y = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);
        numbers.push_back(sigma * x + mu);
        numbers.push_back(sigma * y + mu);
    }
}

int main() {
    int n = 1e+4;
    double mu = 0.0;
    double sigma = 1.0;
    vector<double> numbers;
    
    generate_norm_dist(n, mu, sigma, numbers);
    
    ofstream outFile("results.txt");
    for (int i = 0; i < n; i++) {
        outFile << numbers[i] << endl;
    }
    outFile.close();
    
    return 0;
}
