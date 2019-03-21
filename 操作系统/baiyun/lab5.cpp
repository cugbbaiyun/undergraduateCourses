#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct page {
    int rank;
    bool isModified = 0;
    bool vis = 0;
};

struct diaodu {
    vector<page> array;
    vector<bool> interrupt;
    const int window = 3;
    const int gap = 3;
    void inputArray() {
        int num;
        srand(time(NULL));
        cout << "Input the num:" << endl;
        cin >> num;
        cout << "Input the rank of the page:" << endl;
        for (int i = 0; i < num; ++i) {
            page t;
            cin >> t.rank;
            t.vis = rand() % 2;
            t.isModified = rand() % 2;
            array.push_back(t);
        }
        cout << "Rank:";
        for (auto c : array) {
            cout << c.rank << " ";
        }
        cout << endl;
        cout << "Vis :";
        for (auto c : array) {
            cout << c.vis << " ";
        }
        cout << endl;
        cout << "Modi:";
        for (auto c : array) {
            cout << c.isModified << " ";
        }
        cout << endl;
    }

    int FIFO() {
        deque<int> now;
        int num = 0;
        interrupt.clear();
        for (auto &c : array) {
            bool flag = false;
            cout << "页号：" << c.rank << endl;
            cout << "页框中的页号：";
            for (auto d : now) {
                cout << d << " ";
            }
            for (auto d : now) {
                if (c.rank == d) {
                    flag = true;
                }
            }
            cout << endl;
            if (flag) {
                cout << "查找命中" << endl;
                interrupt.push_back(0);
                continue;
            }
            cout << "查找未命中,";
            interrupt.push_back(1);
            if (now.size() < window) {
                cout << "无需替换" << endl;
                ++num;
                now.push_back(c.rank);
            } else {
                ++num;
                cout << "替换的页为:" << now.front() << endl;
                now.pop_front();
                now.push_back(c.rank);
            }
        }
        for (auto c : array) {
            cout << c.rank << " ";
        }
        cout << endl;
        for (auto c : interrupt) {
            cout << c << " ";
        }
        cout << endl;
        cout << "缺页率:" << (double) num / (double) array.size() * 100 << "%" << endl;
        return num;
    }

    int LRU() {
        int num = 0;
        map<int, int> last;
        list<int> now;
        interrupt.clear();
        for (auto c : array) {
            last[c.rank] = -1;
        }
        for (int i = 0; i < array.size(); ++i) {
            cout << "缺页：" << array[i].rank << endl;
            bool flag = false;
            cout << "页框中的页:";
            for (auto &d : now) {
                if (d == array[i].rank) {
                    flag = true;
                }
                cout << d << " ";
            }
            cout << endl;
            if (flag) {
                cout << "查找命中" << endl;
                interrupt.push_back(0);
                last[array[i].rank] = max(last[array[i].rank], i);
                continue;
            }
            interrupt.push_back(1);
            if (now.size() < window) {
                ++num;
                last[array[i].rank] = max(last[array[i].rank], i);
                now.push_back(array[i].rank);
            } else {
                list<int>::iterator ii = now.begin(), t = now.begin();
                cout << "上一次出现的位置为：" << endl;
                while (t != now.end()) {
                    if (last[*ii] > last[*t]) ii = t;
                    cout << *t << ":" << last[*t] << " ";
                    ++t;
                }
                cout << endl;
                cout << "查找未命中,";
                cout << "需要替换的页为:" << *ii << endl;
                now.erase(ii);
                now.push_back(array[i].rank);
                last[array[i].rank] = max(last[array[i].rank], i);
                ++num;
            }
        }
        for (auto c : array) {
            cout << c.rank << " ";
        }
        cout << endl;
        for (auto c : interrupt) {
            cout << c << " ";
        }
        cout << endl;
        cout << "缺页率:" << (double) num / (double) array.size() * 100 << "%" << endl;
        return num;
    }

    int Clock() {
        list<page> now;
        int num = 0;
        interrupt.clear();
        for (auto c : array) {
            bool flag = false;
            cout << "缺页:" << c.rank << endl;
            cout << "页框中的页:";
            auto ii = now.end();
            for (auto i = now.begin(); i != now.end(); ++i) {
                if (i->rank == c.rank) {
                    flag = true;
                    ii = i;
                }
                cout << i->rank << " ";
            }
            cout << endl;
            if (flag) {
                cout << "查找命中" << endl;
                ii->vis = 1;
                if (ii->isModified == false) {
                    ii->isModified = rand() % 2;
                }
                interrupt.push_back(0);
                continue;
            }
            interrupt.push_back(1);
            if (now.size() < window) {
                cout << "查找未命中，无需替换" << endl;
                ++num;
                now.push_back(c);
            } else {
                flag = false;
                auto t = now.begin();
                while (flag == false) {
                    cout << "rank"
                         << "\t"
                         << "modi"
                         << "\t"
                         << "vis" << endl;
                    for (auto c : now) {
                        cout << c.rank << "\t\t" << c.isModified << "\t\t" << c.vis << endl;
                    }

                    for (t = now.begin(); t != now.end(); ++t) {
                        if (t->vis == false && t->isModified == false) {
                            flag = true;
                            break;
                        }
                    }
                    if (flag == false) {
                        cout << "第一类页面查找失败" << endl;
                        for (t = now.begin(); t != now.end(); ++t) {
                            if (t->vis == false) {
                                flag = true;
                                break;
                            }
                        }
                    }
                    if (flag == false) {
                        cout << "第二类页面查找失败" << endl;
                        for (t = now.begin(); t != now.end(); ++t) {
                            t->vis = 0;
                        }
                    }
                }
                ++num;
                cout << "选中的页号为：" << t->rank << endl;
                now.erase(t);
                now.push_back(c);
            }
        }
        for (auto c : array) {
            cout << c.rank << " ";
        }
        cout << endl;
        for (auto c : interrupt) {
            cout << c << " ";
        }
        cout << endl;
        cout << "缺页率:" << (double) num / (double) array.size() * 100 << "%" << endl;
        return num;
    }
};

int main() {
    diaodu test;
    test.inputArray();
    cout << test.FIFO() << endl;
    cout << test.LRU() << endl;
    cout << test.Clock() << endl;
    return 0;
}
/*

20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1

*/