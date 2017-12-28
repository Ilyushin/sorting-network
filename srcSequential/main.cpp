#include <iostream>
#include <limits.h>
#include <string.h>
#include <stddef.h>
#include <mpi.h>
#include <omp.h>
#include "point.h"
#include "quickSort.h"

// Returns a next coordinate which was calculated using a function:
//      coord = (counter - 1)*delta
float getNextCoordinate(int i, int j) {
    return (rand() / (float) RAND_MAX * i) + j;
}

// Iterate since 0 to n1, 1 to n2 and create Points of a grid
void fillCoord(int length, Point *points) {
    int i, j;
    for (i = 0, j = 0; i < length; ++i, ++j) {
        points[i] = *(createPoint(
                getNextCoordinate(i, j),
                getNextCoordinate(i, j),
                i
        ));
    }
}

int main(int argc, char *argv[]) {

    int n1 = 0;
    int n2 = 0;
    int k = 0; // Number of domains

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

    int length = n1 * n2;

    //PARALLEL AREA
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int processors;
    MPI_Comm_size(MPI_COMM_WORLD, &processors);

    Point *sortArray;
    if (rank == 0) {
        sortArray = new Point[length];
        fillCoord(length, sortArray);


        double execTime;
        execTime = MPI_Wtime();

        quickSort(length, sortArray);

        execTime = MPI_Wtime() - execTime;
        std::cout << "Time of sorting " << length << " elements on a CPU: " << execTime << std::endl;

        delete[] sortArray;
    }

    MPI_Finalize();

    return 0;
}

