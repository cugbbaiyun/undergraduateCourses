#ifndef MONSTER_H
#define MONSTER_H
#include "basicmap.h"
#include "mapelement.h"
#include <QPainter>
class monster : public mapElement {
  public:
    monster() = default;
    monster(std::pair<int, int> a);
    monster(int a, int b);
    void setIcon(int a);
    virtual int getType() const;
    virtual int getType();
    virtual void draw(QPainter *p);
    void setRect(QRect a);
    void automove(const basicmap &m);
    void setSize(int i);
    void setLen(int a) {
        this->len = a;
    }
    std::pair<int, int> aim;

  private:
    int icon;
    QRect r;
    int len;
    int size;
    std::pair<int, int> leftUp;
    bool ismoving = false;
    int dire = -1;
    int dis = 0;
    int iconnumber=0;
};

#endif // MONSTER_H
