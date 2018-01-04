#include <iostream>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include <stddef.h>
#include <mpi.h>
#include <omp.h>
#include "sortingNetwork.h"
#include "point.h"
#include "quickSort.h"
#include "heapSort.h"
#include "dhSort.h"

MPI_Datatype MPI_PointType;

float getNextCoordinate(int i, int j) {
    return (rand() / (float) RAND_MAX * i) + j;
}

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

int main(int argc, char *argv[]) {

    int n1 = 0;
    int n2 = 0;
    //int k = 0; // Number of domains

    if (argc >= 3) {
        n1 = atoi(argv[1]);
        n2 = atoi(argv[2]);
    } else {
        std::cout << "A dimension of a network (n1, n2) wasn't passed to the program!\n";
        return 0;
    }

    bool useQSort = false;
    bool useHeap = false;
    bool usePar = false;
    if (argc >= 3) {
        for (int i = 3; i < argc; ++i) {
            if (strcmp(argv[i], "q") == 0) {
                useQSort = true;
                break;
            } else if (strcmp(argv[i], "h") == 0) {
                useHeap = true;
                break;
            } else if (strcmp(argv[i], "p") == 0) {
                usePar = true;
                break;
            }
        }
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

    int axis = 0;
    if (processors > 1) {

        double sortingTime = MPI_Wtime();
        SortingNetwork *network = new SortingNetwork(processors);
        network->buildSchedule();
        permutation_vec_t permutation = network->getPermutations();
        network->sortBySchedule(&localPoints, numberElemOnCPU, &MPI_PointType, MPI_COMM_WORLD, axis);
        sortingTime = MPI_Wtime() - sortingTime;

        double maxSortingTime;
        MPI_Reduce(&sortingTime, &maxSortingTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            std::cout << "Full time " << length << " elements: " << maxSortingTime << std::endl;
            std::cout << "Tacts number: " << network->getTacts() << std::endl;
            std::cout << "Comparators number: " << permutation.size() << std::endl;
        }

        delete network;

    } else {
        double sortingTime = MPI_Wtime();
        quickSort(numberElemOnCPU, localPoints, false);
        sortingTime = MPI_Wtime() - sortingTime;
        std::cout << "Full time " << length << " elements: " << sortingTime << std::endl;
    };

    MPI_Barrier(MPI_COMM_WORLD);
    //Free up the type
    MPI_Type_free(&MPI_PointType);
    delete[] localPoints;
    MPI_Finalize();

    return 0;
}

