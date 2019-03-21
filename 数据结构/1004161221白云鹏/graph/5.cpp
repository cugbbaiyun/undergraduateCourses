#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
const int maxn = 1e5;
template <typename T> struct node {
    vector<int> to;
    int in = 0;
};
node<int> G[maxn];
struct cmp {
    bool operator()(int a, int b) const {
        return G[a].in > G[b].in;
    }
};
template <typename T> struct topp {
    set<int> vs;
    void init() {
        for (int i = 0; i < maxn; ++i) {
            G[i].to.clear();
        }
        cout << "Input the num of the events:" << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << "Input the index of the event:" << endl;
            int num;
            cin >> num;
            vs.insert(num);
            cout << "Input the num of the pre events:" << endl;
            int k;
            cin >> k;
            G[num].in = k;
            cout << "Input the index of the pre events: " << endl;
            for (int j = 0; j < k; ++j) {
                int pre;
                cin >> pre;
                G[pre].to.push_back(num);
                vs.insert(pre);
            }
        }
    }

    void topsort() {
        priority_queue<int, vector<int>, cmp> q;
        for (auto c : vs) {
            q.push(c);
        }
        while (!q.empty()) {
            cout << q.top() << " ";
            for (auto c : G[q.top()].to) {
                --G[c].in;
            }
            q.pop();
        }
    }
};
topp<int> tt;
int main() {
    tt.init();
    tt.topsort();
}
/*

9

1 0
2 0
3 2  1 2
4 1 1
5 1 2
6 3 3 4 5
7 1 6
8 2 6 7
9 3 6 7 8

*/