#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 50;
double B[maxn];
double xk[maxn];
double q[maxn][maxn];
double ans[maxn];
double eps = 0.005;
int n;
void input();
void getWork();
void init();
bool run(double *k);
double fun1(double rk[maxn], double rk2[maxn]);
void fun2(double rk[maxn], double rk2[maxn][maxn], double qqq[maxn]);
void fun3(double a, double rk[maxn], double rk_1[maxn]);
void fun4(double rk[maxn][maxn], double dk[maxn], double ans[maxn]);
void solv();

void getWork() {
    cout << "Input the nums of the unknown x:" << endl;
    cin >> n;
    B[0] = 14;
    B[n - 1] = 14;
    for (int i = 1; i < n - 1; ++i) {
        B[i] = 22;
    }
    q[0][0] = 6;
    q[0][1] = 8;
    q[n - 1][n - 1] = 6;
    q[n - 1][n - 2] = 8;
    for (int i = 1; i < n - 1; ++i) {
        q[i][i] = 6;
        q[i][i - 1] = 8;
        q[i][i + 1] = 8;
    }
}

void input() {
    cout << "Input the nums of the unknown x:" << endl;
    cin >> n;
    cout << "Input the b:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> B[i];
    }
    cout << "Input the A:" << endl;
    cout << "The A should be symmetric" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> q[i][j];
        }
    }
    cout << "Input the initial x:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> xk[i];
    }
}

void init() {
    memset(B, 0, sizeof B);
    memset(xk, 0, sizeof xk);
    memset(q, 0, sizeof q);
    int mode;
    cout << "1.The martix is in the homework" << endl;
    cout << "2.Input the martix" << endl;
    cout << "Input the choice:";
    cin >> mode;
    if (mode == 1)
        getWork();
    else
        input();
}

bool run(double *k) {
    double sum1 = 0;
    for (int i = 0; i < n; ++i) {
        sum1 += (k[i] * k[i]);
    }
    return sum1 >= eps * eps;
}

double fun1(double rk[maxn], double rk2[maxn]) {
    double sum1 = 0;
    for (int i = 0; i < n; ++i) {
        sum1 += (rk[i] * rk2[i]);
    }
    return sum1;
}
void fun2(double rk[maxn], double rk2[maxn][maxn], double qqq[maxn]) {
    for (int i = 0; i < n; ++i) {
        qqq[i] = 0;
        for (int j = 0; j < n; ++j) {
            qqq[i] += (rk2[j][i] * rk[j]);
        }
    }
}
void fun3(double a, double rk[maxn], double rk_1[maxn]) {
    for (int i = 0; i < n; ++i) {
        rk_1[i] = xk[i];
        rk_1[i] += rk[i] * a;
    }
}
void fun4(double rk[maxn][maxn], double dk[maxn], double ans[maxn]) {
    for (int i = 0; i < n; ++i) {
        ans[i] = 0;
        for (int j = 0; j < n; ++j) {
            ans[i] += rk[i][j] * dk[j];
        }
    }
}
void solv() {
    double rk[maxn];
    double dk[maxn];
    for (int i = 0; i < n; ++i) {
        rk[i] = B[i];
        double sum1 = 0;
        for (int j = 0; j < n; ++j) {
            sum1 += q[i][j] * xk[j];
        }
        rk[i] -= sum1;
        dk[i] = rk[i];
    }
    while (1) {
        double up = fun1(rk, rk);
        double tem2[maxn];
        memset(tem2, 0, sizeof tem2);
        fun2(dk, q, tem2);
        double down = fun1(tem2, dk);
        double ak = up / down;
        double xk_1[maxn];
        fun3(ak, dk, xk_1);
        cout << "xk_1:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << xk_1[i] << " ";
        }
        cout << endl;
        memset(tem2, 0, sizeof tem2);
        fun4(q, dk, tem2);
        double rk_1[maxn];
        for (int i = 0; i < n; ++i) {
            rk_1[i] = rk[i] - ak * tem2[i];
        }
        if (run(rk_1) == 0) {
            for (int i = 0; i < n; ++i) {
                ans[i] = xk_1[i];
            }
            return;
        }
        up = fun1(rk_1, rk_1);
        down = fun1(rk, rk);
        double bk = up / down;
        for (int i = 0; i < n; ++i) {
            dk[i] = rk_1[i] + bk * dk[i];
            xk[i] = xk_1[i];
            rk[i] = rk_1[i];
        }
        cout << endl;
    }
}

int main() {
    init();
    solv();
    cout << endl << endl;
    cout << "The ans is:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    // cout << endl;
    // double back[maxn];
    // fun4(q, ans, back);
    // for (int i = 0; i < n; ++i) {
    //     cout << back[i] << " ";
    // }
    cout << endl;
}