#include "mainwindow.h"
#include <QPainter>
#include <QRect>
#include <QStatusBar>
#include <QTimer>
#include <iostream>
using namespace std;
using pii = pair<int, int>;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle(tr("迷宫小游戏"));
    this->resize(QSize(1000, 700));
    QPalette palette;
    QPixmap pixmap(":/backjpgs/background.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(palette);
    QPixmap choicejpg(":/backjpgs/test.jpg");
    note = new QLabel(this);
    note->setPixmap(QPixmap(":/backjpgs/readme.png"));
    note->setScaledContents(true);
    choice = new QLabel(this);
    choice->setPixmap(choicejpg);
    choice->setScaledContents(true);
    QTimer *timer = new QTimer(this);
    leftU = pii(1000, 600);
    QRect loca = QRect(1000, 600, 400, 100);
    note->setGeometry(loca);
    note->setScaledContents(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
    fileMenu = menuBar()->addMenu(tr("文件"));
    exitAction = new QAction(tr("退出"));
    fileMenu->addAction(exitAction);
    statusBar()->show();
    beginstat();
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}
void MainWindow::paintEvent(QPaintEvent *) {
    if (leftU.first >= 300) {
        --leftU.first;
    }
    QRect loca = QRect(leftU.first, leftU.second, 400, 100);
    note->setGeometry(loca);
}
void MainWindow::beginstat() {
    if (this->stat == 0) {
        this->stat = 1;
    }
    choice->setGeometry(QRect(400, 437, 20, 20));
}
void MainWindow::endstat() {
    if (this->stat == 1) {
        this->stat = 0;
    }
    choice->setGeometry(QRect(400, 510, 20, 20));
}
void MainWindow::keyPressEvent(QKeyEvent *e) {
    int key = e->key();
    cout << key << endl;
    if (key == 16777237) {
        endstat();
    } else if (key == 16777235) {
        beginstat();
    } else if (key == 16777220) {
        if (this->stat == 0) {
            close();
        } else {
            gamewidget = new centerWidget(this);
            gamewidget->show();
            setCentralWidget(gamewidget);
//            delete choice;
        }
    }
}
