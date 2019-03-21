#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "centerwidget.h"
#include <QMainWindow>
#include <QMenu>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    CenterWidget *centerWidget;
    QMenu *fileMenu;
    QMenu *changecolor;
    QAction *changeback;
    QAction *changeline;
    QAction *exitAction;
  protected slots:
    void backg();
    void cline();
};

#endif // MAINWINDOW_H
