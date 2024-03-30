#include <iostream>
#include "mps_lib/mps.h"
#include <chrono>
#include <random>

using namespace std;

#include <bitset>
#include <iostream>



int main() {

for (unsigned long mant = 53; mant <= 53; mant++) {
    mps one(25, 11, 1.8);
    mps two(25, 11, 1.8000001);

    //mps one(mant, 11, 3.90034);
    //mps two(mant, 11, 35.2365786);

    std::chrono::milliseconds t_1 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );

    auto sum = 0;
    //cout << "Mant: " << mant << endl;
    //one * two;
    for (long int i = 0; i < 500000; i++) {


        //one.setValue(4);
        //one = 4;
        //auto three = two;
        auto ret = one.check_precision(two, 20);
        if(ret){
            sum++;
        }
        //c = b*a;
    }

    cout << sum << endl;
    std::chrono::milliseconds t_2 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );


    std::chrono::milliseconds t = t_2 - t_1;
    std::cout << t.count() << std::endl;
}

    // std::cout << c << std::endl;
}


