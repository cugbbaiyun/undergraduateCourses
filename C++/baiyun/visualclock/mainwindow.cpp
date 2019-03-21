#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle(tr("可视化时钟"));
    centerWidget = new CenterWidget(this);
    setCentralWidget(centerWidget);
    fileMenu = menuBar()->addMenu(tr("文件"));
    changecolor = menuBar()->addMenu(tr("变色"));
    exitAction = new QAction(tr("退出"), this);
    fileMenu->addAction(exitAction);
    changeback = new QAction(QIcon("null"), tr("更改背景颜色"), this);
    changeline = new QAction(QIcon("null"), tr("更改刻度颜色"), this);
    changecolor->addAction(changeback);
//    changecolor->addAction(exitAction);
    changecolor->addAction(changeline);
    statusBar()->show();
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(changeback, SIGNAL(triggered()), this, SLOT(backg()));
    connect(changeline, SIGNAL(triggered()), this, SLOT(cline()));
}

MainWindow::~MainWindow() {}
void MainWindow::backg() {
    this->centerWidget->changeback();
    centerWidget->update();
}
void MainWindow::cline() {
    this->centerWidget->changeLine();
    centerWidget->update();
}
