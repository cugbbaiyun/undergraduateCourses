#include "role.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
using pii = pair<int, int>;
int Role::getType() const {
    return 1;
}
int Role::getType() {
    return 1;
}
bool Role::hasBullet() const {
    return bull;
}
bool Role::hasBullet() {
    return bull;
}
Role::Role(int size) {
    srand(time(0));
    this->bull = 1;
    setPosition(pii(rand() % size, rand() % size));
}
void Role::setLen(int a) {
    this->len = a;
}
void Role::draw(QPainter *p) {
    int xmid = r.width() / 2 + r.x();
    int ymid = r.height() / 2 + r.y();
    xmid -= len * (size / 2);
    ymid -= len * (size / 2);
    pii leftUp(xmid, ymid);
    QPixmap pixmap(":/backjpgs/test.jpg");
    pii po = getPosition();
    p->drawPixmap(po.first * len + len / 4 + leftUp.first, po.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, pixmap);
}
void Role::setRectangle(QRect R) {
    this->r = R;
}
void Role::setSize(int n) {
    this->size = n;
}
