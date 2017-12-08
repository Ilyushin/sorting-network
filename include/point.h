//
// Created by Evgeny Ilyushin on 11/30/17.
//

#ifndef SORTINGNETWORK_POINT_H
#define SORTINGNETWORK_POINT_H

struct Point {
    float x;
    float y;
    int index;
};

Point *createPoint(float x, float y, int index);


#endif //SORTINGNETWORK_POINT_H
