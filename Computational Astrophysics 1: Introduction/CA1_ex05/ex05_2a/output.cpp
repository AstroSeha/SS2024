#include <X11/Xlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void output() {
    vector<double> x, y;
    ifstream infile("orbit_data.txt");

    double t, vx, vy, px, py;
    while (infile >> t >> px >> py >> vx >> vy) {
        x.push_back(px);
        y.push_back(py);
    }

    infile.close();

    Display* display;
    Window window;
    int screen;
    GC gc;

    display = XOpenDisplay(NULL);

    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 800, 800, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    gc = XCreateGC(display, window, 0, NULL);

    XColor yellow, blue;
    Colormap colormap = DefaultColormap(display, screen);

    XAllocNamedColor(display, colormap, "darkorange", &yellow, &yellow);
    XAllocNamedColor(display, colormap, "dodgerblue", &blue, &blue);

    XEvent e;
    while (true) {
        XNextEvent(display, &e);

        if (e.type == Expose) {
            XSetForeground(display, gc, BlackPixel(display, screen));
            XFillRectangle(display, window, gc, 0, 0, 800, 800);

            XSetForeground(display, gc, yellow.pixel);
            XFillArc(display, window, gc, 390, 390, 20, 20, 0, 360 * 64);

            XSetForeground(display, gc, blue.pixel);
            for (size_t i = 0; i < x.size(); ++i) {
                int px = static_cast<int>((x[i] * 100) + 400);
                int py = static_cast<int>((y[i] * 100) + 400);
                XFillArc(display, window, gc, px - 4, py - 4, 8, 8, 0, 360 * 64);
            }
        }

        if (e.type == KeyPress) {
            break;
        }
    }

    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}
