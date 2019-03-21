#include "rectangle.h"

Rectangle::Rectangle(QPoint p1,QPoint p2,QColor c): point1(p1),point2(p2),Shape(c){
}
QPoint Rectangle::topLeft()const{
    return point1;
}
QPoint Rectangle::bottomRight()const{
    return point2; }
void Rectangle::draw(QPainter *p){
    QPen pen(color,1,Qt::SolidLine);
    p->setPen(pen);
    p->drawRect(QRect(point1,point2));
}
void Rectangle::save(QTextStream &out){
    out<<"2 "<<topLeft().x()<<" "<<topLeft().y()<<" " <<bottomRight().x()<<" "<<bottomRight().y()<<endl;
}
Shape* Rectangle::read(QTextStream &in){
    int x1,y1,x2,y2;
    in>>x1>>y1>>x2>>y2;
    return new Rectangle(QPoint(x1,y1),QPoint(x2,y2));
}
