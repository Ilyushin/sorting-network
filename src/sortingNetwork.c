#include <stdio.h>
#include <stdlib.h>

typedef struct comparator {
    int i;
    int j;
} comparator;

void getSchedule(int start, int end);

void merge(int start, int pivotStart, int end, int pivotEnd, int step);

int main(int argc, char *argv[]) {
    int n = 0;

    if (argc >= 2) {
        n = atoi(argv[1]);
    } else {
        puts("Need to pass a size of an array");
        return 0;
    }

    getSchedule(0, n);

    return 0;
}

void getSchedule(int start, int end) {
    if (end - start < 2) return;

    int pivot = (start + end) / 2 | 0;

    getSchedule(start, pivot);
    getSchedule(pivot, end);
    merge(start, pivot, pivot, end, 1);
}

void merge(int start, int pivotStart, int end, int pivotEnd, int step) {
    int nextStep = step * 2;

    int m = pivotStart - start;
    int n = pivotEnd - end;

    if (m <= 0 || n <= 0) {
        return;
    } else if (m <= step && n <= step) {
        printf("[%d, %d]\n", start, end);
    } else {

        merge(start, pivotStart , end   , pivotEnd, nextStep ) ;
        merge( start + step , pivotStart , end + step, pivotEnd, nextStep ) ;

        for ( start += step , pivotStart -= step ; start < pivotStart ; start += nextStep ) {
            printf("[%d, %d]\n", start, start+step);
        }

//        //handles the case when we want to merge
        if ( start < pivotStart + step ) {
            printf("[%d, %d]\n", start, end);
            end += step;
        }

        for ( pivotEnd -= step ; end < pivotEnd ; end += nextStep ) {
            printf("[%d, %d]\n", end, end+step);
        }

    }
}
