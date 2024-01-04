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
    mps();
    ~mps();
    //-------------------------------

    // getter methods
    //-------------------------------
    [[nodiscard]] int getMantisseLength() const;
    [[nodiscard]] int getExponentLength() const;
    [[nodiscard]] int getBitArrayLength() const;
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
    void setNaN();
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
    [[nodiscard]] static vector<bool> binarySubtractor(vector<bool>& minuend, vector<bool> subtrahend);
    static inline void round(vector<bool>* mantissa, int mantissa_len);

    [[nodiscard]] static int binaryToInt(vector<bool> bit_vector);
    [[nodiscard]] static vector<bool> intToBinary(unsigned int value);
    [[nodiscard]] static char larger(vector<bool>& a, vector<bool>& b);
    static void matchMantissas(vector<bool>* vector_right_shift, vector<bool>* vector_left_shift, int amount);
    static bool addOneToBinary(vector<bool>* vector);
    //-------------------------------

};


#endif //MPS_LIB_MPS_H
