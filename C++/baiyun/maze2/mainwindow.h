#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "centerwidget.h"
#include <QAction>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QToolBar>
#include <utility>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow() = default;
    void paintEvent(QPaintEvent *p);
    void keyPressEvent(QKeyEvent *e);

  private:
    std::pair<int, int> leftU;
    QMenu *fileMenu;
    QAction *exitAction;
    QAction *againAction;
    void showgame();
    void beginstat();
    void endstat();
    void again();
    centerWidget *gamewidget;
    bool stat = 1;
    QLabel *note;
    QLabel *choice;
};

#endif // MAINWINDOW_H
