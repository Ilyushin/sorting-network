#include <gtest/gtest.h>
#include "../../src/sortingNetwork.h"

int checkArr(int_vec_t &arr) {
    int result = 1;
    if (arr.size() <= 1) {
        return result;
    }

    int currentValue = arr[0];
    int count = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (currentValue != arr[i]) {
            if (count == 1) {
                return 0;
            } else {
                currentValue = arr[i];
                ++count;
            }
        }
    }
    return result;
}

 TEST(SortingNetwork, PossiblePermutations) {
//    for (int n = 2; n <= 24; ++n) {
//        for (int i = 0; i < n; ++i) {
//            int_vec_t arr(n);
//            int_vec_t copyArr(n);
//            std::fill(arr.begin(), arr.begin() + i, 1);
//            std::sort(arr.begin(), arr.end());
//            do {
//                copyArr.clear();
//                std::copy(arr.begin(), arr.end(), copyArr.begin());
//                sort(n, copyArr);
//                EXPECT_EQ(1, checkArr(copyArr));
//                std::cout << std::endl;
//            } while (std::next_permutation(arr.begin(), arr.end()));
//            std::cout << std::endl;
//        }
//    }
};

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

