#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <queue>
#include <string>
using namespace std;
int nowTime;
struct task {
    int arriveTime;
    int needTime;
    int rank;
    double pro;
    bool operator<(const task &b) {
        return this->pro < b.pro;
    }
};
struct processor {
    list<task> ll;
    vector<task> tasks;
    const int maxTime = 300;
    const int gap = 30;
    const int maxLen = 60;
    processor() {
        ll.clear();
        tasks.clear();
    }
    void init() {
        ll.clear();
        nowTime = INT_MAX;
        for (auto &c : tasks) {
            ll.push_back(c);
            nowTime = min(nowTime, c.arriveTime);
        }
    }
    void autoGenerate() {
        int num = 0;
        srand(time(NULL));
        num = rand() % 5;
        for (int i = 0; i < num; ++i) {
            task t;
            t.arriveTime = rand() % maxTime;
            t.needTime = rand() % maxLen;
            t.rank = i;
            tasks.push_back(t);
        }
        cout << "The tasks num :" << num << endl;
        cout << "The tasks' arrive time and the need time: " << endl;
        for (auto c : tasks) {
            cout << c.rank << "." << c.arriveTime << " " << c.needTime << endl;
        }
        return;
    }

    void inputTask() {
        int num = 0;
        cout << "Input the tasks num:" << endl;
        cin >> num;
        for (int i = 0; i < num; ++i) {
            cout << "Input the task's arrive time and need time:" << endl;
            task t;
            cin >> t.arriveTime >> t.needTime;
            t.rank = i;
            tasks.push_back(t);
        }
    }
    void getArray() {
        auto c = turn();
        int num = 0;
        int t, tt;
        t = c.back();
        c.pop_back();
        tt = c.back();
        c.pop_back();
        cout << "CPU:" << (double) tt / (double) t * 100 << "%" << endl;
        for (auto d : c) {
            num == 0 ? cout << "The array by turn:" << endl : cout << " -> ";
            cout << d;
            ++num;
        }
        cout << endl;
        c = HRRN();
        num = 0;
        t = c.back();
        c.pop_back();
        tt = c.back();
        c.pop_back();
        cout << "CPU:" << (double) tt / (double) t * 100 << "%" << endl;
        for (auto d : c) {
            num == 0 ? cout << "The array by HRRN:" << endl : cout << " -> ";
            cout << d;
            ++num;
        }
        cout << endl;
    }
    vector<int> turn() {
        vector<int> ret;
        init();
        int startTime = nowTime;
        int workTime = 0;
        ret.clear();
        while (ll.size() != 0) {
            list<task>::iterator i = ll.begin(), t = ll.begin();
            i = ll.begin();
            for (t = ll.begin(); t != ll.end(); ++t) {
                t->arriveTime < i->arriveTime ? i = t : i = i;
            }
            auto tem = *i;
            ret.push_back(tem.rank);
            ll.erase(i);
            nowTime = max(nowTime, tem.arriveTime);
            int tt = min(gap, tem.needTime);
            workTime += tt;
            nowTime += tt;
            tem.needTime -= tt;
            if (tem.needTime > 0) {
                tem.arriveTime = nowTime;
                ll.push_back(tem);
            }
        }
        int endTime = nowTime;
        ret.push_back(workTime);
        ret.push_back(endTime - startTime);
        return ret;
    }

    double getDiv(task t, int now) {
        if (now < t.arriveTime) return -1;
        return ((double) now - (double) t.arriveTime + (double) t.needTime) / (double) t.needTime;
    }

    vector<int> HRRN() {
        init();
        vector<int> ret;
        ret.clear();
        int startTime = nowTime;
        int workTime = 0;
        while (ll.size() != 0) {
            list<task>::iterator i = ll.begin(), t = ll.begin();
            int tt = INT_MAX;
            i->pro = getDiv(*i, nowTime);
            for (t = ll.begin(); t != ll.end(); ++t) {
                t->pro = getDiv(*t, nowTime);
                if (t->pro > i->pro) {
                    i = t;
                }
                tt = min(tt, t->arriveTime);
            }
            if (i->pro == -1) {
                nowTime = tt;
                continue;
            }
            cout << "now time : ";
            cout << nowTime << ":" << endl;
            cout << "-1 means the task has not arrived." << endl;
            cout << "Task rank:"
                 << "\t"
                 << "Start Time"
                 << "\t"
                 << "Need Time"
                 << "\t"
                 << "pro" << endl;
            for (auto c : ll) {
                cout << c.rank << "\t" << c.arriveTime << "\t" << c.needTime << "\t" << c.pro << endl;
            }
            cout << endl;
            task tem = *i;
            ll.erase(i);
            int ttt = tem.needTime;
            workTime += ttt;
            nowTime += ttt;
            ret.push_back(tem.rank);
        }
        int endTime = nowTime;
        ret.push_back(workTime);
        ret.push_back(endTime - startTime);
        return ret;
    }
};
int main() {
    processor test;
    // test.inputTask();
    test.autoGenerate();
    test.getArray();
}