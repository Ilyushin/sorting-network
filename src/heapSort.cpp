#include "heapSort.h"

void heapify(int size, Point arr[], int i, int axis) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left <= size - 1 && arr[left].coord[axis] > arr[largest].coord[axis]) {
        largest = left;
    };

    if (right <= size - 1 && arr[right].coord[axis] > arr[largest].coord[axis]) {
        largest = right;
    };

    if (largest != i) {
        Point temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(size, arr, largest, axis);
    }
}

void heapSort(int size, Point arr[], int axis) {

    // Build heap
    for (int i = (size / 2) - 1; i >= 0; --i) {
        heapify(size, arr, i, axis);
    };

    // sort
    int length = size;
    for (int i = length - 1; i > 0; --i) {
        Point temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        --length;
        heapify(length, arr, 0, false);
    }
}
