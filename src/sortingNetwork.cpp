#include "../include/sortingNetwork.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

SortingNetwork::SortingNetwork(){
    _size = 0;
    _numberTacts = 0;
}

SortingNetwork::SortingNetwork(int n){
    _size = n;
    _numberTacts = 0;
}

void SortingNetwork::buildSchedule(){
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
                        for(int i = 0; i < currentComp.size(); ++i){
                            _permutations.push_back(currentComp[i]);
                        }
                        currentComp.clear();
                        ++_numberTacts;
                    }

                    Permutation newPerm = *new Permutation(left, right);
                    currentComp.push_back(newPerm);


                    /*if (arr.size() > 0) {
                        swap(arr, left, right);
                    }*/
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
    for(int i = 0; i<currentComp.size(); ++i){
        Permutation curPerm = currentComp[i];
        if(curPerm.getLeft() == left || curPerm.getRight() == right){
            result = true;
            break;
        }
    }

    return result;
}










/*void swap(int_vec_t &arr, int left, int right) {
    if (arr[left] > arr[right]) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
    }
}*/
