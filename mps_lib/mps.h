#ifndef MPS_LIB_MPS_H
#define MPS_LIB_MPS_H

#include <vector>
#include <cmath>
#include <string>

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
    [[nodiscard]] bool getSign() const;
    [[nodiscard]] vector<bool> getMantissa() const;
    [[nodiscard]] vector<bool> getExponent() const;
    [[nodiscard]] vector<bool> getBitArray() const;

    [[nodiscard]] unsigned long getMantisseLength() const;
    [[nodiscard]] unsigned long getExponentLength() const;
    [[nodiscard]] unsigned long getBitArrayLength() const;
    [[nodiscard]] double getValue() const;

    [[nodiscard]] bool isZero() const;
    [[nodiscard]] bool isInf() const;
    [[nodiscard]] bool isPositive() const;
    [[nodiscard]] bool isNaN() const;

    [[nodiscard]] std::string print() const;
    [[nodiscard]] std::string toString(int precision = -1) const;

    // precision
    //-------------------------------
    [[nodiscard]] bool checkPrecision(const mps& compare, unsigned long precision) const;
    [[nodiscard]] long long int getPrecision(const mps& compare) const;
    [[nodiscard]] mps getAbsoluteError(const mps& compare) const;
    [[nodiscard]] mps getRelativeError(const mps& compare) const;
    [[nodiscard]] double getAbsoluteError_double(const mps& compare) const;
    [[nodiscard]] double getRelativeError_double(const mps& compare) const;
    [[nodiscard]] double getAbsoluteError_double(const double& compare) const;
    [[nodiscard]] double getRelativeError_double(const double& compare) const;

    // setter methods
    //-------------------------------
    void setInf(bool negative = false);
    void setZero(bool negative = false);
    void setNaN(bool negative = false);
    void setSign(bool negative);
    void setMantissa(vector<bool>& new_mantissa);
    void setExponent(vector<bool>& new_exponent);

    // cast
    //-------------------------------
    void cast(unsigned long new_mantissa_size, unsigned long new_exponent_size);

    // operators
    //-------------------------------
    mps& operator=(const mps& other);
    mps& operator|=(const mps& other);
    mps& operator=(double value);
    mps operator+(const mps& other) const;
    mps operator-(const mps& other) const;
    mps operator*(const mps& other) const;
    mps operator/(const mps& other) const;

    // comparators
    //-------------------------------
    bool operator==(const mps& other) const;
    bool operator!=(const mps& other) const;
    bool operator>(const mps& other) const;
    bool operator<(const mps& other) const;
    bool operator>=(const mps& other) const;
    bool operator<=(const mps& other) const;


private:

    // helper for cast
    //-------------------------------
    void resize_mps_object(unsigned long new_mantissa_size, unsigned long new_exponent_size);

    // helper for operators
    //-------------------------------
    void setValue(double value);
    [[nodiscard]] static mps addition(const mps& one, const mps& two, bool set_sign) ;
    [[nodiscard]] static mps subtraction(const mps& minued, const mps& subtrahend, bool set_sign) ;
    [[nodiscard]] static mps multiplication(const mps& minued, const mps& subtrahend, bool set_sign) ;
    [[nodiscard]] static mps division(const mps& dividend, const mps& divisor, bool set_sign) ;

    // helper for comparators
    //-------------------------------
    [[nodiscard]] static bool equal(const mps& one, const mps& two) ;
    [[nodiscard]] static bool notEqual(const mps& one, const mps& two) ;
    [[nodiscard]] static bool larger(const mps& one, const mps& two) ;
    [[nodiscard]] static bool smaller(const mps& one, const mps& two) ;
    [[nodiscard]] static bool largerEqual(const mps& one, const mps& two) ;
    [[nodiscard]] static bool smallerEqual(const mps& one, const mps& two) ;

    [[nodiscard]] static char compare(const mps& one, const mps& two) ;

    // general helper functions
    //-------------------------------
    [[nodiscard]] static vector<bool> binaryAddition(const vector<bool>& one, const vector<bool>& two, bool* carrier_return = nullptr);
    [[nodiscard]] static vector<bool> binarySubtraction(const vector<bool>& minuend, const vector<bool>& subtrahend);

    static void binarySummation(vector<bool>* summand, const vector<bool>& addend, bool = false);
    static vector<bool> binaryOffsetAddition(const vector<bool>& lp, const vector<bool>& rp, unsigned long off_set, bool c, const bool p[2], const bool hd[2],  bool* cr = nullptr);
    static inline bool round(vector<bool>* mantissa, unsigned long mantissa_len);

    [[nodiscard]] static unsigned long binaryToInt(vector<bool> bit_vector);
    [[nodiscard]] static vector<bool> intToBinary(unsigned long value);

    [[nodiscard]] long getBias() const;
    [[nodiscard]] static char larger(const vector<bool>& a, const vector<bool>& b, bool division_case = false);
    static void shiftLeft(vector<bool>* vec);
    static bool addOneToBinary(vector<bool>* vector);
    static bool subtractOneFromBinary(vector<bool>* vector);
    [[nodiscard]] static vector<bool> invertAndAddOne(const vector<bool> &vec, bool *carrie = nullptr, bool division_case = false);
    [[nodiscard]] static bool allTrue(const vector<bool>& vector);
    [[nodiscard]] static bool allFalse(const vector<bool>& vector);
};


#endif //MPS_LIB_MPS_H
