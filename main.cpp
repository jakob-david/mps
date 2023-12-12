#include <iostream>
#include "mps_lib/mps.h"
#include <chrono>

using namespace std;

void func(bool* test_1, bool* test_2, bool* test_3, int size){
    for (int i = 0; i < 10000000; i++) {
        for (int j = 0; j < size; j++) {
            test_3[j] = test_1[j] * test_2[j];
        }
    }
}

void func(vector<bool> test_1, vector<bool> test_2, vector<bool> test_3, int size){
    for (int i = 0; i < 100000; i++) {
        for (int j = 0; j < size; j++) {
            test_3[j] = test_1[j] * test_2[j];
        }
    }
}


int main() {

    for (int i = 0; i < 100; i++) {

/*
        bool test_1[i];
        bool test_2[i];
        bool test_3[i];

        for (int j = 0; j < i; j++) {
            test_1[j] = j % 3;
            test_2[j] = j % 2;
        }

*/

        vector<bool> test_1;
        vector<bool> test_2;
        vector<bool> test_3;

        for (int j = 0; j < i; j++) {
            test_1.push_back(j % 3);
            test_2.push_back(j % 2);
            test_3.push_back(0);
        }


        chrono::milliseconds t_1 = duration_cast<chrono::milliseconds>(
                chrono::system_clock::now().time_since_epoch()
        );

        func(test_1, test_2, test_3, i);

        chrono::milliseconds t_2 = duration_cast<chrono::milliseconds>(
                chrono::system_clock::now().time_since_epoch()
        );

        chrono::milliseconds t = t_2 - t_1;

        std::cout << t.count() << std::endl;
    }
}


