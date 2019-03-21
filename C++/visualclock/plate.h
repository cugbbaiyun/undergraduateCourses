#ifndef PLATE_H
#define PLATE_H

#include <QColor>
#include <QPainter>
#include <QRect>
class Plate {
  public:
    Plate();
    void setRectangle(QRect rect);
    void draw(QPainter *q);
    void setbackground(QColor a);
    void setline(QColor a);

  private:
    int LINE_LENTH;
    int LINE_WIDTH;
    int GAP;
    QColor backgroundColor;
    QColor lineColor;
    QColor numColor;
    QRect r;
};

#endif // PLATE_H
