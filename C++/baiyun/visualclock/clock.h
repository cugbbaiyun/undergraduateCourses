#ifndef CLOCK_H
#define CLOCK_H

#include "arm.h"
#include "plate.h"

class Clock {
  public:
    void draw(QPainter *p);
    void setRectangle(QRect rect);
    Clock();
    void setshicha(int n);
    void changeback() {
        plate.setbackground(Qt::blue);
    }
    void changeline() {
        plate.setline(Qt::black);
    }

  private:
    Plate plate;
    Arm hour, minute, second;
};

#endif // CLOCK_H
