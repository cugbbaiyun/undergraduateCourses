#include <cctype>
#include <iostream>
using namespace std;
struct isDigit {
	//The judge string
    string str;
	//The stat
    int nowStat = 0;
	//The string's length
    int len = 0;
	
	//Set the judge string
    void setStr(const string &strr) {
        str = strr;
        len = str.size();
        nowStat = 0;
    }
	
	//Judge the char is HexDigit
    bool isHexDigit(int t) {
        if (isdigit(str[t])) return 1;
        if (islower(str[t])) {
            int dis = str[t] - 'a';
            int maxdis = 'f' - 'a';
            return (dis >= 0 && dis <= maxdis);
        }
        if (isupper(str[t])) {
            int dis = str[t] - 'A';
            return (dis >= 0 && dis <= ('F' - 'A'));
        }
        return 0;
    }

	//The automation
    bool isLegalDigit() {
        int nowLo = 0;
        while (nowLo <= len + 1) {
            if (nowStat == 0) {
                cout << "Stat:0 开始判断" << endl;
                if (nowLo == len)
                    nowStat = 8;
                else if (str[nowLo] == '+' || str[nowLo] == '-')
                    nowStat = 1;
                else if (str[nowLo] == '.')
                    nowStat = 3;
                else if (str[nowLo] == '0')
                    nowStat = 4;
                else if (isdigit(str[nowLo]))
                    nowStat = 2;
                else
                    return 0;
            } else if (nowStat == 1) {
                cout << "Stat:1 字符前有+/-号" << endl;
                if (str[nowLo] == '0')
                    nowStat = 4;
                else if (isdigit(str[nowLo]))
                    nowStat = 2;
                else if (str[nowLo] == '.')
                    nowStat = 3;
                else
                    return 0;
            } else if (nowStat == 2) {
                cout << "Stat:2 在这里需要读入全部剩下的整数部分" << endl;
                if (nowLo == len)
                    nowStat = 8;
                else if (str[nowLo] == 'l' || str[nowLo] == 'L')
                    nowStat = 6;
                else if (str[nowLo] == '.')
                    nowStat = 9;
                else if (str[nowLo] == 'e' || str[nowLo] == 'E')
                    nowStat = 10;
                else if (!isdigit(str[nowLo]))
                    return 0;
            } else if (nowStat == 3) {
                cout << "Stat:3 这可能是一个小数" << endl;
                if (isdigit(str[nowLo]))
                    nowStat = 9;
                else
                    return 0;
            } else if (nowStat == 4) {
                cout << "Stat:4 这里需要判断是十进制还是十六进制" << endl;
                if (nowLo == len)
                    nowStat = 8;
                else if (str[nowLo] == 'x' || str[nowLo] == 'X')
                    nowStat = 5;
                else if (isdigit(str[nowLo]))
                    nowStat = 2;
                else if (str[nowLo] == 'l' || str[nowLo] == 'L')
                    nowStat = 6;
                else
                    return 0;
            } else if (nowStat == 5) {
                cout << "Stat:5 在这里读入全部的十六进制数字" << endl;
                if (nowLo == len)
                    nowStat = 8;
                else if (str[nowLo] == 'l' || str[nowLo] == 'L')
                    nowStat = 6;
                else if (!isHexDigit(nowLo))
                    return 0;
            } else if (nowStat == 6) {
                cout << "Stat:6 这里表示后缀中有一个l/L" << endl;
                if (nowLo == len)
                    nowStat = 8;
                else if (str[nowLo] == 'l' || str[nowLo] == 'L')
                    nowStat = 7;
                else
                    return 0;
            } else if (nowStat == 7) {
                cout << "Stat:7 这里表示后缀中有两个l/L" << endl;
                if (nowLo == len)
                    nowStat = 8;
                else
                    return 0;
            } else if (nowStat == 8) {
                cout << "Stat:8 字符串可接受" << endl;
                return 1;
            } else if (nowStat == 9) {
                cout << "Stat:9 这里需要读入剩下全部的小数部分" << endl;
                if (nowLo == len)
                    nowStat = 8;
                else if (str[nowLo] == 'E' || str[nowLo] == 'e')
                    nowStat = 10;
                else if (!isdigit(str[nowLo]))
                    return 0;
            } else if (nowStat == 10) {
                cout << "Stat:10 这可能是一个科学计数法表示的字符串" << endl;
                if (str[nowLo] == '+' || str[nowLo] == '-')
                    nowStat = 12;
                else if (isdigit(str[nowLo]))
                    nowStat = 11;
                else
                    return 0;
            } else if (nowStat == 11) {
                cout << "Stat:11 这里则需要读入全部的e指数" << endl;
                if (nowLo == len)
                    nowStat = 8;
                else if (!isdigit(str[nowLo]))
                    return 0;
            } else if (nowStat == 12) {
                cout << "Stat:12 这里表示e指数有+/-" << endl;
                if (isdigit(str[nowLo]))
                    nowStat = 11;
                else
                    return 0;
            }
            ++nowLo;
        }
        return 0;
    }
};

int main() {
    isDigit test;
    string str;
    cin >> str;
    test.setStr(str);
    bool ans = test.isLegalDigit();
    if (ans) {
        cout << "Yes, it is." << endl;
        ;
    } else {
        cout << "No, it isn't." << endl;
    }
}
