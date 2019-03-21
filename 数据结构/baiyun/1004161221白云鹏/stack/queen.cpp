#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;
const int maxn = 10;
int ans = 0;
bool mark[maxn][maxn];
bool test(int x, int y) {
    if (x < 0 || y < 0) return 0;
    if (x >= 8 || y >= 8) return 0;
    for (int i = 0; i < 8; ++i) {
        if (mark[x][i] == 1) return 0;
    }
    for (int i = 0; i < 8; ++i) {
        if (mark[i][y] == 1) return 0;
    }
    int min1 = min(x, y);
    for (int i = 0; i <= min1; ++i) {
        int nextx = x - i;
        int nexty = y - i;
        if (mark[nextx][nexty]) return 0;
    }
    for (int i = 0; i < 8; ++i) {
        int nextx = x + i;
        int nexty = y + i;
        if (nextx >= 8 || nexty >= 8) break;
        if (mark[nextx][nexty]) return 0;
    }
    for (int i = 0; i < 8; ++i) {
        int nextx = x + i;
        int nexty = y - i;
        if (nexty < 0) break;
        if (nextx >= 8 || nexty >= 8) break;
        if (mark[nextx][nexty]) return 0;
    }
    for (int i = 0; i < 8; ++i) {
        int nextx = x - i;
        int nexty = y + i;
        if (nextx >= 8 || nexty >= 8) break;
        if (nextx < 0) break;
        if (mark[nextx][nexty]) return 0;
    }
    return 1;
}
int G[maxn][maxn];
void dfs(int n) {
    if (n == 8) {
        cout << "ans" << ++ans << ":" << endl;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                cout << mark[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    for (int j = 0; j < 8; ++j) {
        if (test(n, j)) {
            mark[n][j] = 1;
            dfs(n + 1);
            mark[n][j] = 0;
        }
    }
    return;
}
int main() {
    dfs(0);
    cout << "Total:" << ans << endl;
}