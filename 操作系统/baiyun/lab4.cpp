#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
struct block {
    int rank = -1;
    int size;
    int start;
};
struct company {
    vector<list<block>> ll;
    list<block> used;
    const int lenn = 10;
    void init() {
        ll.clear();
        block ini;
        ini.size = 1 << lenn;
        ini.start = 0;
        list<block> in;
        in.clear();
        for (int i = 0; i < lenn; ++i) {
            ll.push_back(in);
        }
        in.push_back(ini);
        ll.push_back(in);
    }

    void show() {
        vector<block> allBlocks;
        for (auto c : used) {
            allBlocks.push_back(c);
        }
        for (auto c : ll) {
            for (auto d : c) {
                allBlocks.push_back(d);
            }
        }
        sort(allBlocks.begin(), allBlocks.end(), [=](block &a, block &b) { return a.start < b.start; });
        for (auto c : allBlocks) {
            if (c.rank != -1) {
                cout << "Rank:" << c.rank << " ";
            } else {
                cout << "Not used:"
                     << " ";
            }
            cout << "start:" << c.start << " "
                 << "Size:" << c.size << endl;
        }
    }

    void test() {
        init();
        int mode;
        while (1) {
            cout << "Input the mode:" << endl;
            cout << "1.Alloc" << endl;
            cout << "2.Free" << endl;
            cin >> mode;
            if (mode == 1) {
                if (alloc()) {
                } else {
                    cout << "Failed." << endl;
                }
            } else {
                if (mfree()) {
                } else {
                    cout << "Failed." << endl;
                }
            }
            show();
        }
    }
    bool alloc() {
        cout << "Input size:";
        int sz;
        cin >> sz;
        int i = 0;
        while (i <= lenn && sz > (1 << i) || ll[i].size() == 0) {
            ++i;
        }
        if (i > lenn) return false;
        if (sz == 0) return true;
        auto c = ll[i].front();
        ll[i].pop_front();
        while ((i > 0) && sz <= (1LL << (i - 1))) {
            block a, b;
            a.start = c.start;
            int newsz = c.size / 2;
            a.size = newsz;
            b.size = newsz;
            b.start = a.start + newsz;
            ll[i - 1].push_back(b);
            c = a;
            --i;
        }
        c.rank = used.size() + 1;
        used.push_back(c);
        cout << "Alloc finished." << endl;
        cout << "Start: " << c.start << " "
             << "Size:" << c.size << endl;
        return true;
    }

    bool mfree() {
        block newBlock;
        cout << "Input the rank: " << endl;
        cin >> newBlock.rank;
        bool flag = false;
        list<block>::iterator i, t = used.end();
        for (i = used.begin(); i != used.end(); ++i) {
            if (i->rank == newBlock.rank) {
                t = i;
                break;
            }
        }
        if (t == used.end()) return false;
        newBlock = *t;
        used.erase(t);
        int ii = 0;
        newBlock.rank = -1;
        while ((1 << ii) < newBlock.size) ++ii;
        int fg = 1;
        while (fg) {
            t = ll[ii].end();
            fg = 0;
            for (i = ll[ii].begin(); i != ll[ii].end(); ++i) {
                if (newBlock.start == (i->start + i->size)) {
                    fg = 1;
                    t = i;
                    break;
                } else if (newBlock.start + newBlock.size == i->start) {
                    fg = 2;
                    t = i;
                    break;
                }
            }
            if (fg == 1) {
                newBlock.start = i->start;
                newBlock.size <<= 1;
                ll[ii++].erase(t);
            } else if (fg == 2) {
                newBlock.size <<= 1;
                ll[ii++].erase(t);
            } else
                break;
        }
        ll[ii].push_back(newBlock);
        return true;
    }
};
int main() {
    company test;
    test.test();
}