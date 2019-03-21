#include "mainwindow.h"
#include<iostream>
#include <QActionGroup>
#include <QStatusBar>
#include <QMessageBox>
#include<QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle(tr("简单绘图-未命名"));
    centerWidget = new CenterWidget(this);
    setCentralWidget(centerWidget);
    fileMenu = menuBar()->addMenu(tr("文件"));
    colorMenu = menuBar()->addMenu(tr("更换颜色"));
    blueAction =new QAction(tr("蓝色"),this);
    redAction =new QAction(tr("红色"),this);
    blackAction=new QAction(tr("黑色"),this);
    colorMenu -> addAction(blueAction);
    colorMenu->addAction(redAction);
    colorMenu->addAction(blackAction);
    newAction = new QAction(tr("新建"), this);
    newAction->setShortcut(tr("Ctrl + N"));
    newAction->setStatusTip(tr("新建绘图文件"));
    openAction = new QAction(tr("打开文件"), this);
    openAction->setShortcut(tr("Ctrl + O"));
    openAction->setStatusTip(tr("打开保存的绘图文件"));
    saveAction = new QAction(tr("保存文件"), this);
    saveAction->setShortcut(tr("Ctrl + S"));
    saveAction->setStatusTip("保存文件");
    exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(tr("Ctrl + X"));
    exitAction->setStatusTip("退出");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);
    drawMenu = menuBar()->addMenu(tr("绘图"));
    lineAction = new QAction(QIcon("line.gif"), tr("线条"), this);
    lineAction->setShortcut(tr("Ctrl+L"));
    lineAction->setStatusTip(tr("绘制线条"));
    ellipseAction = new QAction(QIcon("ellipse.gif"), tr("椭圆"), this);
    ellipseAction->setShortcut(tr("Ctrl+E"));
    ellipseAction->setStatusTip(tr("绘制椭圆"));
    rectangleAction = new QAction(QIcon("rectangle.gif"), tr("矩形"), this);
    rectangleAction->setShortcut(tr("Ctrl+R"));
    rectangleAction->setStatusTip(tr("绘制矩形"));
    // drawMenu->addAction(lineAction);
    blueAction->setCheckable(1);
    blackAction->setCheckable(1);
    redAction->setCheckable(1);
    lineAction->setCheckable(1);
    ellipseAction->setCheckable(1);
    rectangleAction->setCheckable(1);
    QActionGroup *group = new QActionGroup(this);
    QActionGroup *colors=new QActionGroup(this);
    colors->addAction(blueAction);
    colors->addAction(blackAction);
    colors->addAction(redAction);
    colors->setExclusive(true);
    group->addAction(lineAction);
    group->addAction(ellipseAction);
    group->addAction(rectangleAction);
    group->setExclusive(true);
    lineAction->setChecked(true);
    drawMenu->addAction(lineAction);
    drawMenu->addAction(ellipseAction);
    drawMenu->addAction(rectangleAction);
    drawToolBar = addToolBar(tr("Draw"));
    drawToolBar->addAction(newAction);
    drawToolBar->addAction(openAction);
    drawToolBar->addAction(saveAction);
    drawToolBar->addSeparator();
    drawToolBar->addAction(lineAction);
    drawToolBar->addAction(ellipseAction);
    drawToolBar->addAction(rectangleAction);
    menuBar()->show();
    statusBar()->show();
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(lineAction,SIGNAL(triggered()),this,SLOT(line()));
    connect(ellipseAction,SIGNAL(triggered()),this,SLOT(ellipse()));
    connect(rectangleAction,SIGNAL(triggered()),this,SLOT(rectangle()));
    connect(newAction,SIGNAL(triggered()),this,SLOT(newDrawing()));
    connect(openAction,SIGNAL(triggered()),this,SLOT(openDrawing()));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveDrawing()));
    connect(blueAction,SIGNAL(triggered()),this,SLOT(toBlue()));
    connect(redAction,SIGNAL(triggered()), this,SLOT(toRed()));
    connect(blackAction,SIGNAL(triggered()),this,SLOT(toBlack()));
}
void MainWindow::toBlue(){
    centerWidget->setColor(Qt::blue);
}
void MainWindow::toBlack(){
    centerWidget->setColor(Qt::black);
}
void MainWindow::toRed(){
    centerWidget->setColor(Qt::red);
}

void MainWindow::rectangle(){
    this->centerWidget->setDrawType(2);
}
void MainWindow::ellipse(){
    this->centerWidget->setDrawType(1);
}
void MainWindow::line(){
    this->centerWidget->setDrawType(0);
}
void MainWindow::saveDrawing(){
    centerWidget->saveDrawing();
}
void MainWindow::newDrawing(){
    std::cout<<1<<std::endl;
    if(centerWidget->getModifiedFlag()==true){
        std::cout<<1<<std::endl;
        switch(QMessageBox::question(this,tr("文档保存提示"),
                                     tr("文档已经修改，是否保存文档"), QMessageBox::Ok|
                                    QMessageBox::Cancel|QMessageBox::No,QMessageBox::Ok)){
        case QMessageBox::Ok:
            centerWidget->saveDrawing();
            break;
        case QMessageBox::Cancel:
            return;
        case QMessageBox::No:
            break;
        default:
            break;
        }
    }
    centerWidget->newDrawing();
}
void MainWindow::closeEvent(QCloseEvent *event){
    if(centerWidget->getModifiedFlag()==true){ //文档已修改
        switch(QMessageBox::question(this,tr("文档保存提示"),tr("文档已经修改，是否保存文档"),
                                     QMessageBox::Ok|QMessageBox::Cancel|QMessageBox::No,
                                     QMessageBox::Ok)){
        case QMessageBox::Ok:
            centerWidget->saveDrawing();
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            return;
        case QMessageBox::No:
            event->accept();
            break;
        default: event->accept();
            break;
        }
    }
}
void MainWindow::openDrawing(){
    if(centerWidget->getModifiedFlag()==true){ //文档已修改
        switch(QMessageBox::question(this,tr("文档保存提示"), tr("文档已经修改，是否保存文档"),
                                     QMessageBox::Ok|QMessageBox::Cancel
                                     |QMessageBox::No,QMessageBox::Ok)){
        case QMessageBox::Ok:
            centerWidget->saveDrawing(); break;
        case QMessageBox::Cancel:
            return;
        case QMessageBox::No:
            break;
        default:
            break;
        } }
    centerWidget->openDrawing();
}

