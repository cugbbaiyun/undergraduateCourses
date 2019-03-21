#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int nex[N];
void getNext(string str) {
    int len = str.size(), k = -1, j = 0;
    nex[0] = -1;
    while (j < len) {
        if (k == -1 || str[j] == str[k]) {
            j++, k++;
            nex[j] = k;
        } else
            k = nex[k];
    }
}
int match(string S, string P) {
    int lenS = S.size();
    int lenP = P.size();
    int j = 0, k = 0;
    while (k < lenP && j < lenS) {
        if (k == -1 || S[j] == P[k]) {
            j++, k++;
        } else
            k = nex[k];
    }
    if (k < lenP) {
        return -1;
    } else
        return j - lenP;
}
int main() {
    string S = "";
    string P = "";
    getNext(P);
    cout << match(S, P);
    return 0;
}