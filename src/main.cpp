#include <iostream>
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

//typedef std::vector<Point> point_vec_t;

// Returns a next coordinate which was calculated using a function:
//      coord = (counter - 1)*delta
float getNextCoordinate(int i, int j) {
    return (rand() / (float) RAND_MAX * i) + j;
}

// Iterate since 0 to n1, 1 to n2 and create Points of a grid
void fillCoord(int realLength, int length, Point *points) {
    int i, j;
    for (i = 0, j = 0; i < realLength; ++i, ++j) {
        points[i] = *(createPoint(
                getNextCoordinate(i, j),
                getNextCoordinate(i, j),
                i
        ));
    }

    // Add dummy points
    for (; i < length; ++i) {
        points[i] = *(createPoint(
                -1,
                -1,
                -1
        ));
    }
}

//TODO Move some piece of code to macroses or function
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

    int realLength = length;
    if (length % processors != 0) {
        do {
            ++length;
        } while (length % processors != 0);
    }

    Point *sortArray;
    if (rank == 0) {
        sortArray = new Point[length];
        fillCoord(realLength, length, sortArray);
    }

    int numberElem = length / processors;
    Point *localPoints = new Point[numberElem];

    // Create a new type of MPI
    const int n = 2;
    int blocklengths[n] = {2, 1};
    MPI_Datatype types[n] = {MPI_FLOAT, MPI_INT};
    MPI_Datatype MPI_PointType_proto, MPI_PointType;
    MPI_Aint offsets[n];

    offsets[0] = offsetof(Point, coord);
    offsets[1] = offsetof(Point, index);

    MPI_Type_create_struct(n, blocklengths, offsets, types, &MPI_PointType_proto);

    // Resize the type so that its length matches the actual structure length

    // Get the constructed type lower bound and extent
    MPI_Aint lb, extent;
    MPI_Type_get_extent(MPI_PointType_proto, &lb, &extent);

    // Get the actual distance between to array elements
    extent = (char *) &localPoints[1] - (char *) &localPoints[0];

    // Create a resized type whose extent matches the actual distance
    MPI_Type_create_resized(MPI_PointType_proto, lb, extent, &MPI_PointType);
    MPI_Type_commit(&MPI_PointType);

    double sharedTime = MPI_Wtime();

    MPI_Scatter(sortArray, numberElem, MPI_PointType, localPoints, numberElem, MPI_PointType, 0, MPI_COMM_WORLD);

    sharedTime = MPI_Wtime() - sharedTime;


    double sortingTime = MPI_Wtime();

    int threads = 0;
    #pragma omp parallel
    {
        threads = omp_get_num_threads();
    }


    if (useQSort) {
        quickSort(numberElem, localPoints);
    } else if (useHeap) {
        heapSort(numberElem, localPoints);
    } else if (usePar) {
        dhSortPar(numberElem, localPoints, 0, threads);
    } else {
        if (numberElem <= 50000) {
            heapSort(numberElem, localPoints);
        } else {
            dhSortPar(numberElem, localPoints, false, threads);
        }
    }

    sortingTime = MPI_Wtime() - sortingTime;

    int axis = 0;
    if (processors > 1) {

        SortingNetwork *network = new SortingNetwork(processors);
        network->buildSchedule();
        permutation_vec_t permutation = network->getPermutations();

        Point *gettingPoints = new Point[numberElem];
        Point *resultPoints = new Point[numberElem];

        double batcherTime = MPI_Wtime();
        MPI_Status status;
        for (int i = 0; i < permutation.size(); ++i) {
            //Permutation curPerm = permutation[i];
            if (permutation[i].getLeft() == rank) {
                MPI_Send(localPoints, numberElem, MPI_PointType, permutation[i].getRight(), 0, MPI_COMM_WORLD);
                MPI_Recv(gettingPoints, numberElem, MPI_PointType, permutation[i].getRight(), 0, MPI_COMM_WORLD, &status);

                int locIndx = 0;
                int getIndx = 0;
                for (int i = 0; i < numberElem; ++i) {
                    if (localPoints[locIndx].coord[axis] > gettingPoints[getIndx].coord[axis]) {
                        resultPoints[i] = gettingPoints[getIndx];
                        ++getIndx;
                    } else {
                        resultPoints[i] = localPoints[locIndx];
                        ++locIndx;
                    }
                }

            } else if (permutation[i].getRight() == rank) {
                MPI_Recv(gettingPoints, numberElem, MPI_PointType, permutation[i].getLeft(), 0, MPI_COMM_WORLD, &status);
                MPI_Send(localPoints, numberElem, MPI_PointType, permutation[i].getLeft(), 0, MPI_COMM_WORLD);

                int locIndx = numberElem - 1;
                int getIndx = numberElem - 1;
                for (int i = numberElem - 1; i >= 0; --i) {
                    if (localPoints[locIndx].coord[axis] < gettingPoints[getIndx].coord[axis]) {
                        resultPoints[i] = gettingPoints[getIndx];
                        --getIndx;
                    } else {
                        resultPoints[i] = localPoints[locIndx];
                        --locIndx;
                    }
                }
            }
        }
        batcherTime = MPI_Wtime() - batcherTime;

        double maxSharedTime, maxSortingTime, maxBatcherTime;
        MPI_Reduce(&sharedTime, &maxSharedTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        MPI_Reduce(&sortingTime, &maxSortingTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        MPI_Reduce(&batcherTime, &maxBatcherTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            std::cout << "Time of shared " << length << " elements: " << maxSharedTime << std::endl;
            std::cout << "Time of sorting " << length << " elements on a CPU: " << maxSortingTime << std::endl;
            std::cout << "Time of BatcherSorting " << length << " elements: " << maxBatcherTime << std::endl;
            std::cout << "Time without the shared time  " << length << " elements: " << maxSortingTime + maxBatcherTime
                      << std::endl;
            std::cout << "Full time " << length << " elements: " << maxSharedTime + maxSortingTime + maxBatcherTime
                      << std::endl;
            std::cout << "Tacts number: " << network->getTacts() << std::endl;
            std::cout << "Comparators number: " << permutation.size() << std::endl;
        }

        delete network;
        delete[] gettingPoints;
        delete[] resultPoints;
    };

    MPI_Barrier(MPI_COMM_WORLD);
    //Free up the type
    MPI_Type_free(&MPI_PointType);
    if (rank == 0) {
        delete[] sortArray;
    }
    delete[] localPoints;
    MPI_Finalize();

    return 0;
}

