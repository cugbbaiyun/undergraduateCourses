#include <bits/stdc++.h>
using namespace std;
using pdd = pair<double, double>;
const double crossP = 0.2;
const double varP = 0.1;
const int maxG = 900;
const double selfCrossP = 0.05;
const int maxk = 50;
vector<pdd> ps;
set<pdd> pss;
double caldis(pdd a, pdd b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}
struct path {
    list<pdd> p;
    void init() {
        p.push_back(ps[0]);
        p.push_back(ps[0]);
    }
    double len = 0;

    void addHB() {
        if (p.front() != ps[0]) p.push_front(ps[0]);
        if (p.back() != ps[0]) p.push_back(ps[0]);
    }
    void removeHB() {
        if (p.front() == ps[0]) p.pop_front();
        if (p.back() == ps[0]) p.pop_back();
    }
    void push(pdd a) {
        p.pop_back();
        p.push_back(a);
        p.push_back(ps[0]);
    }

    path var() {
        auto ret = (*this);
        ret.removeHB();
        int lo = rand() % ret.p.size();
        int to = rand() % ps.size();
        while (to == 0) to = rand() % ps.size();
        auto ii = ret.p.begin();
        for (int i = 0; i < lo; ++i, ++ii)
            ;
        (*ii) = ps[to];
        ret.handle();
        ret.addHB();
        ret.callen();
        return ret;
    }

    void erase(int left, int right) {
        if (left < right) {
            int tem = left;
            left = right;
            right = tem;
        }
        auto lefti = p.begin();
        auto righti = p.begin();
        int i = 0;
        while (i != left) {
            ++i;
            ++lefti;
        }
        i = 0;
        while (i != right) {
            ++i;
            ++righti;
        }
        p.erase(lefti, righti);
    }
    void callen() {
        len = 0;
        vector<pdd> pps;
        for (auto c : p) {
            pps.push_back(c);
        }
        for (int i = 1; i < pps.size(); ++i) {
            len += caldis(pps[i], pps[i - 1]);
        }
    }
    void handle() {
        set<pdd> st;
        removeHB();
        vector<pdd> vt;
        for (auto c : p) {
            if (c == ps[0]) continue;
            if (st.find(c) != st.end()) continue;
            st.insert(c);
            vt.push_back(c);
        }
        p.clear();
        if (p.front() != ps[0]) p.push_front(ps[0]);
        st.insert(ps[0]);
        for (auto c : vt) {
            p.push_back(c);
        }
        vector<pair<pdd, int>> lefts;
        for (auto c : ps) {
            if (c == ps[0]) continue;
            if (st.find(c) == st.end()) {
                pair<pdd, int> t;
                t.first.first = c.first;
                t.first.second = c.second;
                t.second = rand() % 500;
                st.insert(c);
                lefts.push_back(t);
            }
        }
        sort(lefts.begin(), lefts.end(), [=](pair<pdd, int> d, pair<pdd, int> e) { return d.second < e.second; });
        for (auto c : lefts) {
            p.push_back(c.first);
        }
        addHB();
    }
    void showPath() {
        auto d = p.begin();
        cout << "(" << d->first << "," << d->second << ")";
        ++d;
        while (d != p.end()) {
            cout << "->(" << d->first << "," << d->second << ")";
            ++d;
        }
        cout << endl;
    }
};

vector<path> father;
vector<path> sons;

void init() {
    srand(time(NULL));
    string name;
    cin >> name;
    fstream in(name);
    string str;
    while (getline(in, str)) {
        stringstream iin(str);
        pdd t;
        if (iin >> t.first >> t.second) {
            ps.push_back(t);
            pss.insert(t);
        }
    }
}

void generateFather() {
    for (int i = 0; i < maxk; ++i) {
        path p;
        p.init();
        set<int> st;
        st.insert(0);
        srand(time(NULL));
        while (p.p.size() != (ps.size() + 1)) {
            int t = rand() % ps.size();
            while (st.find(t) != st.end()) {
                t = rand() % ps.size();
            }
            p.p.push_back(ps[t]);
            st.insert(t);
        }
        p.callen();
        father.push_back(p);
    }
}
void selectsons() {
    double sums = 0;
    for (auto &c : sons) {
        c.callen();
        sums += c.len;
    }
    vector<double> p;
    vector<int> left;
    vector<path> pps;

    for (auto c : sons) {
        double qwe = c.len / sums * 100;
        int t = rand() % 100;
        double tt = double(t) / 100.0;
        if (tt <= qwe) {
            pps.push_back(c);
        }
    }
    sons = pps;
}

vector<path> cross(path a, path b) {
    a.removeHB();
    b.removeHB();
    int len = rand() % (a.p.size() / 2);
    int sa = rand() % (a.p.size() - len);
    int sb = rand() % (a.p.size() - len);
    vector<path> ret;
    path son1;
    path son2;
    vector<pdd> p1;
    vector<pdd> p2;
    vector<pdd> tem;
    for (auto c : a.p) {
        p1.push_back(c);
    }
    for (auto d : b.p) {
        p2.push_back(d);
    }
    for (int i = 0; i < len; ++i) {
        tem.push_back(p1[sa + i]);
        p1[sa + i] = p2[sa + i];
    }
    for (int i = 0; i < len; ++i) {
        p2[sb + i] = tem[i];
    }
    son1.addHB();
    son2.addHB();
    for (auto c : p1) {
        son1.push(c);
    }
    for (auto c : p2) {
        son2.push(c);
    }
    son1.handle();
    son2.handle();
    son1.callen();
    son2.callen();
    ret.push_back(son1);
    ret.push_back(son2);
    return ret;
}

void generateSons() {
    sons.clear();
    for (auto c : father) {
        sons.push_back(c);
    }
    int crossNum = father.size() * crossP;
    int varNum = father.size() * varP;
    int selfCrossNum = father.size() * selfCrossP;
    for (int i = 0; i < crossNum; ++i) {
        int t1 = rand() % father.size();
        int t2 = rand() % father.size();
        auto d = cross(father[t1], father[t2]);
        sons.push_back(d[0]);
        sons.push_back(d[1]);
    }
    for (int i = 0; i < varNum; ++i) {
        int t1 = rand() % father.size();
        auto t = father[t1].var();
        sons.push_back(t);
    }
    selectsons();
}
void getans() {
    path ans;
    double minlen = INT_MAX;
    for (int i = 0; i < sons.size(); ++i) {
        if (minlen > sons[i].len) {
            minlen = sons[i].len;
            ans = sons[i];
        }
    }
    cout << ans.len << endl;
    ans.showPath();
}
int main() {
    init();
    generateFather();
    for (int i = 0; i < maxG; ++i) {
        generateSons();
        father.clear();
        father = sons;
    }
    getans();
}
