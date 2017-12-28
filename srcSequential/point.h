#ifndef SORTINGNETWORK_POINT_H
#define SORTINGNETWORK_POINT_H

struct Point {
    float coord[2];
    int index;
};

// TODO Need to write a test
Point *createPoint(float x, float y, int index);

#endif //SORTINGNETWORK_POINT_H
