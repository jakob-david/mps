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
    // old: 69153

    unsigned long n = 50;
    //unsigned long n = 5;
    auto IRA = ira(n);
    IRA.setRandomMatrix(53, 11);
    IRA.PLU_decomposition(53, 11);

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

    // Set up b
    //--------------------------------
    vector<mps> b;
    double tmp;
    for(unsigned long i = 0; i < n; i++){
        tmp = 0;
        for(unsigned long j = 0; j < n; j++){
            tmp += x_should[j].getValue() * IRA.getMatrixElement((n * i) + j).getValue();
        }
        b.emplace_back(53, 11, tmp);
    }
    //--------------------------------

    //unsigned long ul[2] = { 53, 11};    // precision: LU
    //unsigned long u[2] = {52, 11};      // precision: working

    std::chrono::milliseconds t_1 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );

    //17807
    // i = 20
    for(unsigned long i = 0; i < 1000; i++){
        //auto x = ira::matrixVectorProduct(IRA.P, b);
        auto x = ira::permuteVector(b, IRA.P_new);
        //auto x = ira::permuteVector(tmp_b, this->P_new);
    }

    std::chrono::milliseconds t_2 = chrono::duration_cast<chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );

    /*
    for(unsigned long i = 0; i < n; i++){
        for(unsigned long j = 0; j < n; j++){
            cout << IRA.P[i * n + j].getValue() << " ";
        }
        cout << endl;
    }

    cout << endl;


    for(unsigned long i = 0; i < n; i++){
        cout << IRA.P_new[i].getValue() << " ";
    }
*/
    cout << endl << endl;
    std::chrono::milliseconds t = t_2 - t_1;
    std::cout << t.count() << std::endl;

}



