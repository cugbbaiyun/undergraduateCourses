#include <iostream>
template <typename T> struct arrayList {
  public:
    arrayList() = default;

    bool reAlloc(int n) {
        if (n <= maxn) return 0;
        auto tem = new T[n];
        if (tem == NULL) {
            std::cout << "Alloc failed. ";
            return 1;
        }
        maxn = n;
        for (int i = 0; i < size; ++i) {
            tem[i] = data[i];
        }
        delete[] data;
        data = tem;
        return 0;
    }

    void push_back(const T &a) {
        if (size == maxn) {
            bool err = reAlloc(maxn * 2);
            if (err != 0) return;
        }
        data[size++] = a;
    }

    int getMaxn() {
        return this->maxn;
    }

    int getSize() {
        return this->size;
    }

    void outPut() {
        for (int i = 0; i < getSize(); ++i) {
            std ::cout << data[i] << " ";
        }
        return;
    }

    T &locate(int n) {
        if (n < 0 || n >= size) {
            std ::cout << "Illegal input" << std ::endl;
            return data[0];
        }
        return data[n];
    }

    void clear() {
        delete[] data;
        maxn = 100;
        size = 0;
        data = new T[maxn];
    }

    bool isEmpty() {
        return this->size == 0;
    }

    int getLo(const T &a) {
        for (int i = 0; i < getSize(); ++i) {
            if (a == data[i]) {
                return i;
            }
        }
        return -1;
    }

    void insert(int n, const T &a) { // insert before n;
        if (n > size || n < 0) {
            std::cout << "Illeagal location." << std::endl;
            return;
        }
        if (size == maxn) {
            reAlloc(maxn * 2);
        }
        for (int i = size; i > n; --i) {
            data[i] = data[i - 1];
        }
        data[n] = a;
        ++size;
        return;
    }

    void erase(int n) {
        if (n < 0 || n >= size) {
            std::cout << "Illeagal location." << std::endl;
            return;
        }
        for (int i = n; i < size; ++i) {
            data[i] = data[i + 1];
        }
        --size;
        return;
    }

  private:
    int maxn = 100;
    int size = 0;
    T *data = new T[maxn];
};
using namespace std;
arrayList<char> test;
int main() {
    test.push_back('a');
    test.push_back('b');
    test.push_back('c');
    test.push_back('d');
    test.push_back('e');
    cout << test.getSize() << endl;
    test.outPut();
    cout << test.isEmpty() << endl;
    cout << test.locate(3) << endl;
    cout << test.getLo('d') << endl;
    test.insert(3, 'f');
    test.outPut();
    cout << endl;
    test.erase(2);
    test.outPut();
    test.clear();
    return 0;
}
