#include <cstring>
#include<queue>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
const int maxn = 1e5 + 7;
struct node {
    vector<int> G[maxn];
    bool mark[maxn];
    vector<int> path;
    bool out1[maxn];
    int n;
    set<int> vers;
    void init() {
        memset(out1,0,sizeof out1);
        memset(mark, 0, sizeof mark);
        for (int i = 0; i < maxn; ++i) {
            G[i].clear();
        }
        input();
    }
    void input() {
        cout << "Input the num of the edges:" << endl;
        int k;
        cin >> k;
        cout << "Input the edges:" << endl;
        for (int i = 0; i < k; ++i) {
            int lef, ri;
            cin >> lef >> ri;
            vers.insert(lef);
            vers.insert(ri);
            G[lef].push_back(ri);
        }
    }
    void dfs(int k) {
        if(!out1[k]){
        cout << k << " " ;
        out1[k]=1;
        }
        for (auto c : G[k]) {
            if (!mark[c]) {
                path.push_back(c);
                mark[c] = 1;
                dfs(c);
                mark[c] = 0;
            }
        }
    }
    void bfs(int st){
        memset(mark,0,sizeof mark);
        deque<int> q;
        q.push_back(st);
        while(!q.empty()){
            auto c=q.front();
            q.pop_front();
            cout << c << " ";
            mark[c] =1;
            for(auto d:G[c]){
                if(!mark[d]){
                    q.push_back(d);
                }
            }
        }
    }
};
int main() {
    node t;
    t.init();
    cout << "The dfs: " << endl;
    t.dfs(1);
    cout << endl;
    cout << "The bfs: "<< endl;
    t.bfs(1);
}
