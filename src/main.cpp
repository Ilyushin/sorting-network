#include <iostream>
#include <sortingNetwork.h>
#include <mpi.h>
#include "../include/point.h"
#include "../include/heapSort.h"
#include "../include/quickSort.h"

typedef std::vector<Point> point_vec_t;

// Iterate since 0 to n1, 1 to n2 and create Points of a grid
void fillCoord(int size, Point *points, int cpu);

// Returns a next coordinate which was calculated using a function:
//      coord = (counter - 1)*delta
float getNextCoordinate(int i, int j);

//TODO Move some piece of code to macroses or function
int main(int argc, char *argv[]) {

    //if(rank == 0) {
    int n1 = 0;
    int n2 = 0;

    if (argc >= 3) {
        n1 = atoi(argv[1]);
        n2 = atoi(argv[2]);
    } else {
        std::cout << "A dimension of a network (n1, n2) wasn't passed to the program!\n";
        return 0;
    }

    if (n1 > INT_MAX / n2) {
        std::cout << "A dimension of a network (n1, n2) is too big for calculating!\n";
        MPI_Finalize();
        return 0;
    }

    int realSize = n1 * n2;
    int size = realSize;
    // Check the size is even or not
    // If it's not, creating a dummy point
    bool needDummy = false;
    if (realSize % 2 != 0) {
        ++size;
    }

    //PARALLEL AREA
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int processors;
    MPI_Comm_size(MPI_COMM_WORLD, &processors);

    int numberElem = size / processors;
    Point localPoints[numberElem];
    fillCoord(numberElem, localPoints, rank);

    std::cout << "CPU #" << rank << ":" << std::endl;

    if (numberElem <= 50000) {
        heapSort(numberElem, localPoints);
        //quickSort(numberElem, localPoints, false);
    }

    for (int i = 0; i < numberElem; ++i) {
        std::cout << i << " " << localPoints[i].x << std::endl;
    }

    std::cout << std::endl;

    MPI_Finalize();

    return 0;
}

void fillCoord(int size, Point *points, int cpu) {
    int indx = cpu * size;
    for (int i = 0; i < size; ++i) {
        points[i] = *createPoint(
                getNextCoordinate(indx, indx),
                getNextCoordinate(indx, indx),
                indx
        );
        ++indx;
    }
}

float getNextCoordinate(int i, int j) {
    return (rand() / (float) RAND_MAX * i) + j;
}
