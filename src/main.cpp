#include <iostream>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stddef.h>
#include <mpi.h>
#include "sortingNetwork.h"
#include "point.h"
#include "heapSort.h"
#include "dhSort.h"
#include "decompose.h"

MPI_Datatype MPI_PointType;
MPI_Datatype MPI_PointDomainType;

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
void fillCoord(int realLength, int length, Point *points, int n2) {
    int indx;
    for (indx = 0; indx < realLength; ++indx) {
        int i = indx / n2;
        int j = indx % n2;
        points[indx] = *(createPoint(
                getNextCoordinate(i, j),
                getNextCoordinate(i, j),
                i*n2+j
        ));
    }

    // Add dummy points
    for (; indx < length; ++indx) {
        points[indx] = *(createPoint(
                FLT_MAX,
                FLT_MAX,
                -1
        ));
    }
}

void saveResults(PointDomain *array, int n, char *filename, int n1, int n2, int rank) {
    MPI_Status status;

    MPI_File output;
    if(MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE |
                                               MPI_MODE_WRONLY, MPI_INFO_NULL, &output) != MPI_SUCCESS){
        if(rank == 0) {
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
        std::cout << "A dimension of a network (n1, n2), number of domains or a file's name wasn't passed to the program!\n";
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

    int realLength = length;
    if (length % processors != 0) {
        do {
            ++length;
        } while (length % processors != 0);
    }

    Point *sortArray;
    if (rank == 0) {
        sortArray = new Point[length];
        fillCoord(realLength, length, sortArray, n2);
    }

    int numberElemOnCPU = length / processors;
    Point *localPoints = new Point[numberElemOnCPU];

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
    createMPI_PointDomainType();

    MPI_Scatter(sortArray, numberElemOnCPU, MPI_PointType, localPoints, numberElemOnCPU, MPI_PointType, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    double decomposeTime = MPI_Wtime();
    int axis = 1;
    int *domains = new int[length];
    if(processors == 1) {
        decompose(sortArray, 0, length, domains, 0, k, &axis);
        /*for(int i = 0; i < length; ++i){
            std::cout << i << "   " << domains[i] << std::endl;
        }*/
    } else {
        decomposePar(&localPoints, numberElemOnCPU, &domains, 0, k, &numberElemOnCPU,
                     &MPI_PointType, MPI_COMM_WORLD, &axis);
    }
//    decomposeTime = MPI_Wtime() - decomposeTime;
//    double maxDecomposeTime = 0.0;
//    MPI_Reduce(&decomposeTime, &maxDecomposeTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
//
//    int localEdges = countEdges(domains, localPoints, numberElemOnCPU, n2);
//    int totalEdges = 0;
//    MPI_Reduce(&localEdges, &totalEdges, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

//    if (rank == 0) {
//        std::cout << "Size (elements): " << length << std::endl;
//        std::cout << "Processors: " << processors << std::endl;
//        std::cout << "Decompose time (sec): " << maxDecomposeTime << std::endl;
//        std::cout << "Cutted edges: " << n1 * (n2 - 1) + n2 * (n1 - 1) - totalEdges << std::endl;
//    }



//    int count = 0;
//    PointDomain *res = new PointDomain[numberElemOnCPU];
//    for(int i = 0; i < numberElemOnCPU; i++){
//        if(localPoints[i].index == -1)
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
    MPI_Type_free(&MPI_PointType);
    MPI_Type_free(&MPI_PointDomainType);
    if (rank == 0) {
        delete[] sortArray;
    }
    delete[] domains;
    delete[] localPoints;
    MPI_Finalize();

    return 0;
}

