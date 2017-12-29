#include "dhSort.h"

void merge(Point *arr1, int length1, Point *arr2, int length2, int axis) {
    int pos1 = 0, pos2 = 0, pos3 = 0;

    Point *temp = new Point[length1 + length2];

    while (pos1 < length1 && pos2 < length2) {
        if (arr1[pos1].coord[axis] < arr2[pos2].coord[axis]) {
            temp[pos3++] = arr1[pos1++];
        } else {
            temp[pos3++] = arr2[pos2++];
        }
    }

    while (pos2 < length2) {
        temp[pos3++] = arr2[pos2++];
    }
    while (pos1 < length1) {
        temp[pos3++] = arr1[pos1++];
    }

    for (pos3 = 0; pos3 < length1; ++pos3) {
        arr1[pos3] = temp[pos3];
    }
    pos2 = 0;
    for (pos3 = length1; pos3 < length1 + length2; ++pos3) {
        arr2[pos2++] = temp[pos3];
    }

    delete[] temp;
}

void dhSort(int length, Point *arr, int axis) {
    if (length == 1) {
        return;
    };

    if (length == 2) {
        if (arr[0].coord[axis] > arr[1].coord[axis]) {
            Point tmp = arr[0];
            arr[0] = arr[1];
            arr[1] = tmp;
        }
        return;
    }

    if (length > 1) {
        dhSort(length / 2, arr, axis);
        dhSort(length - length / 2, arr + length / 2, axis);
        merge(arr, length / 2, arr + length / 2, length - length / 2, axis);
    }
}