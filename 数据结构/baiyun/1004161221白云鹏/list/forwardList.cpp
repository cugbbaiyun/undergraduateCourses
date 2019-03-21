#include "node.hpp"
#include <iostream>
#include <sstream>
#include <string>
template <typename T> struct forwardList {
  public:
    void init() {
        start = new node<T>;
        end = new node<T>;
        size = 0;
    }

    forwardList() {
        init();
    }

    void push_back(T a = 0) {
        node<T> *tem = new node<T>;
        tem->setNum(a);
        if (size == 0) {
            start->setRight(tem);
            end = tem;
        } else {
            end->setRight(tem);
            tem->setRight(NULL);
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
        c->setRight(tem);
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
            --size;
            if (size == 0) end = start;
            return;
        }
        auto tem = locate(n - 1);
        if (tem->getRight() == end) {
            end = tem;
        }
        auto c = tem->getRight();
        tem->setRight(c->getRight());
        delete c;
        --size;
        return;
    }

  private:
    node<T> *start = NULL;
    node<T> *end = NULL;
    int size = 0;
};

// using namespace std;
// int main() {
//     forwardList<int> test;
//     for (int i = 0; i < 3; ++i) {
//         test.push_back(i);
//     }
//     test.insert(3, 3);
//     cout << test.getSize() << endl;
//     test.outPut();
//     cout << test.isEmpty() << endl;
//     cout << test.locate(3)->getNum() << endl;
//     cout << test.getLo(2) << endl;
//     test.erase(3);
//     test.outPut();
// }
using namespace std;
struct train {
  public:
    train() = default;
    void changeStart(const string &str) {
        start = str;
        return;
    }
    void changeEnd(const string &str) {
        end = str;
        return;
    }
    void changeNumber(const string &str) {
        number = str;
    }
    void changeStartTime(const string &str) {
        startTime = str;
    }
    void changeEndTime(const string &str) {
        endTime = str;
    }
    string getStart() const {
        return start;
    }
    string getEnd() const {
        return end;
    }
    string getNumber() const {
        return number;
    }
    string getStartTime() const {
        return startTime;
    }
    string getEndTime() const {
        return endTime;
    }
    train(const train &a) {
        this->start = a.start;
        this->startTime = a.startTime;
        this->end = a.end;
        this->endTime = a.endTime;
        this->number = a.number;
    }
    train &operator=(const train &a) {
        this->start = a.start;
        this->startTime = a.startTime;
        this->end = a.end;
        this->endTime = a.endTime;
        this->number = a.number;
        return *this;
    }
    bool operator==(const train &a) {
        // if (getStart() != a.getStart()) return 0;
        // if (getEnd() != a.getEnd()) return 0;
        if (getNumber() != a.getNumber()) return 0;
        // if (getStartTime() != a.getStartTime()) return 0;
        // if (getEndTime() != a.getEndTime()) return 0;
        return 1;
    }
    bool operator<(const train &a) {
        if (getStart() != a.getStart()) return getStart() < a.getStart();
        if (getEnd() != a.getEnd()) return getEnd() < a.getEnd();
        if (getNumber() != a.getNumber()) return getNumber() < a.getNumber();
        if (getStartTime() != a.getStartTime()) return getStartTime() < a.getStartTime();
        if (getEndTime() != a.getEndTime()) return getEndTime() < a.getEndTime();
        return 0;
    }
    train(int a) {
        start = end = number = startTime = endTime = "";
    }
    void output() {
        cout << "车次:" << number << endl;
        cout << "始发站:" << start << endl;
        cout << "终点站:" << end << endl;
        cout << "出发时间:" << startTime << endl;
        cout << "到站时间:" << endTime << endl;
    }

  private:
    string start;
    string end;
    string number;
    string startTime;
    string endTime;
};

forwardList<train> test;
bool check(const string &str) {
    if (str != "1" && str != "2" && str != "3" && str != "4") return 0;
    return 1;
}
int welcome() {
    cout << "------------------------" << endl;
    cout << "\t火车信息管理" << endl;
    cout << "1.增加火车" << endl;
    cout << "2.修改信息" << endl;
    cout << "3.查询信息" << endl;
    cout << "4.删除信息" << endl;
    cout << "------------------------" << endl;
    cout << "选择功能：" << endl;
    string str;
    cin >> str;
    while (!check(str)) {
        cout << "非法输入，重新输入" << endl;
        cin >> str;
    }
    int n;
    stringstream in(str);
    in >> n;
    return n;
}
void addTrain() {
    train tem;
    string str;
    cout << "车次:" << endl;
    cin >> str;
    tem.changeNumber(str);
    cout << "出发时间:" << endl;
    cin >> str;
    tem.changeStartTime(str);
    cout << "到站时间:" << endl;
    cin >> str;
    tem.changeEndTime(str);
    cout << "始发站:" << endl;
    cin >> str;
    tem.changeStart(str);
    cout << "终点站:" << endl;
    cin >> str;
    tem.changeEnd(str);
    test.push_back(tem);
}

void updateTrain() {
    cout << "输入要更改的车次信息" << endl;
    string str;
    cin >> str;
    train tem;
    tem.changeNumber(str);
    int c = test.getLo(tem);
    if(c == -1){
        cout << "车次信息错误" << endl;
        return;
    }
    auto ptr = test.locate(c);
    cout << "要更改的车次信息:" << endl;
    cout << "1.车次" << endl;
    cout << "2.始发站" << endl;
    cout << "3.终点站" << endl;
    cout << "4.始发时间" << endl;
    cout << "5.到站时间" << endl;
    cin >> str;
    while (check(str) == 0 && str != "5") {
        cout << "输入非法，重新输入" << endl;
        cin >> str;
    }
    string mess;
    cout << "输入信息" << endl;
    cin >> mess;
    if (str == "1") {
        ptr->getNum().changeNumber(mess);
    } else if (str == "2") {
        ptr->getNum().changeStart(mess);
    } else if (str == "3") {
        ptr->getNum().changeEnd(mess);
    } else if (str == "4") {
        ptr->getNum().changeStartTime(mess);
    } else
        ptr->getNum().changeEndTime(mess);
}
void query() {
    string num;
    cout << "输入要查询的车次信息:" << endl;
    cin >> num;
    train tem;
    tem.changeNumber(num);
    int ttt = test.getLo(tem);
    if(ttt==-1){
        cout <<"车次信息错误" << endl;
        return;
    }
    auto ptr = test.locate(ttt);
    ptr->getNum().output();
}
void erase() {
    string num;
    cout << "输入要删除的车次信息:" << endl;
    cin >> num;
    train tem;
    tem.changeNumber(num);
    int ttt = test.getLo(tem);
    if(ttt == -1){
        cout <<"车次信息错误" << endl;
        return ;
    }
    test.erase(ttt);
}
int main() {
    while (1) {
        int fu = welcome();
        if (fu == 1) {
            addTrain();
        } else if (fu == 2) {
            updateTrain();
        } else if (fu == 3) {
            query();
        } else {
            erase();
        }
    }
}