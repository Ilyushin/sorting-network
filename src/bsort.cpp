#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

typedef std::vector<int> int_vec_t;
typedef std::vector<int>::iterator int_vec_itr;

void sort(int n, int_vec_t &arr);

int checkPar(int_vec_t &arr, int i, int j);

void swap(int_vec_t &arr, int left, int right);

int checkArr(int_vec_t &arr);

int main(int argc, char *argv[]) {

    int n = 0;

    if (argc >= 2) {
        n = atoi(argv[1]);
    } else {
        std::cout << "Не указано количество элементов n";
        return 0;
    }

    if (n > 10000) {
        std::cout << "Расчет сети для количества элементов > 10000 не предусмотрен.";
        return 0;
    }

    std::cout << n << " 0 0\n";

    if (n == 1) {
        std::cout << "0\n 0\n";
        return 0;
    } else if (n == 2) {
        std::cout << "1\n 1\n";
        return 0;
    }

    int_vec_t arr;
    sort(n, arr);


    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void sort(int n, int_vec_t &arr) {

    if (n == 1) {
        std::cout << "0\n 0\n";
        std::cout << 0 << std::endl;
        std::cout << 0 << std::endl;
        return;
    }

    if (n == 2) {
        swap(arr, 0, 1);
        std::cout << 0 << " " << 1 << std::endl;
        std::cout << 1 << std::endl;
        std::cout << 1 << std::endl;
        return;
    }

    int numberTacts = 1;
    int numberComparators = 0;
    int_vec_t currentComp;

    int t = ceil(log2(n));//2^t >= n
    int p = pow(2, t - 1);//Step
    int left, right;

    while (p > 0) {
        int q = pow(2, t - 1);
        int r = 0;
        int d = p;

        while (d > 0) {
            for (int i = 0; i < n - d; ++i) {
                if ((i & p) == r) {
                    left = i;
                    right = i + d;
                    if (checkPar(currentComp, left, right) == 1) {
                        currentComp.clear();
                        ++numberTacts;
                    }
                    currentComp.push_back(left);
                    currentComp.push_back(right);

                    if (arr.size() > 0) {
                        swap(arr, left, right);
                    }

                    std::cout << left << " " << right << std::endl;
                    ++numberComparators;
                }
            }

            d = q - p;
            q /= 2;
            r = p;
        }
        p /= 2;
    }

    std::cout << numberComparators << std::endl;
    std::cout << numberTacts << std::endl;
}

int checkPar(int_vec_t &arr, int left, int right) {
    int_vec_itr result = std::find(arr.begin(), arr.end(), left);
    if (result != arr.end()) {
        return 1;
    };

    result = std::find(arr.begin(), arr.end(), right);
    if (result != arr.end()) {
        return 1;
    };

    return 0;
}

void swap(int_vec_t &arr, int left, int right) {
    if (arr[left] > arr[right]) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
    }
}

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
                currentValue != arr[i];
                ++count;
            }
        }
    }
    return result;
}

TEST(BasicTest, PossiblePermutations) {
    for (int n = 2; n <= 24; ++n) {
        for (int i = 0; i < n; ++i) {
            int_vec_t arr(n);
            int_vec_t copyArr(n);
            std::fill(arr.begin(), arr.begin() + i, 1);
            std::sort(arr.begin(), arr.end());
            do {
                copyArr.clear();
                std::copy(arr.begin(), arr.end(), copyArr.begin());
                sort(n, copyArr);
                EXPECT_EQ(1, checkArr(copyArr));
                std::cout << std::endl;
            } while (std::next_permutation(arr.begin(), arr.end()));
            std::cout << std::endl;
        }
    }
};


