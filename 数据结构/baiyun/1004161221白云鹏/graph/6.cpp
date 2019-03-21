#include <algorithm>
#include <cstring>
#include<set>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int maxn = 1e3;
template <typename T> struct edge {
    T cost = 0;
    int s, t;
};
template <typename T> struct dijstra {
    vector<edge<T>> G[maxn];
    const T inf = 0x3f3f3f3f;
    set<int> vs;
    void init() {
        for (int i = 0; i < maxn; ++i) {
            G[i].clear();
        }
        vs.clear();
        addeage();
    }
    void addeage() {
        cout << "Input the num of the edge:" << endl;
        int k;
        cin >> k;
        for (int i = 0; i < k; ++i) {
            cout << "Input the start end and the cost of the edge:" << endl;
            edge<T> tem;
            cin >> tem.s >> tem.t >> tem.cost;
            vs.insert(tem.s);
            vs.insert(tem.t);
            G[tem.s].push_back(tem);
        }
    }
    void dj() {
        int start;
        cout << "Input the start:" << endl;
        cin >> start;
        T dis[maxn];
        for(int i =0;i <maxn;++i){
            dis[i] = inf;
        }
        dis[start] = 0;
        bool mark[maxn];
        memset(mark, 0, sizeof mark);
        mark[start] = 1;
        for(auto c:G[start]) dis[c.t] = c.cost;
        for(int t =1;t< vs.size();++t){
            int k = -1;
            T min1 = inf;
            for (int i = 0; i < maxn; ++i) {
                if (!mark[i] && min1 > dis[i]) {
                    min1 = dis[i];
                    k = i;
                }
            }
            if(k == -1){return;}
            mark[k] = 1;
            for (auto c : G[k]) {
                if (mark[c.t] == 0) dis[c.t] = min(dis[c.t], dis[k] + c.cost);
            }
        }
        for(auto c:vs){
            cout << c << " : " << dis[c] << endl;
        }
    }
};
dijstra<int> tt;
int main() {
    tt.init();
     tt.dj();
}
/*

10
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

*/
