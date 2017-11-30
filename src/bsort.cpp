#include "../include/bsort.h"

void swap(int_vec_t &arr, int left, int right) {
    if (arr[left] > arr[right]) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
    }
}

void sort(SortingNetwork &network){
    permutation_vec_t schedule = network.getPermutations();
    
    for(int i = 0; i < schedule.size(); ++i){
        
    }
}



