#include <iostream>
#include "mps_lib/mps.h"
#include "ira_lib/ira.h"
#include "mpe_lib/mpe.h"
#include <chrono>
#include <random>

using namespace std;

#include <bitset>
#include <iostream>



int main() {


    mps MPS_1(52, 4, 8);
    mps MPS_2(52, 4, 8);

    bool result = true;
    vector<bool> new_exponent = {0, 0, 1, 1};
    MPS_1.setExponent(new_exponent);
    MPS_2.setExponent(new_exponent);

    std::chrono::milliseconds start = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );


    //for(unsigned long run = 0; run < 1000000; run++){
    //
    //}

    result = MPS_1.checkPrecision(MPS_2, 3);

    std::chrono::milliseconds end = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );


    cout << endl << endl;
    if(result){
        cout << "true" << endl;
    }
    std::chrono::milliseconds t = end - start;
    std::cout << t.count() << std::endl;

}



