#include <iostream>
using namespace std;
template <typename T> struct circlequeue {
  public:
    // Default construct function
    circlequeue() {
        front = 0;
        tail = 0;
        sz = 0;
        len = 2;
        data = new T[len];
    };

    ~circlequeue() {
        delete[] data;
    }

    void init() {
        delete[] data;
        len = 2;
        front = tail = 0;
        sz = 0;
        data = new T[len];
    }
    int getlen() {
        return len - 1;
    }

    bool push_back(const T &a) {
        ++sz;
        if (!reAlloc(sz + 1)) return 0;
        data[tail] = a;
        tail++;
        tail %= len;
        return 1;
    }

    bool isEmpty() const {
        return getsize() == 0;
    }

    int getsize() const {
        return sz;
    }

    bool pop_back() {
        if (isEmpty()) {
            cerr << "The queue is empty." << endl;
            return 0;
        }
        tail += len;
        tail -= 1;
        tail %= len;
        sz--;
        if (sz < len / 4) reAlloc(len / 4 + 1);
        return 1;
    }

    bool pop_front() {
        if (isEmpty()) {
            cerr << "The queue is empty." << endl;
            return 0;
        }
        front = (front + 1) % len;
        --sz;
        if (sz < len / 4) reAlloc(len / 4 + 1);
        return 1;
    }

    T &getfront() {
        if (isEmpty()) {
            cerr << "The queue is empty." << endl;
            return data[0];
        }
        return data[front];
    }

    T &gettail() {
        if (isEmpty()) {
            cerr << "The queue is empty." << endl;
            return data[0];
        }
        int next = (tail - 1 + len) % len;
        return data[next];
    }
    void showdata() {
        for (int i = 0; i < len; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    void showqueue() {
        if (isEmpty()) {
            cerr << "The queue is empty." << endl;
            return;
        }
        for (int i = front; i != tail; ++i, i %= len) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

  private:
    bool reAlloc(const int &a) {
        if (a < len) return 1;
        int back = len;
        len = a * 2;
        auto tem = new T[len];
        if (tem == nullptr) {
            cerr << "No more memory" << endl;
            return 0;
        }
        int j = 0;
        for (int i = front; i != tail; ++i, ++j, i %= back) {
            tem[j] = data[i];
        }
        delete[] data;
        data = tem;
        front = 0;
        tail = j;
        return 1;
    }

    int front;
    int tail;
    T *data;
    int sz;
    int len;
};
/*
int main() {
    circlequeue<int> test;
    while (1) {
        cout << "Functions:" << endl;
        cout << "1.init" << endl;
        cout << "2.is empty" << endl;
        cout << "3.push_back" << endl;
        cout << "4.get back" << endl;
        cout << "5.pop front" << endl;
        cout << "6.pop back" << endl;
        cout << "7.show data" << endl;
        cout << "8.show queue" << endl;
        cout << "9.exit" << endl;
        int n;
        cin >> n;
        if (n == 1) {
            test.init();
        } else if (n == 2) {
            if (test.isEmpty()) {
                cout << "The queue is empty" << endl;
            } else {
                cout << "The queue is not empty" << endl;
            }
        } else if (n == 3) {
            cout << "Input the element" << endl;
            int n;
            cin >> n;
            test.push_back(n);
        } else if (n == 4) {
            if (test.isEmpty()) {
                cout << "The queue is empty." << endl;
            } else
                cout << "The " << test.getsize() << "th:" << test.gettail() << endl;
        } else if (n == 5) {
            if (test.isEmpty())
                cerr << "The queue is empty." << endl;
            else
                test.pop_front();
        } else if (n == 6) {
            if (test.isEmpty())
                cerr << "The queue is empty." << endl;
            else
                test.pop_back();
        } else if (n == 7) {
            test.showdata();
        } else if (n == 8)
            test.showqueue();
        else if (n == 9) {
            return 0;
        }
    }
}
*/