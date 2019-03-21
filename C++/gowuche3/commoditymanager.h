#ifndef COMMODITYMANAGER_H
#define COMMODITYMANAGER_H
#include "commodity.h"
struct commoditymanager {
  // constructors
  commoditymanager();
  commoditymanager(int a);
  ~commoditymanager() { delete[] commodities; }
  commoditymanager(const commoditymanager &a) = delete;
  commodity &operator=(const commoditymanager &c) = delete;

  // api to change the commoditymanager
  void addcommodity(commodity a);
  void viewcommodity(long long id) const;
  void viewallcommodities() const;
  void removeCommodity(long long id);

  // api to get the messages of the commodity manager
  void checkout() const;
  int getSize() const { return this->size; }
  commodity *begin() const { return this->commodities; }
  commodity *end() const { return (commodities + this->getSize()); }
  int getmaxsize() const { return this->maxsize; }

  // Resize the commodity manager
  void remaxsize(int newmaxsize);
  void reallocmemory(int a);

private:
  commodity *commodities;
  int maxsize;
  int size;
  commodity *findCommodityById(long long id) const;
  void reallocmemory();
};

#endif // COMMODITYMANAGER_H
