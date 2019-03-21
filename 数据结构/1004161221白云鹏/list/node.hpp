#include <iostream>
template <typename T> struct node {
  public:
    node() = default;
    node(T tem) {
        this->num = tem;
    }
    node(const node<T> &b) {
        this->num = b.num;
        this->right = b.right;
        this->left = b.left;
    }
    T &getNum() {
        return this->num;
    }
    node<T> *getRight() {
        return this->right;
    }
    void setRight(node<T> *a) {
        this->right = a;
        return;
    }
    void setLeft(node<T> *a) {
        this->left = a;
        return;
    }
    node<T> *getLeft() {
        return this->left;
    }

    void setNum(const T &a) {
        this->num = a;
    }

    bool operator<(const node<T> &a) {
        return this->num < a.num;
    }
    bool operator==(const node<T> &a) {
        return this->num == a.num;
    }
    node<T> &operator=(const node<T> &a) {
        this->num = a.num;
        this->right = a.right;
        this->left = a.left;
        return *this;
    }

  private:
    T num = 0;
    node<T> *right = NULL;
    node<T> *left = NULL;
};
