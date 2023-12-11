#include <iostream>
#include "mps_lib/mps.h"
#include <chrono>

using namespace std;

int main() {

    for (int i = 0; i < 100; i++) {

        bool test_1[i];
        bool test_2[i];
        bool test_3[i];

        for (int i = 0; i < sizeof(test_1); i++) {
            test_1[i] = i % 3;
            test_2[i] = i % 2;
        }

        chrono::milliseconds t_1 = duration_cast<chrono::milliseconds>(
                chrono::system_clock::now().time_since_epoch()
        );

        for (int i = 0; i < 10000000; i++) {
            for (int j = 0; j < sizeof(test_1); j++) {
                test_3[j] = test_1[j] & test_2[j];
            }
        }

        chrono::milliseconds t_2 = duration_cast<chrono::milliseconds>(
                chrono::system_clock::now().time_since_epoch()
        );

        chrono::milliseconds t = t_2 - t_1;

        std::cout << t.count() << std::endl;
    }
}
