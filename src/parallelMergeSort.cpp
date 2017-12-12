#include <iostream>
#include "parallelMergeSort.h"

void merge(int i, int j, Point *arr)
{
    int mid = (i+j)/2;
    int leftI = i;
    int rightI = mid+1;

    //Point newa[j-i+1], newai = 0;
    Point result[j-i+1];
    int index = 0;

    while(leftI <= mid && rightI <= j) {
        if (arr[leftI].x > arr[rightI].x)
            result[index++] = arr[rightI++];
        else
            result[index++] = arr[leftI++];
    }

    while(leftI <= mid) {
        result[index++] = arr[leftI++];
    }

    while(rightI <= j) {
        result[index++] = arr[rightI++];
    }

    for (leftI = 0; leftI < (j-i+1) ; leftI++)
        arr[i+leftI] = result[leftI];

}

void *sort(void *arguments) {

    ThreadArgs *threadArgs = (ThreadArgs *)arguments;
    int mid = (threadArgs->chunk->i+threadArgs->chunk->j)/2;

    ThreadArgs threadArgs1, threadArgs2;
    threadArgs1.arr = threadArgs->arr;
    threadArgs2.arr = threadArgs->arr;

    Chunk chunk1 = {
            threadArgs->chunk->i,
            mid,
    };

    Chunk chunk2 = {
            mid+1,
            threadArgs->chunk->j,
    };

    threadArgs1.chunk = &chunk1;
    threadArgs2.chunk = &chunk2;

    pthread_t tid1, tid2;
    int ret;
    if (threadArgs->chunk->i >= threadArgs->chunk->j) return 0;

    ret = pthread_create(&tid1, NULL, sort, &threadArgs1);
    if (ret) {
        std::cout << __LINE__ << " function: " << __FUNCTION__ << " - unable to create thread - ret - " << ret << std::endl;
        exit(1);
    }


    ret = pthread_create(&tid2, NULL, sort, &threadArgs2);
    if (ret) {
        std::cout << __LINE__ << ' ' << __FUNCTION__ << " - unable to create thread - ret - " << ret << std::endl;
        exit(1);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    merge(threadArgs->chunk->i, threadArgs->chunk->j, threadArgs->arr);
    pthread_exit(NULL);

}

void parallelMergeSort(int length, Point *arr, bool byY) {
    Chunk chunkArray = {
            0,
            length - 1,
    };
    pthread_t tid;

    ThreadArgs threadArgs = {
            &chunkArray,
            arr,
    };

    int ret = pthread_create(&tid, NULL, sort, &threadArgs);
    if (ret) {
        std::cout << __LINE__ << ' ' << __FUNCTION__ << " - unable to create thread - ret - " << ret << std::endl;
        exit(1);
    }

    pthread_join(tid, NULL);
}