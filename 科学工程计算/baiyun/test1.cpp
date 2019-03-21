#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 50;
double x[maxn];
double y[maxn];
double form[maxn];
double xx[maxn];
int k;
int kk;
double larg(double xxx) {
    double l[maxn];
    for (int j = 0; j < k; ++j) {
        l[j] = 1;
        for (int i = 0; i < k; ++i) {
            if (i == j) continue;
            l[j] *= ((xxx - x[i]) / (x[j] - x[i]));
        }
    }
    double ans = 0;
    for (int i = 0; i < k; ++i) {
        ans += (y[i] * l[i]);
    }
    return ans;
}

double fx(double xxx) {
    return (double) (1.0) / (1.0 + 25 * xxx * xxx);
}

double getxy() {
    xx[0] = 0.98;
}

void test() {
    getxy();
    kk = 1;
    for (k = 5; k <= 20; ++k) {
        cout << "k=" << k << endl;
        for (int i = 0; i < k; ++i) {
            x[i] = (double) (-1) + (double) 2.0 * i / k;
            y[i] = fx(x[i]);
        }
        for (int i = 0; i < kk; ++i) {
            cout << xx[i] << ":";
            double tt = larg(xx[i]);
            printf("%.8f\n", tt);
        }
    }
}

int main() {
    test();
}
//样例说明：
//首先输入样本点的个数
//然后输入样本点
//输入待求x的个数
//接下来输入待求点的x坐标
/*

5
0.2 0.98 0.4 0.92 0.6 0.81 0.8 0.64 1.0 0.38
4
0.2  0.208   1.08   1.0

 */