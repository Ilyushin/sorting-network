#ifndef SORTINGNETWORK_HSORT_H
#define SORTINGNETWORK_HSORT_H

#include "./point.h"

// TODO Public only for testing
void heapify(int size, Point arr[], int i, int axis = 0);

void heapSort(int size, Point arr[], int axis = 0);

#endif //SORTINGNETWORK_HSORT_H
