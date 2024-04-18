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





    //unsigned long ul[2] = { 53, 11};    // precision: LU
    //unsigned long u[2] = {52, 11};      // precision: working

    std::chrono::milliseconds t_1 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );


    mpe MPE;
    MPE.setIterations(1000);



    std::chrono::milliseconds t_2 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );


    cout << endl << endl;
    std::chrono::milliseconds t = t_2 - t_1;
    std::cout << t.count() << std::endl;

}



