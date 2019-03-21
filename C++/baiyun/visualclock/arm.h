#ifndef ARM_H
#define ARM_H

#include <QColor>
#include <QPainter>
#include <QRect>

class Arm {
  public:
    Arm() = default;
    enum ArmType { HOUR, MINUTE, SECOND };
    Arm(ArmType t);
    void setColor(QColor c);
    void setRectangle(QRect rect);
    void draw(QPainter *p);
    void setshicha(int n) {
        shicha = n;
    }

  private:
    ArmType type;    //指针类型
    QColor armColor; //指针的颜色
    QRect r;         //外接矩形
    int shicha;
};

#endif // ARM_H
