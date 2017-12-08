#include "../include/point.h"

Point *createPoint(float x, float y, int index){
    Point *point = new Point;
    point->x = x;
    point->y = y;
    point->index = index;

    return point;
}

