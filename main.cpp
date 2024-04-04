#include <iostream>
#include "mps_lib/mps.h"
#include "ira_lib/ira.h"
#include <chrono>
#include <random>

using namespace std;

#include <bitset>
#include <iostream>



int main() {

    // old: 7750

    auto IRA = ira(50);
    IRA.setRandomMatrix(53, 11);

    std::chrono::milliseconds t_1 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );


    for(unsigned long i = 0; i < 20; i++){
        IRA.PLU_decomposition(53, 11);
    }

    std::chrono::milliseconds t_2 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );

    std::chrono::milliseconds t = t_2 - t_1;
    std::cout << t.count() << std::endl;

}



