#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 7;
double st = 1e-6;
const double inf = 0x7f7f7f7f;
double a[maxn][maxn];
double b[maxn][maxn];
double u[maxn][maxn];
double A[maxn][maxn];
double l[maxn][maxn];
double D[maxn][maxn];
const double eps = 1e-6;

void back() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            a[i][j] = b[i][j];
        }
    }
}

bool run(double k[], double kk[], int n) {
    double tmp = 0;
    for (int i = 0; i < n; ++i) {
        double tem = k[i] - kk[i];
        tmp += (tem * tem);
    }
    return abs(tmp) > st;
}

void jaboci(int n) {
    int qqq = 0;
    double x[maxn];
    double B[maxn];
    double last[maxn];
    memset(B, 0, sizeof B);
    memset(x, 0, sizeof x);
    for (int i = 0; i < n; ++i) {
        B[i] = a[i][n];
    }
    cout << "Input the inintal vector of the x";
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        last[i] = inf;
    }
    while (run(x, last, n)) {
        ++qqq;
        for (int i = 0; i < n; ++i) {
            last[i] = x[i];
            x[i] = B[i];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                x[i] -= a[i][j] * last[j];
            }
            x[i] /= a[i][i];
        }
    }

    cout << "the ans of the jaboci:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << x[i] << " ";
    }

    cout << endl;
    cout << "迭代次数 : " << qqq << endl;
}

int sgn(const double &k) {
    if (abs(k) <= eps) return 0;
    if (k - eps > 0)
        return 1;
    else
        return -1;
}

void gauss(int n) {
    double x[maxn];
    for (int i = 0; i < n; ++i) {
        int maxl = i;
        for (int j = i; j < n; ++j) {
            if (a[maxl][maxl] <= a[j][j]) {
                maxl = j;
            }
        }
        if (a[maxl][maxl] == 0) {
            cout << "无解" << endl;
            return;
        }
        for (int j = 0; j < n + 1; ++j) {
            double tem = a[maxl][j];
            a[maxl][j] = a[i][j];
            a[i][j] = tem;
        }
        for (int j = i + 1; j < n; ++j) {
            double k = a[j][i] / a[i][i];
            for (int l = i; l < n + 1; ++l) {
                a[j][l] -= (k * a[i][l]);
            }
        }
    }
    cout << "the martix:";
    cout << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    x[n - 1] = a[n - 1][n] / a[n - 1][n - 1];
    for (int i = n - 2; i >= 0; --i) {
        for (int j = n - 1; j > i; --j) {
            a[i][n] -= (a[i][j] * x[j]);
        }
        x[i] = a[i][n] / a[i][i];
        if (sgn(x[i]) == 0) x[i] = 0;
    }
    cout << "The ans of the gauss:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << x[i] << " ";
    }
}

void sor(int n) {
    int kkk = 0;
    double last[maxn];
    memset(last, 0, sizeof last);
    cout << "Input the inintal of the sor:" << endl;
    double x[maxn];
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    while (run(last, x, n)) {
        ++kkk;
        for (int i = 0; i < n; ++i) {
            last[i] = x[i];
        }
        memset(x, 0, sizeof x);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                x[i] -= a[i][j] * x[j];
            }
            for (int j = i + 1; j < n; ++j) {
                x[i] -= a[i][j] * last[j];
            }
            x[i] += a[i][n];
            x[i] /= a[i][i];
        }
    }
    cout << "The ans of the sor:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << x[i] << " ";
    }
    cout << endl;
    cout << "迭代次数 : " << kkk << endl;
}

void lu(int n) {
    memset(l, 0, sizeof l);
    memset(u, 0, sizeof u);
    for (int i = 0; i < n; ++i) {
        u[0][i] = a[0][i];
        l[i][i] = 1;
    }
    for (int i = 1; i < n; ++i) {
        l[i][0] = a[i][0] / u[0][0];
        a[i][0] /= a[0][0];
    }
    for (int r = 1; r < n; ++r) {
        for (int i = r; i < n; ++i) {
            double tem = 0;
            double tem2 = 0;
            for (int k = 0; k < r; ++k) {
                tem2 += (a[r][k] * a[k][i]);
                tem += (l[r][k] * u[k][i]);
            }
            u[r][i] = a[r][i] - tem;
            a[r][i] -= tem2;
        }
        if (r != n) {
            for (int i = r + 1; i < n; ++i) {
                double tem = 0;
                double tem2 = 0;
                for (int k = 0; k < r; ++k) {
                    tem2 += a[i][k] * u[k][r];
                    tem += l[i][k] * u[k][r];
                }
                l[i][r] = (a[i][r] - tem) / u[r][r];
                a[i][r] -= tem2;
                a[i][r] /= a[r][r];
            }
        }
    }
    // double ans[maxn][maxn];
    // memset(ans, 0, sizeof ans);
    // for (int i = 0; i < 4; ++i) {
    //     for (int j = 0; j < 4; ++j) {
    //         for (int k = 0; k < 4; ++k) {
    //             ans[i][k] += l[i][j] * u[j][k];
    //         }
    //     }
    // }
    // for (int i = 0; i < 4; ++i) {
    //     for (int j = 0; j < 4; ++j) {
    //         cout << ans[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout << endl;
    cout << "a:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
    cout << "l:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << l[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
    cout << "u:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << u[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    double y[maxn];
    double x[maxn];
    memset(y, 0, sizeof y);
    memset(x, 0, sizeof x);
    y[0] = a[0][n];
    // cout << y[0] << endl;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            a[i][n] -= l[i][j] * y[j];
        }
        y[i] = a[i][n];
    }

    x[3] = y[3] / u[3][3];
    for (int i = n - 1; i >= 0; --i) {
        for (int k = i + 1; k < n; ++k) {
            y[i] -= u[i][k] * x[k];
        }
        // cout << "???" << endl;
        x[i] = y[i] / u[i][i];
        if (sgn(x[i]) == 0) x[i] = 0;
    }
    cout << "The answer of the LU: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << x[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "Input the size of the martix:";
    int tmm;
    cin >> tmm;
    for (int i = 0; i < tmm; ++i) {
        for (int j = 0; j <= tmm; ++j) {
            cin >> a[i][j];
            b[i][j] = a[i][j];
        }
    }
    cout << endl;
    gauss(tmm);
    cout << endl;
    back();
    cout << endl;
    lu(tmm);
    cout << endl;
    back();
    jaboci(tmm);
    back();
    sor(tmm);
}
/*
10 -7 0 1 8
-3 2.099999 6 2 5.900001
5 -1 5 -1 5
2 1 0 2 1
*/