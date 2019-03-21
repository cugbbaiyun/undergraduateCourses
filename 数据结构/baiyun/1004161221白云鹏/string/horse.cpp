#include "adt.cpp"
using namespace std;
int max1[maxn];
int min1[maxn];
vector<adt<int>> ans;
void init() {
    for (int i = 0; i < maxn; ++i) {
        max1[i] = -1;
        min1[i] = 999;
    }
    cout << "输入行列数目" << endl;
    cin >> mar.n >> mar.m;
    for (int i = 0; i < mar.n; ++i) {
        for (int j = 0; j < mar.m; ++j) {
            int t;
            cin >> t;
            if (min1[i] > t) {
                min1[i] = t;
            }
            if (max1[j] < t) {
                max1[j] = t;
            }
            if (t != 0) {
                adt<int> tem;
                tem.x = i;
                tem.y = j;
                tem.num = t;
                mar.push_back(tem);
            }
        }
    }
}
void getans() {
    for (auto c : mar.num) {
        if (min1[c.x] == c.num && max1[c.y] == c.num) {
            ans.push_back(c);
        }
    }
}
int main() {
    init();
    getans();
    for (auto c : ans) {
        cout << "martix"
             << "[" << c.x << "]"
             << "[" << c.y << "] = " << c.num << " ";
    }
}