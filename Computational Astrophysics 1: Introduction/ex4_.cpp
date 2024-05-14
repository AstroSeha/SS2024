// Implement your own struct/class complex d for complex numbers (with double type members) as shown in the lecture and test it. This class should be able to perform the following operations: +,-,*,/ and also taking the absolute of a complex number: absolute(). Test your class with some basic calculations in the main program.
//Bonus: Avoid using the cmath library at all by implementing also your own method sqrt() for the absolute. Hint: Use Heron’s method. You might need to declare the corresponding function as const:
//double my_sqrt(double a) const { ... }

#include <iostream>

class complex_d {
public:
    double re, im;
    complex_d(double re, double im) : re(re), im(im) {}
    complex_d operator+(const complex_d& c) const {
        return complex_d(re + c.re, im + c.im);
    }
    complex_d operator-(const complex_d& c) const {
        return complex_d(re - c.re, im - c.im);
    }
    complex_d operator*(const complex_d& c) const {
        return complex_d(re * c.re - im * c.im, re * c.im + im * c.re);
    }
    complex_d operator/(const complex_d& c) const {
        double den = c.re * c.re + c.im * c.im;
        return complex_d((re * c.re + im * c.im) / den, (im * c.re - re * c.im) / den);
    }
    double absolute() const {
        return my_sqrt(re * re + im * im);
    }
    double my_sqrt(double a) const {
        double x = a;
        for (int i = 0; i < 10; i++) {
            x = 0.5 * (x + a / x);
        }
        return x;
    }
};