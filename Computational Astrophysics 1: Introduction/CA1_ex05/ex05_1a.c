#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "Xgraphics.h"

void generate_analytic_solution(const char *filename, int n, double dt) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < n; ++i) {
        double t = i * dt;
        fprintf(file, "%f %f %f\n", t, cos(t), -sin(t));
    }
    fclose(file);
}

int main() {
    Window mywindow;
    World myworld;
    XEvent myevent;
    int done = 0;
    int n = 10001;
    int nout = 500;
    double t, v, v_old, x;
    const double dt = 2.0 * M_PI / (n - 1);
    x = 1.0;
    v = 0.0;
    t = 0.0;

    InitX();
    mywindow = CreateWindow(800, 600, (char*)"ex05_1a");
    myworld = CreateWorld(mywindow, 50, 50, 750, 550, 0, 2 * M_PI, 1, -1, 0, 0);
    ShowWindow(mywindow);

    FILE *file = fopen("euler_1a.dat", "w");

    for (int i = 0; i < n; ++i) {
        v_old = v;
        t += dt;
        v -= x * dt;
        x += v_old * dt;
        if (i % nout == 0) {
            fprintf(file, "%f %f %f\n", t, x, v);
        }
    }

    fclose(file);
    generate_analytic_solution("analytic_1a.dat", n, dt);

    FILE *euler_file = fopen("euler_1a.dat", "r");
    FILE *analytic_file = fopen("analytic_1a.dat", "r");

    double t, x_euler, v_euler, x_analytic, v_analytic;
    int first_point = 1;
    double prev_x_analytic, prev_v_analytic, prev_t;

    while (fscanf(euler_file, "%lf %lf %lf", &t, &x_euler, &v_euler) != EOF &&
           fscanf(analytic_file, "%lf %lf %lf", &t, &x_analytic, &v_analytic) != EOF) {
        WDrawPoint(myworld, t, x_euler, 0);
        WDrawPoint(myworld, t, v_euler, 0);

        if (!first_point) {
            WDrawLine(myworld, prev_t, prev_x_analytic, t, x_analytic, 1);
            WDrawLine(myworld, prev_t, prev_v_analytic, t, v_analytic, 2);
        }

        prev_t = t;
        prev_x_analytic = x_analytic;
        prev_v_analytic = v_analytic;
        first_point = 0;
    }

    fclose(euler_file);
    fclose(analytic_file);

    while (!done) {
        GetEvent(&myevent, 1);
        if (myevent.type == ButtonPress) done = 1;
    }

    ExitX();
    return 0;
}