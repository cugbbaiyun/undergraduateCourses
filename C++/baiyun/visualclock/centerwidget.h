#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include "clock.h"
#include <QWidget>

class CenterWidget : public QWidget {
    Q_OBJECT
  public:
    explicit CenterWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void changeback (){
        clock.changeback();
    };
    void changeLine(){
        clock.changeline();
    }
  signals:

  public slots:
  private:
    Clock clock;
    Clock clock2;
};

#endif // CENTERWIDGET_H
