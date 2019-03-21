#include "adt.cpp"
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
