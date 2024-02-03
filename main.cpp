#include <iostream>
#include "mps_lib/mps.h"
#include <chrono>
#include <random>

using namespace std;

#include <bitset>
#include <iostream>


void func(const bool* test_1, const bool* test_2, bool* test_3, int size){
    for (int i = 0; i < 10000000; i++) {

        for (int j = 0; j < size; j++) {
            test_3[j] = test_1[j] * test_2[j];

        }
    }
}

void func(vector<bool> test_1, vector<bool> test_2, vector<bool> test_3, unsigned long size){
    for (unsigned long i = 0; i < 1000000; i++) {
        for (unsigned long j = 0; j < size; j++) {
            test_3[j] = test_1[j] * test_2[j];
        }
    }
}


int main() {


for (unsigned long mant = 2; mant <= 53; mant++) {
    mps one(mant, 11, 7.45);
    mps two(mant, 11, 4.3 );

    std::chrono::milliseconds t_1 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );

    //cout << "Mant: " << mant << endl;
    //one * two;
    for (long int i = 0; i < 100000; i++) {


        //one.setValue(4);
        //one = 4;
        one * two;
        //c = b*a;
    }

    std::chrono::milliseconds t_2 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );


    std::chrono::milliseconds t = t_2 - t_1;
    std::cout << t.count() << std::endl;
}

    // std::cout << c << std::endl;
}


