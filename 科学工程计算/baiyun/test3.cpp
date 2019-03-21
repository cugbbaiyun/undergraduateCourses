#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
double x[10];
double y[10];
double p[5][20];
double b[5];
double a[5];
int nx = 7;
double a_[5];
double getp(const double &t, int i, double pk, double pk_1) {
    return (t - a[i]) * pk - b[i - 1] * pk_1;
}
void init() {
    memset(b, 0, sizeof b);
    memset(p, 0, sizeof p);
    memset(a, 0, sizeof a);
    double tem = 0;
    for (int i = 0; i < nx; ++i) {
        p[0][i] = 1;
        a[0] += x[i] * p[0][i] * p[0][i];
        tem += p[0][i] * p[0][i];
    }
    a[0] /= tem;
    for (int i = 0; i < nx; ++i) {
        p[1][i] = x[i] - a[0];
    }
    for (int i = 1; i < 4; ++i) {
        double pkpk = 0;
        double pk_pk_ = 0;
        double xpkpk = 0;
        for (int j = 0; j < nx; ++j) {
            pkpk += p[i][j] * p[i][j];
            xpkpk += x[j] * p[i][j] * p[i][j];
        }
        a[i] = xpkpk / pkpk;
        for (int j = 0; j < nx; ++j) {
            pk_pk_ += p[i - 1][j] * p[i - 1][j];
        }
        b[i - 1] = pkpk / pk_pk_;
        for (int j = 0; j < nx; ++j) {
            p[i + 1][j] = getp(x[j], i, p[i][j], p[i - 1][j]);
        }
    }
    cout << "a:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "b:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;
    cout << "a*:" << endl;
    for (int i = 0; i < 4; ++i) {
        double pkf = 0;
        double pkpk = 0;
        for (int j = 0; j < nx; ++j) {
            pkf += p[i][j] * y[j];
            pkpk += p[i][j] * p[i][j];
        }
        a_[i] = pkf / pkpk;
        cout << a_[i] << " ";
    }
    cout << endl;
}

double sx(const double &t) {
    double ans = 0;
    double q[10];
    q[0] = 1;
    q[1] = t - a[0];
    for (int i = 1; i < 4; ++i) {
        q[i + 1] = getp(t, i, q[i], q[i - 1]);
    }
    for (int i = 0; i < 4; ++i) {
        ans += a_[i] * q[i];
    }
    return ans;
}

double fx(const double &t) {
    return (double) 1.0 / (t * t * 25 + 1.0);
}
void updatexy() {
    nx = 11;
    for (int i = 0; i <= 10; ++i) {
        x[i] = -1 + 0.2 * i;
        y[i] = fx(x[i]);
    }
    for (int i = 1; i < 4; ++i) {
    }
}

int main() {
    for (int i = 0; i < nx; ++i) {
        cin >> x[i];
    }
    for (int j = 0; j < nx; ++j) {
        cin >> y[j];
    }
    init();
    for (int i = 0; i < nx; ++i) {
        cout << sx(x[i]) << " ";
    }
    cout << endl;
    updatexy();
    init();
    cout << "S(0.98): " << endl;
    cout << sx(0.98) << endl;
    return 0;
}
/*

0.0 0.1 0.2 0.3 0.5 0.8 1.0
1.0 0.41 0.50 0.61 0.91 2.02 2.46

*/
