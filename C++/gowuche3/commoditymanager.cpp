#include "commoditymanager.h"
#include "commodity.h"
#include <iostream>

using namespace std;

commoditymanager::commoditymanager() : commoditymanager(100) {}

commoditymanager::commoditymanager(int a) : maxsize(a), size(0) {
  commodities = new commodity[maxsize];
}

// add commodity
void commoditymanager::addcommodity(commodity a) {
  auto c = findCommodityById(a.getID());
  if (c != nullptr) {
    cout << "The id exists,update it" << endl;
    *c = a;
    return;
  }
  while (getSize() > getmaxsize()) {
    reallocmemory();
  }
  commodities[size++] = a;
}

// view onw commodity by id
void commoditymanager::viewcommodity(long long id) const {
  // first find the commodity
  auto c = findCommodityById(id);
  // if not return
  if (c == nullptr) {
    cout << "Sorry,can't find the commodity" << endl;
    return;
  }
  c->output();
  return;
}

// to show all the commodities
void commoditymanager::viewallcommodities() const {
  // If the size ie zero return;
  if (getSize() == 0) {
    cout << "The car is empty!" << endl;
    return;
  }
  for (int i = 0; i < getSize(); ++i) {
    commodities[i].output();
  }
  return;
}

// check out
void commoditymanager::checkout() const {
  double sum = 0;
  for (int i = 0; i < getSize(); ++i) {
    sum += commodities[i].getnetprice();
  }
  cout << "Now the value of the car is " << sum << endl;
  return;
}

// delete one commodity
void commoditymanager::removeCommodity(long long id) {
  auto c = findCommodityById(id);
  if (c == nullptr) {
    cout << "Can't find the id! Remove failed!" << endl;
    return;
  }
  auto d = c + 1;
  while (d != end()) {
    *c = *d;
    ++c;
    ++d;
  }
  cout << "Remove success!" << endl;
}

// to find the commodity by id
commodity *commoditymanager::findCommodityById(long long id) const {
  auto cur = begin();
  while (cur != end()) {
    // if find return the pointer
    if (cur->getID() == id) {
      return cur;
    }
    ++cur;
  }
  return nullptr;
}

// Maxsize->maxsize*2
void commoditymanager::reallocmemory() {
  commodity *tem = commodities;
  this->commodities = new commodity[maxsize * 2];
  for (int i = 0; i < size; ++i) {
    commodities[i] = tem[i];
  }
  delete[] tem;
}

// maxsize->somenumber*2;
void commoditymanager::reallocmemory(int a) {
  // first check if the new size less than the maxsize now
  // if less ,return
  if (a < getmaxsize())
    return;
  // else realloc
  commodity *tem = begin();
  this->commodities = new commodity[a * 2];
  for (int i = 0; i < size; ++i) {
    commodities[i] = tem[i];
  }
  delete[] tem;
}

// change the maxsize
void commoditymanager::remaxsize(int newmaxsize) {
  if (getmaxsize() < newmaxsize)
    reallocmemory(newmaxsize);
}