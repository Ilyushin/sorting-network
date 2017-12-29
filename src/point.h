//
// Created by Evgeny Ilyushin on 11/30/17.
//

#ifndef SORTINGNETWORK_POINT_H
#define SORTINGNETWORK_POINT_H

struct Point {
    float coord[2];
    int index;
};

struct PointDomain{
    int i;
    int j;
    float coord[2];
    int domain;
};

// TODO Need to write a test
Point *createPoint(float x, float y, int index);

#endif //SORTINGNETWORK_POINT_H
