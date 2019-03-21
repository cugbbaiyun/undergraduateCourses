#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include "basicmap.h"
//#include "bullets.h"
#include "mapelement.h"
#include "monster.h"
#include "role.h"
#include <QKeyEvent>
#include <QPainter>
#include <QWidget>
#include <iostream>
#include <utility>
#include <vector>

class centerWidget : public QWidget {
    Q_OBJECT
  public:
    explicit centerWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *e);
    void showend();

  private:
    int check();
    int endnumber=0;
    bool failflag=0;
    void failed();
    void createMonsters();
    bool hassame(std::pair<int, int> a);
    std::vector<monster *> monsters;
    basicmap *myMap;
    Role *role;
    void showpath();
    QWidget *pa;
    std::pair<int, int> end;

  signals:

  public slots:
    void timeToShow();
};

#endif // CENTERWIDGET_H
