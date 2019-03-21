#include <cstring>
#include <iostream>
using namespace std;
int *arr;
bool *mark;
int len;
long long k = 0;
void dfs(int n) {
    if (n == len) {
        for (int i = 0; i < len; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        ++k;
        return;
    }
    for (int i = 1; i <= len; ++i) {
        if (mark[i]) continue;
        mark[i] = 1;
        arr[n] = i;
        dfs(n + 1);
        mark[i] = 0;
    }
}
int main() {
    cout << "Input the length of the array:";
    cin >> len;
    arr = new int[len + 7];
    mark = new bool[len + 7];
    for (int i = 0; i < len; ++i) {
        mark[i] = 0;
    }
    dfs(0);
    cout << "Total:" << k << endl;
}