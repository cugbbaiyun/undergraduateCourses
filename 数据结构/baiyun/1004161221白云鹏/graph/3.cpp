#include <iostream>
#include <map>
using namespace std;
map<int, int> in;
map<int, int> out;
int main() {
    int k;
    cout << "Input the num of the edges:" << endl;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cout << "Input the start and the end of the edge:" << endl;
        int s, e;
        cin >> s >> e;
        ++in[e];
        ++out[s];
    }
    cout << "In:" << endl;
    for (auto c : in) {
        cout << c.first << ":" << c.second << endl;
    }
    cout << endl << endl << "out:" << endl;
    for (auto c : out) {
        cout << c.first << ":" << c.second << endl;
    }
    cout << endl;
}