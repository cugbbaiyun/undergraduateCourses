#include <bits/stdc++.h>
using namespace std;
const int maxchar = 26;
struct node {
    node *next[maxchar];
    node *fail = nullptr;
    vector<int> sz;
    // int isFinal = -1;
    node() {
        for (int i = 0; i < maxchar; ++i) { next[i] = nullptr; }
    }
};
node *root;
vector<string> strs;
//Build the trie tree
void buildtrie(string str, int num) {
    node *now = root;
    for (auto c : str) {
        if (now->next[c - 'a'] == nullptr) { now->next[c - 'a'] = new node; }
        now = now->next[c - 'a'];
    }
    now->sz.push_back(num);
    // now->isFinal = num;
}

//Use BFS build the fail pointer
void buildFail() {
    deque<node *> q;
    q.push_back(root);
	//Root's fail pointer should always point at nullptr
    root->fail = nullptr;
    while (!q.empty()) {
        auto now = q.front();
        q.pop_front();
        for (int i = 0; i < maxchar; ++i) {
			//If the char is nullptr, go to the fail pointer until it meet root
            if (now->next[i] != nullptr) {
				//If the vertex is the child of root, the fail pointer should point at root
                if (now == root) {
                    now->next[i]->fail = root;
                } else {
                    auto t = now->fail;
                    while (t != nullptr && t->next[i] == nullptr) {
                        t = t->fail;
                    }
                    if (t == nullptr)
                        now->next[i]->fail = root;
                    else
                        now->next[i]->fail = t->next[i];
                }
                q.push_back(now->next[i]);
            }
        }
    }
}

vector<int> query(string str) {
    int len = str.size();
    vector<int> ret;
    node *now = root;
    for (int i = 0; i < len; ++i) {
        int lo = str[i] - 'a';
		//If it lost match, it should go to the fail pointer
        while (now->next[lo] == nullptr && now != root) now = now->fail;
        if (now->next[lo] == nullptr) { continue; }
        now = now->next[lo];
        node *t = now;
		//Collect all the answers
        while (t != root) {
            if (t->sz.size() != 0) {
                for(auto c:t->sz)ret.push_back(c);
                t->sz.clear();
            }
            t = t->fail;
        }
    }
    sort(ret.begin(),ret.end());
    ret.erase(unique(ret.begin(),ret.end()),ret.end());
    return ret;
}

int main() {
    root = new node;
    cout <<"输入模式串的个数:";
    int n;
    cin >> n;
    vector<int> ans;
    cout << "输入模式串:" << endl;
    for (int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        strs.push_back(str);
        buildtrie(str, i);
    }
    buildFail();
    string str;
    cout <<"输入大文本:" << endl;
    cin >> str;
    ans = query(str);
    cout << "共有" << ans.size() << "个子字符串出现在原字符串中，它们分别为:" << endl;
    for (auto c : ans) { cout << strs[c] << endl; }
}
