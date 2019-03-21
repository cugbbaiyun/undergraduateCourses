#include "node.hpp"
#include <iostream>
#include <stack>
using namespace std;
template <typename T> struct List {
  public:
    void init() {
        start = new node<T>;
        end = new node<T>;
        size = 0;
    }

    List() {
        init();
    }

    void push_back(T a = 0) {
        node<T> *tem = new node<T>;
        tem->setNum(a);
        if (size == 0) {
            start->setRight(tem);
            end = tem;
        } else {
            tem->setLeft(end);
            end->setRight(tem);
            end = tem;
        }
        ++size;
        return;
    }

    int getSize() {
        return this->size;
    }

    node<T> *locate(int n) {
        if (n <= 0 || n > getSize()) return NULL;
        auto now = start;
        for (int i = 0; i < n; ++i) {
            now = now->getRight();
        }
        return now;
    }

    node<T> *insert(int n, T a) { // Insert a after element n
        auto c = locate(n);
        if (c == NULL) {
            std::cout << " Element not exists." << std::endl;
            return NULL;
        }
        auto tem = new node<T>;
        tem->setNum(a);
        tem->setRight(c->getRight());
        if (tem->getRight() != NULL) tem->getRight()->setLeft(tem);
        c->setRight(tem);
        tem->setLeft(c);
        if (c == end) {
            end = tem;
        }
        ++size;
        return tem;
    }

    node<T> *getStart() {
        return this->start;
    }

    node<T> *getEnd() {
        return this->end;
    }

    bool isEmpty() {
        return (getSize() == 0) && (getStart() == NULL);
    }

    int getLo(T a) {
        auto now = start->getRight();
        for (int i = 0; i < size; ++i) {
            if (now->getNum() == a) return i + 1;
            now = now->getRight();
        }
        return -1;
    }

    void clear() {
        auto c = start->getRight();
        while (c != NULL) {
            auto tem = c->getRight();
            delete c;
            c = tem;
        }
        end->setRight(NULL);
        start->setRight(NULL);
        return;
    }
    void outPut() {
        auto c = start->getRight();
        while (c != NULL) {
            std::cout << c->getNum() << "->";
            c = c->getRight();
        }
        std ::cout << std::endl;
        return;
    }

    void erase(int n) {
        if (n == 1) {
            auto c = start->getRight()->getRight();
            delete start->getRight();
            start->setRight(c);
            c->setLeft(NULL);
            --size;
            if (size == 0) end = start;
            return;
        }
        auto tem = locate(n - 1);
        if (tem == NULL) return;
        if (tem->getRight() == end) {
            end = tem;
        }
        auto c = tem->getRight();
        tem->setRight(c->getRight());
        if (tem->getRight() != NULL) tem->getRight()->setLeft(tem);
        delete c;
        --size;
        return;
    }
    void reverse() {
        stack<node<T> *> tem;
        auto now = start->getRight();
        while (now != NULL) {
            tem.push(now);
            now = (tem.top())->getRight();
        }
        cout << "Fuck" << endl;
        now = start;
        while (!tem.empty()) {
            now->setRight(tem.top());
            tem.pop();
            now = now->getRight();
        }
        now->setRight(NULL);
    }

  private:
    node<T> *start = NULL;
    node<T> *end = NULL;
    int size = 0;
};

using namespace std;
List<char> test;
int main() {
    test.push_back('a');
    test.push_back('b');
    test.push_back('c');
    test.push_back('d');
    test.push_back('e');
    test.outPut();
    test.reverse();
    test.outPut();
    return 0;
}
