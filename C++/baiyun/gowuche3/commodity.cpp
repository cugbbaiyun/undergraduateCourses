#include "commodity.h"
#include <iostream>
using namespace std;

// Default constructor
commodity::commodity()
    : id(commodity::autoincrese()), name("Null"), price(0), num(0),
      discount(0) {}

// Constructors
commodity::commodity(long long a, std::string b, double c, int d, double e)
    : id(a), name(b), price(c), num(d), discount(e) {}

commodity::commodity(long long a) : commodity(a, "Null", 0, 0, 0) {}

commodity::commodity(long long a, std::string b) : commodity(a, b, 0, 0, 0) {}

commodity::commodity(long long a, std::string b, double c)
    : commodity(a, b, c, 0, 0) {}

commodity::commodity(long long a, std::string b, double c, int d)
    : commodity(a, b, c, d, 0) {}

// Api to change the commodity
void commodity::setPrice(const double &newprice) { this->price = newprice; }

void commodity::setName(const double &newname) { this->name = newname; }

void commodity::setDiscount(const double &newdiscount) {
  this->discount = newdiscount;
}

void commodity::setNum(const int &newNum) { this->num = newNum; }

void commodity::setId(const long long &newId) { this->id = newId; }

// Api to get the commodity's messages
std::string commodity::getName() const { return this->name; }

long long commodity::getID() const { return this->id; }

int commodity::getNum() const { return this->num; }

double commodity::getPrice() const { return this->price; }

double commodity::getDiscount() const { return this->discount; }

// Api to print the commodity's messages
void commodity::output() const {
  cout << "Name: " << this->name << endl;
  cout << "Id: " << this->id << endl;
  cout << "Price: " << this->price << endl;
  cout << "Num: " << this->num << endl;
  cout << "Discount: " << this->discount << endl;
  cout << "The netprice is " << this->getnetprice() << endl;
}

commodity::~commodity() = default;

//= overload
commodity &commodity::operator=(const commodity &a) {
  this->id = a.getID();
  this->price = a.getPrice();
  this->name = a.getName();
  this->num = a.getNum();
  this->discount = a.getDiscount();
  return *this;
}

// define nextid
long long commodity::nextid = 0;
