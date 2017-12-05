#include "point.h"

Point::Point() {
    _coord[0] = 0;
    _coord[1] = 0;
    _index = 0;
}

Point::Point(float x, float y, int index) {
    _coord[0] = x;
    _coord[1] = y;
    _index = index;
}