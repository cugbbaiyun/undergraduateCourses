#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;
template <typename T> struct node {
    T data;
    int weight;
    node<T> *left = nullptr;
    node<T> *right = nullptr;
};
template <typename T> struct cmp {
    bool operator()(node<T> *a, node<T> *b) {
        return a->weight >= b->weight;
    }
};
template <typename T> struct haffman {
    node<T> *root;
    vector<node<T> *> vc;
    priority_queue<node<T> *, vector<node<T> *>, cmp<T>> vq;
    map<T, string> list;
    void init() {
        cout << "input the count of the node:" << endl;
        int k;
        cin >> k;
        cout << "Input the data and the weight of the node:" << endl;
        for (int i = 0; i < k; ++i) {
            auto tem = new node<T>;
            cin >> tem->data >> tem->weight;
            vc.push_back(tem);
        }
        buildtree();
        code(root);
    }
    void outcode() {
        for (auto c : list) {
            cout << c.first << ":" << c.second << " ";
            cout << endl;
        }
    }
    void buildtree() {
        for (auto c : vc) {
            vq.push(c);
        }
        while (vq.size() > 1) {
            auto c = vq.top();
            vq.pop();
            auto d = vq.top();
            vq.pop();
            auto tem = new node<T>;
            tem->left = c;
            tem->right = d;
            tem->weight = c->weight + d->weight;
            vq.push(tem);
        }
        root = vq.top();
    }

    void code(node<T> *now, string str = "") {
        if (now->data.size() != 0) {
            list[now->data] = str;
            return;
        }
        if (now->left != nullptr) {
            code(now->left, str + "0");
        }
        if (now->right != nullptr) {
            code(now->right, str + "1");
        }
    }
};
int main() {
    haffman<string> test;
    test.init();
    test.outcode();
}
/*

15
The 1192
of 677
a 541
to 518
and 462
In 450
that 242
he 195
is 190
at 181
on 174
for 157
his 138
are 124
be 123

*/
