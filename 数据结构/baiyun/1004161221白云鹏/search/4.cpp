#include<iostream>
using namespace std;
template <typename T> struct node {
  node<T> *left = nullptr;
  node<T> *right = nullptr;
  T data;
  node(const T &tem) { data = tem; }
  node() = default;
};

template <typename T> struct tree {
  node<T> *root;
  int len;
  void init() { root = new node<T>; }

  void create(){
    init();
    int k;
    cout << "Input the length of the data:"<< endl;
    cin >> k;
    cout << "Input the data:" << endl;
    T tem;
    cin >> tem;
    root -> data = tem;
    for(int i=1; i < k;++i){
      cin >> tem;
      insert(root,tem);
    }
  }

  void insert(node<T> *now, T &tem) {
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

  bool check(node<T> *now){
    if(now->left == nullptr && now ->right == nullptr)return 1;
    bool l =1, r =1;
    bool ok1 =1, ok2 =1;
    if(now ->left != nullptr){l= check(now ->left);if(now->data <now->left->data)ok1=0;}
    if(now->right!=nullptr){r=check(now->right);if(now->data>now->right -> data)ok2=0;}
    if(!ok1||!ok2||!l || ! r)return 0;
    return 1 ;
  }

  void search(){
    T tem;
    cout << "Input the element to search:" << endl;
    cin >> tem;
    auto now  = root;
    while(now != nullptr){
      cout << now->data << " " ;
      if(now -> data == tem)return;
      if(now -> data > tem){
        now = now->left;
      }else{
        now = now->right;
      }
    }
    cout << "Not found" << endl;
    return;
  }
};
int main(){
  tree<int> test;
  test.init();
  test.create();
  test.search();
  cout << test.check(test.root) << endl;
}
