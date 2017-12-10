#ifndef SORTINGNETWORK_HSORT_H
#define SORTINGNETWORK_HSORT_H

#include "./point.h"

// TODO Public only for testing
void heapify(int size, Point arr[], int i, bool byY);

void heapSort(int size, Point arr[], bool byY = false);

#endif //SORTINGNETWORK_HSORT_H
