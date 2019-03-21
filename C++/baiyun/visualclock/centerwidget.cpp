#include "centerwidget.h"
#include <QPainter>

CenterWidget::CenterWidget(QWidget *parent)
    : QWidget(parent) {}
void CenterWidget::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    QRect full = this->geometry();
    int halfx = full.width() / 2;
    clock.setRectangle(QRect(0, 0, halfx, full.height()));
    clock.draw(&p);
    clock2.setshicha(13);
    clock2.setRectangle(QRect(halfx + 1, 0, halfx, full.height()));
    clock2.draw(&p);
    update();
}
