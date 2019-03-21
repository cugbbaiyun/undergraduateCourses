#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
const int maxn = 1e5 + 7;
template <typename T> struct adt {
    int x;
    int y;
    T num;
};
template <typename T> struct martix {
    vector<adt<T>> num;
    int m, n;
    void push_back(const adt<T> &a) {
        num.push_back(a);
        return;
    }
    martix getT() {
        vector<adt<T>> ttt(num);
        martix ret;
        int rowsize[maxn];
        int rowstart[maxn];
        memset(rowsize, 0, sizeof rowsize);
        memset(rowstart, 0, sizeof rowstart);
        for (auto c : num) {
            rowsize[c.y]++;
        }
        for (int i = 1; i < maxn; ++i) {
            rowstart[i] = rowstart[i - 1] + rowsize[i - 1];
        }
        for (int i = 0; i < num.size(); ++i) {
            adt<T> tem;
            tem.x = num[i].y;
            tem.y = num[i].x;
            tem.num = num[i].num;
            ttt[rowstart[tem.x]++] = tem;
        }
        ret.num = ttt;
        ret.m = n;
        ret.n = m;
        return ret;
    }
    void makeup() {
        sort(num.begin(), num.end(), [=](adt<T> a, adt<T> b) {
            if (a.x != b.x)
                return a.x < b.x;
            else
                return a.y < b.y;
        });
    }
    void output() {
        makeup();
        int top = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (top < num.size() && num[top].x == i && num[top].y == j) {
                    cout << num[top++].num << " ";
                } else
                    cout << 0 << " ";
            }
            cout << endl;
        }
    }
};
martix<int> mar;

/*
int main() {
  cout << "输入行列数目" << endl;
  cin >> mar.n >> mar.m;
  for (int i = 0; i < mar.n; ++i) {
    for (int j = 0; j < mar.m; ++j) {
      cout << "输入"
           << "a"
           << "[" << i << "]"
           << "[" << j << "]" << endl;
      int t;
      cin >> t;
      if (t != 0) {
        adt<int> tem;
        tem.x = i;
        tem.y = j;
        tem.num = t;
        mar.push_back(tem);
      }
    }
  }
  mar.output();
  auto c = mar.getT();
  c.output();
}

*/