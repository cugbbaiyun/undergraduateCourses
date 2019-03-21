#include <iostream>
#include <stack>
using namespace std;
template <typename T> struct node {
  node<T> *left = nullptr;
  node<T> *right = nullptr;
  T data;
  node(const T &tem) { data = tem; }
  node() = default;
};
/*
template <typename T> struct tree {
  node<int> *root;
  void init() { root = new node<int>; }

  void create(const T &tem) { root->data = tem; }

  void insert(node<T> *now, cosnt T &tem) {
    if (tem <= now->data && now->left == nullptr) {
      now->left = new node<int>(tem);
    } else if (tem > now->data && now->right == nullptr) {
      now->right = new node<int>(tem);
    } else if (tem > now->data) {
      insert(now->right, tem);
    } else if (tem <= now->data) {
      insert(now->left, tem);
    }
  }

  void pre(node<T> *now) {
    if (now == nullptr)
      return;
    cout << now->data << " ";
    if (now->left != nullptr) {
      pre(now->left);
    }
    if (now->right != nullptr) {
      pre(now->right);
    }
    return;
  }

  void pre1() {
    stack<node<T> *> st;
    if (root == nullptr)
      return;
    st.push(root);
    while (!st.empty()) {
      auto c = st.top();
      st.pop();
      cout << c.data << " ";
      if (c->left != nullptr) {
        st.push(c->left);
      }
      if (c->right != nullptr) {
        st.push(c->right);
      }
    }
    return;
  }

  void aft(node<T> *now) {
    if (now == nullptr)
      return;
    if (now->left != nullptr) {
      aft(now->left);
    }
    if (now->right != nullptr) {
      aft(now->right);
    }
    cout << now->data << " ";
  }
  void aft1() {
    if (root == nullptr)
      return;
    stack<node<T>> st;
    st.push(root);
    while (!st.empty()) {
      auto c = st.top();
      st.pop();
      if (c->left != nullptr)
        st.push(c->left);
      if (c->right != nullptr)
        st.push(c->right);
      cout << c->data
    }
  }

  void in(node<T> *now) {
    if (now == nullptr)
      return;
    if (now->left != nullptr) {
      in(now->left);
    }
    cout << now->data << " ";
    if (now->right != nullptr) {
      in(now->right);
    }
  }
  int
};
*/

int main() {
  int k;
  cout << "Input the counts of the nums:";
  cin >> k;
  cout << "Input the num:" << endl;
  init();
  {
    int tem;
    cin >> tem;
    create(tem);
  }
  for (int i = 1; i < k; ++i) {
    int tem;
    cin >> tem;
    insert(root, tem);
  }
  pre(root);
  cout << endl;
  in(root);
  cout << endl;
  aft(root);
  cout << endl;
}