#include <iostream>
#include <sortingNetwork.h>
#include "point.h"

typedef std::vector<Point> point_vec_t;

void fillCoord(point_vec_t &points, const int *n1, const int *n2);

float getNextCoordinate(int counter, int delta);

int main(int argc, char *argv[]) {

    int n1 = 0;
    int n2 = 0;

    if (argc >= 3) {
        n1 = atoi(argv[1]);
        n2 = atoi(argv[2]);
    } else {
        std::cout << "A dimension of a network (n1, n2) wasn't passed to the program!";
        return 0;
    }

    if (n1 > INT_MAX / n2) {
        std::cout << "A dimension of a network (n1, n2) is too big for calculating!";
        return 0;
    }

    int size = n1 * n2;

    SortingNetwork network = SortingNetwork(size);
    network.buildSchedule();

    point_vec_t points;
    fillCoord(points, &n1, &n2);

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
