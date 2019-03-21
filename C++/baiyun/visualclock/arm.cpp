#include "arm.h"
#include <QPainter>
#include <QPen>
#include <QTime>
#include <cmath>
#include <iostream>
using namespace std;
Arm::Arm(Arm::ArmType t)
    {
    type = t;
    armColor = Qt::white;
}
void Arm::setColor(QColor c) {
    armColor = c;
}
void Arm::setRectangle(QRect rect) {
    r = rect;
}
void Arm::draw(QPainter *p) {
    const double pi = acos(-1);
    QTime timenow = QTime::currentTime();
    double a = 0;
    double minValue = min(r.width() / 2, r.height() / 2);
    double size = minValue;
    // cout << size << endl;
    if (this->type == HOUR) {
        int h = timenow.hour();
        h += shicha;
        a = h * 30 + (timenow.minute() / 60.0 * 30.0);
        size *= (5.0 / 7.0);
    } else if (this->type == MINUTE) {
        int m = timenow.minute();
        a = m * 6;
        size *= 15.0 / 20.0;
    } else {
        int s = timenow.second();
        a = s * 6;
        size *= 19.0 / 20.0;
    }
    a *= pi / 180;
    QPen pen(armColor, 1, Qt::SolidLine);
    p->setPen(pen);
    double rr = minValue / 160;
    double beginx = r.width() / 2 + r.x();
    double endx = r.width() / 2 + size * sin(a) + r.x();
    double beginy = r.height() / 2 + r.y();
    double endy = r.height() / 2 - size * cos(a) + r.y();
    p->drawLine(beginx, beginy, endx, endy);
}
