#include "commodity.h"
#include "commoditymanager.h"
#include "funciton.h"
#include <iostream>
#include <string>

using namespace std;
// File location
const string filename("./test.txt");

int main() {
  commoditymanager cm;
  // First recover from the file
  readFromFile(filename, cm);

  // Then enter the system
  while (1) {
    // Get the function number
    char c = menu();
    // If customer want to exit
    if (c == '0') {
      // First save data
      if (writefile(filename, cm)) {
        break;
      } else {
        // If the file open failed
        // Warning
        cout << "You can't close the window! Or your datas will lost!" << endl;
      }
    }
    // Judge the function
    judge(c, cm);
  }
  // Exit success
  cout << "See you" << endl;
  return 0;
}
