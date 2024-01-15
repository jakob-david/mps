#include "mps.h"
#include <iostream>
#include <algorithm>


/*
 * NOTES
 * Use all_of with lambda: https://youtu.be/nqfgOCU_Do4?t=774
 * Use lambda instead of steps: https://youtu.be/nqfgOCU_Do4?t=983
 *
 *
 * */

// constructors and destructor
//-------------------------------

/**
 * Constructor for a multiprecision simulator object using values.
 *
 * @param mantisse Mantisse of the floating point representation.
 * @param exponent Exponent of the floating point representation.
 * @param value Value of the floating point number.
 */
mps::mps(unsigned long mantissa_length, unsigned long exponent_length, double value) {
    this->mantissa_length = mantissa_length;
    this->exponent_length = exponent_length;

    this->exponent.resize(this->exponent_length);
    this->mantissa.resize(this->mantissa_length);

    this->sign = false;
    this->exponent_as_int = 0;

    this->setValue(value);
}

/**
 * Constructor for an empty multiprecision simulator object.
 */
mps::mps(){
    this->mantissa_length = 0;
    this->exponent_length = 0;

    this->sign = false;
    this->exponent_as_int = 0;
}

/**
 * Destructor for a multiprecision simulator object.
 */
mps::~mps() = default;

//-------------------------------


// getter methods
//-------------------------------

/**
 * Returns the length of the matisse.
 *
 * @return length matisse
 */
unsigned long mps::getMantisseLength() const {
    return this->mantissa_length;
}

/**
 * Returns the length of the exponent.
 *
 * @return length exponent
 */
unsigned long mps::getExponentLength() const {
    return this->exponent_length;
}

/**
 * Returns the length of the whole bit array.
 * (sign + matisse + exponent)
 *
 * @return length matisse
 */
unsigned long mps::getBitArrayLength() const {
    return this->exponent.size() + this->mantissa.size() + 1;
}

/**
 * Concatenates the sign bit with the exponent vector and the mantissa vector.
 * The resulting vector is representing the floating point number in memory.
 *
 * @return vector representing the floating point number.
 */
vector<bool> mps::getBitArray() const {

    vector<bool> ret;
    ret.reserve(1 + this->exponent_length + this->mantissa_length);

    ret.push_back(this->sign);
    ret.insert(ret.end(), this->exponent.begin(), this->exponent.end());
    ret.insert(ret.end(), this->mantissa.begin(), this->mantissa.end());

    return ret;
}

/**
 * Calculates the value of the floating point object as double.
 *
 * @return value as double.
 */
double mps::getValue() const {

    // handle special cases
    if(isZero()){
        return 0;
    } else if (isInfinity() && isPositive()){
        return numeric_limits<double>::infinity();
    } else if (isInfinity()){
        return numeric_limits<double>::infinity() * -1;
    } else if (isNaN()){
        return numeric_limits<double>::quiet_NaN();
    }


    double ret;

    // positive or negative
    if(this->sign){
        ret = -1;
    } else {
        ret = 1;
    }

    // handle mantissa
    for(unsigned long i = 0; i < mantissa_length; i++){
        if(mantissa[i]){
            if(ret >= 0){
                ret += pow(0.5, i + 1);
            } else {
                ret -= pow(0.5, i + 1);
            }
        }
    }

    return ret * pow(2, exponent_as_int);
}

/**
 * Returns true if the mps object is zero.
 *
 * @return true if zero.
 */
bool mps::isZero() const{

    if(this->sign){
        return false;
    }

    for(unsigned long i = 0; i < this->exponent_length; i++){
        if(this->exponent[i]){
            return false;
        }
    }

    for(unsigned long i = 0; i < this->mantissa_length; i++){
        if(this->mantissa[i]){
            return false;
        }
    }

    return true;
}

/**
 * Returns true if the mps object is positive or negative infinity.
 *
 * @return true if pos. or neg. infinity.
 */
bool mps::isInfinity() const{


    for(unsigned long i = 0; i < this->exponent_length; i++){
        if(!this->exponent[i]){
            return false;
        }
    }

    for(unsigned long i = 0; i < this->mantissa_length; i++){
        if(this->mantissa[i]){
            return false;
        }
    }

    return true;
}

/**
 * Returns true if the mps object is positive.
 *
 * @return true if positive.
 */
bool mps::isPositive() const{

    if(this->sign){
        return false;
    } else {
        return true;
    }
}

/**
 * Returns true if the mps object is representing a NaN value.
 * The sign bit is irrelevant since some implementations differ between -NaN and +NaN.
 *
 * @return true if NaN.
 */
bool mps::isNaN() const{

    for(unsigned long i = 0; i < exponent_length; i++){

        if(!exponent[i]){
            return false;
        }
    }

    if(!mantissa[0]){
        return false;
    }

    for(unsigned long i = 1; i < mantissa_length; i++){

        if(mantissa[i]){
            return false;
        }
    }

    return true ;
}
//-------------------------------


// setter methods
//-------------------------------

/**
 * Sets the floating point number to infinity.
 *
 * @param negative set to true for negative infinity. (default false)
 */
void mps::setInf(bool negative) {

    if(negative){
        sign = true;
    } else {
        sign = false;
    }

    for(unsigned long i = 0; i < exponent_length; i++){
        exponent[i] = true;
    }

    for(unsigned long i = 0; i < mantissa_length; i++){
        mantissa[i] = false;
    }
}

/**
 * Sets the floating point number to zero.
 */
void mps::setZero(){

    sign = false;
    for(unsigned long i = 0; i < exponent_length; i++){
        exponent[i] = false;
    }
    for(unsigned long i = 0; i < mantissa_length; i++){
        mantissa[i] = false;
    }
}

/**
 * Sets the floating point number to NaN (not a number)
 */
void mps::setNaN(bool negative){

    if(negative){
        sign = true;
    } else {
        sign = false;
    }

    for(unsigned long i = 0; i < exponent_length; i++){
        exponent[i] = true;
    }

    mantissa[0] = true;
    for(unsigned long i = 1; i < mantissa_length; i++){
        mantissa[i] = false;
    }
}
//-------------------------------



// operators
//-------------------------------

/**
 * Sets the value of the mps object.
 */
mps& mps::operator=(double value){

    this->setValue(value);
    return *this;
}

/**
 * Sets one mps object equal to an other mps object.
 */
mps& mps::operator=(const mps& other) {

    if (this == &other){
        return *this;
    }

    if(0 == this->exponent_length && 0 == this->mantissa_length){
        this->exponent_length = other.exponent_length;
        this->mantissa_length = other.mantissa_length;

        this->exponent.resize(this->exponent_length);
        this->mantissa.resize(this->mantissa_length);
    } else {
        if (this->exponent_length != other.exponent_length) {
            cout << "ERROR: in = : Exponents do not match" << endl;
        }
        if (this->mantissa_length != other.mantissa_length) {
            cout << "ERROR: in = : Mantissas do not match" << endl;
        }
    }

    this->sign = other.sign;
    for(unsigned long i = 0; i < this->mantissa_length; i++){
        this->mantissa[i] = other.mantissa[i];
    }
    for(unsigned long i = 0; i < this->exponent_length; i++){
        this->exponent[i] = other.exponent[i];
    }
    this->exponent_as_int = other.exponent_as_int;


    this->mantissa_length = other.mantissa_length;
    this->exponent_length = other.exponent_length;

    return *this;
}

/**
 * Performs am addition to two mps floating point values.
 *
 * It is responsible for error handling, special values and choosing with "calculation" to use.
 */
mps mps::operator+(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        cout << "ERROR: in + : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in + : Mantissas do not match" << endl;
    }


    if(this->isPositive() && other.isPositive()){
        return addition(*this, other, false);
    } else if(!this->isPositive() && !other.isPositive()){
        return addition(*this, other, true);
    } else if(!this->isPositive()){
        return subtraction(other, *this, false);
    } else{
        return subtraction(*this, other, false);
    }

}

/**
 * Performs a subtraction to two mps floating point values.
 *
 * It is responsible for error handling, special values and choosing with "calculation" to use.
 */
mps mps::operator-(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        cout << "ERROR: in - : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in - : Mantissas do not match" << endl;
    }


    if(this->isPositive() && other.isPositive()){
        return subtraction(*this, other, false);
    } else if(!this->isPositive() && !other.isPositive()){
        return subtraction(*this, other, true);
    } else if(this->isPositive()) {
        return addition(*this, other, false);
    } else {
        return addition(*this, other, true);
    }
}

/**
 * Performs a multiplication to two mps floating point values.
 *
 * It is responsible for error handling, special values and choosing with "calculation" to use.
 */
mps mps::operator*(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        cout << "ERROR: in - : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in - : Mantissas do not match" << endl;
    }

    return multiplication(*this, other, this->sign != other.sign);
}


/**
 * Calculates the binary floating point representation of the given value and saves it inside the mps object.
 *
 * @param value the value to which the bit array should be set.
 */
void mps::setValue(const double value) {

    // Handle special values.
    //-------------------------------
    if(0 == value){
        setZero(); return;
    } else if(numeric_limits<double>::infinity() == value) {
        setInf(); return;
    } else if (numeric_limits<double>::infinity() * -1 == value){
        setInf(true); return;
    } else if (isnan(value)){
        if(signbit(value)){
            setNaN(true);
        } else {
            setNaN();
        }
        return;
    }
    //-------------------------------

    // prepare vectors
    //-------------------------------
    exponent.clear();
    mantissa.clear();
    //-------------------------------


    // set sign
    //-------------------------------
    this->sign = value <= 0;
    //-------------------------------


    // exponent
    //-------------------------------
    // calculate the exponent
    long mantissa_shift;
    if(abs(value) > numeric_limits<float>::max()){
        // When the value is too large rounding problems occur using log2.
        // (At least I think that is the problem)
        double tmp_value = abs(value);
        long tmp_count = 0;

        while(tmp_value > 1){
            tmp_value /= 2;
            tmp_count++;
        }

        mantissa_shift = tmp_count-1;
    } else {
        mantissa_shift = (long) floor(log2(abs(value)));
    }
    exponent_as_int =  mantissa_shift;

    // Getting the exponent in binary format.
    // The sign is not relevant. Always returns a "positive" value.
    // TODO: Maybe prevent insert.
    for(auto i = exponent_as_int + getBias(); i > 0; i /= 2){
        exponent.insert(exponent.begin(), i % 2);
    }

    // Fill not used but available bits with zero.
    if(exponent.size() > exponent_length) {

        if(value > 0){
            this->setInf();
        } else {
            this->setInf(true);
        }

        return;

    } else {
        for(unsigned long i = exponent.size(); i < exponent_length; i++){
            exponent.insert(exponent.begin(), false);
        }
    }
    //-------------------------------


    // mantissa
    //-------------------------------
    auto tmp_value = value / pow(2, mantissa_shift); // adjust the value so that everything is behind the decimal point.

    // Convert the part after the decimal point to a bit string.
    // The sign is not relevant. Always returns a "positive" value.
    double reminder = abs(tmp_value) - floor(abs(tmp_value));
    for(unsigned long i = 0; i < mantissa_length; i++){

        reminder *= 2;
        if(reminder >= 1){
            mantissa.push_back(true); reminder -= 1;
        } else{
            mantissa.push_back(false);
        }
    }
    //-------------------------------

}

/**
 * Performs an addition on two mps objects which have the same sign.
 *
 * @param one reference to the first addend
 * @param two reference to the second addend
 * @param set_sign the sign to which the final result should be set.
 * @return the resulting mps object.
 */
mps mps::addition(const mps &one, const mps &two, const bool set_sign) const {

    // Set up the return object.
    //-------------------------------
    mps ret;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    ret.sign = set_sign;
    //-------------------------------

    // Extract exponents and mantissas
    //-------------------------------
    vector<bool> a_mantissa = one.mantissa;
    a_mantissa.insert(a_mantissa.begin(), true);

    vector<bool> b_mantissa = two.mantissa;
    b_mantissa.insert(b_mantissa.begin(), true);
    //-------------------------------


    // Match mantissas and set exponent
    //-------------------------------
    unsigned long exponent_diff;
    char larger_tmp = larger(one.exponent, two.exponent);
    if(1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(one.exponent, two.exponent));
        ret.exponent = one.exponent;
        ret.exponent_as_int = one.exponent_as_int;
        matchMantissas(&b_mantissa, &a_mantissa, exponent_diff);
    } else if(-1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(two.exponent, one.exponent));
        ret.exponent = two.exponent;
        ret.exponent_as_int = two.exponent_as_int;
        matchMantissas(&a_mantissa, &b_mantissa, exponent_diff);
    } else {
        ret.exponent = one.exponent;
        ret.exponent_as_int = one.exponent_as_int;
    }
    //-------------------------------

    // Actual addition and adjusting mantissa
    //-------------------------------
    bool carrier;
    ret.mantissa = binaryAddition(a_mantissa, b_mantissa,true, &carrier);
    ret.mantissa.erase(ret.mantissa.begin(), ret.mantissa.begin()+1);
    if(carrier){
        addOneToBinary(&ret.exponent);
        ret.exponent_as_int++;
    }
    //-------------------------------

    round(&ret.mantissa, ret.mantissa_length);

    return ret;
}

/**
 * Performs a subtraction on two mps objects which have the same sign.
 *
 * @param minued reference to the minued number.
 * @param subtrahend reference to the subtracted number
 * @param set_sign the sign to which the final result should be set.
 * @return the resulting mps object.
 */
mps mps::subtraction(const mps &minued, const mps &subtrahend, bool set_sign) const {

    // Set up the return object.
    //-------------------------------
    mps ret;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    ret.sign = set_sign;
    //-------------------------------


    // Extract exponents and mantissas
    //-------------------------------
    vector<bool> a_mantissa = minued.mantissa;
    a_mantissa.insert(a_mantissa.begin(), true);

    vector<bool> b_mantissa = subtrahend.mantissa;
    b_mantissa.insert(b_mantissa.begin(), true);
    //-------------------------------


    // Match mantissas and set exponent
    //-------------------------------
    char larger_tmp = larger(minued.exponent, subtrahend.exponent);
    if(1 == larger_tmp){
        unsigned long exponent_diff = binaryToInt(binarySubtraction(minued.exponent, subtrahend.exponent));
        ret.exponent = minued.exponent;
        ret.exponent_as_int = minued.exponent_as_int;
        matchMantissas(&b_mantissa, &a_mantissa, exponent_diff);
    } else if(-1 == larger_tmp){
        unsigned long exponent_diff = binaryToInt(binarySubtraction(subtrahend.exponent, minued.exponent));
        ret.exponent = subtrahend.exponent;
        ret.exponent_as_int = subtrahend.exponent_as_int;
        matchMantissas(&a_mantissa, &b_mantissa, exponent_diff);
    } else {
        ret.exponent = minued.exponent;
        ret.exponent_as_int = minued.exponent_as_int;
    }
    //-------------------------------


    // Actual Subtraction
    //-------------------------------
    larger_tmp = larger(a_mantissa, b_mantissa);
    if(1 == larger_tmp){
        ret.mantissa = binarySubtraction(a_mantissa, b_mantissa);
    } else if(-1 == larger_tmp){
        ret.mantissa = binarySubtraction(b_mantissa, a_mantissa);
        ret.sign = !ret.sign; // flip sign
    } else {
        ret.setZero();
        return ret;
    }
    //-------------------------------


    // Adjust mantissa and exponent
    //-------------------------------
    unsigned long exponent_shift = 0;
    for(unsigned long i = 0; i < ret.mantissa.size(); i++){
        if(ret.mantissa[i]){
            exponent_shift = i;
            break;
        }
    }

    ret.mantissa.erase(ret.mantissa.begin(), ret.mantissa.begin() + (long) exponent_shift + 1);
    ret.exponent_as_int -= (long) exponent_shift;

    // TODO: Place for improvement
    vector<bool> exponent_shift_binary = intToBinary(exponent_shift);
    for(unsigned long i = exponent_shift_binary.size(); i < ret.exponent_length; i++){
        exponent_shift_binary.insert(exponent_shift_binary.begin(), false);
    }
    ret.exponent = binarySubtraction(ret.exponent, exponent_shift_binary);

    //-------------------------------


    round(&ret.mantissa, ret.mantissa_length);


    return ret;
}

/**
 * Performs a multiplication on two mps objects which have the same sign.
 *
 * @param one reference to the first multiplicand.
 * @param two reference to the second multiplicand.
 * @param set_sign the sign to which the final result should be set.
 * @return the resulting mps object.
 */
mps mps::multiplication(const mps& one, const mps& two, bool set_sign) const {

    // Set up the return object.
    //-------------------------------
    mps ret;
    ret.exponent_length = one.exponent_length;
    ret.mantissa_length = one.mantissa_length;
    //-------------------------------


    // Set up sign.
    ret.sign = set_sign;



    vector<bool> A(one.mantissa.begin(), one.mantissa.end());
    vector<bool> S;

    A.reserve(A.size() + (two.mantissa_length + two.exponent_length + 1) + 1 +2 +2);
    A.insert(A.begin(), true);
    A.insert(A.begin(), false);
    S.reserve(A.size() + (two.mantissa_length + two.exponent_length + 1) + 1 +2 +2);

    for(unsigned long i = 0; i < A.size(); i++){
        S.push_back(!A[i]);
    }
    addOneToBinary(&S);

    for(unsigned long i = 0; i < two.mantissa_length + 1 +1 +1; i++){
        A.push_back(false);
        S.push_back(false);
    }

    vector<bool> P;
    P.reserve(A.size() + (two.mantissa_length + two.exponent_length + 1) + 1 +2 +2);
    for(unsigned long i = 0; i < one.mantissa_length+1+1; i++){
        P.push_back(false);
    }
    P.push_back(false);
    P.push_back(true);
    for(unsigned long i = 0; i < two.mantissa_length; i++){
        P.push_back(two.mantissa[i]);
    }
    P.push_back(false);


    for(unsigned long i = 0; i < two.mantissa_length+2; i++){


        if(!P.end()[-2] && P.back()){
            P = binaryAddition(P, A, false);
        } else if(P.end()[-2] && !P.back()) {
            P = binaryAddition(P, S, false);
        }

        P.pop_back();
        P.insert(P.begin(), P[0]);

    }

    P.pop_back();
    P.erase (P.begin());
    int count = 0;
    for(unsigned long i = 0; i < P.size(); i++){
        if(P[0]){
            P.erase(P.begin());
            break;
        }
        P.erase(P.begin());
        count++;
    }


    round(&P, ret.mantissa_length);


    vector<bool> a_exponent(one.exponent.begin(), one.exponent.end());
    vector<bool> b_exponent(two.exponent.begin(), two.exponent.end());

    // TODO: Check for carry
    b_exponent[0] = !b_exponent[0];
    addOneToBinary(&b_exponent);
    if(count <= 1){
        addOneToBinary(&b_exponent);
    }

    ret.exponent = binaryAddition(a_exponent, b_exponent, false);
    ret.exponent_as_int = (long) binaryToInt(ret.exponent) - ret.getBias();
    ret.mantissa = P;



    return ret;

}
//-------------------------------


// helper methods
//-------------------------------

/**
 * Performs a binary addition using a full adder.
 * The binary numbers are represented as vector containing booleans.
 *
 * @param a reference to the first addend
 * @param b reference to the second addend
 * @param carry set to true if an adjustment is wanted when the carrier bit of the last iteration is 1
 * @param carrier_return pointer to a boolean where the last state of the carrier bit can be save
 * @return the result as binary number.
 */
vector<bool> mps::binaryAddition(const vector<bool>& a, const vector<bool>& b, bool carry, bool* carrier_return){

    vector<bool> ret;
    bool carrier = false;

    // full adder
    for(auto i = a.size(); i > 0;){
        i--;
        ret.insert(ret.begin(), (a[i] ^ b[i]) ^ carrier);
        carrier = ((a[i] && b[i]) || (a[i] && carrier)) || (b[i] && carrier);
    }

    // adjust if carrier bit is 1
    if(carry && carrier){
        ret.insert(ret.begin(), true);
        ret.pop_back();
    }

    // save the state of the carrier bit in carrier_return.
    if(carrier_return != nullptr){
        *carrier_return = carrier;
    }

    return ret;
}

/**
 * Performs a binary subtraction.
 * The binary numbers are represented as vector containing booleans.
 *
 * @param minuend reference to the vector which should be reduced
 * @param subtrahend reference to the vector which should be subtracted.
 * @return the result as a binary number.
 */
vector<bool> mps::binarySubtraction(const vector<bool>& minuend, const vector<bool>& subtrahend){

    vector<bool> tmp_subtrahend;
    tmp_subtrahend.reserve(subtrahend.size());

    for(auto i : subtrahend){
        tmp_subtrahend.push_back(!i);
    }

    /*
    // invert
    for(auto && i : subtrahend){
        i = !i;
    }
*/
    // add one
    if(addOneToBinary(&tmp_subtrahend)){
        return minuend; // if there is a carrier bit present at the end the subtrahend is zero.
    }

    return binaryAddition(minuend, tmp_subtrahend, false);
}

/**
 * Performs the rounding of the mantissa according to IEEE754.
 *
 * @param mantissa Pointer to the mantissa which should be rounded.
 * @param mantissa_len The length to which the mantissa should be rounded.
 */
void mps::round(vector<bool> *mantissa, unsigned long mantissa_len) {

    if(mantissa->size() > mantissa_len){
        bool tmp = false;
        for(auto i = mantissa_len+1 ; i < mantissa->size(); i++){
            if ((*mantissa)[i]){
                tmp = true;
                break;
            }
        }
        if((*mantissa)[mantissa_len] && tmp){
            mantissa->erase(mantissa->end()- (long) (mantissa->size()- mantissa_len), mantissa->end());
            if(addOneToBinary(mantissa)){
                addOneToBinary(mantissa);
            }
        } else if((*mantissa)[mantissa_len]){
            if((*mantissa)[mantissa_len-1]){
                mantissa->erase(mantissa->end()- (long) (mantissa->size()-mantissa_len), mantissa->end());
                if(addOneToBinary(mantissa)){
                    addOneToBinary( mantissa);
                }
            } else {
                mantissa->erase(mantissa->end()- (long) (mantissa->size()-mantissa_len), mantissa->end());
            }
        }else {
            mantissa->erase(mantissa->end()- (long) (mantissa->size()-mantissa_len), mantissa->end());
        }
    }
}


/**
 * Converts a binary number to an integer.
 * The binary number is stored in a vector of booleans.
 *
 * @param vector vector containing the binary number
 * @return the binary number as integer
 */
unsigned long mps::binaryToInt(vector<bool> vector){

    unsigned long ret = 0;

    for(unsigned long i = 0; i < vector.size(); i++){
        if(vector[vector.size()-i-1]){
            ret += (unsigned long) pow(2,i);
        }
    }

    return ret;
}

/**
 * Converts an integer to a binary number.
 * The binary number is stored in a vector of booleans.
 *
 * @param value the value of the integer.
 * @return the value as binary number.
 */
vector<bool> mps::intToBinary(unsigned long value) {

    vector<bool> ret;

    while (value >= 1){
        ret.insert(ret.begin(), value%2);
        value /= 2;
    }

    return ret;
}


/**
 * Returns the bias of the exponent.
 *
 * @return bias of the exponent
 */
int mps::getBias() const{
    return ((int) pow (2, exponent_length)) / 2 -1;
}

/**
 * To be read: Is the bit value a represents larger than the one of b.
 * 1 if a > b
 * 0 if a == b
 * -1 if a < b
 *
 * Only works for vectors of same size.
 *
 * @param a reference to the vector containing the first binary number
 * @param b reference to the vector containing the second binary number
 * @return 1 if a > b, 0 if a == b, -1 if a < b
 */
char mps::larger(const vector<bool>& a, const vector<bool>& b){

    // TODO: Remove at the end.
    if(a.size() != b.size()){
        cout << "ERROR: larger: not same size" << endl;
    }

    for(unsigned long i = 0; i < a.size(); i++){
        if(a[i] && !b[i]) { return 1;}
        else if(b[i] && !a[i]) {return -1;}
    }
    return 0;
}

/**
 * Aligns two bit vectors about an amount.
 * The amount is the number so that after the operation the two bit vectors align and have the same exponent.
 *
 * The vectors are not really shifted but zeros are added either to the left or the right.
 * Therefore the size of both vectors is increased by the amount both are "shifted".
 *
 * @param vector_right_shift pointer to the vector which should be "shifted" to the right
 * @param vector_left_shift pointer to the vector which should be "shifted" to the left
 * @param amount amount the two vectors should be "shifted"
 */
void mps::matchMantissas(vector<bool>* vector_right_shift, vector<bool>* vector_left_shift, unsigned long amount){

    for(unsigned long i = 0; i < amount; i++){
        vector_right_shift->insert(vector_right_shift->begin(), false);
        vector_left_shift->insert(vector_left_shift->end(), false);
    }
}

/**
 * Adds one to a binary number saved inside a vector.
 * The vector consists of booleans which represents a binary number.
 *
 * If a carrier bit is present in the last iteration a "one" is added at the beginning
 * and the last element is erased.
 *
 * @param vector pointer to the vector containing the binary number where one should be added
 * @return true if a carrier bit was present in the last iteration, false otherwise
 */
bool mps::addOneToBinary(vector<bool>* vector){

    // TODO: Make while loop
    for(long i = (long) vector->size() - 1; i >= 0; i--){
        (*vector)[(unsigned long) i] = !(*vector)[(unsigned long) i];
        if((*vector)[(unsigned long) i]){
            return false;
        }
    }

    vector->insert(vector->begin(), true);
    vector->pop_back();
    return true;
}
//-------------------------------