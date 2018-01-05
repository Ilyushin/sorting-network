#include <iostream>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stddef.h>
#include <mpi.h>
#include "sortingNetwork.h"
#include "point.h"
#include "heapSort.h"
#include "dhSort.h"
#include "quickSort.h"

#define deleteArrPtr(ptr){delete[] ptr; ptr = NULL;}

MPI_Datatype MPI_PointType;
MPI_Datatype MPI_PointDomainType;
int axis = 1;

void createMPI_PointType(){
    const int n = 2;
    int blocklengths[n] = {2, 1};
    MPI_Datatype types[n] = {MPI_FLOAT, MPI_INT};
    MPI_Aint offsets[n];

    offsets[0] = offsetof(Point, coord);
    offsets[1] = offsetof(Point, index);

    MPI_Type_create_struct(n, blocklengths, offsets, types, &MPI_PointType);

    MPI_Type_commit(&MPI_PointType);
}

void createMPI_PointDomainType() {
    const int n = 4;
    int blocklengths[n] = {1, 1, 2, 1};
    MPI_Datatype types[n] = {MPI_INT, MPI_INT, MPI_FLOAT, MPI_INT};
    MPI_Aint offsets[n];

    offsets[0] = offsetof(PointDomain, i);
    offsets[1] = offsetof(PointDomain, j);
    offsets[2] = offsetof(PointDomain, coord);
    offsets[3] = offsetof(PointDomain, domain);

    MPI_Type_create_struct(n, blocklengths, offsets, types, &MPI_PointDomainType);
    MPI_Type_commit(&MPI_PointDomainType);
}

// Returns a next coordinate which was calculated using a function:
float getNextCoordinate(int i, int j) {
    return (rand() / (float) RAND_MAX * i) + j;
}

// Iterate since 0 to n1, 1 to n2 and create Points of a grid
void fillCoord(int numberElemOnCPU, Point *localPoints, int rank, int length, int n2) {
    int start = rank * numberElemOnCPU;
    for (int k = 0; k < numberElemOnCPU; ++k) {
        int index = start + k;
        if (index >= length) {
            localPoints[k] = *(createPoint(
                    FLT_MAX,
                    FLT_MAX,
                    -1
            ));
        } else {
            int i = index / n2;
            int j = index % n2;
            localPoints[k] = *(createPoint(
                    getNextCoordinate(i, j),
                    getNextCoordinate(i, j),
                    index
            ));
        }
    }
}

void saveResults(PointDomain *array, int n, char *filename, int n1, int n2, int rank) {
    MPI_Status status;

    MPI_File output;
    if (MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE |
                                                MPI_MODE_WRONLY, MPI_INFO_NULL, &output) != MPI_SUCCESS) {
        if (rank == 0) {
            std::cout << "Can't open " << filename << std::endl;
        }
        MPI_Finalize();
        exit(1);
    }
    MPI_File_set_size(output, 0);

    MPI_File_write_ordered(output, &n1, rank == 0, MPI_INT, &status);
    MPI_File_write_ordered(output, &n2, rank == 0, MPI_INT, &status);
    MPI_File_write_ordered(output, array, n, MPI_PointDomainType, &status);

    MPI_File_close(&output);
}

int countEdges(int *domains, Point *points, int size, int n2) {
    if (size == 0)
        return 0;

    int edges = 0;
    int offset = 0;
    int startDomain = domains[0];
    while (offset < size) {
        while (domains[offset] == startDomain && offset < size) {
            int xCoord = points[offset].index / n2;
            int yCoord = points[offset].index % n2;

            for (int j = offset + 1; domains[j] == startDomain && j < size; ++j) {
                int xCoordCheck = points[j].index / n2;
                int yCoordCHeck = points[j].index % n2;
                if ((xCoord == xCoordCheck && abs(yCoord - yCoordCHeck) <= 1) ||
                    (yCoord == yCoordCHeck && abs(xCoord - xCoordCheck) <= 1)) {
                    ++edges;
                }
            }
            ++offset;
        }
        ++startDomain;
    }

    return edges;
}

void decompose(Point *arr, int arrayStartIndx, int length, int *domains, int domainStartIndx, int k) {
    std::cout << "6) *arr - " << arr
              << "; length - " << length
              << "; k - " << k
              << "; arr[0]: " << (arr)[0].index << std::endl;

    if (k == 1) {
        for (int i = 0; i < length; i++)
            domains[arrayStartIndx + i] = domainStartIndx;
        return;
    }

    axis = !axis;
    quickSort(length, arr + arrayStartIndx, &axis);

    int k1 = (k + 1) / 2;
    int k2 = k - k1;
    int length1 = length * (k1 / (double) k);
    int length2 = length - length1;

    decompose(arr, arrayStartIndx, length1, domains, domainStartIndx, k1);
    decompose(arr, arrayStartIndx + length1, length2, domains, domainStartIndx + k1, k2);
}

int deleteDummyElements(Point **arr, int length) {
    Point *res = new Point[length];
    int j = 0;
    for (int i = 0; i < length; i++) {
        if ((*arr)[i].index == -1)
            continue;
        res[j++] = (*arr)[i];
    }
    deleteArrPtr(*arr);
    *arr = res;
    return j;
}

Point *align(Point *array, int size, int procNumber) {
    int epp = ceil(size / (double) procNumber);
    Point *res = new Point[epp * procNumber];
    int k = 0;
    for (int i = 0; i < size; i++, k++) {
        res[k] = array[i];
        array[i].index = -1;
        array[i].coord[0] = FLT_MAX;
        array[i].coord[1] = FLT_MAX;
    }
    for (; k < epp * procNumber; k++) {
        res[k].index = -1;
        res[k].coord[0] = FLT_MAX;
        res[k].coord[1] = FLT_MAX;
    }
    return res;
}

void decomposePar(Point **arr, int length, int **domains, int domainStartIndx,
                  int k, int *numberElemOnCPU, MPI_Comm communicator) {
    int rank, processors;
    MPI_Comm_rank(communicator, &rank);
    MPI_Comm_size(communicator, &processors);

    int realLength;
    if (processors == 1) {
        //realLength = deleteDummyElements(arr, *numberElemOnCPU);
        Point *res = new Point[length];
        int j = 0;
        for (int i = 0; i < length; i++) {
            if ((*arr)[i].index == -1)
                continue;
            res[j++] = (*arr)[i];
        }

        std::cout << "1) Rank: " << rank << " *arr - " << (*arr)
                  << "; length - " << length
                  << "; k - " << k
                  << "; processors - " << processors
                  << "; arr[0]: " << (*arr)[0].index << std::endl;

        delete[] (*arr);
        *arr = res;

        realLength = j;
        *domains = new int[realLength];
        decompose(*arr, 0, realLength, *domains, domainStartIndx, k);
        *numberElemOnCPU = realLength;
        return;
    }

    if (k == 1) {

        std::cout << "2) Rank: " << rank << " *arr - " << (*arr)
                  << "; length - " << length
                  << "; k - " << k
                  << "; processors - " << processors
                  << "; arr[0]: " << (*arr)[0].index << std::endl;

        //realLength = deleteDummyElements(arr, *numberElemOnCPU);
        Point *res = new Point[length];
        realLength = 0;
        for (int i = 0; i < length; i++) {
            if ((*arr)[i].index == -1)
                continue;
            res[realLength++] = (*arr)[i];
        }

        delete[] (*arr);
        *arr = res;
        *domains = new int[realLength];
        for (int i = 0; i < realLength; i++)
            (*domains)[i] = domainStartIndx;
        *numberElemOnCPU = realLength;
        return;
    }

    axis = !axis;
    SortingNetwork *network = new SortingNetwork(processors);
    network->buildSchedule();
    network->sortBySchedule(arr, length, &MPI_PointType, communicator, axis);
    delete network;


    int k1 = (k + 1) / 2;
    int k2 = k - k1;
    int length1 = length * (k1 / (double) k);
    int length2 = length - length1;

    int leftCPUs = length1 / (*numberElemOnCPU);
    int rightCPUs = processors - leftCPUs;
    int middle = length1 % (*numberElemOnCPU);

    int color;
    if (leftCPUs == 0) {
        color = rank > leftCPUs ? 0 : 1;
    } else {
        color = rank >= leftCPUs ? 0 : 1;
    }

    MPI_Comm new_comm;
    MPI_Comm_split(communicator, color, rank, &new_comm);

    MPI_Status status;
    if (leftCPUs == 0) {
        int epp = ceil(((*numberElemOnCPU) - middle) / (double) (rightCPUs));
        if (rank == leftCPUs) {

            std::cout << "3) Rank: " << rank << " *arr - " << (*arr)
                      << "; length - " << length
                      << "; k - " << k
                      << "; processors - " << processors
                      << "; arr[0]: " << (*arr)[0].index << std::endl;

            Point *temp = align((*arr) + middle, (*numberElemOnCPU) - middle, rightCPUs - 1);

            for (int i = leftCPUs + 1, j = 0; i < processors; i++, j++) {
                MPI_Send(temp + j * epp, epp, MPI_PointType, i, 0, communicator);
            }
            delete[] temp;

            decomposePar(arr, length1, domains, 0, k1,
                         numberElemOnCPU, new_comm);
        } else {
            std::cout << "4) Rank: " << rank << " *arr - " << (*arr)
                      << "; length - " << length
                      << "; k - " << k
                      << "; processors - " << processors
                      << "; arr[0]: " << (*arr)[0].index << std::endl;

            Point *arrNew = new Point[*numberElemOnCPU + epp];
            MPI_Recv(arrNew + (*numberElemOnCPU), epp, MPI_PointType, leftCPUs, 0,
                     communicator, &status);
            memcpy(arrNew, *arr, (*numberElemOnCPU) * sizeof(Point));
            *numberElemOnCPU += epp;
            //delete[] (*arr);
            *arr = arrNew;

            decomposePar(arr, length2, domains, domainStartIndx + k1, k2,
                         numberElemOnCPU, new_comm);
        }
        return;
    }


    std::cout << "5) Rank: " << rank << " *arr - " << (*arr)
              << "; length - " << length
              << "; k - " << k
              << "; processors - " << processors
              << "; arr[0]: " << (*arr)[0].index << std::endl;
    if (rank <= leftCPUs) {
        int epp = ceil(middle / (double) leftCPUs);
        if (rank == leftCPUs) {
            Point *temp = align(*arr, middle, leftCPUs);
            for (int i = 0; i < leftCPUs; i++) {
                MPI_Send(temp + i * epp, epp, MPI_PointType, i, 0, communicator);
            }
            delete[] temp;
        } else {
            Point *arrNew = new Point[*numberElemOnCPU + epp];
            MPI_Recv(arrNew + (*numberElemOnCPU), epp, MPI_PointType, leftCPUs, 0,
                     communicator, &status);
            memcpy(arrNew, *arr, (*numberElemOnCPU) * sizeof(Point));
            *numberElemOnCPU += epp;
            delete[] (*arr);
            *arr = arrNew;
        }
    }

    if (rank < leftCPUs) {
        decomposePar(arr, length1, domains, domainStartIndx, k1,
                     numberElemOnCPU, new_comm);
    } else {
        decomposePar(arr, length2, domains, domainStartIndx + k1, k2,
                     numberElemOnCPU, new_comm);
    }
}

int main(int argc, char *argv[]) {

    int n1 = 0;
    int n2 = 0;
    int k = 0; // Number of domains
    std::string resultFile;

    if (argc >= 5) {
        n1 = atoi(argv[1]);
        n2 = atoi(argv[2]);
        k = atoi(argv[3]);
        resultFile = argv[4];
    } else {
        std::cout
                << "A dimension of a network (n1, n2), number of domains or a file's name wasn't passed to the program!\n";
        return 0;
    }

    if (n1 > INT_MAX / n2) {
        std::cout << "A dimension of a network (n1, n2) is too big for calculating!\n";
        MPI_Finalize();
        return 0;
    }

    int length = n1 * n2;

    //PARALLEL AREA
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int processors;
    MPI_Comm_size(MPI_COMM_WORLD, &processors);

    int numberElemOnCPU = ceil(length / (float) processors);
    Point *localPoints = new Point[numberElemOnCPU];
    fillCoord(numberElemOnCPU, localPoints, rank, length, n2);

    // Create a new type of MPI
    createMPI_PointType();

    double decomposeTime = MPI_Wtime();
    int *domains = NULL;
    if (processors == 1) {
        decompose(localPoints, 0, length, domains, 0, k);
    } else {
        decomposePar(&localPoints, numberElemOnCPU, &domains, 0, k, &numberElemOnCPU, MPI_COMM_WORLD);
    }
    decomposeTime = MPI_Wtime() - decomposeTime;
    double maxDecomposeTime = 0.0;
    MPI_Reduce(&decomposeTime, &maxDecomposeTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

//    int localEdges = countEdges(domains, localPoints, numberElemOnCPU, n2);
//    int totalEdges = 0;
//    MPI_Reduce(&localEdges, &totalEdges, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        std::cout << "Size (elements): " << length << std::endl;
//        std::cout << "Processors: " << processors << std::endl;
//        std::cout << "Decompose time (sec): " << maxDecomposeTime << std::endl;
//        std::cout << "Total edges: " << totalEdges << std::endl;
//        std::cout << "Cutted edges: " << n1 * (n2 - 1) + n2 * (n1 - 1) - totalEdges << std::endl;
//    }


//    int count = 0;
//    PointDomain *res = new PointDomain[numberElemOnCPU];
//    for (int i = 0; i < numberElemOnCPU; i++) {
//        if (localPoints[i].index == -1)
//            continue;
//        res[count].coord[0] = localPoints[i].coord[0];
//        res[count].coord[1] = localPoints[i].coord[1];
//        res[count].i = localPoints[i].index / n2;
//        res[count].j = localPoints[i].index % n2;
//        res[count].domain = domains[i];
//        count++;
//    }
//
//    saveResults(res, count, argv[4], n1, n2, rank);

    //Free up the type
    //MPI_Type_free(&MPI_PointType);
    //MPI_Type_free(&MPI_PointDomainType);

    delete[] domains;
    delete[] localPoints;
    MPI_Finalize();

    return 0;
}

