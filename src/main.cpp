#include <iostream>
#include <sortingNetwork.h>
#include <mpi.h>
#include "point.h"

typedef std::vector<Point> point_vec_t;

// Iterate since 0 to n1, 1 to n2 and create Points of a grid
void fillCoord(point_vec_t &points, const int *n1, const int *n2);

// Returns a next coordinate which was calculated using a function:
//      coord = (counter - 1)*delta
float getNextCoordinate(int counter, int delta);

//TODO Move some piece of code to macroses or function
int main(int argc, char *argv[]) {

    //PARALLEL AREA

    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int processors;
    MPI_Comm_size(MPI_COMM_WORLD, &processors);

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

    point_vec_t points;
    fillCoord(points, &n1, &n2);

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


    //}

    MPI_Finalize();

    return 0;
}

void fillCoord(point_vec_t &points, const int *n1, const int *n2) {
    for (int i = 0, j = 1; i < *n1 || j < *n2; ++i, ++j) {
        points.push_back(*createPoint(
                getNextCoordinate(i, 1),
                getNextCoordinate(j, 1),
                (i * (*n2) + j)));

    }
}

float getNextCoordinate(int counter, int delta) {
    return (float) (counter - 1) * delta;
}
