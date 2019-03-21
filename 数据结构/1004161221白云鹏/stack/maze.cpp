#include "stack.cpp"
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using pii = pair<int, int>;
set<stack<pii>> anss;
stack<pii> ans;
bool G[8][8];
bool mark[8][8];
pii dir[8] = {pii(-1, 0), pii(1, 0), pii(0, -1), pii(0, 1),pii(-1,-1),pii (1,-1),pii(-1,1),pii(1,1)};
stack<stack<int>> ss;
bool test(int x, int y) {
    return (G[x][y] == 1) && (mark[x][y] == 0);
}

void dfs() {
    stack<pii> st;
    st.push(pii(1, 1));
    mark[1][1] = 1;
    {
        stack<int> tem;
        tem.push(-1);
        ss.push(tem);
    }
    while (!st.isEmpty()) {
        auto c = st.getTop();
        if (c.first == 5 && c.second == 5) {
            anss.insert(st);
            st.pop();
            ss.pop();
            mark[c.first][c.second] = 0;
            continue;
        }
        int start = ss.getTop().getTop() + 1;
        if (start >= 8) {
            st.pop();
            ss.pop();
            mark[c.first][c.second] = 0;
            continue;
        }
        int cc = 0;
        for (; start < 8; ++start) {
            int nx = c.first + dir[start].first;
            int ny = c.second + dir[start].second;
            ss.getTop().push(start);
            if (test(nx, ny)) {
                mark[nx][ny] = 1;
                st.push(pii(nx, ny));
                stack<int> tem;
                tem.push(-1);
                ss.push(tem);
                ++cc;
                break;
            }
        }
        if (cc == 0) {
            st.pop();
            ss.pop();
            mark[c.first][c.second] = 0;
        }
    }
    return;
}

int main() {
    for (int i = 1; i <= 5; ++i) {
        G[1][i] = 1;
    }
    G[2][1] = G[2][4] = 1;
    G[3][1] = G[3][3] = G[3][4] = G[3][5] = 1;
    G[4][1] = G[4][2] = G[4][3] = G[4][5] = 1;
    G[5][1] = G[5][4] = G[5][5] = 1;
    dfs();
    while (!ans.isEmpty()) {
        cout << ans.getTop().first << "," << ans.getTop().second << " ";
        ans.pop();
    }
    cout << "Total:";
    cout << anss.size() << endl;
    // for (auto tem : anss) {
    //     stack<pii> c;
    //     while (!tem.isEmpty()) {
    //         c.push(tem.getTop());
    //         tem.pop();
    //     }
    //     while (!c.isEmpty()) {
    //         cout << "(";
    //         cout << c.getTop().first << "," << c.getTop().second << "";
    //         cout << ")";
    //         if (c.getSize() != 1) {
    //             cout << " -> ";
    //         }
    //         c.pop();
    //     }
    //     cout << endl;
    // }
    for(auto tem:anss){
        while(!tem.isEmpty()){
            cout << tem.getTop().first << "," << tem.getTop().second << " ";
            tem.pop();
        }
        cout << endl;
    }
}
