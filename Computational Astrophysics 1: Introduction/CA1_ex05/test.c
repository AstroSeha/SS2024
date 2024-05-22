#include <unistd.h>
#include "Xgraphics.h"

int main() {
    Window mywindow;
    World myworld;
    XEvent myevent;
    int done = 0;

    InitX();
    mywindow = CreateWindow(800, 600, (char*)"Simple Test");
    myworld = CreateWorld(mywindow, 50, 50, 750, 550, 0, 10, 10, 0, 0, 0);
    ShowWindow(mywindow);

    // Draw a few static points
    WDrawPoint(myworld, 1, 1, 1);
    WDrawPoint(myworld, 2, 2, 1);
    WDrawPoint(myworld, 3, 3, 1);
    WDrawPoint(myworld, 4, 4, 1);

    // Draw a few static lines
    WDrawLine(myworld, 1, 1, 2, 2, 1);
    WDrawLine(myworld, 2, 2, 3, 3, 1);
    WDrawLine(myworld, 3, 3, 4, 4, 1);
    WDrawLine(myworld, 4, 4, 5, 5, 1);

    // Ensure everything is drawn
    XFlush(display);

    // Event handling
    while (!done) {
        GetEvent(&myevent, 1);
        if (myevent.type == ButtonPress) done = 1;
    }

    ExitX();
    return 0;
}
