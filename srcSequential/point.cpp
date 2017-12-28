#include "point.h"

Point *createPoint(float x, float y, int index){
    Point *point = new Point;
    point->coord[0] = x;
    point->coord[1] = y;
    point->index = index;

    return point;
}

