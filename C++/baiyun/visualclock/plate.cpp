#include "plate.h"
#include <QObject>
#include <QPainter>
#include <cmath>

#include <iostream>
Plate::Plate() {
    LINE_LENTH = 9; //刻度长度
    LINE_WIDTH = 2; //线宽 GAP=10; //保留和边界的距离
    backgroundColor = Qt::black;
    lineColor = Qt::white;
    numColor = Qt::white;
}

void Plate::setRectangle(QRect rect) {
    r = rect;
}
void Plate::draw(QPainter *p) {
    double pi = acos(-1);
    int width = r.width();
    int height = r.height();
    int minValue = std::min(width, height); //长宽最小值
    int x = r.x() + width / 2;
    int y = r.y() + height / 2;      //中心点 x、y 坐标
    int radius = minValue / 2 - GAP; //计算半径
    QRect rect(x - radius, y - radius, radius * 2, radius * 2);
    QPen pen(lineColor, LINE_WIDTH, Qt::SolidLine);
    QBrush brush(backgroundColor);
    p->setPen(pen);
    p->setBrush(brush); //设置背景颜色
    p->drawEllipse(rect);
    QRect rect1(x - minValue / 160, y - minValue / 160, minValue / 80, minValue / 80);
    QString tem;
    int count1 = 1;
    QFont font(QObject::tr("宋体"), 10, QFont::Bold, true);
    p->setFont(font);
    p->setPen(QPen(QColor(lineColor)));
    for (int i = 30; i <= 360; i += 30) {
        double size;
        if (i % 90) {
            size = radius * (1.5 / 20.0);
        } else {
            size = radius * (3.0 / 20.0);
        }
        double a = i;
        a *= (acos(-1) / 180);
        double endx = r.width() / 2 + radius * sin(a) + r.x();
        double endy = r.height() / 2 - radius * cos(a) + r.y();
        double beginx = r.width() / 2 + radius * sin(a) - size * sin(a) + r.x();
        double beginy = r.height() / 2 - radius * cos(a) + size * cos(a) + r.y();
        p->drawLine(beginx, beginy, endx, endy);
    }
}
void Plate::setbackground(QColor a) {
    backgroundColor = a;
}
void Plate::setline(QColor a) {
    lineColor = a;
}
