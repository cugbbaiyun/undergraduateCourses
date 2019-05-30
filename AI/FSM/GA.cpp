#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
const int MAXP = 50;
const int MAXLEN = 100;
const int MAXHEIGHT = 20;
const double VARP = 0.2;
const int MAXGEN = 500;
struct line {
    int x;
    int starty, endy;
    bool operator<(const line &b) {
        return this->x < b.x;
    }
};

vector<line> ls;
struct solve {
    vector<bool> ops;
    int goal = 0;
    void init() {
        for (int i = 0; i < MAXLEN; ++i) { ops.push_back(0); }
    }
    void setGoal() {
        goal = fx();
    }
    void output() {
        cout << fx() << ":";
        for (auto c : ops) { cout << c << " "; }
        cout << endl;
    }
    int fx() {
        int height = MAXHEIGHT / 2;
        int nowx = 0;
        int nowline = 0;
        while (nowx < MAXLEN + 1) {
            while (nowline == ls.size() || nowx < ls[nowline].x) {
                if (ops[nowx]) {
                    height += 5;
                    if (height > MAXHEIGHT) return nowx;
                } else {
                    height -= 3;
                    if (height < 0) return nowx;
                }
                ++nowx;
                if (nowx == MAXLEN + 1) return nowx;
            }
            while (nowline < ls.size() && ls[nowline].x == nowx) {
                if (!(height >= ls[nowline].starty &&
                      height <= ls[nowline].endy)) {
                    return nowx;
                }
                ++nowline;
            }
        }
        return nowx;
    }
};

vector<solve> parent;
vector<solve> f1;
void generateP() {
    srand(time(NULL));
    for (int j = 0; j < MAXP; ++j) {
        for (int i = 0; i < 50; ++i) {
            solve t;
            t.ops.clear();
            for (int i = 0; i < MAXLEN; ++i) { t.ops.push_back(rand() % 2); }
            parent.push_back(t);
        }
    }
}

void init() {
    int n;
    srand(time(NULL));
    for (int i = 1; i <= MAXLEN; ++i) {
        line tem;
        tem.x = i;
        do {
            tem.starty = rand() % MAXHEIGHT;
            tem.endy = rand() % MAXHEIGHT;
        } while (tem.starty == tem.endy);
        if (tem.starty >= tem.endy) {
            int back = tem.starty;
            tem.starty = tem.endy;
            tem.endy = back;
        }
    }
}

solve vary(solve p) {
    int lo = rand() % MAXLEN;
    p.ops[lo] = !p.ops[lo];
    return p;
}

pair<solve, solve> cross(solve s1, solve s2) {
    int from = rand() % MAXLEN;
    int to = rand() % MAXLEN;
    if (from > to) {
        int tem = from;
        from = to;
        to = tem;
    }
    for (int i = from; i < to; ++i) {
        int tem = s1.ops[i];
        s1.ops[i] = s2.ops[i];
        s2.ops[i] = tem;
    }
    return pair<solve, solve>(s1, s2);
}

void generateSon() {
    f1.clear();
    for (auto c : parent) {
        f1.push_back(c);
        int t = rand() % 100;
        double tt = double(t) / 100;
        if (tt < VARP) { f1.push_back(vary(c)); }
        int c2 = rand() % parent.size();
        auto d = cross(parent[c2], c);
        f1.push_back(d.first);
        f1.push_back(d.second);
    }
    parent.clear();
    set<int> ttt;
    for (int i = 0; i < f1.size(); ++i) { ttt.insert(i); }
    double sumgoal;
    for (auto &c : f1) {
        c.setGoal();
        sumgoal += c.goal;
    }
    while (parent.size() < MAXP) {
        for (auto c : ttt) {
            double ppp = double(f1[c].goal) / sumgoal;
            double pp = double(rand()) / double(RAND_MAX);
            if (pp <= ppp) {
                parent.push_back(f1[c]);
                ttt.erase(c);
                break;
            }
        }
    }
}

int outMax() {
    int maxstep = 0;
    for (auto c : parent) {
        int t = c.fx();
        cout << t <<" ";
        if (t >= 100) ++maxstep;
    }
    cout << endl;
    return maxstep;
}
vector<int> k1;
vector<int> k2;

void run() {
    init();
    generateP();
    // cout << "Generation 0:";
    k1.push_back(0);
    k2.push_back(outMax());
    // cout << endl;
    for (int i = 0; i < MAXGEN; ++i) {
        generateSon();
        // cout << "Generation " << i + 1 << ":";
        int t = outMax();
        k1.push_back(i + 1);
        k2.push_back(t);
        // cout << endl;
    }
}
void outK() {
    for (auto c : k1) { cout << c << " "; }
    cout << endl;
    for (auto d : k2) { cout << d << ","; }
    cout << endl;
}

int main() {
    run();
    outK();
}