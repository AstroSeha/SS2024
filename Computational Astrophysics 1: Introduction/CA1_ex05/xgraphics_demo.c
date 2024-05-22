#include <math.h>
#include "Xgraphics.h"
//Main program 
int main () {
//Variables for window handling 
Window mywindow ;
World myworld ;
XEvent myevent ;
 int i, done = 0 ; // control variables
//1st: Connect to X-server 
InitX() ;
//Set window and drawing area 
mywindow = CreateWindow(
               400, 400, // width, height
               (char*)"demo1" // name of window
               ); 
myworld = CreateWorld(
               mywindow, // window to draw in
               5,5,390,390, // x,y,width,height
               -1,1,1,-1, // wx1,wy1,wx2,wy2
               0,        // scaling property
               0 // "gravity" 
);
//Presenting the window and drawing a Lissajous figure 
ShowWindow(mywindow) ;
 for(i=1;i<620;++i) WDrawCircle(myworld,cos(i),sin(2*i),0.1,1);
//Event handling: wait for mouse click 
while(!done) {
   GetEvent (&myevent,1) ;
   if (myevent.type == ButtonPress) done = 1 ;
}

//Clean exit of program 
ExitX() ; // clean up memory 
return 0 ;
}