#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
template <typename T> struct node {
    T c;
    node *left = nullptr;
    node *right = nullptr;
};
template <typename T> struct buildtree {
    node<T> *root = nullptr;
    vector<T> str1;
    vector<T> str2;
    int cur = 0;
    void run() {
        init();
        input();
        root->c = str1[0];
        build(root, 0, str1.size());
        cout << "the after:" << endl;
        aft(root);
    }
    void init() {
        clear(root);
        root = nullptr;
        cur = 0;
        str1.clear();
        str2.clear();
        root = new node<T>;
    }

    void input() {
        cout << "Input the num of the str:";
        int k;
        cin >> k;
        while (1) {
            cout << "Input the pre:" << endl;
            for (int i = 0; i < k; ++i) {
                T tem;
                cin >> tem;
                str1.push_back(tem);
            }
            cout << "Input the in:" << endl;
            for (int i = 0; i < k; ++i) {
                T tem;
                cin >> tem;
                str2.push_back(tem);
            }
            if (testinput()) break;
        }
    }

    bool testinput() {
        vector<T> back1 = str1;
        vector<T> back2 = str2;
        sort(back1.begin(), back1.end());
        sort(back2.begin(), back2.end());
        if (back1 != back2) {
            cout << "Wrong input,retry." << endl;
        }
        return 1;
    }

    void build(node<T> *now, int left1, int right1) {
        if (now == nullptr) return;
        if (cur == str1.size()) return;
        int mid;
        for (mid = left1; mid < right1; ++mid) {
            if (str1[cur] == str2[mid]) break;
        }
        int i;
        ++cur;
        bool flag1 = 0, flag2 = 0;
        for (i = left1; i < mid; ++i) {
            if (str2[i] == str1[cur]) {
                flag1 = 1;
                break;
            }
        }
        if (flag1) {
            now->left = new node<T>;
            now->left->c = str1[cur];
            build(now->left, left1, mid);
        }
        for (i = mid + 1; i < right1; ++i) {
            if (str2[i] == str1[cur]) {
                flag2 = 1;
                break;
            }
        }
        if (flag2) {
            now->right = new node<T>;
            now->right->c = str1[cur];
            build(now->right, mid + 1, right1);
        }
        return;
    }

    void clear(node<T> *now) {
        if (now == nullptr) return;
        if (now->left == nullptr && now->right == nullptr) {
            delete now;
            return;
        }
        if (now->left != nullptr) clear(now->left);
        if (now->right != nullptr) {
            clear(now->right);
        }
        now->left = nullptr;
        now->right = nullptr;
        delete now;
    }

    void aft(node<T> *now) {
        if (now->left != nullptr) aft(now->left);
        if (now->right != nullptr) aft(now->right);
        cout << now->c << " ";
    }
};

int main() {
    buildtree<char> tem;
    tem.run();
    cout << endl;
}
/*
10
A B E C D F G H I J
E B C D A F H I G J
*/