#include <iostream>
using namespace std;

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
        return Heron_sqrt(re * re + im * im);
    }
    double Heron_sqrt(double a) const {
        double x = a;
        for (int i = 0; i < 10; i++) {
            x = 0.5 * (x + a / x);
        }
        return x;
    }
};


int main(){
    //four integer numbers from input
    double a, b, c, d;
    cout << "Enter four integers, separated by space: ";
    cin >> a >> b >> c >> d;
    //print as complex number
    complex_d c1(a, b);
    complex_d c2(c, d);
    cout << "c1 = " << c1.re << " + " << c1.im << "i" << endl;
    cout << "c2 = " << c2.re << " + " << c2.im << "i" << endl;
    
    //arithmetics
    complex_d sum = c1 + c2;
    complex_d diff = c1 - c2;
    complex_d prod = c1 * c2;
    complex_d quot = c1 / c2;
    complex_d abs_c1 = c1.absolute();
    complex_d abs_c2 = c2.absolute();

    //print results
    cout << "c1 + c2 = " << sum.re << " + " << sum.im << "i" << endl;
    cout << "c1 - c2 = " << diff.re << " + " << diff.im << "i" << endl;
    cout << "c1 * c2 = " << prod.re << " + " << prod.im << "i" << endl;
    cout << "c1 / c2 = " << quot.re << " + " << quot.im << "i" << endl;
    cout << "|c1| = " << abs_c1.re << endl;
    cout << "|c2| = " << abs_c2.re << endl;
    return 0;
}