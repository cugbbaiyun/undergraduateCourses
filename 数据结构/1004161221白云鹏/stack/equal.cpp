#include "stack.cpp"
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
string str;
stack<char> s;
string sstr;
// stack<int> ss;
vector<string> ss;
map<char, int> qwe;
void init() {
    qwe['('] = 1;
    qwe['-'] = qwe['+'] = 2;
    qwe['*'] = qwe['/'] = 3;
    qwe[')'] = 4;
}
stack<int> nums;
int cal() {
    for (auto c : ss) {
        if (isdigit(c[0])) {
            stringstream in(c);
            int tem;
            in >> tem;
            nums.push(tem);
        } else if (c[0] == '-') {
            int tem1, tem2;
            tem1 = nums.getTop();
            nums.pop();
            tem2 = nums.getTop();
            nums.pop();
            nums.push(tem2 - tem1);
        } else if (c[0] == '/') {
            int tem1, tem2;
            tem1 = nums.getTop();
            nums.pop();
            tem2 = nums.getTop();
            nums.pop();
            nums.push(tem2 / tem1);
        } else if (c[0] == '*') {
            int tem1, tem2;
            tem1 = nums.getTop();
            nums.pop();
            tem2 = nums.getTop();
            nums.pop();
            nums.push(tem2 * tem1);
        } else if (c[0] == '+') {
            int tem1, tem2;
            tem1 = nums.getTop();
            nums.pop();
            tem2 = nums.getTop();
            nums.pop();
            nums.push(tem2 + tem1);
        }
    }
    int ans = nums.getTop();
    return ans;
}
void output(string str) {
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && !isdigit(str[i]) && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '(' && str[i] != ')') {
            cout << "不合法输入!";
            return;
        }
        if (isdigit(str[i])) {
            string tem;
            tem.clear();
            while (isdigit(str[i])) {
                char c = str[i];
                tem = tem + c;
                ++i;
            }
            ss.push_back(tem);
            cout << tem << " ";
        }
        if (s.getSize() == 0) {
            s.push(str[i]);
        } else if (str[i] == '(') {
            s.push(str[i]);
        } else if (str[i] == ')') {
            while (s.getTop() != '(') {
                string tem;
                tem += s.getTop();
                ss.push_back(tem);
                cout << s.getTop() << " ";
                s.pop();
            }
            s.pop();
        } else if (qwe[s.getTop()] < qwe[str[i]]) {
            s.push(str[i]);
        } else if (qwe[s.getTop()] >= qwe[str[i]]) {
            while (s.getSize() != 0 && qwe[s.getTop()] >= qwe[str[i]]) {
                string tem;
                tem += s.getTop();
                ss.push_back(tem);
                cout << s.getTop() << " ";
                s.pop();
            }
            s.push(str[i]);
        }
    }
    while (!s.isEmpty()) {
        string tem;
        tem += s.getTop();
        ss.push_back(tem);
        cout << s.getTop() << " ";
        s.pop();
    }
    cout << endl;
}
int main() {
    init();
    cin >> str;
    string tem = str;
    output(str);
    cout << endl;
    cout << endl;
    cout << cal();
    cout << endl;
}