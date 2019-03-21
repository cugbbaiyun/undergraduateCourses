#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
string str;
string ans;
int nfind() {
  string back(str);
  vector<string> strs;
  while (back.size() != 0) {
    strs.push_back(back);
    back.erase(back.begin());
  }
  sort(strs.begin(), strs.end());
  int maxn = -1;
  for (int i = 0; i < strs.size() - 1; ++i) {
    int j;
    string tem;
    tem.clear();
    for (j = 0; j < strs[i].size() && j < strs[i + 1].size(); ++j) {
      if (strs[i][j] != strs[i + 1][j])
        break;
      tem = tem + strs[i][j];
    }
    if (j > maxn) {
      ans = tem;
      maxn = j;
    }
  }
  return maxn;
}

int main() {
  cout << "Input the string:" << endl;
  cin >> str;
  cout << nfind() << endl;
  return 0;
}