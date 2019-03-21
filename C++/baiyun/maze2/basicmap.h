#ifndef BASICMAP_H
#define BASICMAP_H
#include <QPainter>
#include <QRect>
#include <iostream>
#include <utility>
#include <vector>

class basicmap {
  public:
    basicmap();
    basicmap(int n);
    void creatMap();
    bool haveEdge(std::pair<int, int> a, std::pair<int, int> b);
    int getSize() const;
    int getSize();
    void setSize(int a);
    void draw(QPainter *p);
    void setRectangle(QRect rect);
    bool road[200][200][4];
    std::pair<int, int> pathto[200][200];
    bool isshowing = 0;

  private:
    void showDistance();
    void loop(std::pair<int, int> a);
    bool noWay(const std::pair<int, int> &a);
    int size = 60;
    bool mark[200][200];
    int distance[200][200];
    QRect r;
    QColor lineColor = Qt::black;
};

#endif // BASICMAP_H
