#ifndef SORTINGNETWORK_DECOMPOSE_H
#define SORTINGNETWORK_DECOMPOSE_H

#include "point.h"

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
void decompose(Point *arr, int arrayStartIndx, int length, int *domains, int domainStartIndx, int k);

#endif //SORTINGNETWORK_DECOMPOSE_H
