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


    vector<bool> b;
    b.resize(10);
    b.insert(b.begin(), false);
    cout << b.size() << endl;
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
//double a = 3432.334;
//double b = 3664.334;
//double d = 456.34;
//double e = 345.4;
//double f = 8657.456;
//double g = 128.34;
//double c;

    //double lower_bound = 0;
    //double upper_bound = 100;

for (unsigned long mant = 0; mant < 70; mant++) {
    mps one(mant, 8, 3432.45);
    mps two(mant, 8, 143.3 );

    std::chrono::milliseconds t_1 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );

    for (long int i = 0; i < 1000000; i++) {

/*
        std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
        std::default_random_engine re;
        a = unif(re);
        b = unif(re);
        d = unif(re);
        e = unif(re);
        f = unif(re);
        g = unif(re);
*/

        //one.setValue(4);
        one = 4;
        //one * two;
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


