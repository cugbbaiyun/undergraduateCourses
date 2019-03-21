#include <iostream>

using namespace std;

int main() {
    cout << "请输入对三角矩阵中的非零数，用‘Z’表示结束" << endl;
    char temp[200];
    int N;
    for (int i = 0;; i++) {
        cin >> temp[i];
        N = i + 1;
        if (temp[i] == 'z' || temp[i] == 'Z') break;
    }
    int n = (N + 2) / 3;
    double A[N], B[n];
    cout << "请输入结果矩阵的值" << endl;
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }
    for (int i = 0; i < N; i++) {
        A[i] = temp[i] - '0';
    }
    double a[n], b[n - 1], c[n - 1];
    for (int i = 0, j = 0, k = 0, l = 1; i < N; i++) {
        if (i % 3 == 0) //初始化a[]
        {
            a[j] = A[i];
            j++;
        } else if (i % 3 == 1) //初始化c[]
        {
            c[k] = A[i];
            k++;
        } else //初始化b[]
        {
            b[l] = A[i];
            l++;
        }
    }

    //计算p，q，存入a c
    c[0] = c[0] / a[0];
    for (int i = 1; i < n; i++) {
        a[i] = a[i] - b[i] * c[i - 1]; //此时a[i]表示p[i]
        c[i] = c[i] / a[i];            //此时c[i]表示q[i]
    }
    double y[n] = {0};
    y[0] = B[0] / a[0];

    for (int i = 1; i < n; i++) {
        y[i] = (B[i] - b[i] * y[i - 1]) / a[i];
    }
    double x[n] = {0};
    x[n - 1] = y[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = y[i] - c[i] * x[i + 1];
    }
    return 0;
}
