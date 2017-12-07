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


int main(int argc, char *argv[]) {

    //PARALLEL AREA

    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int processors;
    MPI_Comm_size(MPI_COMM_WORLD, &processors);

    if(rank == 0) {
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

        int size = n1 * n2;
        // Check the size is even or not
        // If it's not, creating a dummy point
        bool needDummy = false;
        if(size % 2 != 0){
            needDummy = true;
        }

        SortingNetwork network = SortingNetwork(size+1);
        network.buildSchedule();

        point_vec_t points;
        fillCoord(points, &n1, &n2);



    }

    MPI_Finalize();

    return 0;
}

void fillCoord(point_vec_t &points, const int *n1, const int *n2) {
    for (int i = 0, j = 1; i < *n1 || j < *n2; ++i, ++j) {
        points.push_back(*new Point(
                getNextCoordinate(i, 1),
                getNextCoordinate(j, 1),
                (i * (*n2) + j)));

    }
}

float getNextCoordinate(int counter, int delta) {
    return (float) (counter - 1) * delta;
}
