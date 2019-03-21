#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 50;
double d[maxn];
double x[maxn];
double h[maxn];
double y[maxn];
double lymbda[maxn];
double martix[maxn][maxn];
double m[maxn];
double u[maxn];
double testx;
int n;
void LU(int n);
double f(const double &k) {
    return (double) 1.0 / ((double) 1.0 + (double) 25 * k * k);
}
void getxy() {
    for (int i = 0; i <= n; ++i) {
        x[i] = (double) (-1) + (double) 2.0 * i / n;
        y[i] = f(x[i]);
    }
}
void geth() {
    for (int i = 1; i <= n; ++i) {
        h[i] = x[i] - x[i - 1];
    }
}
void getdlymu() {
    for (int i = 1; i <= n; ++i) {
        d[i] = (double) 6.0 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i]) / (h[i] + h[i + 1]);
        lymbda[i] = h[i + 1] / (h[i] + h[i + 1]);
        u[i] = 1 - lymbda[i];
    }
    lymbda[0] = 0;
    u[n] = 0;
}
double f2(const double &ttt) {
    double tem = f(ttt);
    return (double) (-50) * (tem * tem - (double) (100 * ttt) * tem * tem * tem);
}
void getmartix() {
    m[0] = f2(-1);
    m[n] = f2(1);
    lymbda[0] = u[n] = 0;
    d[0] = 2 * m[0];
    d[n] = 2 * m[n];
    martix[0][0] = 2;
    martix[0][1] = lymbda[0];
    martix[n][n] = 2;
    martix[n][n - 1] = u[n];
    for (int i = 1; i <= n - 1; ++i) {
        martix[i][i] = 2;
        martix[i][i - 1] = u[i];
        martix[i][i + 1] = lymbda[i];
    }
}
double sx(int i) {
    double sum1 = 0;
    double t1 = x[i] - testx;
    double t2 = testx - x[i - 1];
    sum1 += (m[i - 1] * t1 * t1 * t1) / ((double) 6.0 * h[i]) + m[i] * (t2 * t2 * t2) / ((double) 6.0 * h[i]);
    sum1 += (y[i - 1] - m[i - 1] * h[i] * h[i] / (double) 6.0) * (t1 / h[i]);
    sum1 += (y[i] - m[i] * h[i] * h[i] / (double) 6.0) * (t2 / h[i]);
    return sum1;
}
double solv() {
    // cin >> testx;
    for (int i = 1; i <= n; ++i) {
        if (testx < x[i]) return sx(i);
    }
}
double init() {
    memset(x, 0, sizeof x);
    memset(y, 0, sizeof y);
    memset(h, 0, sizeof h);
    memset(lymbda, 0, sizeof lymbda);
    memset(u, 0, sizeof u);
    memset(d, 0, sizeof d);
    // cout << "Input the nums of the sample point(start from 0):";
    // cin >> n;
    // int mode;
    // cout << "1.The martix in the homework:" << endl;
    // cout << "2.Input the sample points." << endl;
    // cout << "Input your choice:";
    // cin >> mode;
    // if (mode == 1) {
    // getxy();
    // } else if (mode == 2) {
    //     cout << "Input the x vector:" << endl;
    //     for (int i = 0; i < n; ++i) {
    //         cin >> x[i];
    //     }
    //     cout << "Input the y vector:" << endl;
    //     for (int i = 0; i < n; ++i) {
    //         cin >> y[i];
    //     }
    // }
    for(n=5;n<=20;++n){
        getxy();
        geth();
        getdlymu();
        getmartix();
        LU(n);
        testx = 0.98;
        cout << solv() << endl;
    }
}

void LU(int nn) {
    ++nn;
    double l[maxn][maxn];
    double uu[maxn][maxn];
    memset(l, 0, sizeof l);
    memset(uu, 0, sizeof uu);
    for (int i = 0; i < nn; ++i) {
        uu[0][i] = martix[0][i];
        l[i][i] = 1;
    }
    for (int i = 1; i < nn; ++i) {
        l[i][0] = martix[i][0] / uu[0][0];
        martix[i][0] /= martix[0][0];
    }
    for (int r = 1; r < nn; ++r) {
        for (int i = r; i < nn; ++i) {
            double tem = 0;
            double tem2 = 0;
            for (int k = 0; k < r; ++k) {
                tem2 += (martix[r][k] * martix[k][i]);
                tem += (l[r][k] * uu[k][i]);
            }
            uu[r][i] = martix[r][i] - tem;
            martix[r][i] -= tem2;
        }
        if (r != nn) {
            for (int i = r + 1; i < nn; ++i) {
                double tem = 0;
                double tem2 = 0;
                for (int k = 0; k < r; ++k) {
                    tem2 += martix[i][k] * uu[k][r];
                    tem += l[i][k] * uu[k][r];
                }
                l[i][r] = (martix[i][r] - tem) / uu[r][r];
                martix[i][r] -= tem2;
                martix[i][r] /= martix[r][r];
            }
        }
    }
    double yy[maxn];
    memset(yy, 0, sizeof yy);
    yy[0] = d[0];
    for (int i = 1; i < nn; ++i) {
        for (int j = 0; j < i; ++j) {
            d[i] -= l[i][j] * yy[j];
        }
        yy[i] = d[i];
    }
    m[nn - 1] = yy[nn - 1] / uu[nn - 1][nn - 1];
    for (int i = nn - 1; i >= 0; --i) {
        for (int k = i + 1; k < nn; ++k) {
            yy[i] -= uu[i][k] * m[k];
        }
        m[i] = yy[i] / uu[i][i];
    }
}
int main() {
    init();
}