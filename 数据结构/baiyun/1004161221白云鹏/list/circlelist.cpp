#include "node.hpp"
#include <iostream>
template <typename T> struct circleList {
  public:
    void init() {
        start = new node<T>;
        end = new node<T>;
        size = 0;
    }
    circleList() {
        init();
        end->setRight(start);
    }

    node<T> *push_back(T a = 0) {
        node<T> *tem = new node<T>;
        tem->setNum(a);
        if (size == 0) {
            start->setRight(tem);
            tem->setRight(start);
            end = tem;
        } else {
            end->setRight(tem);
            tem->setRight(start);
            end = tem;
        }
        ++size;
        return tem;
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
        if (n == size) {
            return push_back(a);
        }
        auto tem = new node<T>;
        tem->setNum(a);
        tem->setRight(c->getRight());
        c->setRight(tem);
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
        for (int i = 0; i < size && now != start; ++i) {
            if (now->getNum() == a) return i + 1;
            now = now->getRight();
        }
        return -1;
    }

    void clear() {
        auto c = start->getRight();
        while (c != start) {
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
        while (c != start) {
            std::cout << c->getNum() << "->";
            c = c->getRight();
        }
        std ::cout << std::endl;
        return;
    }

    node<T> *erase(int n) {
        if (n <= 0 || n > getSize()) return start;
        if (n == 1) {
            auto c = start->getRight()->getRight();
            delete start->getRight();
            start->setRight(c);
            --size;
            if (size == 0) {
                end->setRight(start);
                start->setRight(NULL);
            }
            return start;
        }
        auto tem = locate(n - 1);
        auto c = tem->getRight();
        tem->setRight(c->getRight());
        if (tem->getRight() == start) {
            end = tem;
        }
        delete c;
        --size;
        return tem->getRight();
    }

  private:
    node<T> *start = NULL;
    node<T> *end = NULL;
    int size = 0;
};
using namespace std;
circleList<int> list;
int test() {
    int m, n;
    cin >> n >> m;
    if (n <= 0 || m <= 0) return -1;

    auto now = list.getStart();
    for (int i = 1; i <= n; ++i) {
        list.push_back(i);
    }

    while (list.getSize() > 1) {
        for (int i = 0; i < m - 1; ++i) {
            if (now == list.getStart()) now = now->getRight();
            now = now->getRight();
            if (now == list.getStart()) now = now->getRight();
        }
        int n = list.getLo(now->getNum());
        cout << now->getNum() << "->";
        now = list.erase(n);
        if (now == list.getStart()) now = now->getRight();
    }

    return list.getStart()->getRight()->getNum();
}
int main() {
    cout << test();
    cout << endl;
    return 0;
}
