#include <iostream>
#include <cmath>
#include <unistd.h>
#include "Xgraphics.h"

using namespace std;

void generate_analytic_solution(double *t_vals, double *x_vals, double *v_vals, int n, double dt) {
    for (int i = 0; i < n; ++i) {
        double t = i * dt;
        t_vals[i] = t;
        x_vals[i] = cos(t);
        v_vals[i] = -sin(t);
    }
}

int main() {
    int n = 10001, nout = 500;
    double t, v, v_old, x;
    const double dt = 2.0 * M_PI / double(n - 1);
    x = 1.0;
    t = 0.0;
    v = 0.0;

    double *t_vals = new double[n];
    double *x_vals = new double[n];
    double *v_vals = new double[n];

    for (int i = 0; i < n; ++i) {
        t += dt;
        v_old = v;
        v -= x * dt;
        x += v_old * dt;
        t_vals[i] = t;
        x_vals[i] = x;
        v_vals[i] = v;
    }

    double *t_analytic = new double[n];
    double *x_analytic = new double[n];
    double *v_analytic = new double[n];
    generate_analytic_solution(t_analytic, x_analytic, v_analytic, n, dt);

    Window mywindow;
    World myworld;
    XEvent myevent;
    int done = 0;

    InitX();
    mywindow = CreateWindow(800, 600, (char*)"Harmonic Oscillator");
    myworld = CreateWorld(mywindow, 50, 50, 750, 550, 0, 2 * M_PI, 1, -1, 0, 0);
    ShowWindow(mywindow);

    for (int i = 0; i < n; i += nout) {
        WDrawCircle(myworld, t_vals[i], x_vals[i], 0.01, 1); // Euler x(t)
        WDrawCircle(myworld, t_vals[i], v_vals[i], 0.01, 2); // Euler v(t)
    }

    for (int i = 1; i < n; ++i) {
        WDrawLine(myworld, t_analytic[i-1], x_analytic[i-1], t_analytic[i], x_analytic[i], 1); // Analytic x(t)
        WDrawLine(myworld, t_analytic[i-1], v_analytic[i-1], t_analytic[i], v_analytic[i], 2); // Analytic v(t)
    }

    while (!done) {
        GetEvent(&myevent, 1);
        if (myevent.type == ButtonPress) done = 1;
    }

    ExitX();

    delete[] t_vals;
    delete[] x_vals;
    delete[] v_vals;
    delete[] t_analytic;
    delete[] x_analytic;
    delete[] v_analytic;

    return 0;
}
