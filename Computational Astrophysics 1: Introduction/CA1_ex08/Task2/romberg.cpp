#include <cmath>
#include <algorithm>

double romberg(double (*func)(double), double a, double b, int max_steps, double tol) {
    double R[max_steps][max_steps];

    R[0][0] = 0.5 * (b - a) * (func(a) + func(b));

    for (int k = 1; k < max_steps; ++k) {
        double sum = 0.0;
        int n = 1 << (k - 1); // 2^(k-1)
        double h = (b - a) / n;
        for (int i = 1; i <= n; ++i) {
            sum += func(a + (i - 0.5) * h);
        }
        R[k][0] = 0.5 * (R[k - 1][0] + (b - a) * sum / n);

        for (int j = 1; j <= k; ++j) {
            R[k][j] = R[k][j - 1] + (R[k][j - 1] - R[k - 1][j - 1]) / (pow(4, j) - 1);
        }

        if (fabs(R[k][k] - R[k - 1][k - 1]) < tol) {
            return R[k][k];
        }
    }
    return R[max_steps - 1][max_steps - 1];
}
