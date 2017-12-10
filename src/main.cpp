#include <iostream>
#include <sortingNetwork.h>
#include <mpi.h>
#include "../include/point.h"
#include "../include/heapSort.h"

typedef std::vector<Point> point_vec_t;

// Iterate since 0 to n1, 1 to n2 and create Points of a grid
void fillCoord(int *size, Point *points, const int *n1, const int *n2);

// Returns a next coordinate which was calculated using a function:
//      coord = (counter - 1)*delta
float getNextCoordinate(int i);

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

    SortingNetwork network = SortingNetwork(size);
    network.buildSchedule();

    Point points[size];
    fillCoord(&size, points, &n1, &n2);

    /*for(int i = 0; i < size; ++i){
        std::cout << points[i].x << std::endl;
    }*/

    Point test[10] = {
            *createPoint(1, 1, 0),
            *createPoint(2, 2, 1),
            *createPoint(4, 4, 2),
            *createPoint(5, 5, 3),
            *createPoint(6, 6, 4),
            *createPoint(8, 8, 5),
            *createPoint(9, 9, 6),
            *createPoint(10, 10, 7),
            *createPoint(11, 11, 8),
            *createPoint(16, 16, 9)
    };
    for(int i = 0; i < 10; ++i){
        //test[i] = *createPoint(i, i, i);
        std::cout << test[i].x << std::endl;
    }

    heapSort(10, test, false);

    std::cout << "******** After sort **********" << std::endl;

    for(int i = 0; i < 10; ++i){
        std::cout << test[i].x << std::endl;
    }

    //PARALLEL AREA
    /*MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int processors;
    MPI_Comm_size(MPI_COMM_WORLD, &processors);

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
    extent = (char *) &points[1] - (char *) &points[0];

    // Create a resized type whose extent matches the actual distance
    MPI_Type_create_resized(MPI_PointType_proto, lb, extent, &MPI_PointType);
    MPI_Type_commit(&MPI_PointType);

    int numberElem = size / processors;
    Point localPoints[numberElem];
    MPI_Scatter(&points.front(), numberElem, MPI_PointType, &localPoints, numberElem, MPI_PointType, 0, MPI_COMM_WORLD);

    std::cout << "CPU #" << rank << ":" << std::endl;
    for (int i = 0; i < numberElem; ++i) {
        std::cout << localPoints[i].x << std::endl;
    }

    std::cout << std::endl;

    //Free up the type
    MPI_Type_free(&MPI_PointType);

    MPI_Finalize();*/

    return 0;
}

void fillCoord(int *size, Point *points, const int *n1, const int *n2) {
    for (int i = 0, j = 0; i < *size; ++i, ++j) {
        points[i] = *createPoint(
                getNextCoordinate(j),
                getNextCoordinate(j),
                (i)
        );

    }

    /*for (int i = 0, j = *size - 1; i < *size; ++i, --j) {
        points[i] = *createPoint(
                getNextCoordinate(j),
                getNextCoordinate(j),
                (i)
        );

    }*/
}

float getNextCoordinate(int i) {
    float random = ((float) rand()) / (float) RAND_MAX;
    return random + i;
}
