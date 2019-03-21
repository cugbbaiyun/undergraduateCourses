#include "commodity.h"
#include "commoditymanager.h"
#include "funciton.h"
#include "help.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
// to get the function number
char menu() {
  cout << "Welcome to the commmodity manager system" << endl;
  cout << "1)Add commodity" << endl;
  cout << "2)Remove commodity" << endl;
  cout << "3)View commodity" << endl;
  cout << "4)View all commodities" << endl;
  cout << "5)Chec out" << endl;
  cout << "0)Exit" << endl;
  cout << "Input the number you want" << endl;
  char tem;
  cin >> tem;
  return tem;
}
// to switch the function
void judge(char c, commoditymanager &cm) {
  if (c == '1') {
    doaddcommodity(cm);
    return;
  }
  if (c == '2') {
    removecommodity(cm);
    return;
  }
  if (c == '3') {
    doshowcommodity(cm);
    return;
  }
  if (c == '4') {
    showallcommodity(cm);
    return;
  }
  if (c == '5') {
    docheckout(cm);
    return;
  }
  return;
}
// to add one commodity
void doaddcommodity(commoditymanager &cm) {
  cout << "Input id" << endl;
  long long id;
  cin >> id;
  cout << "Input name" << endl;
  string name;
  getchar();
  getline(cin, name);
  cout << "Input price,discount and num" << endl;
  double price;
  double discount;
  int num;
  cin >> price >> discount >> num;
  cm.addcommodity(commodity(id, name, price, num, discount));
}

// to remove one commodity
void removecommodity(commoditymanager &cm) {
  cout << "The id you wan to remove:";
  long long id;
  cin >> id;
  cm.removeCommodity(id);
}

// to show one commodity
void doshowcommodity(const commoditymanager &cm) {
  cout << "The id you want to view?" << endl;
  long long id;
  cin >> id;
  cm.viewcommodity(id);
}

// to show all the commodities
void showallcommodity(commoditymanager &cm) {
  Resort(getsortstd(), cm);
  cm.viewallcommodities();
}

// to check out
void docheckout(const commoditymanager &cm) { cm.checkout(); }

// Recover from file
void readFromFile(const std::string &filename, commoditymanager &cm) {
  ifstream in(filename);
  if (in) {
    cout << "Open the " << filename << "success." << endl;
  } else {
    cout << "Open failed" << endl;
    return;
  }
  int tem;
  in >> tem;
  if (cm.getmaxsize() < tem) {
    cm.remaxsize(tem);
  }
  int curid;
  in >> curid;
  commodity::setnextid(curid);
  for (int i = 0; i < tem; ++i) {
    long long id;
    string name;
    double price, discount;
    int num;
    if (in >> id)
      in >> name >> price >> num >> discount;
    else {
      cout << "The file is broken,please check it" << endl;
      return;
    }
    cm.addcommodity(commodity(id, name, price, num, discount));
  }
}

// To save datas to file
bool writefile(string filename, commoditymanager &cm) {
  ofstream out(filename);
  if (out) {
    cout << "Now is going to writefile to " << filename << endl;
  } else {
    cout << "Open file failed" << endl;
    return false;
  }
  out << cm.getmaxsize() << endl;
  out << commodity::getnextid() << endl;
  commodity *cur = cm.begin();
  while (cur != cm.end()) {
    out << cur->getID() << " " << cur->getName() << " " << cur->getPrice()
        << " " << cur->getNum() << " " << cur->getDiscount() << endl;
    ++cur;
  }
  return true;
}
