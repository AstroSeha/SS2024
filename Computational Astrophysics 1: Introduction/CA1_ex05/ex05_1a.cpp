#include <iostream>
#include <cmath>
using namespace std ;
// set k = m = 1
int main () {
  int n = 10001, nout = 500 ;
  double t, v, v_old, x ;
  double const dt = 2. * M_PI / double(n-1) ;
  x = 1. ; t = 0. ; v = 0. ;
  for (int i = 0 ; i < n ; ++i) {
    t = t + dt ; v_old = v ;
    v = v - x * dt ;
    x = x + v_old * dt ;
    if (i % nout == 0) // print out only each nout step
      cout << t << " " << x << " " << v << endl ;
}
return 0 ; }