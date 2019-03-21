#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
const double pi = acos(-1);
double pnt[20];
int n;

double p1x(double x) {
    return x;
}
double p2x(double x) {
    return (double) 1.5 * x * x - (double) 0.5;
}
double p3x(double x) {
    return (double) 2.5 * x * x * x - (double) 1.5 * x;
}
double getpnt() {
    pnt[0] = 1;
    for (int i = 1; i < n; ++i) {
        pnt[i + 1] = (2 * i + 1) * pnt[1] * pnt[i] - i * pnt[i - 1];
        pnt[i + 1] /= (i + 1);
    }
}

void test1(double t) {
    double p0f = 0;
    double p1f = double(8) / pi / pi;
    double p2f = 0;
    double p3f = (double) 2.5 * (pi * (double) 24 * pi - (double) 96 * 2) / pow(pi, 4) - (double) 12.0 / pi / pi;
    double p1p1 = (double) 2.0 / (double) 3.0;
    double p3p3 = (double) 2.0 / (double) 7.0;
    double p11 = p1f / p1p1;
    double p33 = p3f / p3p3;
    double ans = p11 * p1x(t) + p33 * p3x(t);
    printf("%.8lf", ans);
    cout << endl;
}

double test2(double t) {
    double p0f = (double) 0.2 * (atan(5) - atan(-5));
    double p2f = (double) 3.0 / (double) 25.0 - (double) 14.0 / (double) 125.0 * (atan(5) - atan(-5));
    double p0p0 = 2.0;
    double p2p2 = (double) 2.0 / (double) 5.0;
    double p00 = p0f / p0p0;
    double p22 = p2f / p22;
    double ans = p22 * p2x(t) + p00 * 1;
    printf("%.8f", ans);
    cout << endl;
}

int main() {
    cin >> pnt[1];
    getpnt();
    for (int i = 0; i < 20; ++i) {
        cout << pnt[i] << " ";
    }
    cout << endl;
    test1(0.98);
    test2(0.98);
}