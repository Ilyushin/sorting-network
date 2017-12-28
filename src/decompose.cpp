#include "decompose.h"
#include "./quickSort.h"

/**
* Add a new node to the list of nodes
*
* @return: None
* @arr — a sorting network.
* @domains — выходной массив, в котором хранятся номера доменов для узлов сетки (имеет такую же длину что и массив a).
* @domainStartIndx — начальный индекс доступных номеров доменов.
* @k — number of elements
* @arrayStartIndx — начальный элемент в массиве.
* @length — число элементов в массиве.
*/
void decompose(Point *arr, int arrayStartIndx, int length, int *domains, int domainStartIndx, int k) {
    if (k == 1) {
        for (int i = 0; i < length; i++)
            domains[arrayStartIndx + i] = domainStartIndx;
        return;
    }

    int axis = !axis;
    quickSort(length, arr + arrayStartIndx, axis);

    int k1 = (k + 1) / 2;
    int k2 = k - k1;
    int length1 = length * (k1 / (double)k);
    int length2 = length - length1;

    decompose(arr, domainStartIndx, length1, domains, domainStartIndx, k1);
    decompose(arr, domainStartIndx + length1, length2, domains, domainStartIndx + k1, k2);
}