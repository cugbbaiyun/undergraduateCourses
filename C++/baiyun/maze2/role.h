#ifndef ROLE_H
#define ROLE_H
#include "basicmap.h"
#include <QRect>
#include "mapelement.h"
#include <QPainter>
class Role : public mapElement {
  public:
    Role() = default;
    Role(int a);
    int getType() const;
    int getType();
    void draw(QPainter *p);
    bool hasBullet() const;
    bool hasBullet();
    void setLen(int a);
    void setRectangle(QRect R);
    void setSize(int n);

  private:
    int bull = 1;
    QRect r;
    int len;
    int size;
};

#endif // ROLE_H
