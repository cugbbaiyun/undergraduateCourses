#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
string str;
struct node {
    char data;
    int type = 0;
    node *sublist = nullptr;
    node *next = nullptr;
};
node *beg;
int n;
int height = 0;
void create(node *now) {
    while (n < str.size() && str[n] != ')') {
        while (str[n] == ',') ++n;
        if (str[n] == '(') {
            now->type = 1;
            ++n;
            now->sublist = new node;
            create(now->sublist);
        } else if (islower(str[n])) {
            now->type = 0;
            now->sublist = nullptr;
            now->data = str[n];
            ++n;
            if (str[n] != ')') {
                now->next = new node;
            }
        }
    }
    return;
}

void init() {
    cin >> str;
    height = 0;
    if (str == "") return;
    n = 0;
    beg = new node;
    create(beg);
}

void getheight(node *now, int k) {
    height = max(k, height);
    while (now != nullptr) {
        if (now->type == 1) {
            getheight(now->sublist, k + 1);
        }
        now = now->next;
    }
}
int main() {
    init();
    cout << "Height:";
    getheight(beg, 1);
    cout << height << endl;
}
