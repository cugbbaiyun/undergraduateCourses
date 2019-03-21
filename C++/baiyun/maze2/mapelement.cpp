#include "mapelement.h"
#include <iostream>
#include <utility>
using namespace std;
using pii = pair<int, int>;
void mapElement::setPosition(pii a) {
    this->position = a;
}
pii mapElement::getPosition() {
    return this->position;
}
pii mapElement::getPosition() const {
    return this->position;
}