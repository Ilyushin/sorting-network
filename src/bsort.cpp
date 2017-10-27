#include <iostream>
#include <math.h>
#include <vector>

typedef std::vector<int> int_vec_t;
typedef std::vector<int>::iterator int_vec_itr;

int checkPar(int_vec_t &arr, int i, int j);

int main(int argc, char *argv[]) {
    int n = 0;

    if (argc >= 2) {
        n = atoi(argv[1]);
    } else {
        std::cout << "Не указано количество элементов n";
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
                        currentComp.push_back(i);
                        currentComp.push_back(i + d);
                        ++numberTacts;
                    } else {
                        currentComp.push_back(i);
                        currentComp.push_back(i + d);
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

    return 0;
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

