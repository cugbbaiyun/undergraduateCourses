#include "circlequeue.cpp"
#include <iostream>
using namespace std;
circlequeue<int> q;

int main() {
    while (1) {
        cout << "Functions:" << endl;
        cout << "1.排队" << endl;
        cout << "2.就诊" << endl;
        cout << "3.查看排队" << endl;
        cout << "4.不用排队" << endl;
        cout << "5.退出" << endl;
        int n;
        cin >> n;
        if (n == 1) {
            cout << "Input the number:" << endl;
            int tem;
            cin >> tem;
            q.push_back(tem);
        } else if (n == 2) {
            cout << "就诊号：";
            cout << q.getfront() << endl;
            q.pop_front();
        } else if (n == 3) {
            q.showqueue();
        } else if (n == 4) {
            q.showqueue();
            return 0;
        } else if (n == 5) {
            return 0;
        }
    }
}