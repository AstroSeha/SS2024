#include <X11/Xlib.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void output() {
    vector<double> t, E_euler, E_cromer;
    ifstream infile("energy_data.txt");

    if (!infile) {
        cerr << "Error opening file" << endl;
        return;
    }

    double time, euler_energy, cromer_energy;
    while (infile >> time >> euler_energy >> cromer_energy) {
        t.push_back(time);
        E_euler.push_back(euler_energy);
        E_cromer.push_back(cromer_energy);
    }

    infile.close();

    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        cerr << "Cannot open display" << endl;
        return;
    }

    int screen = DefaultScreen(display);
    Window root = DefaultRootWindow(display);
    int width = 800, height = 600;
    Window window = XCreateSimpleWindow(display, root, 0, 0, width, height, 1,
                                        BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    cairo_surface_t* surface = cairo_xlib_surface_create(display, window, DefaultVisual(display, screen), width, height);
    cairo_t* cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Plot axes
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, 50, 50);
    cairo_line_to(cr, 50, height - 50);
    cairo_line_to(cr, width - 50, height - 50);
    cairo_stroke(cr);

    // Add axis labels and title
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 14);

    // Y-axis label
    cairo_move_to(cr, 20, height / 2);
    cairo_rotate(cr, -M_PI / 2);
    cairo_show_text(cr, "Relative Energy");
    cairo_rotate(cr, M_PI / 2);

    // X-axis label
    cairo_move_to(cr, width / 2, height - 10);
    cairo_show_text(cr, "Relative Time");

    // Title
    cairo_move_to(cr, width / 2 - 50, 30);
    cairo_show_text(cr, "Energy over Time: Euler vs Euler-Cromer");

    // Scaling factors
    double t_max = t.back();
    double E_min = min(*min_element(E_euler.begin(), E_euler.end()), *min_element(E_cromer.begin(), E_cromer.end()));
    double E_max = max(*max_element(E_euler.begin(), E_euler.end()), *max_element(E_cromer.begin(), E_cromer.end()));

    double t_scale = (width - 100) / t_max;
    double E_scale = (height - 100) / (E_max - E_min);

    // Plot Euler energy
    cairo_set_source_rgb(cr, 1, 0, 0); // Red
    for (size_t i = 0; i < t.size(); ++i) {
        double x = 50 + t[i] * t_scale;
        double y = height - 50 - (E_euler[i] - E_min) * E_scale;
        cairo_arc(cr, x, y, 2, 0, 2 * M_PI);
        cairo_fill(cr);
    }

    // Plot Euler-Cromer energy
    cairo_set_source_rgb(cr, 0, 0, 1); // Blue
    for (size_t i = 0; i < t.size(); ++i) {
        double x = 50 + t[i] * t_scale;
        double y = height - 50 - (E_cromer[i] - E_min) * E_scale;
        cairo_arc(cr, x, y, 2, 0, 2 * M_PI);
        cairo_fill(cr);
    }

    // Add legend
    cairo_set_source_rgb(cr, 1, 0, 0); // Red
    cairo_rectangle(cr, width - 150, 50, 10, 10);
    cairo_fill(cr);
    cairo_move_to(cr, width - 130, 60);
    cairo_show_text(cr, "Euler");

    cairo_set_source_rgb(cr, 0, 0, 1); // Blue
    cairo_rectangle(cr, width - 150, 70, 10, 10);
    cairo_fill(cr);
    cairo_move_to(cr, width - 130, 80);
    cairo_show_text(cr, "Euler-Cromer");

    cairo_surface_write_to_png(surface, "energy_plot.png");

    while (true) {
        XEvent e;
        XNextEvent(display, &e);

        if (e.type == KeyPress) {
            break;
        }
    }

    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}
