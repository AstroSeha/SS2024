#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int PADDING = 50;
const int PIXEL_SIZE = 5;

void draw(int neutrons, double* x_positions, double* y_positions, bool* captured_flags, bool* reflected_flags, bool* transmitted_flags, double pc, double ps, double f, double t, double fc, double fr, double ft) {
    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }

    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, WIDTH, HEIGHT, 1, BlackPixel(display, screen), BlackPixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    GC gc = XCreateGC(display, window, 0, NULL);
    XSetForeground(display, gc, WhitePixel(display, screen));

    XFontStruct* font = XLoadQueryFont(display, "-*-helvetica-*-r-*-*-18-*-*-*-*-*-*-*");
    if (font) {
        XSetFont(display, gc, font->fid);
    }

    XDrawLine(display, window, gc, PADDING, 0, PADDING, HEIGHT);
    int t_pos = PADDING + (t / 1.0) * (WIDTH - 2 * PADDING);
    XDrawLine(display, window, gc, t_pos, 0, t_pos, HEIGHT);


    while (true) {
        XEvent event;
        XNextEvent(display, &event);

        if (event.type == Expose) {
            XSetForeground(display, gc, WhitePixel(display, screen));
            XDrawLine(display, window, gc, PADDING, 0, PADDING, HEIGHT);
            XDrawLine(display, window, gc, t_pos, 0, t_pos, HEIGHT);

            stringstream ss;
            ss << "pc: " << pc << ", ps: " << ps << ",  number:" << neutrons << ", t: " << t;
            string input_values = ss.str();
            XDrawString(display, window, gc, WIDTH / 4, PADDING, input_values.c_str(), input_values.length());

            XSetForeground(display, gc, 0xA6E6FF);
            stringstream ss2;
            ss2 << "f: " << f << ", fc: " << fc << ", fr: " << fr << ", ft: " << ft;
            string output_values = ss2.str();
            XDrawString(display, window, gc, WIDTH / 4, PADDING + 20, output_values.c_str(), output_values.length());

            for (int i = 0; i < neutrons; ++i) {
                int x = PADDING + x_positions[i] * (WIDTH - 2 * PADDING);
                int y = PADDING + y_positions[i] * (HEIGHT - 2 * PADDING);

                if (captured_flags[i]) {
                    XSetForeground(display, gc, 0xA98DFA); // violet for captured neutrons
                } else if (reflected_flags[i]) {
                    XSetForeground(display, gc, 0xFA8DC8); // pink for reflected neutrons
                } else if (transmitted_flags[i]) {
                    XSetForeground(display, gc, 0x8DC0FA); // blue for transmitted neutrons
                }

                XFillArc(display, window, gc, x, y, PIXEL_SIZE, PIXEL_SIZE, 0, 360 * 64);
            }
        }

        if (event.type == KeyPress)
            break;
    }

    XCloseDisplay(display);
}
