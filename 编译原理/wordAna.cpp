#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
char ch;
string strToken;
struct wordList {
    int code = -1;
    string str="";
};
vector<wordList> wl;
map<string, int> mm;
set<string> rs;
string line;
int top;
set<char> signs;
void initWords() {
    signs.insert('+');
    signs.insert('-');
    signs.insert('*');
    signs.insert('/');
    signs.insert('%');
    signs.insert('=');
    signs.insert('>');
    signs.insert('<');
    signs.insert('|');
    signs.insert('!');
    signs.insert('&');
    signs.insert('(');
    signs.insert(')');
    signs.insert(';');
    signs.insert('{');
    signs.insert('}');
    signs.insert('[');
    signs.insert(']');
    signs.insert('}');
    signs.insert(',');

    rs.insert("int");
    rs.insert("else");
    rs.insert("if");
    rs.insert("while");
    rs.insert("void");

    mm["int"] = 5;
    mm["else"] = 15;
    mm["if"] = 17;
    mm["while"] = 20;
    mm["+"] = 41;
    mm["-"] = 42;
    mm["*"] = 43;
    mm["/"] = 44;
    mm["%"] = 45;
    mm["="] = 46;
    mm[">"] = 47;
    mm[">="] = 48;
    mm["<"] = 49;
    mm["<="] = 50;
    mm["=="] = 51;
    mm["!="] = 52;
    mm["&&"] = 53;
    mm["||"] = 54;
    mm["++"] = 56;
    mm["!"] = 55;
    mm["--"] = 57;
    mm[")"] = 82;
    mm["("] = 81;
    mm[";"] = 84;
    mm["{"] = 86;
    mm["}"] = 87;
    mm["["] = 88;
    mm[","] = 90;
    mm["]"] = 89;
}
void outPut(wordList c) {
    cout << "< " << c.code << ", ";
    if (c.code != 0)
        cout << c.str;
    else
        cout << "-";
    cout << " >" << endl;
}

void GetChar() {
    if (top < line.size())
        ch = line[top++];
    else
        ch = '#';
}
void GetBC() {
    while (top < line.size() && isspace(ch)) ch = line[top++];
    if (isspace(ch)) ch = '#';
}
void Concat() {
    strToken += ch;
    ch = ' ';
}
bool IsLetter(char letter) {
    return islower(letter) || isupper(letter);
}
bool IsDigit(char letter) {
    return isdigit(letter);
}
int Reserve(string strtk) {
    if (rs.find(strtk) != rs.end()) { return mm[strtk]; }
    return 0;
}
void Retract() {
    ch = ' ';
    --top;
}
bool IsSign(char letter) {
    return (signs.find(letter) != signs.end());
}

wordList InsertID(int code, string str) {
    wordList tem;
    tem.code = code;
    tem.str = str;
    wl.push_back(tem);
    // outPut(tem);
    return tem;
}
wordList InsertConst(string str) {
    wordList tem;
    tem.code = 100;
    tem.str = str;
    wl.push_back(tem);
    // outPut(tem);
    return tem;
}

bool IsHexDigit(char c) {
    if (isdigit(c)) return 1;
    if (islower(c)) {
        int dis = c - 'a';
        int maxdis = 'f' - 'a';
        return (dis >= 0 && dis <= maxdis);
    }
    if (isupper(c)) {
        int dis = c - 'A';
        return (dis >= 0 && dis <= ('F' - 'A'));
    }
    return 0;
}

wordList WordAnlay() {
    wordList tem;
    while (1) {
        GetBC();
        if (IsLetter(ch)) {
            while (IsLetter(ch) || IsDigit(ch)) {
                Concat();
                GetChar();
            }
            if (ch != '#') Retract();
            int code = Reserve(strToken);
            // cout << strToken << endl;
            if (code == 0) {
                tem = InsertID(111, strToken);
            } else {
                tem = InsertID(code, strToken);
            }
            strToken.clear();
            return tem;

        } else if (IsDigit(ch)) {
            while (IsDigit(ch)) {
                Concat();
                GetChar();
            }
            if (ch != '#') Retract();
            // cout << strToken << endl;
            tem = InsertConst(strToken);
            strToken.clear();
            return tem;
        } else if (IsSign(ch)) {
            while (IsSign(ch)) {
                Concat();
                GetChar();
            }
            if (ch != '#') Retract();
            int code = 0;
            while (code == 0) {
                code = mm[strToken];
                if (code != 0) {
                    // cout << strToken << endl;
                    tem = InsertID(code, strToken);
                    strToken.clear();
                    // cout << tem.str << endl;
                    return tem;
                } else {
                    Retract();
                    strToken.pop_back();
                }
            }
        }
        if (ch == '#') break;
    }
}
