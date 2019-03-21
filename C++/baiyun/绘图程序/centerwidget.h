#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QList>
#include <QPoint>
#include <QLabel>
#include <QRect>
#include <QWidget>
#include<QMouseEvent>
#include <QStatusBar>
#include "shape.h"
#include "rectangle.h"
#include "ellipse.h"
#include "line.h"

class CenterWidget : public QWidget {
    Q_OBJECT
public:
    ~CenterWidget();
    explicit CenterWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *p);
    void setDrawType(int a);
    void newDrawing();
    void openDrawing();
    void saveFile(QString fileName);
    void saveDrawing();
    void openFile(QString fileName);
    bool getModifiedFlag();
    void setColor(QColor a){
        nowcolor=a;
    }

signals:

public slots:
private:
    QList<Shape*> shapes;
    QPoint p1, p2;
    int drawtype;
    QColor nowcolor=Qt::black;
    bool begindraw;
    QLabel *mousePosLabel;
    bool isModified;
    QString filename;
    protected:
    void mousePressEvent(QMouseEvent *m);
    void mouseMoveEvent(QMouseEvent* m);
    void mouseReleaseEvent(QMouseEvent *m);
};

#endif // CENTERWIDGET_H
