#include "basicmap.h"
#include <QBrush>
#include <QFont>
#include <QPalette>
#include <QString>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
using pii = pair<int, int>;
basicmap::basicmap() {
    this->size = 10;
    creatMap();
}
basicmap::basicmap(int n) {
    this->size = min(120, n);
    creatMap();
}
void basicmap::showDistance() {
    //定义一个局部结构体用来保存相应的信息
    struct ppi {
        int x, y, len;
        ppi(int a, int b, int c)
            : x(a)
            , y(b)
            , len(c) {}
    };
    //广度优先搜索标记数组
    bool mmark[200][200];
    //清空
    memset(mmark, 0, sizeof mmark);
    //搜索队列
    deque<ppi> q;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            distance[i][j] = 32765;
        }
    }
    //终点进队
    ppi endnode(getSize() - 1, getSize() - 1, 0);
    q.push_back(endnode);
    distance[endnode.x][endnode.y] = 0;
    pathto[endnode.x][endnode.y] = pii(endnode.x, endnode.y);
    //开始循环
    while (!q.empty()) {
        auto c = q.front();
        q.pop_front();
        if (mmark[c.x][c.y] == 1) continue;
        mmark[c.x][c.y] = 1;
        //如果该点的上方没有墙壁,上方点进队,并且设置path数组
        if (road[c.x][c.y][0] == 1) {
            if (mmark[c.x][c.y - 1] == 0) {
                q.push_back(ppi(c.x, c.y - 1, c.len + 1));
                distance[c.x][c.y - 1] = min(c.len + 1, distance[c.x][c.y - 1]);
                pathto[c.x][c.y - 1] = pii(c.x, c.y);
            }
        }
        //如果该点下方没有墙壁,下方点进队,并且设置path数组
        if (road[c.x][c.y][1] == 1) {
            if (mmark[c.x][c.y + 1] == 0) {
                q.push_back(ppi(c.x, c.y + 1, c.len + 1));
                distance[c.x][c.y + 1] = min(c.len + 1, distance[c.x][c.y + 1]);
                pathto[c.x][c.y + 1] = pii(c.x, c.y);
            }
        }
        //如果左方没有墙壁，左方点进队,并且设置path数组
        if (road[c.x][c.y][2] == 1) {
            if (mmark[c.x - 1][c.y] == 0) {
                q.push_back(ppi(c.x - 1, c.y, c.len + 1));
                distance[c.x - 1][c.y] = min(c.len + 1, distance[c.x - 1][c.y]);
                pathto[c.x - 1][c.y] = pii(c.x, c.y);
            }
        }
        //如果右方点没有墙壁，右方点进队,并且设置path数组
        if (road[c.x][c.y][3] == 1) {
            if (mmark[c.x + 1][c.y] == 0) {
                q.push_back(ppi(c.x + 1, c.y, c.len + 1));
                distance[c.x + 1][c.y] = min(c.len + 1, distance[c.x + 1][c.y]);
                pathto[c.x + 1][c.y] = pii(c.x, c.y);
            }
        }
    }
}
void basicmap::creatMap() {
    pii begin1;
    srand(time(0));
    begin1.first = rand() % getSize();
    begin1.second = rand() % getSize();
    memset(road, 0, sizeof road);
    memset(mark, 0, sizeof mark);
    loop(begin1);
    showDistance();
}
bool basicmap::haveEdge(pii a, pii b) {
    if (a.first == b.first - 1) {
        return !road[a.first][a.second][0];
    }
    if (a.first == b.first + 1) {
        return !road[a.first][a.second][1];
    }
    if (a.second == b.second - 1) {
        return !road[a.first][a.second][2];
    }
    return !road[a.first][a.second][3];
}
int basicmap::getSize() const {
    return this->size;
}
int basicmap::getSize() {
    return this->size;
}
void basicmap::setSize(int a) {
    this->size = a;
}
void basicmap::draw(QPainter *p) {
    //得到窗体的左上角的位置
    int len = min(r.width(), r.height());
    len /= size;
    QPen pen(lineColor, 3, Qt::SolidLine);
    int xmid = r.width() / 2 + r.x();
    int ymid = r.height() / 2 + r.y();
    xmid -= len * (size / 2);
    ymid -= len * (size / 2);
    pii leftUp(xmid, ymid);
    //设置画笔及其背景
    p->setPen(pen);
    QBrush brush(QColor(11, 132, 87));
    p->setBrush(brush);
    p->drawRect(QRect(xmid, ymid, size * len, size * len));
    QFont font("宋体", 18, QFont::Bold, true);
    p->setFont(font);
    //每一个点绘制墙壁
    //由于数组中的x，y与像素位置是相反的，所以在绘画过程中也要进行相反操作
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (road[j][i][0] == 0) {
                p->drawLine(QPoint(leftUp.first + len * j, leftUp.second + len * i), QPoint(leftUp.first + len * j + len, leftUp.second + len * i));
            }
            if (road[j][i][1] == 0) {
                p->drawLine(QPoint(leftUp.first + len * j, leftUp.second + len * i + len), QPoint(leftUp.first + len * j + len, leftUp.second + len * i + len));
            }
            if (road[j][i][2] == 0) {
                p->drawLine(QPoint(leftUp.first + len * j, leftUp.second + len * i), QPoint(leftUp.first + len * j, leftUp.second + len * i + len));
            }
            if (road[j][i][3] == 0) {
                p->drawLine(QPoint(leftUp.first + len * j + len, leftUp.second + len * i), QPoint(leftUp.first + len * j + len, leftUp.second + len * i + len));
            }
        }
    }
}
void basicmap::setRectangle(QRect rect) {
    this->r = rect;
}
bool basicmap::noWay(const pair<int, int> &a) {
    if (!mark[a.first - 1][a.second]) return 1;
    if (!mark[a.first][a.second - 1]) return 1;
    if (!mark[a.first + 1][a.second]) return 1;
    if (!mark[a.first][a.second + 1]) return 1;
    return 0;
}
void basicmap::loop(pii a) {
    // using pii=pair<int,int>;
    // a是一个随机生成的起始点
    memset(road, 0, sizeof road);
    // road数组为每一块四周的墙壁 bool road[200][200][4];
    memset(mark, 0, sizeof mark);
    // mark 数组表示是否被访问过
    vector<pii> q;
    //起始点的候选数组
    srand(time(0));
    q.push_back(a);
    while (q.size() != 0) {
        int curid = rand() % q.size();
        mark[q[curid].first][q[curid].second] = 1;
        //首先从q数组中随机选出一个点作为这一步的起始点
        vector<pii> nexts;
        //判断这一个点是否越界
        int xx = q[curid].first, yy = q[curid].second;
        if (xx >= size || xx < 0) {
            q.erase(q.begin() + curid);
            continue;
        }
        if (yy >= size || yy < 0) {
            q.erase(q.begin() + curid);
            continue;
        }
        //获得与起点相邻的四个点(上,下,左,右)
        pii up1(q[curid].first, q[curid].second - 1);
        pii down1(q[curid].first, q[curid].second + 1);
        pii left1(q[curid].first - 1, q[curid].second);
        pii right1(q[curid].first + 1, q[curid].second);
        //判断这四个点是否已经在候选数组中并且没有越界
        if (up1.second >= 0 && !mark[up1.first][up1.second]) {
            nexts.push_back(up1);
        }
        if (down1.second < size && !mark[down1.first][down1.second]) {
            nexts.push_back(down1);
        }
        if (left1.first >= 0 && !mark[left1.first][left1.second]) {
            nexts.push_back(left1);
        }
        if (right1.first < size && !mark[right1.first][right1.second]) {
            nexts.push_back(right1);
        }
        //如果nexts数组为0，说明这个起始点周围的所有点都被访问过了，剔除这个点
        if (nexts.size() == 0) {
            q.erase(q.begin() + curid);
            continue;
        }
        //随机从这个数组中挑出一个点
        int nextid = rand() % nexts.size();
        auto c = nexts[nextid];
        //消除起始点与所选择点之间的墙壁
        if (c == up1) {
            road[q[curid].first][q[curid].second][0] = 1;
            road[c.first][c.second][1] = 1;
        } else if (c == down1) {
            road[q[curid].first][q[curid].second][1] = 1;
            road[c.first][c.second][0] = 1;
        } else if (c == left1) {
            road[q[curid].first][q[curid].second][2] = 1;
            road[c.first][c.second][3] = 1;
        } else if (c == right1) {
            road[q[curid].first][q[curid].second][3] = 1;
            road[c.first][c.second][2] = 1;
        }
        //标记所选的点，表示这个点已经进入了候选数组
        mark[c.first][c.second] = 1;
        //加入候选数组
        q.push_back(c);
    }
}
