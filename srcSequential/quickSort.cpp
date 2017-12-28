//
// Created by Evgeny Ilyushin on 12/10/17.
//
#include <stdlib.h>
#include "quickSort.h"

int compareX(const void *a, const void *b) {
    if (((Point *) a)->coord[0] < ((Point *) b)->coord[0]) return -1;
    if (((Point *) a)->coord[0] == ((Point *) b)->coord[0]) return 0;
    if (((Point *) a)->coord[0] > ((Point *) b)->coord[0]) return 1;
}

int compareY(const void *a, const void *b) {
    if (((Point *) a)->coord[1] < ((Point *) b)->coord[1]) return -1;
    if (((Point *) a)->coord[1] == ((Point *) b)->coord[1]) return 0;
    if (((Point *) a)->coord[1] > ((Point *) b)->coord[1]) return 1;
}

void quickSort(int length, Point *arr, int axis) {
    qsort(arr, length, sizeof(Point), (axis == 1 ? compareY : compareX));
}