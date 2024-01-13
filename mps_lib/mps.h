#ifndef MPS_LIB_MPS_H
#define MPS_LIB_MPS_H

#include <vector>
#include <cmath>

using namespace std;

class mps {

private:

    // properties of the bit array
    //-------------------------------
    unsigned long mantissa_length;    // The length of the mantissa of the bit array.
    unsigned long exponent_length;    // The length of the exponent of the bit array.
    //-------------------------------


    // the actual bit array
    //-------------------------------
    vector<bool> bit_vector;
    //-------------------------------

public:

    // constructors and destructor
    //-------------------------------
    mps(unsigned long mantissa_length, unsigned long exponent_length, double value);
    mps();
    ~mps();
    //-------------------------------

    // getter methods
    //-------------------------------
    [[nodiscard]] unsigned long getMantisseLength() const;
    [[nodiscard]] unsigned long getExponentLength() const;
    [[nodiscard]] unsigned long getBitArrayLength() const;
    [[nodiscard]] vector<bool> getBitArray();
    [[nodiscard]] vector<bool>* getBitArrayReference();
    [[nodiscard]] double getValue();

    [[nodiscard]] bool isZero();
    [[nodiscard]] bool isInfinity();
    [[nodiscard]] bool isPositive();
    //-------------------------------

    // setter methods
    //-------------------------------
    void setInf(bool negative = false);
    void setZero();
    void setNaN(bool negative = false);
    //-------------------------------

    // operators
    //-------------------------------
    mps& operator=(const mps& other);
    mps operator+(mps& other);
    mps operator-(mps& other);
    mps operator*(mps& other);
    //-------------------------------

private:

    // helper functions
    //-------------------------------
    void setBitArray(double value);
    [[nodiscard]] int getBias() const;

public:
    [[nodiscard]] static vector<bool> binaryAddition(vector<bool>& one, vector<bool>& two, bool carry, bool* carrier_return = nullptr);
    [[nodiscard]] static vector<bool> binarySubtraction(vector<bool>& minuend, vector<bool> subtrahend);
    static inline void round(vector<bool>* mantissa, unsigned long mantissa_len);

    [[nodiscard]] static unsigned long binaryToInt(vector<bool> bit_vector);
    [[nodiscard]] static vector<bool> intToBinary(unsigned long value);
    [[nodiscard]] static char larger(vector<bool>& a, vector<bool>& b);
    static void matchMantissas(vector<bool>* vector_right_shift, vector<bool>* vector_left_shift, unsigned long amount);
    static bool addOneToBinary(vector<bool>* vector);
    //-------------------------------

};


#endif //MPS_LIB_MPS_H
