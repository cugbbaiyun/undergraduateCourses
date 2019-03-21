#include "commodity.h"
#include "commoditymanager.h"
#include <iostream>
using namespace std;
// To get how to sort
char getsortstd() {
  cout << "Which sort do you prefer?" << endl;
  cout << "1)sort by the incresing id(default)" << endl;
  cout << "2)sort by the decresing id" << endl;
  cout << "3)sort by the incresing price" << endl;
  cout << "4)sort by the decresing price" << endl;
  cout << "5)sort by the incresing num" << endl;
  cout << "6)sort by the decresing num" << endl;
  cout << "7)sort by the incresing discount" << endl;
  cout << "8)sort by the decresing discount" << endl;
  cout << "Input the number you want:" << endl;
  char tem;
  cin >> tem;
  return tem;
}

// Different sort
void Resort(char c, commoditymanager &cm) {
  switch (c) {
  case '2':
    sort(cm.begin(), cm.end(),
         [](commodity a, commodity b) { return a.getID() > b.getID(); });
    break;
  case '3':
    sort(cm.begin(), cm.end(),
         [](commodity a, commodity b) { return a.getPrice() < b.getPrice(); });
    break;
  case '4':
    sort(cm.begin(), cm.end(),
         [](commodity a, commodity b) { return a.getPrice() > b.getPrice(); });
    break;
  case '5':
    sort(cm.begin(), cm.end(),
         [](commodity a, commodity b) { return a.getNum() > b.getNum(); });
    break;
  case '6':
    sort(cm.begin(), cm.end(),
         [](commodity a, commodity b) { return a.getNum() < b.getNum(); });
    break;
  case '7':
    sort(cm.begin(), cm.end(), [](commodity a, commodity b) {
      return a.getDiscount() < b.getDiscount();
    });
    break;
  case '8':
    sort(cm.begin(), cm.end(), [](commodity a, commodity b) {
      return a.getDiscount() > b.getDiscount();
    });
    break;
  default:
    sort(cm.begin(), cm.end(),
         [](commodity a, commodity b) { return a.getID() < b.getID(); });
    break;
  }
}