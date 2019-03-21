#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int maxn = 1e3 + 7;

template <typename T> struct edge {
    int start;
    int end;
    T cost;
    edge(int l = 0, int r = 0, int c = 0)
        : start(l)
        , end(r)
        , cost(c) {}
};

template <typename T> struct G {
    vector<edge<T>> E[maxn];
    vector<edge<T>> Es;
    bool mark[maxn];
    int root[maxn];
    int s, e;
    set<int> v;
    const T inf = 0x7ffff;

    void init() {
        memset(mark, 0, sizeof mark);
        for (auto &c : E) {
            c.clear();
        }
        addeage();
        cout << "Input the start and the end of the search:" << endl;
        cin >> s >> e;
    }

    int findroot(int n) {
        if (root[n] != n) {
            root[n] = findroot(root[n]);
        }
        return root[n];
    }

    void addeage() {
        cout << "Input the num of the edges:" << endl;
        int k;
        cin >> k;
        for (int i = 0; i < k; ++i) {
            int l, r, c;
            cout << "Input the start ,end and the cost of the edge:" << endl;
            cin >> l >> r >> c;
            v.insert(l);
            v.insert(r);
            E[l].push_back(edge<T>(l, r, c));
            Es.push_back(edge<T>(l, r, c));
        }
    }

    void dfs(int n) {
        if (mark[n]) return;
        for (auto c : E[n]) {
            if (!mark[c.end]) {
                mark[c.end] = 1;
                dfs(c.end);
                mark[c.end] = 0;
            }
        }
    }

    void bfs() {
        memset(mark, 0, sizeof mark);
        deque<int> q;
        q.push_back(s);
        while (!q.empty()) {
            auto c = q.front();
            q.pop_front();
            if (mark[c]) continue;
            for (auto d : E[c]) {
                if (mark[d.end]) {
                    continue;
                } else {
                    q.push_back(d.end);
                }
            }
            mark[c] = 1;
        }
    }

    T kru() {
        for (int i = 0; i < maxn; ++i) {
            root[i] = i;
        }
        sort(Es.begin(), Es.end(), [=](edge<T> a, edge<T> b) { return a.cost < b.cost; });
        int ans = 0;
        int k = 0;
        for (auto c : Es) {
            int l = findroot(c.start);
            int r = findroot(c.end);
            if (l == r) continue;
            ans += c.cost;
            root[l] = r;
            ++k;
            if (k == v.size() - 1) return ans;
        }
        if (k != v.size() - 1) return -1;
    }

    T prim() {
        if (v.size() == 1) return 0;
        memset(mark, 0, sizeof mark);
        T dis[maxn];
        int ok = 0;
        for (int i = 0; i < maxn; ++i) {
            dis[i] = inf;
        }
        T ans = 0;
        mark[1] = 1;
        ++ok;
        for (auto c : E[1]) {
            dis[c.end] = min(c.cost, dis[c.end]);
        }
        for (int tt = 0; tt < v.size(); ++tt) {
            int min1 = inf;
            int k = -1;
            for (int i = 0; i < maxn; ++i) {
                if (mark[i] == 0 && dis[i] < min1) {
                    min1 = dis[i];
                    k = i;
                }
            }
            ++ok;
            if (k == -1) return -1;
            mark[k] = 1;
            ans += min1;
            if (ok == v.size()) return ans;
            for (auto c : E[k]) {
                dis[c.end] = min(c.cost, dis[c.end]);
            }
        }
        cout << endl;
        if (ok == v.size())
            return ans;
        else
            return -1;
    }
};

int main() {
    G<int> test;
    test.init();
    cout << test.kru() << endl;
    cout << test.prim() << endl;
    cout << endl;
}
/*
Undir:

20
1 2 5
2 3 4
3 4 5
4 5 5
5 6 1
6 1 3
1 3 8
1 4 7
6 3 9
6 4 6
2 1 5
3 2 4
4 3 5
5 4 5
6 5 1
1 6 3
3 1 8
4 1 7
3 6 9
4 6 6

*/