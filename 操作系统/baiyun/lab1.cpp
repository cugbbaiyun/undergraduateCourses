#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
struct task {
    string rank;
    map<int, int> need;
    map<int, int> have;
    map<int, int> all;
    task() {
        rank.clear();
        need.clear();
        have.clear();
        all.clear();
    }
    void clear() {
        need.clear();
        have.clear();
        all.clear();
    }
    void setRank(const string &k) {
        rank = k;
    }
    void addHave(const int &rank, const int &haveNum) {
        have[rank] = haveNum;
    }
    void addMaxNeed(const int &rank, const int &needNum) {
        all[rank] = needNum;
    }
    bool updateNeed() {
        bool flag = 1;
        for (auto &c : all) {
            int t;
            t = c.second - have[c.first];
            need[c.first] = t;
            if (t > 0) flag = 0;
        }
        return flag;
    }
};
struct banker {
    map<int, int> aviliable;
    deque<task> finishedTasks;
    deque<task> unFinishedTasks;
    bool enough(task &t, map<int, int> &av) {
        for (auto &c : t.need) {
            if (t.all[c.first] < c.second + t.have[c.first]) return false;
            if (av[c.first] < c.second) return false;
        }
        return true;
    }
    void isSafe() {
        auto t = getFq();
        if (t.size() == finishedTasks.size() + unFinishedTasks.size()) {
            cout << "Safe" << endl;
            int k = 0;
            for (auto &c : t) {
                k == 0 ? cout << "The array :" : cout << "->";
                cout << c.rank;
                ++k;
            }
        } else {
            cout << "No safe" << endl;
        }
    }

    deque<task> getFq() {
        auto avi1 = aviliable;
        auto fq1 = finishedTasks;
        auto ufq1 = unFinishedTasks;
        int num = 0;
        while (ufq1.size() != 0 && num != ufq1.size()) {
            auto t = ufq1.front();
            ufq1.pop_front();
            if (enough(t, avi1)) {
                num = 0;
                for (auto &c : t.have) {
                    avi1[c.first] += c.second;
                }
                fq1.push_back(t);
                cout << "Still need:" << endl;
                ;
                for (auto c : ufq1) {
                    cout << c.rank << " : "
                         << "\t";
                    for (auto d : c.need) {
                        cout << d.first << ":" << d.second << "\t";
                    }
                    cout << endl;
                }
                cout << "System:" << endl;
                for (auto c : avi1) {
                    cout << c.first << ":" << c.second << "\t";
                }
                cout << endl;
            } else {
                ++num;
                ufq1.push_back(t);
            }
        }
        return fq1;
    }

    void inputReso() {
        fstream in("lab1in.txt");
        string str;
        getline(in, str);
        stringstream iin(str);
        int num;
        iin >> num;
        getline(in, str);
        stringstream iiin(str);
        for (int i = 0; i < num; ++i) {
            int tem;
            iiin >> tem;
            aviliable[i] = tem;
        }
    }
    void inputTask() {
        fstream iin("lab1in.txt");
        int num;
        string temstr;
        getline(iin, temstr);
        getline(iin, temstr);
        getline(iin, temstr);
        stringstream iiin(temstr);
        iiin >> num;
        finishedTasks.clear();
        unFinishedTasks.clear();
        for (int i = 0; i < num; ++i) {
            task t;
            getline(iin, t.rank);
            int resouceSize = aviliable.size();
            string line;
            line.clear();
            while (line.empty() || line == "\n") getline(iin, line);
            int inte;
            stringstream in(line);
            int qq = 0;
            int tem;
            for (int q = 0; q < aviliable.size(); ++q) {
                in >> tem;
                t.addHave(qq, tem);
                ++qq;
            }
            qq = 0;
            for (int q = 0; q < aviliable.size(); ++q) {
                in >> tem;
                t.addMaxNeed(qq, tem);
                ++qq;
            }
            cout << t.rank << ":" << endl;
            t.updateNeed();
            cout << "Need:";
            for (auto c : t.all) {
                cout << c.second << " ";
            }
            cout << endl;
            cout << "Have:";
            for (auto c : t.have) {
                cout << c.second << " ";
            }
            cout << endl;
            cout << "Need:";
            for (auto c : t.need) {
                cout << c.second << " ";
            }
            cout << endl;
            unFinishedTasks.push_back(t);
        }
    }
};
int main() {
    banker test;
    test.inputReso();
    test.inputTask();
    test.isSafe();
}

/*
3
3 3 2
5
p0
0 1 0 7 4 3
p1
2 0 0 1 2 2
p2
3 0 2 6 0 0
p3
2 1 1 0 1 1
p4
0 0 2 4 3 1
*/