#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

double L1(int i, double x, const vector<double>& E) {
        double result = 1.0;
        for (size_t j = 0; j < E.size(); ++j) {
            if (i != j) {
                result *= (x - E[j]) / (E[i] - E[j]);
            }
        }
        return result;
    }

double L2(double x, const vector<double>& E, const vector<double>& sigma) {
    double result = 0.0;
    for (size_t i = 0; i < E.size(); ++i) {
        result += sigma[i] * L1(i, x, E);
    }
    return result;
}

void lagrange(const vector<double>& E, const vector<double>& sigma){        
    vector<double> x_vals;
        for (double x = 0; x <= 200; x += 1.0) {
            x_vals.push_back(x);
        }

        for (double x : x_vals) {
            double y = L2(x, E, sigma);

            ofstream file("results.txt", ios::app);
            file << x << " " << y << endl;
        }
    }
int main() {  
    vector<double> E;
    vector<double> sigma;
    string line;
    ifstream file("data.txt"); 

    while (getline(file, line)){ 
        stringstream ss(line);
        double e, s;
        ss >> e >> s;
        E.push_back(e);
        sigma.push_back(s);
    }

    lagrange(E, sigma);
    return 0;
}