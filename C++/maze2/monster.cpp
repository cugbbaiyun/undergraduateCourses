#include "monster.h"
#include <iostream>
using namespace std;
using pii = pair<int, int>;
monster::monster(std::pair<int, int> a) {
    setPosition(a);
}
int monster::getType() const {
    return 2;
}
int monster::getType() {
    return 2;
}
void monster::setIcon(int a) {
    this->icon = a;
}
void monster::setRect(QRect a) {
    this->r = a;
}
void monster::setSize(int a) {
    this->size = a;
}
void monster::automove(const basicmap &m) {
    if (ismoving) {
        if(dis==len){
            ismoving=false;
            dire=-1;
            dis = 0;
            setPosition(aim);
        }else ++dis;
    } else {
        auto po = getPosition();
        dire = rand() % 4;
        if (m.road[po.first][po.second][dire]) {
            if (dire == 0) {
                aim = pii(po.first, po.second - 1);
            } else if (dire == 1) {
                aim = pii(po.first, po.second + 1);
            } else if (dire == 2) {
                aim = pii(po.first - 1, po.second);
            } else {
                aim = pii(po.first + 1, po.second);
            }
            ismoving = true;
            dis = 0;
        }else{
            aim = getPosition();
            ismoving=false;
            dis=0;
            dire=-1;
        }
    }
}
void monster::draw(QPainter *p) {
    int xmid = r.width() / 2 + r.x();
    int ymid = r.height() / 2 + r.y();
    xmid -= len * (size / 2);
    ymid -= len * (size / 2);
    pii leftUp(xmid, ymid);
    pii po = getPosition();
    if (this->icon == 1) {
        QPixmap pixmap;
        iconnumber = iconnumber+ 1;
        iconnumber %= 4;
        if(iconnumber==0){
            QPixmap pixmap2(":/backjpgs/monster11.png");
            pixmap=pixmap2;
        }else if(iconnumber == 1){
            QPixmap pixmap2(":/backjpgs/monster12.png");
            pixmap=pixmap2;
        }else if(iconnumber==2){
            QPixmap pixmap2(":/backjpgs/monster13.png");
            pixmap=pixmap2;
        }else{
            QPixmap pixmap2(":/backjpgs/monster14.png");
            pixmap=pixmap2;
        }
        if(ismoving){
            if (dire == 0) {
                p->drawPixmap(po.first * len + len / 4 + leftUp.first, po.second * len + len / 4 + leftUp.second - dis, len * 2 / 4, len * 2 / 4, pixmap);
            } else if (dire == 1) {
                p->drawPixmap(po.first * len + len / 4 + leftUp.first, po.second * len + len / 4 + leftUp.second + dis, len * 2 / 4, len * 2 / 4, pixmap);
            } else if (dire == 2) {
                p->drawPixmap(po.first * len + len / 4 + leftUp.first - dis, po.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, pixmap);
            } else if (dire == 3) {
                p->drawPixmap(po.first * len + len / 4 + leftUp.first + dis, po.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, pixmap);
            }
        }else {
            p->drawPixmap(po.first * len + len / 4 + leftUp.first, po.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, pixmap);
        }
    } else {
        QPixmap pixmap;
        iconnumber=iconnumber+1;
        iconnumber %=4;
        if(iconnumber==0){
            QPixmap tem(":/backjpgs/monster20.png");
            pixmap=tem;
        }else if(iconnumber==1){
            QPixmap tem(":/backjpgs/monster21.png");
            pixmap=tem;
        }else if(iconnumber ==2){
            QPixmap tem(":/backjpgs/monster22.png");
            pixmap=tem;
        }else{
            QPixmap tem(":/backjpgs/monster23.png");
            pixmap=tem;
        }
        if(ismoving){
            if (dire == 0) {
                p->drawPixmap(po.first * len + len / 4 + leftUp.first, po.second * len + len / 4 + leftUp.second - dis, len * 2 / 4, len * 2 / 4, pixmap);
            } else if (dire == 1) {
                p->drawPixmap(po.first * len + len / 4 + leftUp.first, po.second * len + len / 4 + leftUp.second + dis, len * 2 / 4, len * 2 / 4, pixmap);
            } else if (dire == 2) {
                p->drawPixmap(po.first * len + len / 4 + leftUp.first - dis, po.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, pixmap);
            } else if (dire == 3) {
                p->drawPixmap(po.first * len + len / 4 + leftUp.first + dis, po.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, pixmap);
            }
        }else {
            p->drawPixmap(po.first * len + len / 4 + leftUp.first, po.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, pixmap);
        }
    }
}
