#include <iostream>
#include <chrono>
#include <random>
#include <bitset>
#include <iostream>
#include <cmath> 

#include "mps/mps.h"
#include "ira/ira.h"

using namespace std;



int main() {

    // mps constructor input values: 1. mantissa, 2. exponent, 3. value 
    mps MPS_1(26, 9, 3.14159);
    mps MPS_2(26, 9, 2.71828);

    auto result = MPS_1 + MPS_2; 

    // Showing standard operations 
    //------------------------------------------------------------------------------------------------------
    cout << endl; 
    cout << "Value 1: " << MPS_1.getValue() << endl; 
    cout << "Value 2: " << MPS_2.getValue() << endl << endl; 

    cout << "Simple Calculations:" << endl; 
    cout << "Addition:\t" << MPS_1.getValue() << " + " << MPS_2.getValue() << " = " << (MPS_1 + MPS_2).getValue() << endl; 
    cout << "Subtraction:\t" << MPS_1.getValue() << " - " << MPS_2.getValue() << " = " << (MPS_1 - MPS_2).getValue() << endl; 
    cout << "Multiplication:\t" << MPS_1.getValue() << " * " << MPS_2.getValue() << " = " << (MPS_1 * MPS_2).getValue() << endl; 
    cout << "Division:\t" << MPS_1.getValue() << " / " << MPS_2.getValue() << " = " << (MPS_1 / MPS_2).getValue() << endl;
    cout << endl;  
    //------------------------------------------------------------------------------------------------------



    // Showing the Iterative Refinement Algorithm
    //------------------------------------------------------------------------------------------------------

    // Defining Precisions 
    unsigned long precision = 51;       // the number of mantissa bits which should be checked.
    unsigned long ur[2] = {52, 11};     // precision: A
    unsigned long ul[2] = {23, 11};     // precision: LU
    unsigned long u[2] = {52, 11};      // precision: working

    // Defining the System Matrix and Precisions 
    ira IRA(3, ur[0], ur[1]);
    vector<double> new_A{563.46, 634.34, 575.34, 694.34, 573.23, 468.67, 985.45, 575.56, 978.56};
    IRA.setMatrix(new_A);
    IRA.setWorkingPrecision(u[0], u[1]);
    IRA.setLowerPrecision(ul[0], ul[1]);

    // Defining the Inhomogeneity 
    vector<mps> b;
    b.emplace_back(ur[0], ur[1], 463.56);
    b.emplace_back(ur[0], ur[1], 875.35);
    b.emplace_back(ur[0], ur[1], 235.57);

    // Performing the Iterative Refinement Algorithm
    auto x = IRA.irPLU(b);

    // Printing the Result. 

    cout << "Solving Ax = b using Iterative Refinement:" << endl; 
    cout << "--------------------------------------------------------------" << endl; 

    cout << "System Matrix: \t[ "; 
    for (int i = 0; i < new_A.size(); i++){
        
        cout  << new_A[i] << ", "; 

        if((i % 3) == 2){ cout << "\b\b ]" << endl << "\t\t[ "; } 
    }
    cout << "\b\b  "; 

    cout << "\n" << "Inhomogeneity:\t[ "; 
    for (auto element : b){
        cout << element.getValue() << ", "; 
    }
    cout << "\b\b ]" << endl; 

    cout << "\n" << "Solution:\t[ "; 
    for (auto element : x){
        cout << element.getValue() << ", "; 
    }
    cout << "\b\b ]" << endl; 

    cout << "--------------------------------------------------------------" << endl << endl; 
    //------------------------------------------------------------------------------------------------------

    return 0;
}



