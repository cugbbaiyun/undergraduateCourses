#include "ellipse.h"
#include "shape.h"
Ellipse::Ellipse(QPoint p1,QPoint p2,QColor c): point1(p1),point2(p2),Shape(c){
}
QPoint Ellipse::topLeft()const{
    return point1;
}
QPoint Ellipse::bottomRight()const{
    return point2;
}
void Ellipse::draw(QPainter *p){
    QPen pen(color,1,Qt::SolidLine);
    p->setPen(pen);
    p->drawEllipse(QRect(point1,point2));
}
void Ellipse::save(QTextStream &out){
    out<<"1 "<<topLeft().x()<<" "<<topLeft().y()<<" " <<bottomRight().x()<<" "<<bottomRight().y()<<endl;
}
Shape* Ellipse::read(QTextStream &in){
    int x1,y1,x2,y2;
    in>>x1>>y1>>x2>>y2;
    return new Ellipse(QPoint(x1,y1),QPoint(x2,y2));
}
