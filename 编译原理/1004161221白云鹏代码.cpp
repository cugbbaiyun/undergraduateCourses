#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
char ch;
string strToken;
struct wordList {
  int code = -1;
  string str = "";
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
bool IsLetter(char letter) { return islower(letter) || isupper(letter); }
bool IsDigit(char letter) { return isdigit(letter); }
int Reserve(string strtk) {
  if (rs.find(strtk) != rs.end()) {
    return mm[strtk];
  }
  return 0;
}
void Retract() {
  ch = ' ';
  --top;
}
bool IsSign(char letter) { return (signs.find(letter) != signs.end()); }

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
wordList word;
// int tp = 0;
int nextquad = 0;
struct node {
  string name;
  int result = 1;
  int inndim;
  string offset;
  string array;
  int truelist = -1;
  int falselist = -1;
  string inarray;
  int quad = -1;
  int op4 = -1;
  int nextlist = -1;
};

struct emits {
  int code;
  string str_code;
  string op1;
  string op2;
  string op3;
  string op4;
  int next = -1;

  emits(string ce, string str1, string str2, string str3, string str4) {
    str_code = ce;
    op1 = str1;
    op2 = str2;
    op3 = str3;
    op4 = str4;
    code = atoi(ce.c_str());
  }
};

vector<emits> outstring;

int M() { return nextquad; }
const string outfile = "./debug.txt";
ofstream outt(outfile);

void output() {
  for (auto c : outstring) {
    outt << c.code << ":\t";
    outt << c.op1 << "," << c.op2 << "," << c.op3 << "," << c.op4 << endl;
  }
}

string limit(string a, int b) { return "n" + to_string(b); }

int temp = 1;
node term();
node factor();
node rest5(node rest5in);
node rest6(node rest6in);
node unary();
node rel();
node expr();
void rest4();
node Bool();
node stmt();
int ncode = 0;

int makelist(int n) {
  // node *ret = new node;
  // ret->quad = n;
  // ret->nextlist = nullptr;
  return n;
}
string newtemp() { return "T" + to_string(temp++); }

vector<string> vs1;
string vs2;

void emit(string ce, string op1, string op2, string op3, string op4) {
  emits fuck(ce, op1, op2, op3, op4);
  outstring.push_back(fuck);
  ++ncode;
  ++nextquad;
}

int Merge(int a2, int a1) {
  int back = a2;
  emits *pre = nullptr;
  while (a2 != -1) {
    bool flag = 0;
    for (auto &c : outstring) {
      if (c.code == a2) {
        flag = 1;
        c.op4 = to_string(a1);
        pre = &c;
        a2 = c.next;
      }
    }
    if (flag == 0) break;
  }
  a2 = back;
  int head = a1;
  // pre = nullptr;
  // pre->next = a2;
  int lc = 0;
  for (; lc < outstring.size(); ++lc) {
    if (outstring[lc].code == a1) break;
  }
  if (lc != outstring.size()) {
    while (outstring[lc].next != -1) {
      lc = outstring[lc].next;
    }
    outstring[lc].next = a2;
  }
  return head;
}

int N() {
  int t = makelist(nextquad);
  emit(to_string(ncode), "j", "-", "-", "-");

  return t;
}

int toint(wordList a) {
  if (a.code != 100) {
    cerr << "error it is not a num";
    exit(0);
  }
  string str = a.str;
  istringstream in(str);
  int t;
  in >> t;
  return t;
}

void backpatch(int nc, int n) {
  while (nc != -1) {
    bool flag = 0;
    for (auto &c : outstring) {
      if (c.code == nc) {
        flag = 1;
        c.op4 = to_string(n);
        nc = c.next;
        break;
      }
    }
    if (flag == 0) break;
  }
}

node rest1(node &rest1in) {
  if (word.str == ",") {
    auto t = newtemp();
    int m = rest1in.inndim + 1;
    emit(to_string(ncode), "*", rest1in.name, limit(rest1in.inarray, m), t);
    // cout << "rest1 -> ,expr rest1" << endl;
    // string str1 = "rest1";
    // string str2 = ",expr rest1";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    word = WordAnlay();
    auto exprt = expr();
    emit(to_string(ncode), "+", t, exprt.name, t);
    node rest11;
    rest11.inarray = rest1in.inarray;
    rest11.inndim = m;
    rest11.name = t;
    auto result = rest1(rest11);
    rest1in.array = result.array;
    rest1in.offset = result.offset;
    return rest1in;
  } else {
    node ret;
    ret.array = rest1in.inarray;
    ret.offset = rest1in.name;
    return ret;
  }
}

node rest0(node &rest0in) {
  if (word.code == 111 || word.code == 17 || word.code == 20) {
    // cout << "rest0 -> stmt rest0" << endl;
    // string str1 = "rest0";
    // string str2 = "stmt rest0";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    int mquad = M();
    backpatch(rest0in.nextlist, mquad);
    node t = stmt();
    node rest01in;
    rest01in.nextlist = t.nextlist;
    node ret;
    ret = rest0(rest01in);
    return ret;
  } else {
    // cout << "rest0 -> {}" << endl;
    // string str1 = "rest0";
    // string str2 = "";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    return rest0in;
  }
}

node elist(node &elistin) {
  // cout << "elist -> expr rest1" << endl;
  string str1 = "elist";
  string str2 = "expr rest1";
  int lo = vs2.find(str1);
  if (lo != -1) {
    vs2.replace(lo, str1.size(), str2);
    vs1.push_back(vs2);
  }
  node ret;
  node rest1in;
  rest1in.inarray = elistin.inarray;
  rest1in.inndim = 1;
  node exprt = expr();
  rest1in.name = exprt.name;
  node rest1t = rest1(rest1in);
  ret.array = rest1t.array;
  ret.offset = rest1t.offset;
  return ret;
}

node resta(node &b) {
  node defaultret;
  if (word.str == "[") {
    node elistin;
    elistin.inarray = b.inarray;
    // cout << "resta -> [elist]" << endl;
    // string str1 = "resta";
    // string str2 = "[elist]";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    word = WordAnlay();
    if (word.code == -1) {
      cout << "error resta";
      exit(0);
    }
    node t = elist(elistin);
    b.name = newtemp();
    emit(to_string(ncode), "-", t.array, "C", b.name);
    b.offset = newtemp();
    emit(to_string(ncode), "*", t.offset, "w", b.offset);
    word = WordAnlay();
    if (word.code == -1) {
      cout << "error resta";
      exit(0);
    }

    if (word.str == "]") {
      word = WordAnlay();
      if (word.code == -1) {
        cout << "error resta";
        exit(0);
      }
    } else
      return b;
  } else {
    b.name = b.inarray;
    b.offset.clear();
    // cout << "resta -> {}" << endl;
    // string str1 = "resta";
    // string str2 = "";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    return b;
  }
}

node loc() {
  // cout << "loc -> id resta" << endl;
  // string str1 = "loc";
  // string str2 = "id resta";
  // int lo = vs2.find(str1);
  // if (lo != -1) {
  //     vs2.replace(lo, str1.size(), str2);
  //     vs1.push_back(vs2);
  // }
  if (word.code == 111) {
    node t;
    t.name = word.str;
    t.inarray = t.name;
    word = WordAnlay();
    if (word.code == -1) {
      cout << "error loc -1";
      exit(0);
    }
    node restat = resta(t);
    node ret;
    ret.name = restat.name;
    ret.offset = restat.offset;
    return ret;
  } else {
    cout << "error loc";
    cout << word.str << " " << word.code << endl;
    // cout << vs2 << endl;
    exit(0);
  }
}

node stmt() {
  if (word.str == "if") {
    // cout << "stmt ->  if(bool) stmt else stmt" << endl;
    // string str1 = "stmt";
    // string str2 = "if(bool) stmt else stmt";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    int m1, m2, nn;
    node stmt1, stmt2;
    node boolt;
    word = WordAnlay();
    if (word.code == -1) {
      cout << "error stmt";
      exit(0);
    }
    if (word.str == "(") {
      word = WordAnlay();
      if (word.code == -1) exit(0);
      boolt = Bool();
    } else {
      cout << "error stmt";
      exit(0);
    }
    if (word.str == ")") {
      word = WordAnlay();
      if (word.code == -1) exit(0);
      m1 = M();
      stmt1 = stmt();
      nn = N();
    } else {
      cout << "error stmt";
      exit(0);
    }
    if (word.str == "else") {
      word = WordAnlay();
      if (word.code == -1) exit(0);
      m2 = M();
      stmt2 = stmt();
      backpatch(boolt.truelist, m1);
      backpatch(boolt.falselist, m2);
      // cerr << stmt1.nextlist << endl;
      // node *ret;
      // node *t1 = &stmtt;
      // node *t2 = &nn;
      // node *t3 = &stmt2t;
      int ret;
      // cerr << stmt2.nextlist << " " << nn << endl;
      // ret = Merge(nn, m2);
      // cout << stmt1.nextlist << " " << stmt2.nextlist<<endl;
      // output();
      // backpatch(nn,stmt2.nextlist);
      ret = Merge(stmt1.nextlist, stmt2.nextlist);
      // cout << ret << " " << nn << endl;
      // cout << nn << endl;
      ret = Merge(ret, nn);
      // cout << nn << endl;
      // cout << ret << endl;
      // ret = Merge(stmt2.nextlist, nn);
      // cout << ret;
      // cout << "nn" << nn << endl;
      // ret = Merge(ret,m2);
      node d;
      d.nextlist = ret;
      // cout << ret << endl;
      // return stmt1;
      return d;
    } else {
      cout << "error";
      exit(0);
    }
  } else if (word.str == "while") {
    // cout << "stmt ->  while(bool) stmt " << endl;
    // string str1 = "stmt";
    // string str2 = "while(bool) stmt ";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    int m1quad, m2quad;
    node stmtt;
    node boolt;
    word = WordAnlay();
    if (word.code == -1) {
      cout << "error while";
      exit(0);
    }
    if (word.str == "(") {
      word = WordAnlay();
      if (word.code == -1) {
        cout << "error (";
        exit(0);
      }
      m1quad = M();
      // cout << word.str << endl;
      boolt = Bool();
      if (word.str == ")") {
        word = WordAnlay();
        if (word.code == -1) {
          cout << "error )";
          exit(0);
        }
        m2quad = M();
        stmtt = stmt();
        // cerr << stmtt.nextlist << m1quad << endl;
        backpatch(boolt.truelist, m2quad);
        // output();
        emit(to_string(ncode), "j", "-", "-", to_string(m1quad));
        backpatch(stmtt.nextlist, m1quad);
        // backpatch(m1quad, stmtt.nextlist);
        // cerr << word.str << endl;
        // cerr << m2quad << " " << boolt.truelist << endl;
        node ret;
        ret.nextlist = boolt.falselist;
        return ret;
      } else {
        cout << "error missing )";
        exit(0);
      }
    } else {
      cout << "error";
      exit(0);
    }
  } else {
    // cout << "stmt -> loc = expr;" << endl;
    // string str1 = "stmt";
    // string str2 = "loc = expr;";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    node ret;
    node b = loc();
    if (word.str == "=") {
      word = WordAnlay();
      node tt = expr();
      // emit(b.name + "=" + tt.name);
      if (b.offset.size() == 0) {
        emit(to_string(ncode), "=", tt.name, "-", b.name);
      } else {
        emit(to_string(ncode), "=[],", tt.name, "-",
             b.name + "[" + b.offset + "])");
      }
      ret.nextlist = makelist(nextquad);
      // cerr << ret.nextlist << endl;
    } else {
      cout << "error missing =";
      exit(0);
    }
    if (word.str == ";") {
      word = WordAnlay();
    } else {
      cout << "error missing ;";
      exit(0);
    }
    return ret;
  }
}

void stmts() {
  vs1.clear();
  // vs2 = "\tstmt rest0\n";
  // cout << "stmts -> stmt rest0" << endl;
  vs1.push_back(vs2);
  node t;
  t = stmt();
  // cerr << word.str << endl;
  // cerr << t.nextlist << endl;
  // t.nextlist << endl;
  // t.nextlist = stmtt.nextlist;
  rest0(t);
}

node rest4(node &rest4in) {
  if (word.str == "==" || word.str == "!=") {
    // cout << "rest4 -> " << word.str << " rel rest4" << endl;
    // string str1 = "rest4";
    // string str2 = word.str + " rel rest4";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    word = WordAnlay();
    if (word.code == -1) {
      cout << "error rest4";
      exit(0);
    }
    auto d = rel();
    // node t;
    // t.truelist = d.truelist;
    // t.falselist = d.falselist;
    auto ret = rest4(d);
    // cout << "fuck";
    return ret;
  } else {
    auto d = rest4in;
    // cout << "rest4 -> {}" << endl;
    // string str1 = "rest4";
    // string str2 = "";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    return d;
  }
}

node rop_expr(node exprin) {
  if (word.str == "<" || word.str == "<=" || word.str == ">" ||
      word.str == ">=") {
    string sign = word.str;
    exprin.truelist = makelist(ncode);
    exprin.falselist = makelist(ncode + 1);
    // cout << "relop -> " << word.str << "expr" << endl;
    // string str1 = "rop_exp";
    // string str2 = word.str + " expr";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    word = WordAnlay();
    if (word.code == -1) {
      cout << "error";
      exit(0);
    }
    node d = expr();
    emit(to_string(ncode), "j" + sign, exprin.name, d.name, "-");
    //  to_string(exprin.truelist));
    // cerr << ncode << " " << exprin.falselist << endl;
    emit(to_string(ncode), "j", "-", "-", "-");
    // to_string(exprin.falselist));
    return exprin;
  } else {
    exprin.truelist = makelist(ncode);
    exprin.falselist = makelist(ncode + 1);
    emit(to_string(ncode), "jnz", exprin.name, "-", "-");
    emit(to_string(ncode), "j", "-", "-", "-");
    // cout << "rop_exp -> {}";
    // string str1 = "rop_exp";
    // string str2 = "";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    return exprin;
  }
}

node rel() {
  // cout << "rel -> expr rop_exp" << endl;
  // string str1 = "rel";
  // string str2 = "expr rop_exp";
  // int lo = vs2.find(str1);
  // if (lo != -1) {
  //     vs2.replace(lo, str1.size(), str2);
  //     vs1.push_back(vs2);
  // }
  node rop_exprin = expr();
  node ret;
  ret = rop_expr(rop_exprin);
  return ret;
}

node equality() {
  // cout << "equality -> rel rest4" << endl;
  // string str1 = "equality";
  // string str2 = "rel rest4";
  // int lo = vs2.find(str1);
  // if (lo != -1) {
  //     vs2.replace(lo, str1.size(), str2);
  //     vs1.push_back(vs2);
  // }
  node rest4in = rel();
  // cout << word.str << endl;
  node ret = rest4(rest4in);
  // cout << "fuck" << endl;
  return ret;
}

node Bool() {
  // cout << "bool -> equality" << endl;
  // string str1 = "bool";
  // string str2 = "equality";
  // int lo = vs2.find(str1);
  // if (lo != -1) {
  //     vs2.replace(lo, str1.size(), str2);
  //     vs1.push_back(vs2);
  // }
  vs1.push_back(vs2);
  node ret = equality();
  node boolt;
  // boolt.truelist = ret.truelist;
  // boolt.falselist = ret.falselist;
  return ret;
}

node factor() {
  if (word.code == 100) {
    node t;
    t.name = word.str;
    t.result = toint(word);
    // int numvalue = toint(word);
    // cout << numvalue << endl;
    // cout << "factor -> num" << endl;
    // string str1 = "factor";
    // string str2 = "num";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    word = WordAnlay();
    return t;
  } else if (word.str == "(") {
    // cout << "factor -> (expr)" << endl;
    // string str1 = "factor";
    // string str2 = "(expr)";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    word = WordAnlay();
    if (word.code == -1) {
      cout << "error factor";
      exit(0);
    }
    node val = expr();
    if (word.str == ")") word = WordAnlay();
    return val;
  } else if (word.code == -1 || word.code == 0) {
    cout << "error factor";
    exit(0);
  } else {
    // cout << word.str << " " << word.code << endl;
    // cout << "factor -> loc" << endl;
    // string str1 = "factor";
    // string str2 = "loc";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    node val = loc();
    if (val.offset.size() == 0) {
    } else {
      auto d = newtemp();
      emit(to_string(ncode), "=[]", val.name + "[" + val.offset + "]", "-", d);
      val.name = d;
    }
    return val;
  }
}

node unary() {
  // string str1 = "unary";
  // string str2 = "factor";
  // int lo = vs2.find(str1);
  // if (lo != -1) {
  //     vs2.replace(lo, str1.size(), str2);
  //     vs1.push_back(vs2);
  // }
  // cout << "unary -> factor" << endl;
  node t = factor();
  // cout << "unary:" << t << endl;
  return t;
}

node rest6(node rest6in) {
  if (word.str == "*" || word.str == "/") {
    node rest6innode;
    // cout << "rest6 ->" << word.str << "unary rest6" << endl;
    // string str1 = "rest6";
    // string str2 = word.str + " unary rest6";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    string op = word.str;
    word = WordAnlay();
    // cout << word.str << " " << word.code << endl;
    if (word.code == -1) {
      cout << "error";
      exit(0);
    }
    if (op == "*") {
      rest6innode.name = newtemp();
      node unaryvalue = unary();
      emit(to_string(ncode), "*", rest6in.name, unaryvalue.name,
           rest6innode.name);
      // emit(rest6innode.name + "=" + rest6in.name + "*" +
      // unaryvalue.name);
      rest6in.result = rest6in.result * unaryvalue.result;
      rest6in.name = rest6innode.name;
      // cout <<"rest6in" << rest6in << endl;
    } else {
      node unaryvalue = unary();
      if (unaryvalue.result == 0) {
        cout << "/0 error" << endl;
        exit(0);
      }
      rest6innode.name = newtemp();
      emit(to_string(ncode), "/", rest6in.name, unaryvalue.name,
           rest6innode.name);
      // emit(rest6innode.name + "=" + rest6in.name + "/" +
      // unaryvalue.name);
      rest6in.result = rest6in.result / unaryvalue.result;
      rest6in.name = rest6innode.name;
    }
    node ret = rest6(rest6in);
    // cout << "rest6:" << ret << endl;
    return ret;
  } else {
    // cout << "rest6 -> {}" << endl;
    // string str1 = "rest6";
    // int lo = vs2.find(str1);
    // string str2 = "";
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    // cout << "rest6{}:" << rest6in.name << endl;
    return rest6in;
  }
}

node rest5(node rest5in) {
  if (word.str == "+" || word.str == "-") {
    // string str1 = "rest5";
    // string str2 = word.str + " term rest5";
    // int lo = vs2.find(str1);
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    string op = word.str;
    word = WordAnlay();
    // cout << word.str << " " << word.code << endl;
    if (word.code == -1) {
      cout << "error rest5";
      exit(0);
    }
    node termvalue = term();
    if (op == "+") {
      node rest5innode;
      rest5innode.name = newtemp();
      emit(to_string(ncode), "+", rest5in.name, termvalue.name,
           rest5innode.name);
      // emit(rest5innode.name + "=" + rest5in.name + "+" +
      // termvalue.name);
      rest5in.result = rest5in.result + termvalue.result;
      rest5in.name = rest5innode.name;
    } else {
      node rest5innode;
      rest5innode.name = newtemp();
      emit(to_string(ncode), "-", rest5in.name, termvalue.name,
           rest5innode.name);
      // emit(rest5innode.name + "=" + rest5in.name + "-" +
      // termvalue.name);
      rest5in.result = rest5in.result - termvalue.result;
      rest5in.name = rest5innode.name;
    }
    // cout << "rest5in:" << rest5in << endl;
    node rest5val = rest5(rest5in);
    // cout << "rest5out:" << rest5val << endl;
    return rest5val;
  } else {
    // cout << "rest5 -> {}" << endl;
    // string str1 = "rest5";
    // int lo = vs2.find(str1);
    // string str2 = "";
    // if (lo != -1) {
    //     vs2.replace(lo, str1.size(), str2);
    //     vs1.push_back(vs2);
    // }
    return rest5in;
  }
}

node term() {
  // cout << "term -> unary rest6" << endl;
  // string str1 = "term";
  // string str2 = "unary rest6";
  // int lo = vs2.find(str1);
  // if (lo != -1) {
  //     vs2.replace(lo, str1.size(), str2);
  //     vs1.push_back(vs2);
  // }
  node ret;
  node unaryvalue = unary();
  ret = rest6(unaryvalue);
  return ret;
}

node expr() {
  // cout << "expr -> term rest5" << endl;
  // string str1 = "expr";
  // string str2 = "term rest5";
  // vs2 = "\tterm rest5\n";
  // int lo = vs2.find(str1);
  // if (lo != -1) {
  //     vs2.replace(lo, str1.size(), str2);
  //     vs1.push_back(vs2);
  // }

  vs1.push_back(vs2);

  node b = term();
  node ret;
  ret = rest5(b);
  return ret;
}

int main() {
  initWords();
  string filename;
  cout << "Input file name:" << endl;
  cin >> filename;
  ifstream in(filename);
  string subline;
  while (getline(in, subline)) {
    line += subline;
    top = 0;
    ch = ' ';
  }
  while (ch != '#') {
    word = WordAnlay();
    // outPut(word);
    node t;
    // if (word.code == 111) {
    //     t = stmt();
    // } else {
    stmts();
    // }
    // t = expr();
    for (auto &c : vs1) {
      string str1 = "  ";
      string str2 = "";
      int lo = c.find(str1);
      while (lo != string::npos) {
        if (lo != -1) {
          c.replace(lo, str1.size(), str2);
        }
        lo = c.find(str1);
      }
      cout << c;
    }
    output();
    cout << t.result << endl;
  }
  cout << "Check debug!";
}