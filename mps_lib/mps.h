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
    bool sign;
    vector<bool> exponent;
    vector<bool> mantissa;
    //-------------------------------



public:
    // constructors and destructor
    //-------------------------------
    mps(unsigned long mantissa_length, unsigned long exponent_length, double value);
    mps(unsigned long mantissa_length, unsigned long exponent_length);
    mps();
    ~mps();

    // getter methods
    //-------------------------------
    [[nodiscard]] unsigned long getMantisseLength() const;
    [[nodiscard]] unsigned long getExponentLength() const;
    [[nodiscard]] unsigned long getBitArrayLength() const;
    [[nodiscard]] vector<bool> getBitArray() const;
    [[nodiscard]] double getValue() const;

    [[nodiscard]] bool isZero() const;
    [[nodiscard]] bool isInfinity() const;
    [[nodiscard]] bool isPositive() const;
    [[nodiscard]] bool isNaN() const;

    // setter methods
    //-------------------------------
    void setInf(bool negative = false);
    void setZero();
    void setNaN(bool negative = false);


public:
    // operators
    //-------------------------------
    mps& operator=(const mps& other);
    mps& operator=(double value);
    mps operator+(const mps& other) const;
    mps operator-(const mps& other) const;
    mps operator*(const mps& other) const;
    mps operator/(const mps& other) const;

private:
    // helper for operators
    //-------------------------------
    void setValue(double value);
    [[nodiscard]] static mps addition(const mps& one, const mps& two, bool set_sign) ;
    [[nodiscard]] static mps subtraction(const mps& minued, const mps& subtrahend, bool set_sign) ;
    [[nodiscard]] static mps multiplication(const mps& minued, const mps& subtrahend, bool set_sign) ;
    [[nodiscard]] static mps division(const mps& dividend, const mps& divisor, bool set_sign) ;


private:
    // general helper functions
    //-------------------------------
    [[nodiscard]] static vector<bool> binaryAddition(const vector<bool>& one, const vector<bool>& two, bool carry, bool* carrier_return = nullptr);
    [[nodiscard]] static vector<bool> binarySubtraction(const vector<bool>& minuend, const vector<bool>& subtrahend);
    static inline void round(vector<bool>* mantissa, unsigned long mantissa_len);

    [[nodiscard]] static unsigned long binaryToInt(vector<bool> bit_vector);
    [[nodiscard]] static vector<bool> intToBinary(unsigned long value);

    [[nodiscard]] long getBias() const;
    [[nodiscard]] static char larger(const vector<bool>& a, const vector<bool>& b);
    static void shiftLeft(vector<bool>* vec);
    static void matchMantissas(vector<bool>* vector_right_shift, vector<bool>* vector_left_shift, unsigned long amount);
    static bool addOneToBinary(vector<bool>* vector);
    [[nodiscard]] static bool allTrue(const vector<bool>& vector);
};


#endif //MPS_LIB_MPS_H
