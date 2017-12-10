//
// Created by Evgeny Ilyushin on 12/10/17.
//
#include <stdlib.h>
#include "quickSort.h"

int compareX(const void *a, const void *b) {
    if (((Point *) a)->x < ((Point *) b)->x) return -1;
    if (((Point *) a)->x == ((Point *) b)->x) return 0;
    if (((Point *) a)->x > ((Point *) b)->x) return 1;
}

int compareY(const void *a, const void *b) {
    if (((Point *) a)->y < ((Point *) b)->y) return -1;
    if (((Point *) a)->y == ((Point *) b)->y) return 0;
    if (((Point *) a)->y > ((Point *) b)->y) return 1;
}

void quickSort(int length, Point *arr, bool byY) {
    qsort(arr, length, sizeof(Point), (byY ? compareY : compareX));
}