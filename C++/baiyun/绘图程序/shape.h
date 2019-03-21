#ifndef SHAPE_H
#define SHAPE_H
#include <QColor>
#include <QPainter>
#include <QTextStream>
class Shape{
public:
    Shape(QColor c);
    QColor getColor()const;
    void setColor(QColor c);
    virtual void draw(QPainter *p)=0;
    virtual void save(QTextStream& s)=0;
protected:
    QColor color;
};
#endif // SHAPE_H
