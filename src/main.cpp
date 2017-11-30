#include <iostream>
#include <sortingNetwork.h>

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

    SortingNetwork network = SortingNetwork(n);
    network.buildSchedule();

    return 0;
}
