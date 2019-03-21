#ifndef COMMODITY_H
#define COMMODITY_H
#include <string>
struct commodity {
  // constructors
  commodity();
  commodity(long long a, std::string b, double c, int d, double e);
  commodity(long long a);
  commodity(long long a, std::string b);
  commodity(long long a, std::string b, double c);
  commodity(long long a, std::string b, double c, int d);

  // api to change the commodity
  void setPrice(const double &newprice);
  void setName(const double &newname);
  void setDiscount(const double &newdiscount);
  void setNum(const int &newNum);
  void setId(const long long &newId);

  // api to get the commodity
  std::string getName() const;
  long long getID() const;
  int getNum() const;
  double getPrice() const;
  double getDiscount() const;
  void output() const;
  double getnetprice() const { return getPrice() * getNum() * getDiscount(); }
  static void setnextid(int newid) { commodity::nextid = newid; };
  static long long getnextid() { return commodity::nextid; }

  commodity &operator=(const commodity &a);

  ~commodity();

private:
  static long long nextid;
  long long autoincrese() { return ++nextid; }
  long long id;
  std::string name;
  double price;
  int num;
  double discount;
};
#endif // COMMODITY_H
