#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const double low = 0;
const double high = 1;
const int maxn = 50;
const double eps = 1e-8;
double T[maxn];
double S[maxn];
double R[maxn];
double C[maxn];
double fx(const double &t) {
    return (double) 1.0 / (t + (double) 1.0);
}
bool run(const double &last, const double &rk) {
    if (abs(last - rk) < eps)
        return 0;
    else
        return 1;
}
double romberg(int k) {
    k += 3;
    double h = (high - low);
    T[0] = h / 2 * (fx(low) + fx(high));
    for (int j = 1; j < k; ++j) {
        double sum1 = 0;
        double now = low;
        while (now < high) {
            sum1 += fx(now);
            now += h;
        }
        T[j] = (T[j - 1] / 2 + h * sum1 / 2);
        h /= 2;
    }
    for (int i = 0; i < k - 1; ++i) {
        S[i] = T[i + 1] + (T[i + 1] - T[i]) / (double) 3.0;
    }
    for (int i = 0; i < k - 2; ++i) {
        C[i] = S[i + 1] + (S[i + 1] - S[i]) / (double) 15.0;
    }
    int i;
    for (i = 0; i < k - 3; ++i) {
        R[i] = C[i + 1] + (C[i + 1] - C[i]) / (double) 63.0;
    }
    return R[k - 4];
}
void init() {
    T[1] = (high - low) * (fx(high) + fx(low)) / 2;
}
double solv() {
    init();
    int k = 1;
    double last = 0;
    double rk = 0;
    do {
        last = rk;
        rk = romberg(k++);
        cout << rk << endl;
    } while (run(last, rk));
    return rk;
}
int main() {
    double ans = solv();
    printf("%.8lf", ans);
}