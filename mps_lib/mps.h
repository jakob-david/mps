#ifndef MPS_LIB_MPS_H
#define MPS_LIB_MPS_H

#include <vector>

using namespace std;

class mps {

private:

    // properties of the bit array
    //-------------------------------
    int mantisse_length;    // The length of the mantisse of the bit array.
    int exponent_length;    // The length of the exponent of the bit array.
    //-------------------------------


    // the actual bit array
    //-------------------------------
    vector<bool> bit_vector;
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
    [[nodiscard]] unsigned long getBitArrayLength() const;
    [[nodiscard]] vector<bool> getBitArray();
    [[nodiscard]] vector<bool>* getBitArrayReference();
    //-------------------------------

public:

    // helper functions
    //-------------------------------
    static vector<bool> getIntegerPart(int value);
    vector<bool> getDecimalPart(double value, int length);
    vector<bool> getFloatingPointRepresentation(double value, int exponent_length, int mantissa_length);
    //-------------------------------

};


#endif //MPS_LIB_MPS_H
