//
// Created by Jakob on 11.12.23.
//

#include <cstdlib>

#ifndef MPS_LIB_MPS_H
#define MPS_LIB_MPS_H

class mps {

private:

    // properties of the bit array
    //-------------------------------
    int mantisse_length;    // The length of the mantisse of the bit array.
    int exponent_length;    // The length of the exponent of the bit array.
    int bit_array_length;   // The total length of the bit array (sigh + mantisse + exponent).
    //-------------------------------

    // the value saved as long double
    //-------------------------------
    bool side_calculation_active{};
    long double* side_calculation_value{};
    //-------------------------------

    // the actual bit array
    //-------------------------------
    bool* bit_array;
    //-------------------------------

public:

    // constructors and destructor
    //-------------------------------
    mps(int mantisse, int exponent, double value);
    ~mps();
    //-------------------------------


    // getter methods
    //-------------------------------
    [[nodiscard]] int getMantisseLength() const;
    [[nodiscard]] int getExponentLength() const;
    [[nodiscard]] int getBitArrayLength() const;
    [[nodiscard]] bool* getBitArray();
    //-------------------------------

};


#endif //MPS_LIB_MPS_H
