#include "clock.h"

// Clock::Clock() {}
void Clock::draw(QPainter *p) {
    plate.draw(p);
    hour.draw(p);
    minute.draw(p);
    second.draw(p);
}
Clock::Clock()
    : hour(Arm::ArmType::HOUR)
    , minute(Arm::ArmType::MINUTE)
    , second(Arm::ArmType::SECOND) {
    hour.setColor(Qt::white);
    minute.setColor(Qt::white);
    second.setColor(Qt::red);
}
void Clock::setRectangle(QRect rect) {
    plate.setRectangle(rect);
    hour.setRectangle(rect);
    minute.setRectangle(rect);
    second.setRectangle(rect);
}
void Clock::setshicha(int n) {
    hour.setshicha(n);
}
