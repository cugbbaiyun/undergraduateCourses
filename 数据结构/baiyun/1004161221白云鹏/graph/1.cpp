#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int maxn = 13;
struct graph {
    int G1[maxn][maxn];
    int G2[maxn][maxn];
    int eagenum = 0;
    vector<int> G3[maxn];

    void outG1() {
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxn; ++j) {
                cout << G1[i][j] << " ";
            }
            cout << endl;
        }
    }
    void outG2() {
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxn; ++j) {
                cout << G2[i][j] << " ";
            }
            cout << endl;
        }
    }
    void outG3() {
        for (int i = 0; i < maxn; ++i) {
            if (G3[i].size() != 0) {
                cout << i << ":";
                for (auto c : G3[i]) {
                    cout << c << " ";
                }
                cout << endl;
            }
        }
    }
    void init(){
        memset(G1,0,sizeof G1);
        memset(G2,0,sizeof G2);
        for(int i=0;i<maxn;++i){
            G3[i].clear();
        }
        getG1();
        getG2();
        getG3();
    }
    void getG1() {
        cout << "input the num of the edges:" << endl;
        cin >> eagenum;
        cout << "Input the edges: " << endl;
        for (int i = 0; i < eagenum; ++i) {
            int l, r;
            cin >> l >> r;
            G1[l][r] = 1;
        }
        cout << "the martix is:"<<endl;
        outG1();
    }

    void getG3() {
        cout << "From martix to get list:" << endl;
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxn; ++j) {
                if (G1[i][j]) {
                    G3[i].push_back(j);
                }
            }
        }
        cout << "The list is:" << endl;
        outG3();
    }

    void getG2() {
        cout <<"From the list to get martix:" << endl;
        for (int i = 0; i < maxn; ++i) {
            for (auto c : G2[i]) {
                G2[i][c] = 1;
            }
        }
        outG2();
    }
};
int main() {
    graph test;
    test.init();
}