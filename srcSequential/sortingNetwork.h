#ifndef SORTINGNETWORK_SORTINGNETWORK_H
#define SORTINGNETWORK_SORTINGNETWORK_H

#include <vector>
#include "permutation.h"

typedef std::vector<int> int_vec_t;
typedef std::vector<int>::iterator int_vec_itr;
typedef std::vector<Permutation> permutation_vec_t;

class SortingNetwork {
private:
    int _size;
    int _numberTacts;
    permutation_vec_t _permutations;

    bool _checkPar(permutation_vec_t &currentComp, int left, int right);

public:
    SortingNetwork();
    SortingNetwork(int n);

    int getSize() { return _size; };
    int getTacts() { return _numberTacts; };
    permutation_vec_t getPermutations() { return _permutations; };

    void buildSchedule();
};
#endif //SORTINGNETWORK_SORTINGNETWORK_H
