#include <iostream>
using namespace std;
template <typename T> struct stack {
  public:
    // To init stack
    stack() {
        size = 0;
        reAlloc(50);
    }

    // Assign length to the stack
    stack(const int &n) {
        size = 0;
        len = n;
        data = new T[len];
        // If there is no more memory, cout error
        if (data == nullptr) {
            cerr << "Alloc failed, no more memory.";
            return;
        }
    }

    int getSize() const {
        return this->size;
    }

    // return the stack is empty
    bool isEmpty() const {
        return getSize() == 0;
    }

    // To get the length of the stack
    int getLength() const {
        return this->len;
    }

    // Get the top element
    T &getTop() {
        if (!isEmpty()) {
            return this->data[size - 1];
        }
        cerr << "The stack is empty." << endl;
        ;
        return data[0];
    }

    void showstack() {
        if (isEmpty()) return;
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Push element into the stack
    bool push(const T &a) {
        // Check the length of the stack
        // If not, realloc memory
        // If alloc failed, return false
        if (!reAlloc(size + 1)) {
            return 0;
        }

        data[size++] = a;
        return 1;
    }

    // pop the top element
    bool pop() {
        if (isEmpty()) {
            cerr << "The stack is empty." << endl;
            return 0;
        }
        --size;
        return 1;
    }

    ~stack() = default;

    bool operator<(const stack &c) const {
        int minlen = min(getSize(), c.getSize());
        for (int i = 0; i < minlen; ++i) {
            if (data[i] < c.data[i])
                return 1;
            else if (data[i] < c.data[i])
                return 0;
        }
        return size == minlen;
    }

  private:
    bool reAlloc(const int &n) {
        if (this->len > n) {
            return true;
        }
        len = 2 * n;
        auto tem = new T[len];
        if (tem == nullptr) {
            cerr << "Alloc failed, no more memory." << endl;
            return false;
        }
        for (int i = 0; i < size; ++i) {
            tem[i] = data[i];
        }
        if (data != nullptr) delete[] data;
        data = tem;
        return true;
    }
    T *data = nullptr;
    int size = 0;
    int len = 0;
};

// int main() {
//     stack<int> test;
//     while (1) {
//         cout << "Functions:" << endl;
//         cout << "1.Push" << endl;
//         cout << "2.Pop" << endl;
//         cout << "3.Get top" << endl;
//         cout << "4.Get size" << endl;
//         cout << "5.Get length" << endl;
//         cout << "6.Free stack" << endl;
//         cout << "7.Show stack" << endl;
//         int n;
//         cin >> n;
//         if (n == 6) {
//             return 0;
//         } else if (n == 1) {
//             int q;
//             cout << "Input the element" << endl;
//             cin >> q;
//             test.push(q);
//         } else if (n == 2) {
//             if (test.isEmpty()) {
//                 cout << "The stack is empty" << endl;
//             } else {
//                 cout << "Index:" << test.getSize() << endl;
//                 cout << "Value:" << test.getTop() << endl;
//                 test.pop();
//             }
//         } else if (n == 3) {
//             if (test.isEmpty()) {
//                 cout << "The stack is empty" << endl;
//             } else {
//                 cout << "Index:" << test.getSize() << endl;
//                 cout << "Value:" << test.getTop() << endl;
//             }
//         } else if (n == 4) {
//             cout << test.getSize() << endl;
//         } else if (n == 5) {
//             cout << test.getLength() << endl;
//         } else if (n == 7) {
//             test.showstack();
//         }
//     }
//     return 0;
// }