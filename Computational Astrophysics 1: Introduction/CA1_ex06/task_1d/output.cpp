#include <X11/Xlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void output(const string& filename) {
    vector<double> x, y;
    ifstream infile(filename);

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
    XFontStruct *font_info;

    display = XOpenDisplay(NULL);

    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 500, 500, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    gc = XCreateGC(display, window, 0, NULL);

    font_info = XLoadQueryFont(display, "-*-helvetica-*-r-*-*-24-*-*-*-*-*-*-*");
    XSetFont(display, gc, font_info->fid);

    XColor yellow, blue, white, violet;
    Colormap colormap = DefaultColormap(display, screen);

    // different colors
    XAllocNamedColor(display, colormap, "Gold", &yellow, &yellow);
    XAllocNamedColor(display, colormap, "CornflowerBlue", &blue, &blue);
    XAllocNamedColor(display, colormap, "MediumPurple", &violet, &violet);
    XAllocNamedColor(display, colormap, "LightSteelBlue", &white, &white);

    XEvent e;
    while (true) {
        XNextEvent(display, &e);

        if (e.type == Expose) {
            XSetForeground(display, gc, BlackPixel(display, screen));
            XFillRectangle(display, window, gc, 0, 0, 500, 500);

            // the Sun at the center
            XSetForeground(display, gc, yellow.pixel);
            XFillArc(display, window, gc, 225, 225, 50, 50, 0, 360 * 64);

            // Scale factor for the orbit

            
            // the planet: blue for inner planets, violet for outer planets
            // XSetForeground(display, gc, blue.pixel);
            // for (size_t i = 0; i < x.size(); ++i) {
            //     int px = static_cast<int>((x[i] * 175) + 250);
            //     int py = static_cast<int>((y[i] * 175) + 250);
            //     XFillArc(display, window, gc, px - 8, py - 8, 16, 16, 0, 360 * 64);
            // }

            XSetForeground(display, gc, violet.pixel);
            for (size_t i = 0; i < x.size(); ++i) {
                int px = static_cast<int>((x[i] * 10) + 250);
                int py = static_cast<int>((y[i] * 10) + 250);
                XFillArc(display, window, gc, px - 8, py - 8, 16, 16, 0, 360 * 64);
            }

            // Display the filename
            XSetForeground(display, gc, white.pixel);
            XDrawString(display, window, gc, 10, 20, filename.c_str(), filename.length());
        }

        if (e.type == KeyPress) {
            break;
        }
    }

    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}
