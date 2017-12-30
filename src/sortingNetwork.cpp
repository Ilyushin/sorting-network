#include <iostream>
#include <math.h>
#include <omp.h>
#include "sortingNetwork.h"
#include "heapSort.h"
#include "dhSort.h"

SortingNetwork::SortingNetwork() {
    _size = 0;
    _numberTacts = 0;
}

SortingNetwork::SortingNetwork(int n) {
    _size = n;
    _numberTacts = 0;
}

void SortingNetwork::buildSchedule() {
    _permutations.clear();

    int_vec_t arr;
    if (_size == 1) {
        return;
    }

    if (_size == 2) {
        _numberTacts = 1;
        _permutations.push_back(*new Permutation(0, 1));

        return;
    }

    _numberTacts = 1;
    permutation_vec_t currentComp;

    int t = ceil(log2(_size));//2^t >= n
    int p = pow(2, t - 1);//Step
    int left, right;

    while (p > 0) {
        int q = pow(2, t - 1);
        int r = 0;
        int d = p;

        while (d > 0) {
            for (int i = 0; i < _size - d; ++i) {
                if ((i & p) == r) {
                    left = i;
                    right = i + d;
                    if (_checkPar(currentComp, left, right)) {
                        //Copy to _permutations
                        for (unsigned int i = 0; i < currentComp.size(); ++i) {
                            _permutations.push_back(currentComp[i]);
                        }
                        currentComp.clear();
                        ++_numberTacts;
                    }

                    Permutation newPerm = *new Permutation(left, right);
                    currentComp.push_back(newPerm);
                }
            }

            d = q - p;
            q /= 2;
            r = p;
        }
        p /= 2;
    }

}

bool SortingNetwork::_checkPar(permutation_vec_t &currentComp, int left, int right) {
    bool result = false;
    for (unsigned int i = 0; i < currentComp.size(); ++i) {
        Permutation curPerm = currentComp[i];
        if (curPerm.getLeft() == left || curPerm.getRight() == right) {
            result = true;
            break;
        }
    }

    return result;
}

void SortingNetwork::sortBySchedule(Point **localPoints, int numberElemOnCPU, MPI_Datatype *MPI_PointType,
                                    MPI_Comm communicator, int processors, int axis) {
    int rank;
    MPI_Comm_rank(communicator, &rank);

    int threads = 0;
    #pragma omp parallel
    {
        threads = omp_get_num_threads();
    }

    if (numberElemOnCPU <= 50000) {
        heapSort(numberElemOnCPU, *localPoints);
    } else {
        dhSortPar(numberElemOnCPU, *localPoints, false, threads);
    }

    Point *gettingPoints = new Point[numberElemOnCPU];
    Point *resultPoints = new Point[numberElemOnCPU];


    std::cout << "Before #rank" << rank <<": "<< std::endl;
    for(int i = 0; i < numberElemOnCPU; ++i){
        std::cout << (*localPoints)[i].coord[0] << std::endl;
    }

    MPI_Status status;
    for (unsigned int i = 0; i < _permutations.size(); ++i) {
        if (_permutations[i].getLeft() == rank) {
            MPI_Send(*localPoints, numberElemOnCPU, *MPI_PointType, _permutations[i].getRight(), 0, communicator);
            MPI_Recv(gettingPoints, numberElemOnCPU, *MPI_PointType, _permutations[i].getRight(), 0, communicator,
                     &status);

            int locIndx = 0;
            int getIndx = 0;
            for (int i = 0; i < numberElemOnCPU; ++i) {
                if ((*localPoints)[locIndx].coord[axis] > gettingPoints[getIndx].coord[axis]) {
                    resultPoints[i] = gettingPoints[getIndx];
                    ++getIndx;
                } else {
                    resultPoints[i] = (*localPoints)[locIndx];
                    ++locIndx;
                }
            }

        } else if (_permutations[i].getRight() == rank) {
            MPI_Recv(gettingPoints, numberElemOnCPU, *MPI_PointType, _permutations[i].getLeft(), 0, communicator,
                     &status);
            MPI_Send(*localPoints, numberElemOnCPU, *MPI_PointType, _permutations[i].getLeft(), 0, communicator);

            int locIndx = numberElemOnCPU - 1;
            int getIndx = numberElemOnCPU - 1;
            for (int i = numberElemOnCPU - 1; i >= 0; --i) {
                if ((*localPoints)[locIndx].coord[axis] < gettingPoints[getIndx].coord[axis]) {
                    resultPoints[i] = gettingPoints[getIndx];
                    --getIndx;
                } else {
                    resultPoints[i] = (*localPoints)[locIndx];
                    --locIndx;
                }

            }
        }
    }

    *localPoints = resultPoints;
    delete[] gettingPoints;
    //delete[] resultPoints;

    MPI_Barrier(communicator);
    std::cout << "After #rank" << rank <<": "<< std::endl;
    for(int i = 0; i < numberElemOnCPU; ++i){
        std::cout << (*localPoints)[i].coord[0] << std::endl;
    }
}