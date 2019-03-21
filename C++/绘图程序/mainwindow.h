#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "centerwidget.h"
#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    void newDrawing();
//    ~MainWiidow()=default;

  private:
    CenterWidget *centerWidget;
    QMenu *fileMenu;
    QMenu *drawMenu;
    QMenu *colorMenu;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *lineAction;
    QAction *blackAction;
    QAction *redAction;
    QAction *blueAction;
    QAction *ellipseAction;
    QAction *rectangleAction;
    QToolBar *drawToolBar;
protected slots:
    void line();
    void ellipse();
    void rectangle();
    void openDrawing();
    void saveDrawing();
    void toBlue();
    void toBlack();
    void toRed();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
