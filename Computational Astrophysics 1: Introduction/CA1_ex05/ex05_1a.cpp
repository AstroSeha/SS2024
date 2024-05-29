#include <cmath>
#include "Xgraphics.h"

int main() {
    int n = 10001, nout = 500;
    double t, v, v_old, x;
    const double dt = 2.0 * M_PI / double(n - 1);
    x = 1.0;
    t = 0.0;
    v = 0.0;

    Window mywindow;
    World myworld;
    XEvent myevent;
    int done = 0;

    InitX();

    mywindow = CreateWindow(
        800, 600,
        (char*)"Harmonic Oscillator"
    );
    myworld = CreateWorld(
        mywindow,
        50, 50, 750, 550,
        -2, 2, 2, -2,
        0,
        0
    );

    ShowWindow(mywindow);

    for (int i = 0; i < n && !done; ++i) {
        t += dt;
        v_old = v;
        v -= x * dt;
        x += v_old * dt;

        if (i % nout == 0) {
            WClear(myworld);
            WDrawCircle(myworld, x, 0, 0.05, 1);

            while (XPending(XOpenDisplay(NULL)) > 0) {
                GetEvent(&myevent, 1);
                if (myevent.type == ButtonPress) {
                    done = 1;
                }
            }

            usleep(10000);
        }
    }

    ExitX();

    return 0;
}
