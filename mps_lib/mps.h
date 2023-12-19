#ifndef MPS_LIB_MPS_H
#define MPS_LIB_MPS_H

#include <vector>
#include <cmath>

using namespace std;

class mps {

private:

    // properties of the bit array
    //-------------------------------
    int mantissa_length;    // The length of the mantissa of the bit array.
    int exponent_length;    // The length of the exponent of the bit array.
    //-------------------------------


    // the actual bit array
    //-------------------------------
    vector<bool> bit_vector;
    //-------------------------------

public:

    // constructors and destructor
    //-------------------------------
    mps(int mantissa_length, int exponent_length, double value);
    ~mps();
    //-------------------------------

    // getter methods
    //-------------------------------
    [[nodiscard]] int getMantisseLength() const;
    [[nodiscard]] int getExponentLength() const;
    [[nodiscard]] int getBitArrayLength() const;
    [[nodiscard]] vector<bool> getBitArray();
    [[nodiscard]] vector<bool>* getBitArrayReference();
    //-------------------------------

    // setter methods
    //-------------------------------
    void setInf(bool negative = false);
    void setZero();
    void setNAN();
    //-------------------------------

private:

    // helper functions
    //-------------------------------
    void setBitArray(double value);
    //-------------------------------

};


#endif //MPS_LIB_MPS_H
