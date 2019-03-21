#ifndef MAPELEMENT_H
#define MAPELEMENT_H
#include <QPainter>
#include <cmath>
#include <utility>

class mapElement {
  public:
    mapElement() = default;
    virtual int getType() const = 0;
    virtual int getType() = 0;
    virtual void draw(QPainter *p) = 0;
    void setPosition(std::pair<int, int> a);
    std::pair<int, int> getPosition();
    std::pair<int, int> getPosition() const;

  private:
    std::pair<int, int> position;
};

#endif // MAPELEMENT_H
