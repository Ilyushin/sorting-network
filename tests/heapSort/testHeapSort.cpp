#include <gtest/gtest.h>
#include "../../include/heapSort.h"

TEST(HeapSort, Heapify) {
    Point arr[10];
    for(int i = 0; i < 10; ++i){
        arr[i] = createPoint((float) i, (float) i, i);
    }

    heapSort(10, arr, false);


};

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

