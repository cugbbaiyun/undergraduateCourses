#include "shape.h"

Shape::Shape(QColor c):color(c){ }
void Shape::setColor(QColor c){
    color=c;
}
QColor Shape::getColor()const{
    return color;
}
