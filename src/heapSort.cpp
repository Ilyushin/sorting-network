
#include "heapSort.h"

// TODO Public only for testing
void heapify(int size, Point *arr, int i, bool byY) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if(byY == false) {

        if (left <= size - 1 && arr[left].x > arr[largest].x) {
            largest = left;
        };

        if (right <= size - 1 && arr[right].x > arr[largest].x) {
            largest = right;
        };

    } else {

        if (left <= size - 1 && arr[left].y > arr[largest].y) {
            largest = left;
        };

        if (right <= size - 1 && arr[right].y > arr[largest].y) {
            largest = right;
        };
    }

    if (largest != i) {
        Point temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(size, arr, largest, byY);
    }
}

Point *heapSort(int size, Point *arr, bool byY) {

    // Build heap
    for (int i = (size / 2) - 1; i >= 0; --i) {
        heapify(size, arr, i, byY);
    };

    // sort
    int length = size-1;
    for (int i = length; i >= 1; --i) {
        Point temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        --length;
        heapify(length, arr, 0, false);
    }

    return arr;
}
