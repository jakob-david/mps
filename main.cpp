#include <iostream>
#include "mps/mps.h"
#include <chrono>
#include <random>

using namespace std;

#include <bitset>
#include <iostream>



int main() {

    // mps constructor input values: 1. mantissa, 2. exponent, 3. value 
    mps MPS_1(26, 9, 3.14159);
    mps MPS_2(26, 9, 2.71828);

    auto result = MPS_1 + MPS_2; 

    cout << endl; 
    cout << "Value 1: " << MPS_1.getValue() << endl; 
    cout << "Value 2: " << MPS_2.getValue() << endl << endl; 

    cout << "Simple Calculations:" << endl; 
    cout << "Addition:\t" << MPS_1.getValue() << " + " << MPS_2.getValue() << " = " << (MPS_1 + MPS_2).getValue() << endl; 
    cout << "Subtraction:\t" << MPS_1.getValue() << " - " << MPS_2.getValue() << " = " << (MPS_1 - MPS_2).getValue() << endl; 
    cout << "Multiplication:\t" << MPS_1.getValue() << " * " << MPS_2.getValue() << " = " << (MPS_1 * MPS_2).getValue() << endl; 
    cout << "Division:\t" << MPS_1.getValue() << " / " << MPS_2.getValue() << " = " << (MPS_1 / MPS_2).getValue() << endl;
    cout << endl;  

}



