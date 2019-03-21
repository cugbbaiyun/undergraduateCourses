#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
double eps = 1e-8;
const double low = 0;
const double high = 1.0;
const int step = 5;
double fx(const double &t) {
    return (double) 1.0 / (t + 1.0);
}
bool sgn(const double &s1, const double &s2) {
    return (abs(s1 - s2)) > 15 * eps;
}
double varsimpson() {
    double h = 0, tn = 0, hn = 0, sn = 0, t2n = 0, h2n = 0, s2n = 0;
    int n = 1;
    h = high - low;
    tn = h * (fx(low) - fx(high)) / (double) 2.0;
    hn = h * fx((low + high) / (double) 2.0);
    sn = (tn + (double) 2.0 * hn) / (double) 3.0;
    double back;
    do {
        t2n = (tn + hn) / (double) 2.0;
        h /= (double) 2.0;
        n *= 2;
        h2n = 0;
        for (int i = 1; i <= n; ++i) {
            h2n += h * (fx(low + (i - (double) 0.5) * h));
        }
        s2n = (t2n + 2 * h2n) / 3.0;
        // cout << sn << " " << s2n << endl;
        back = sn;
        tn = t2n;
        hn = h2n;
        sn = s2n;
    } while (sgn(back, s2n));
    return sn;
}

int main() {
    printf("%.8f", varsimpson());
}