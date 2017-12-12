//
// Created by Evgeny Ilyushin on 12/10/17.
//

#ifndef SORTINGNETWORK_MERGESORT_H
#define SORTINGNETWORK_MERGESORT_H

#include "./point.h"

typedef struct chunk {
    int i;
    int j;
} Chunk;

typedef struct threadArgs {
    Chunk *chunk;
    Point *arr;
} ThreadArgs;

void mergeSort(int length, Point arr[], bool byY = false);


#endif //SORTINGNETWORK_MERGESORT_H
