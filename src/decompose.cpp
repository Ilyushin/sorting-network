#include "decompose.h"
#include "quickSort.h"
#include "sortingNetwork.h"

/**
* Add a new node to the list of nodes
* @arr — a sorting network.
* @arrayStartIndx — начальный элемент в массиве.
* @length — число элементов в массиве.
* @domains — выходной массив, в котором хранятся номера доменов для узлов сетки (имеет такую же длину что и массив a).
* @domainStartIndx — начальный индекс доступных номеров доменов.
* @k — number of elements
* @return: None
*/
void decompose(Point *arr, int arrayStartIndx, int length, int *domains, int domainStartIndx, int k, int *axis) {
    if (k == 1) {
        for (int i = 0; i < length; i++)
            domains[arrayStartIndx + i] = domainStartIndx;
        return;
    }

    *axis = !(*axis);
    quickSort(length, arr + arrayStartIndx, axis);

    int k1 = (k + 1) / 2;
    int k2 = k - k1;
    int length1 = length * (k1 / (double)k);
    int length2 = length - length1;

    decompose(arr, arrayStartIndx, length1, domains, domainStartIndx, k1, axis);
    decompose(arr, arrayStartIndx + length1, length2, domains, domainStartIndx + k1, k2, axis);
}

int deleteDummyElements(Point **arr, int length){
    Point *res = new Point[length];
    int j = 0;
    for(int i = 0; i < length; i++){
        if((*arr)[i].index == -1)
            continue;
        res[j++] = (*arr)[i];
    }
    delete [] (*arr);
    *arr = res;
    return j;
}

void decomposePar(Point **arr, int length, int **domains, int domainStartIndx,
                  int k, int *numberElemOnCPU,  MPI_Datatype *MPI_PointType,
                  MPI_Comm communicator, int *axis){

    int rank, processors, realLength;
    MPI_Comm_rank(communicator, &rank);
    MPI_Comm_size(communicator, &processors);
    if(k == 1){
        realLength = deleteDummyElements(arr, *numberElemOnCPU);
        *domains = new int[realLength];
        for(int i = 0; i < realLength; i++)
            (*domains)[i] = domainStartIndx;
        *numberElemOnCPU = realLength;
        return;
    }

    MPI_Status status;
    int k1 = (k + 1) / 2;
    int k2 = k - k1;
    int length1 = length * (k1 / (double)k);
    int length2 = length - length1;

    //
    int pc = length1 / (*numberElemOnCPU);
    int middle = length1 % (*numberElemOnCPU);

    int color;
    if(pc == 0) {
        color = rank > pc ? 0 : 1;
    } else {
        color = rank >= pc ? 0 : 1;
    }

    SortingNetwork *network = new SortingNetwork(processors);
    network->buildSchedule();
    network->sortBySchedule(arr, length, MPI_PointType, communicator, processors, *axis);


    *axis = !(*axis);
    delete network;
}