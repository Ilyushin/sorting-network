#include <iostream>
#include <math.h>
#include <float.h>
#include <string.h>
#include "decompose.h"
#include "heapSort.h"
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
    heapSort(length, arr + arrayStartIndx, *axis);

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

Point* align(Point *array, int size, int procNumber)
{
    int epp = ceil(size / (double)procNumber);
    Point *res = new Point[epp * procNumber];
    int k = 0;
    for(int i = 0; i < size; i++, k++){
        res[k] = array[i];
        array[i].index = -1;
        array[i].coord[0] = FLT_MAX;
        array[i].coord[1] = FLT_MAX;
    }
    for(; k < epp * proc_count; k++){
        res[k].index = -1;
        res[k].coord[0] = FLT_MAX;
        res[k].coord[1] = FLT_MAX;
    }
    return res;
}

void decomposePar(Point **arr, int length, int **domains, int domainStartIndx,
                  int k, int *numberElemOnCPU,  MPI_Datatype *MPI_PointType,
                  MPI_Comm communicator, int *axis){

    int rank, processors, realLength;
    MPI_Comm_rank(communicator, &rank);
    MPI_Comm_size(communicator, &processors);

    *axis = !(*axis);
    if(processors == 1){
        realLength = deleteDummyElements(arr, length);
        *domains = new int[realLength];
        decompose(*arr, 0, realLength, *domains, domainStartIndx, k, axis);
        *numberElemOnCPU = realLength;
        return;
    }

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

    int leftCPUs = length1 / (*numberElemOnCPU);
    int rightCPUs = processors - leftCPUs;
    int middle = length1 % (*numberElemOnCPU);

    int color;
    if(leftCPUs == 0) {
        color = rank > leftCPUs ? 0 : 1;
    } else {
        color = rank >= leftCPUs ? 0 : 1;
    }

    SortingNetwork *network = new SortingNetwork(processors);
    network->buildSchedule();
    network->sortBySchedule(arr, length, MPI_PointType, communicator, processors, *axis);

    MPI_Comm new_comm;
    MPI_Comm_split(communicator, color, rank, &new_comm);



    if(leftCPUs == 0){
        int sendElemNumber = ceil(((*numberElemOnCPU) - middle) / (double)(rightCPUs));
        if(rank == leftCPUs){
            int elemPerProcTemp = ceil((*numberElemOnCPU) - middle/ (double)(rightCPUs -1));
            Point *temp = new Point[elemPerProcTemp * (rightCPUs - 1)];

            int k = 0;
            for (int i = 0; i < (*numberElemOnCPU) - middle; ++i, ++k) {
                temp[i] = (*arr)[i];
                (*arr)[i].index = -1;
                (*arr)[i].coord[0] = FLT_MAX;
                (*arr)[i].coord[1] = FLT_MAX;
            }

            for (; k < elemPerProcTemp * (rightCPUs - 1); ++k) {
                temp[k].index = -1;
                temp[k].coord[0] = FLT_MAX;
                temp[k].coord[1] = FLT_MAX;
            }

            for(int i = leftCPUs + 1, j = 0; i < processors; ++i, ++j)
                MPI_Send(temp + j*sendElemNumber, sendElemNumber, *MPI_PointType, i, 0, communicator);
            delete [] temp;
            decomposePar(arr, length1, domains, domainStartIndx, k1,
                      numberElemOnCPU, MPI_PointType, new_comm, axis);
        }else{
            Point *arrNew = new Point[*numberElemOnCPU + sendElemNumber];
            MPI_Recv(arrNew + (*numberElemOnCPU), sendElemNumber, *MPI_PointType, leftCPUs, 0,
                     communicator, &status);
            memcpy(arrNew, *arr, (*numberElemOnCPU) * sizeof(Point));
            *numberElemOnCPU += sendElemNumber;
            delete [] *arr;
            *arr = arrNew;
            decomposePar(arr, length2, domains, domainStartIndx+k1, k2,
                         numberElemOnCPU, MPI_PointType, new_comm, axis);
        }
        return;
    }
//
//
//    if(rank <= leftCPUs){
//        int sendElemNumber = ceil(middle / (double)leftCPUs);
//        if(rank == leftCPUs){
//            Point *temp = new Point[sendElemNumber * leftCPUs];
//            int k = 0;
//            for (int i = 0; i < processors; ++i, ++k) {
//                temp[i] = *arr[i];
//                (*arr[i]).index = -1;
//                (*arr[i]).coord[0] = FLT_MAX;
//                (*arr[i]).coord[1] = FLT_MAX;
//            }
//            for (; k < sendElemNumber * leftCPUs; ++k) {
//                temp[k].index = -1;
//                temp[k].coord[0] = FLT_MAX;
//                temp[k].coord[1] = FLT_MAX;
//            }
//            for(int i = 0; i < leftCPUs; i++)
//                MPI_Send(temp + i*sendElemNumber, sendElemNumber, *MPI_PointType, i, 0, communicator);
//            delete [] temp;
//        }else{
//            Point *arrNew = new Point[*numberElemOnCPU + sendElemNumber];
//            MPI_Recv(arrNew + (*numberElemOnCPU), sendElemNumber, *MPI_PointType, leftCPUs, 0,
//                     communicator, &status);
//            memcpy(arrNew, *arr, (*numberElemOnCPU) * sizeof(Point));
//            *numberElemOnCPU += sendElemNumber;
//            delete [] (*arr);
//            *arr = arrNew;
//        }
//    }
//    if(rank < leftCPUs){
//        decomposePar(arr, length1, domains, domainStartIndx, k1,
//                     numberElemOnCPU, MPI_PointType, new_comm, axis);
//    }else{
//        decomposePar(arr, length2, domains, domainStartIndx+k1, k2,
//                     numberElemOnCPU, MPI_PointType, new_comm, axis);
//    }

    delete network;
}