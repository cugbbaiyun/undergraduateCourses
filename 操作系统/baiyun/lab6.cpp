#include <climits>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

struct ele {
    int rank;
    int location;
};

struct manage {
    int nstep = 5;
    vector<ele> array;
    const int maxk = 500;
    void init() {
        cout << "Input the num of ele:" << endl;
        int num;
        cin >> num;
        for (int i = 0; i < num; ++i) {
            ele t;
            cout << "Input the rank:" << endl;
            cin >> t.rank;
            cout << "Input the  location:" << endl;
            cin >> t.location;
            array.push_back(t);
        }
    }

    void autoGenerate() {
        srand(time(NULL));
        int rr = rand() % 20;
        for (int i = 0; i < rr; ++i) {
            ele t;
            t.rank = i;
            t.location = rand() % maxk;
            array.push_back(t);
        }
        cout << "The size of the array:" << array.size() << endl;
        cout << "The array:" << endl;
        for (auto c : array) {
            cout << c.location << " ";
        }
        cout << endl;
        return;
    }

    int FCFS() {
        int num = 0;
        int now = 0;
        for (auto c : array) {
            if (now < c.location) {
                num += abs(c.location - now);
            }
            now = c.location;
        }
        cout << "平均缺页次数:" << (double) num / array.size() << endl;
        return num;
    }

    int SCAN() {
        list<int> ll;
        int num = 0;
        int ret = 0;
        srand(time(NULL));
        int now = 0;
        int dir = 1;
        while (num < array.size() || ll.size() != 0) {
            if (ll.size() == 0) {
                int nn = rand() % (array.size() - num) + 1;
                for (int i = 0; i < nn && num < array.size(); ++i) {
                    ll.push_back(array[num++].location);
                }
            } else {
                bool flag = rand() % 2;
                if (flag) {
                    if (num < array.size()) {
                        int nn = rand() % (array.size() - num) + 1;
                        for (int i = 0; i < nn && num < array.size(); ++i) {
                            ll.push_back(array[num++].location);
                        }
                    }
                }
            }

            list<int>::iterator i, t = ll.end(), t2 = ll.end();
            int diff = INT_MAX;
            int diff2 = INT_MAX;
            cout << "now:";
            cout << now << endl;
            cout << "The array: " << endl;
            for (auto c : ll) {
                cout << c << ",";
            }
            cout << endl;
            for (i = ll.begin(); i != ll.end(); ++i) {
                if (((*i) - now) * dir >= 0) {
                    if (diff > abs((*i) - now)) {
                        t = i;
                        diff = abs(*t - now);
                    }
                } else {
                    if (diff2 > abs((*i) - now)) {
                        t2 = i;
                        diff2 = abs(*t2 - now);
                    }
                }
            }
            if (t != ll.end()) {
                ret += diff;
                now = *t;
                ll.erase(t);
            } else if (t2 != ll.end()) {
                dir *= -1;
                ret += diff2;
                now = *t2;
                ll.erase(t2);
            }
        }
        cout << "平均缺页次数:" << (double) ret / array.size() << endl;
        return ret;
    }

    int CSCAN() {
        int num = 0;
        int now = 0;
        list<int> ll;
        int dir = 1;
        int ret = 0;
        while (num < array.size() || ll.size() != 0) {
            if (ll.size() == 0) {
                int nn = rand() % (array.size() - num) + 1;
                for (int i = 0; i < nn && num < array.size(); ++i) {
                    ll.push_back(array[num++].location);
                }
            } else {
                bool flag = rand() % 2;
                if (flag && num < array.size()) {
                    int nn = rand() % (array.size() - num) + 1;
                    for (int i = 0; i < nn && num < array.size(); ++i) {
                        ll.push_back(array[num++].location);
                    }
                }
            }
            cout << "now:";
            cout << now << endl;
            cout << "The array: " << endl;
            for (auto c : ll) {
                cout << c << ",";
            }
            cout << endl;
            int min1 = INT_MAX;
            list<int>::iterator i, t = ll.end();
            for (i = ll.begin(); i != ll.end(); ++i) {
                if ((*i - now) * dir >= 0 && abs(*i - now) < min1) {
                    min1 = abs(*i - now);
                    t = i;
                }
            }
            if (t == ll.end()) {
                ret += now;
                now = 0;
            } else {
                ret += min1;
                now = *t;
                ll.erase(t);
            }
        }
        cout << "平均缺页次数:" << (double) ret / array.size() << endl;
        return ret;
    }
    int NStepScan() {
        int num = 0;
        int now = 0;
        list<ele> ll;
        int k = 0;
        int dir = 1;
        ll.clear();
        while (k < array.size()) {
            for (int tt = 0; k < array.size() && tt < nstep; ++tt, ++k) {
                ll.push_back(array[k]);
            }
            while (ll.size() != 0) {
                cout << "now:" << now << endl;
                cout << "The array:";
                for (auto c : ll) {
                    cout << c.location << " ";
                }
                cout << endl;
                list<ele>::iterator t = ll.end();
                list<ele>::iterator tt = ll.end();
                int min1 = INT_MAX;
                int min2 = INT_MAX;
                for (list<ele>::iterator i = ll.begin(); i != ll.end(); ++i) {
                    int diff = i->location - now;
                    if (diff * dir > 0) {
                        if (min1 > abs(diff)) {
                            t = i;
                            min1 = abs(diff);
                        }
                    } else {
                        if (min2 > abs(diff)) {
                            tt = i;
                            min2 = abs(diff);
                        }
                    }
                }
                if (t != ll.end()) {
                    num += min1;
                    now = t->location;
                    ll.erase(t);
                } else if (tt != ll.end()) {
                    num += min2;
                    now = tt->location;
                    ll.erase(tt);
                    dir *= -1;
                }
            }
        }
        cout << "平均缺页次数:" << (double) num / array.size() << endl;
        return num;
    }
    int SSTF() {
        int num = 0;
        int now = 0;
        int k = 0;
        list<ele> ll;
        for (auto c : array) {
            ll.push_back(c);
        }
        while (k < array.size()) {
            cout << "now:" << now << endl;
            cout << "The array :";
            for (auto c : ll) {
                cout << c.location << " ";
            }
            cout << endl;
            list<ele>::iterator i = ll.begin(), t = ll.begin();
            for (t = ll.begin(); t != ll.end(); ++t) {
                if (abs(i->location - now) > abs(t->location - now)) {
                    i = t;
                }
            }
            num += abs(i->location - now);
            now = i->location;
            ll.erase(i);
            ++k;
        }
        cout << "平均缺页次数:" << (double) num / array.size() << endl;
        return num;
    }
};

int main() {
    manage test;
    int t;
    test.autoGenerate();
    cout << "FCFS:" << endl;
    t = test.FCFS();
    cout << "共缺页:" << t << endl;
    cout << endl;

    cout << "SSTF:" << endl;
    t = test.SSTF();
    cout << "共缺页:" << t << endl;
    cout << endl;
    cout << "SCAN:" << endl;
    t = test.SCAN();
    cout << "共缺页:" << t << endl;
    cout << endl;
    cout << "CSCAN:" << endl;
    t = test.CSCAN();
    cout << "共缺页:" << t << endl;
    cout << endl;
    cout << "NStepScan:" << endl;
    t = test.NStepScan();
    cout << "共缺页:" << t << endl;
}