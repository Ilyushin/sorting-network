//
// Created by Evgeny Ilyushin on 12/10/17.
//

#ifndef SORTINGNETWORK_MERGESORT_H
#define SORTINGNETWORK_MERGESORT_H

#include "./point.h"

void dhSort(int length, Point *arr, int axis);

void dhSortPar(int length, Point *arr, int axis = 0, int threads = 1);


#endif //SORTINGNETWORK_MERGESORT_H
