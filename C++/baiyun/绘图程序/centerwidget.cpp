#include "centerwidget.h"
#include <QPainter>
#include <QLabel>
#include <QStatusBar>
#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
CenterWidget::~CenterWidget(){
    for(auto shape:shapes)
        delete shape;
}
CenterWidget::CenterWidget(QWidget *parent)
        : QWidget(parent) {
    shapes.clear();
    begindraw = false;
    isModified=0;
    filename=tr("");

    mousePosLabel=new QLabel;
    mousePosLabel->setText("");
    mousePosLabel->setFixedWidth(150);
    QMainWindow *p=(QMainWindow *)parent;
    p->statusBar()->addPermanentWidget(mousePosLabel);

    setMinimumSize  (500, 400);
    setMouseTracking(true);
}

bool CenterWidget::getModifiedFlag(){
    return this->isModified;
}
void CenterWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    for(auto shape:shapes){
        p.setPen(QPen(shape->getColor()));
        shape->draw(&p);
    }
    Shape *temp=nullptr;
    switch(drawtype){
    case 0:
        temp=new Line(p1,p2);
        temp->setColor(nowcolor);
        break;
    case 1:
        temp=new Ellipse(p1,p2);
        temp->setColor(nowcolor);
        break;
    case 2:
        temp=new Rectangle(p1,p2);
        temp->setColor(nowcolor);
        break;
    }
    temp->draw(&p);
    delete temp;
}

void CenterWidget::setDrawType(int a){
    this->drawtype=a;
}

void CenterWidget::mousePressEvent(QMouseEvent * m){
    p1=m->pos();
    p2=p1;
    begindraw=1;
}
void CenterWidget::mouseReleaseEvent(QMouseEvent *m){
    p2=m->pos();
    begindraw=0;
    if(p2==p1)return;
    Shape *shape=nullptr;
    switch(drawtype){
    case 0:
        shape=new Line(p1,p2);
        shape->setColor(nowcolor);
        break;
    case 1:
        shape=new Ellipse(p1,p2);
        shape->setColor(nowcolor);
        break;
    case 2:
        shape=new Rectangle(p1,p2);
        shape->setColor(nowcolor);
        break;
    }
    shapes.append(shape);
    update();
    return;
}
void CenterWidget::mouseMoveEvent(QMouseEvent*m){
    mousePosLabel->setText("X:"+QString::number(m->x())+",Y:"+QString::number(m->y()));
    if(m->pos()==p1){
        return;
    }
    p2=m->pos();
    update();
}

//void CenterWidget::newDrawing(){
//    ellipses.clear();
//    rects.clear();
//    isModified=false;
//    fileName=tr("");
//    parentWidget()->setWindowTitle(tr("简单绘图程序 未命名"));
//    update();
//}
void CenterWidget::newDrawing(){
    for(auto shape:shapes)
        delete shape;
    shapes.clear();
    begindraw=false;
    isModified=0;
    filename=tr("") ;
    parentWidget()->setWindowFilePath(tr("简单绘图程序 未命名"));
    //    std::cout<<1<<std::endl;
    update();
}

void CenterWidget::openDrawing(){
    for(auto shape:shapes)
        delete shape;
    shapes.clear();
    filename=QFileDialog::getOpenFileName(this,tr("打开文件对话框"),"/","绘图文件(*.draw);;所有文件(*.*)");
    if(filename==tr(""))
        return;
    begindraw=false;
    isModified=false;
    parentWidget()->setWindowTitle(tr("简单绘图程序")+filename);
    update();
}
void CenterWidget::saveDrawing(){
    if(filename==tr("")) {
        filename=QFileDialog::getOpenFileName(this,tr("保存文件对话框"),"/","绘图文件(*.draw);;所有文件(*.*)");
        if(filename==tr ("")) {
            return;
        }
    }
    saveFile(filename);
    parentWidget()->setWindowTitle(tr("简单绘图程序") +filename);
    isModified=0;
}

void CenterWidget::saveFile(QString fileName){
    QFile file(filename);
    if(file.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream	 out(&file);
        out<<shapes.length()<<endl;
        for(auto shape:shapes)
            shape->save(out);
        file.close();
    }
}
void CenterWidget::openFile(QString fileName){
    QFile file(filename);
    if(file.open(QFile::ReadOnly)){
        int x1,y1,x2,y2;
        QTextStream in(&file);
        int nums;
        in>>nums ;
        int type;
        Shape *curShape; for(int i=0;i<nums;++i){
            in>>type;
            switch(type){
            case 0:
                curShape=Line::read(in);
                break;
            case 1: curShape=Ellipse::read(in);
                break;
            case 2:
                curShape=Rectangle::read(in);
                break;
            }
            shapes.append(curShape); }
        file.close();
    }
}
