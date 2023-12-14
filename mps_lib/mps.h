#ifndef MPS_LIB_MPS_H
#define MPS_LIB_MPS_H

#include <vector>

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

private:

    // helper functions
    //-------------------------------
    static vector<bool> getFloatingPointRepresentation(double value, int exponent_len, int mantissa_len);
    //-------------------------------

};


#endif //MPS_LIB_MPS_H
