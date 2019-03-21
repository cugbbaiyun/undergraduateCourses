#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
template <typename T> struct node {
    node<T> *left = nullptr;
    node<T> *right = nullptr;
    T data;
    bool ltag = 0;
    bool rtag = 0;
};
template <typename T> struct bintree {
    bintree() = default;
    node<T> *root = nullptr;
    vector<T> str;
    int leave = 0;
    int k = 0;
    int height = 0;
    node<T> *pre1 = nullptr;
    int getheight() {
        if (height != 0)
            return height;
        else
            gh(root, 0);
    }
    void gh(node<T> *now, int hh) {
        height = max(hh, height);
        if (now->left != nullptr) gh(now->left, hh + 1);
        if (now->right != nullptr) {
            gh(now->right, hh + 1);
        }
    }

    void create(node<T> *now) {
        if (k >= str.size()) return;
        now->data = str[k++];
        if (k < str.size() && islower(str[k])) {
            now->left = new node<T>;
            create(now->left);
        } else {
            ++k;
        }
        if (k < str.size() && islower(str[k])) {
            now->right = new node<T>;
            create(now->right);
        } else {
            ++k;
        }
    }
    void inThread() {
        pre1 = nullptr;
        if (root != nullptr) {
            inThread(root);
            pre1->right = nullptr;
            pre1->rtag = 1;
        }
    }

    void inno() {
        stack<node<T> *> ss;
        node<T> *now = root;
        do {
            while (now != nullptr) {
                ss.push(now);
                now = now->left;
            }
            if (!ss.empty()) {
                now = ss.top();
                ss.pop();
                cout << now->data << " ";
                now = now->right;
            }
        } while (now != nullptr || !ss.empty());
    }
    void searc(T num) {
        using pni = pair<node<T> *, int>;
        stack<pni> ss;
        int flag = 0;
        vector<T> path;
        node<T> *now = root;
        do {
            while (now != nullptr) {
                ss.push(pni(now, flag));
                path.push_back(now->data);
                now = now->left;
                flag = 0;
            }
            if (!ss.empty()) {
                now = ss.top().first;
                int t = ss.top().second;
                ss.pop();
                if (now->data == num) break;
                if (!t) path.pop_back();
                if (ss.top().second == 1) ss.pop();
                now = now->right;
                flag = 1;
            }
        } while (now != nullptr || !ss.empty());
        for (auto &x : path) {
            cout << x << " ";
        }
        cout << endl;
    }

    void inThread(node<T> *now) {
        if (now == nullptr) return;
        inThread(now->left);
        if (now->left == nullptr) {
            now->left = pre1;
            now->ltag = 1;
        }
        if (pre1 != nullptr && pre1->right == nullptr) {
            pre1->right = now;
            pre1->rtag = 1;
        }
        pre1 = now;
        inThread(now->right);
    }

    void pre(node<T> *now) {
        if (now == nullptr) return;
        cout << now->data << " ";
        if (now->left != nullptr) pre(now->left);
        if (now->right != nullptr) pre(now->right);
    }

    void in(node<T> *now) {
        if (now == nullptr) return;
        if (now->left != nullptr) {
            in(now->left);
        }
        cout << now->data << " ";
        if (now->right != nullptr) {
            in(now->right);
        }
    }

    void aft(node<T> *now) {
        if (now == nullptr) return;
        if (now->left != nullptr) aft(now->left);
        if (now->right != nullptr) aft(now->right);
        cout << now->data << " ";
    }

    int getleave() {
        if (leave == 0)
            return cnt(root);
        else
            return leave;
    }

    int getfloor(T f, node<T> *now, int k) {
        if (now->data == f) return k;
        int ans = 0;
        if (now->left != nullptr) {
            ans = max(ans, getfloor(f, now->left, k + 1));
        }
        if (now->right != nullptr) {
            ans = max(ans, getfloor(f, now->right, k + 1));
        }
        return ans;
    }

    void clear(node<T> *now) {
        if (now->left == nullptr && now->right == nullptr) {
            delete now;
            return;
        }
        if (now->left != nullptr) {
            clear(now->left);
        }
        if (now->right != nullptr) {
            clear(now->right);
        }
    }

    void outlr(T f, node<T> *now) {
        if (now->data == f) {
            cout << "Left child:";
            if (now->left == nullptr)
                cout << "nullptr";
            else
                cout << now->left->data;
            cout << endl;
            cout << "Right child:";
            if (now->right == nullptr) {
                cout << "nullptr";
            } else
                cout << now->right->data;
            cout << endl;
            return;
        }
        if (now->left != nullptr) {
            outlr(f, now->left);
        }
        if (now->right != nullptr) {
            outlr(f, now->right);
        }
    }

    int cnt(node<T> *now) {
        if (now->left == nullptr && now->right == nullptr) {
            ++leave;
            return leave;
        }
        if (now->left != nullptr) cnt(now->left);
        if (now->right != nullptr) cnt(now->right);
    }

    void pre2() {
        node<T> *now = root;
        while (now != nullptr) {
            cout << now->data << " ";
            if (now->ltag == 0)
                now = now->left;
            else if (now->rtag == 0)
                now = now->right;
            else {
                while (now != nullptr && now->rtag == 1) {
                    now = now->right;
                }
                if (now != nullptr) now = now->right;
            }
        }
    }

    node<T> *first(node<T> *current) {
        node<T> *now = current;
        while (now->ltag == 0) now = now->left;
        return now;
    }

    node<T> *next(node<T> *current) {
        node<T> *now = current->right;
        if (current->rtag == 0)
            return first(now);
        else
            return now;
    }

    void in2() {
        node<T> *now;
        for (now = first(now); now != nullptr; now = next(now)) {
            cout << now->data << " ";
        }
    }

    node<T> *parent(node<T> *now) {
        node<T> *p;
        if (now == root) return nullptr;
        for (p = now; p->ltag == 0; p = p->left)
            ;

        if (p->left != nullptr) {
            for (p = p->left; p != nullptr && p->left != now && p->right != now; p = p->right)
                ;
        }
        if (p == nullptr || p->left == nullptr) {
            for (p = now; p->rtag == 0; p = p->right)
                ;
            for (p = p->right; p != nullptr && p->left != now && p->right != now; p = p->left)
                ;
        }
        return p;
    }
    void aft2() {
        node<T> *now = root;
        while (now->ltag == 0 || now->rtag == 0) {
            if (now->ltag == 0)
                now = now->left;
            else if (now->rtag == 0)
                now = now->right;
        }
        cout << now->data << " ";
        node<T> *p;
        while ((p = parent(now)) != nullptr) {
            if (p->right == now || p->rtag == 1) {
                now = p;
            } else {
                now = p->right;
                while (now->ltag == 0 || now->rtag == 0) {
                    if (now->ltag == 0)
                        now = now->left;
                    else if (now->rtag == 0)
                        now = now->right;
                }
            }
            cout << now->data << " ";
        }
    }

    void outlist() {
        cout << "(";
        outlist(root);
        cout << ")";
    }
    void outlist(node<T> *now) {
        if (now == nullptr) return;
        cout << now->data;
        if (now->left != nullptr) {
            cout << "(";
            outlist(now->left);
            if (now->right == nullptr) cout << ")";
        }
        if (now->left != nullptr && now->right != nullptr) {
            cout << ",";
        }
        if (now->right != nullptr) {
            if (now->left == nullptr) {
                cout << "(";
            }
            outlist(now->right);
            cout << ")";
        }
    }
    void init() {
        cout << "input the num of the str: ";
        int k;
        cin >> k;
        cout << "input the str:";
        pre1 = nullptr;
        for (int i = 0; i < k; ++i) {
            T tem;
            cin >> tem;
            str.push_back(tem);
        }
        if (str.empty()) return;
        root = new node<T>;
        root->data = str[0];
        k = 0;
        leave = height = 0;
        create(root);
    }
};

int main() {
    bintree<char> t;
    t.init();
    t.outlist();
    cout << endl;
    t.in(t.root);
    cout << endl;
    t.pre(t.root);
    cout << endl;
    t.aft(t.root);
    cout << endl;
    cout << endl;
    t.inno();
    cout << endl;
    cout << endl;
    t.searc('b');
    t.inThread();
    t.in2();
    cout << endl;
    t.pre2();
    cout << endl;
    t.aft2();
    cout << endl;
    return 0;
}

// 17 a b c . . e . . d f y . . . g . .
