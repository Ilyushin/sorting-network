#include <iostream>
#include <sortingNetwork.h>
#include <mpi.h>
#include "../include/point.h"
#include "../include/quickSort.h"
#include "../include/heapSort.h"
#include "../include/parallelMergeSort.h"

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
        points[i] = *createPoint(
                getNextCoordinate(i, j),
                getNextCoordinate(i, j),
                i
        );
    }

    // Add dummy points
    for (; i < length; ++i) {
        points[i] = *createPoint(
                -1,
                -1,
                -1
        );
    }
}

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

    bool useQSort = false;
    if (argc >= 4) {
        for (int i = 3; i < argc; ++i) {
            if (strcmp(argv[i], "-q") == 0) {
                useQSort = true;
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

    Point sortArray[length];
    if (rank == 0) {
        fillCoord(realLength, length, sortArray);
    }

    int numberElem = length / processors;
    Point localPoints[numberElem];

    // Create a new type of MPI
    const int n = 3;
    int blocklengths[n] = {1, 1, 1};
    MPI_Datatype types[n] = {MPI_DOUBLE, MPI_DOUBLE, MPI_INT};
    MPI_Datatype MPI_PointType_proto, MPI_PointType;
    MPI_Aint offsets[n];

    offsets[0] = offsetof(Point, x);
    offsets[1] = offsetof(Point, y);
    offsets[2] = offsetof(Point, index);

    MPI_Type_create_struct(n, blocklengths, offsets, types, &MPI_PointType_proto);

    // Resize the type so that its length matches the actual structure length

    // Get the constructed type lower bound and extent
    MPI_Aint lb, extent;
    MPI_Type_get_extent(MPI_PointType_proto, &lb, &extent);

    // Get the actual distance between to vector elements
    // (this might not be the best way to do it - if so, substitute a better one)
    extent = (char *) &localPoints[1] - (char *) &localPoints[0];

    // Create a resized type whose extent matches the actual distance
    MPI_Type_create_resized(MPI_PointType_proto, lb, extent, &MPI_PointType);
    MPI_Type_commit(&MPI_PointType);

    MPI_Scatter(sortArray, numberElem, MPI_PointType, &localPoints, numberElem, MPI_PointType, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    std::cout << "Before, CPU #" << rank << ":" << std::endl;
    for (int i = 0; i < numberElem; ++i) {
        std::cout << i << " " << localPoints[i].x << std::endl;
    }

    if (numberElem <= 50000) {
        if (useQSort) {
            quickSort(numberElem, localPoints);
        } else {
            heapSort(numberElem, localPoints);
        }
    } else {
        parallelMergeSort(numberElem, localPoints);
    }

    std::cout << std::endl;

    if (processors > 1) {

        SortingNetwork *network = new SortingNetwork(processors);
        network->buildSchedule();
        permutation_vec_t permutation = network->getPermutations();

        Point gettingPoints[numberElem];
        Point resultPoints[numberElem];

        MPI_Status status;
        for (int i = 0; i < permutation.size(); ++i) {
            Permutation curPerm = permutation[i];
            if (curPerm.getLeft() == rank) {
                MPI_Send(localPoints, numberElem, MPI_PointType, curPerm.getRight(), 0, MPI_COMM_WORLD);
                MPI_Recv(gettingPoints, numberElem, MPI_PointType, curPerm.getRight(), 0, MPI_COMM_WORLD, &status);

                for (int i = 0, j = numberElem - 1; i < numberElem; ++i, --j) {

                    if (localPoints[i].x > gettingPoints[j].x) {
                        resultPoints[i] = gettingPoints[j];
                    } else {
                        resultPoints[i] = localPoints[i];
                    }
                }

            } else if (curPerm.getRight() == rank) {
                MPI_Recv(gettingPoints, numberElem, MPI_PointType, curPerm.getLeft(), 0, MPI_COMM_WORLD, &status);
                MPI_Send(localPoints, numberElem, MPI_PointType, curPerm.getLeft(), 0, MPI_COMM_WORLD);

                for (int i = 0, j = numberElem - 1; i < numberElem; ++i, --j) {
                    if (localPoints[j].x < gettingPoints[i].x) {
                        resultPoints[j] = gettingPoints[i];
                    } else {
                        resultPoints[j] = localPoints[j];
                    }
                }
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);

        if (useQSort) {
            quickSort(numberElem, resultPoints);
        } else {
            heapSort(numberElem, resultPoints);
        }

        std::cout << "After, CPU #" << rank << ":" << std::endl;
        for (int i = 0; i < numberElem; ++i) {
            std::cout << i << " " << resultPoints[i].x << std::endl;
        }

    } else {
        std::cout << "After, CPU #" << rank << ":" << std::endl;
        for (int i = 0; i < numberElem; ++i) {
            std::cout << i << " " << localPoints[i].x << std::endl;
        }
    };

    MPI_Barrier(MPI_COMM_WORLD);
    //Free up the type
    MPI_Type_free(&MPI_PointType);




    std::cout << std::endl;

    MPI_Finalize();

    return 0;
}