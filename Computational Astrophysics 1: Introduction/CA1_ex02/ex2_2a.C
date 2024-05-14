#include <stdio.h>

int main() {
    float y, x = 1.043E-13 ;
    x = x / 10. ; 
    y = x*x - (1.043E-14)*(1.043E-14) ;  

    printf("x= %.15f\n", x);
    printf("y= %.15f\n", y);

    return 0;
}