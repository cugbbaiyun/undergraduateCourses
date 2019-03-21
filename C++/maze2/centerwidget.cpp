#include "centerwidget.h"
#include "basicmap.h"
#include "mainwindow.h"
#include <QTimer>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
using namespace std;
using pii = pair<int, int>;
centerWidget::centerWidget(QWidget *parent)
    : QWidget(parent) {
    this->pa = parent;
    setFocus();
    parent->resize(1700, 1000);
    setFixedSize(1700, 1000);
    myMap = new basicmap();
    role = new Role(myMap->getSize());
    this->end = pair<int, int>(myMap->getSize() - 1, myMap->getSize() - 1);
    QPalette pal(parent->palette());
    pal.setColor(QPalette::Background, Qt::white);
    parent->setAutoFillBackground(true);
    parent->setPalette(pal);
    createMonsters();
    parent->show();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeToShow()));
    timer->start(150);
}

void centerWidget::createMonsters() {
    monsters.clear();
    int monstercount = rand() % 30 + 1;
    for (int i = 0; i < monstercount; ++i) {
        int iconc = rand() % 2 + 1;
        monster *ma = new monster;
        int x = rand() % myMap->getSize();
        int y = rand() % myMap->getSize();
        while (hassame(pii(x, y))) {
            x = rand() % myMap->getSize();
            y = rand() % myMap->getSize();
        }
        ma->setPosition(pii(x, y));
        ma->setIcon(iconc);
        monsters.push_back(ma);
    }
}
bool centerWidget::hassame(pii a) {
    if (a.first == role->getPosition().first && a.second == role->getPosition().second) return 1;
    if (a.first == end.first && a.second == end.second) return 1;
    return 0;
}

void centerWidget::paintEvent(QPaintEvent *) {
    if (failflag) {
        monsters.clear();
        QPainter p(this);
        QPalette palette;
        QPixmap tem(":/backjpgs/gameover.png");
        palette.setBrush(QPalette::Window, QBrush(tem));
        setPalette(palette);
        setAutoFillBackground(true);
        return;
    }
    QPainter p(this);
    QPalette palette;
    QPixmap tem(":/backjpgs/051.jpg");
    palette.setBrush(QPalette::Window, QBrush(tem));
    setPalette(palette);
    setAutoFillBackground(true);
    myMap->setRectangle(this->geometry());
    role->setLen(fmin(this->geometry().width(), this->geometry().height()) / myMap->getSize());
    role->setRectangle(this->geometry());
    role->setSize(myMap->getSize());
    myMap->draw(&p);
    role->draw(&p);
    for (int i = 0; i < monsters.size(); ++i) {
        monsters[i]->setRect(this->geometry());
        monsters[i]->setLen(fmin(this->geometry().width(), this->geometry().height()) / myMap->getSize());
        monsters[i]->setSize(myMap->getSize());
        monsters[i]->draw(&p);
    }
    showend();
    if (myMap->isshowing) {
        pii now = role->getPosition();
        QPainter p(this);
        p.setBrush(QColor(234, 193, 0));
        int size = myMap->getSize();
        int len = (fmin(this->geometry().width(), this->geometry().height()) / myMap->getSize());
        auto r = this->geometry();
        int xmid = r.width() / 2 + r.x();
        int ymid = r.height() / 2 + r.y();
        xmid -= len * (size / 2);
        ymid -= len * (size / 2);
        pii leftUp(xmid, ymid);
        while (now != end) {
            p.drawRect(QRect(leftUp.first + now.first * len, leftUp.second + now.second * len, len, len));
            now = myMap->pathto[now.first][now.second];
            role->draw(&p);
        }
    }
}
void centerWidget::showend() {
    QPainter p(this);
    int min1 = min(this->geometry().width(), this->geometry().height());
    int size = myMap->getSize();
    int len = min1 / myMap->getSize();
    int xmid = this->geometry().width() / 2 + this->geometry().x();
    int ymid = this->geometry().height() / 2 + this->geometry().y();
    xmid -= len * (size / 2);
    ymid -= len * (size / 2);
    pii leftUp(xmid, ymid);
    endnumber=(endnumber+1)%4;
    setAutoFillBackground(true);
    if(endnumber==0){
        QPixmap	tem(":/backjpgs/end0.png");
        p.drawPixmap(end.first * len + len / 4 + leftUp.first, end.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, tem);
    }else if(endnumber==1){
        QPixmap tem(":/backjpgs/end1.png");
         p.drawPixmap(end.first * len + len / 4 + leftUp.first, end.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, tem);
    }else if(endnumber==2){
        QPixmap tem(":/backjpgs/end2.png");
         p.drawPixmap(end.first * len + len / 4 + leftUp.first, end.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, tem);
    }else if(endnumber==3){
        QPixmap tem(":/backjpgs/end3.png");
         p.drawPixmap(end.first * len + len / 4 + leftUp.first, end.second * len + len / 4 + leftUp.second, len * 2 / 4, len * 2 / 4, tem);
    }
}
int centerWidget::check() {
    if (role->getPosition() == end) {
        return 1;
    }
    return 0;
}
void centerWidget::keyPressEvent(QKeyEvent *e) {
    int key = e->key();
    if (key == 16777235) { // up
        pii lo = role->getPosition();
        if (myMap->road[lo.first][lo.second][0] == 1) {
            role->setPosition(pii(lo.first, lo.second - 1));
        }
    } else if (key == 16777237) { // down
        pii lo = role->getPosition();
        if (myMap->road[lo.first][lo.second][1] == 1) {
            role->setPosition(pii(lo.first, lo.second + 1));
        }
    } else if (key == 16777234) { // left
        pii lo = role->getPosition();
        if (myMap->road[lo.first][lo.second][2] == 1) {
            role->setPosition(pii(lo.first - 1, lo.second));
        }
    } else if (key == 16777236) { // right
        pii lo = role->getPosition();
        if (myMap->road[lo.first][lo.second][3] == 1) {
            role->setPosition(pii(lo.first + 1, lo.second));
        }
    } else if (key == 32) { // showpath
        showpath();
    }
    int res = check();
    if (res == 1) {
        int n = myMap->getSize();
        delete myMap;
        myMap = new basicmap(n + 10);
        end = pii(n + 9, n + 9);
        delete role;
        role = new Role;
        createMonsters();
    }
    update();
}
void centerWidget::failed() {
    failflag = 1;
}
void centerWidget::timeToShow() {
    for (auto c : monsters) {
        c->automove(*myMap);
    }
    for (auto c : monsters) {
        if (c->aim == role->getPosition()) {
            failed();
        }
    }
    update();
}
void centerWidget::showpath() {
    monsters.clear();
    myMap->isshowing = 1;
}
