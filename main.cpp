#include <iostream>
#include "mps_lib/mps.h"
#include <chrono>

using namespace std;

int main() {


 bool test_1[1000];
 bool test_2[1000];

    for(int i = 0; i < sizeof(test_1); i++){
        test_1[i] = i%3;
        test_2[i] = i%2;
}

    chrono::milliseconds t_1 = duration_cast< chrono::milliseconds >(
            chrono::system_clock::now().time_since_epoch()
    );

    for(int i = 0; i < 1000000; i++){
        for(int j = 0; j < sizeof(test_1); j++){
            bool test = test_1[j] + test_2[j];
        }
    }

    chrono::milliseconds t_2 = duration_cast< chrono::milliseconds >(
            chrono::system_clock::now().time_since_epoch()
    );

    chrono::milliseconds t = t_2 - t_1;

    std::cout << t.count() << std::endl;
}
