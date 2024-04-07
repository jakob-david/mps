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


    unsigned long n = 50;
    auto IRA = ira(n);
    IRA.setRandomMatrix(53, 11);
    IRA.PLU_decomposition(53,11);

    // Set up x_should;
    //--------------------------------
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    vector<mps> x_should;
    for(unsigned long i = 0 + 1; i <= n; i++){
        x_should.emplace_back(53, 11, dist(mt));
    }
    //--------------------------------


    //unsigned long ul[2] = { 53, 11};    // precision: LU
    //unsigned long u[2] = {52, 11};      // precision: working

    std::chrono::milliseconds t_1 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );


    mpe MPE;
    auto result = MPE.evaluateAddition(10000);

    for(unsigned long i = 0; i < result.size(); i++){
        cout << result[i] << endl;
    }


    std::chrono::milliseconds t_2 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );


    cout << endl << endl;
    std::chrono::milliseconds t = t_2 - t_1;
    std::cout << t.count() << std::endl;

}



