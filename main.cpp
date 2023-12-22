#include <iostream>
#include "mps_lib/mps.h"
#include <chrono>

using namespace std;

#include <bitset>
#include <iostream>


void func(bool* test_1, bool* test_2, bool* test_3, int size){
    for (int i = 0; i < 10000000; i++) {

        for (int j = 0; j < size; j++) {
            test_3[j] = test_1[j] * test_2[j];

        }
    }
}

void func(vector<bool> test_1, vector<bool> test_2, vector<bool> test_3, int size){
    for (int i = 0; i < 1000000; i++) {
        for (int j = 0; j < size; j++) {
            test_3[j] = test_1[j] * test_2[j];
        }
    }
}


int main() {
/*
    for (int i = 0; i < 50; i++) {

        bool test_1[i];
        bool test_2[i];
        bool test_3[i];

        for (int j = 0; j < i; j++) {
            test_1[j] = j % 3;
            test_2[j] = j % 2;
        }


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


    float test = 1;

    float f = 0.125;
    char* bits = reinterpret_cast<char*>(&f);
    for(std::size_t n = 0; n < sizeof f; ++n)
        std::cout << std::bitset<8>(bits[n]);
    std::cout << '\n';

    */
double a = 3432.334;
double b = 3664.334;
for (int mant = 0; mant < 100; mant++) {
    mps one(mant, 8, 34.45);
    mps two(mant, 8, 14.3 );

    chrono::milliseconds t_1 = duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()
    );

    for (int i = 0; i < 10000; i++) {

        one + two;
        //a+b;
    }

    chrono::milliseconds t_2 = duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()
    );

    chrono::milliseconds t = t_2 - t_1;

    std::cout << t.count() << std::endl;
}

}


