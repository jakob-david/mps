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
 * Constructor for the multiprecision simulator.
 *
 * @param mantisse Mantisse of the floating point representation.
 * @param exponent Exponent of the floating point representation.
 * @param value Value of the floating point number.
 */
mps::mps(unsigned long mantissa_length, unsigned long exponent_length, double value) {
    this->mantissa_length = mantissa_length;
    this->exponent_length = exponent_length;

    this->my_exponent.resize(this->exponent_length);
    this->my_mantissa.resize(this->mantissa_length);

    setBitArray(value);
}

mps::mps(){
    this->mantissa_length = 0;
    this->exponent_length = 0;
}

/**
 * Destructor for the multiprecision simulator.
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
    return this->bit_vector.size();
}

unsigned long mps::my_getBitArrayLength() const {
    return this->my_exponent.size() + this->my_mantissa.size() + 1;
}

/**
 * Returns the bit vector.
 *
 * @return bit vector
 */
vector<bool> mps::getBitArray() {
    return this->bit_vector;
}

vector<bool> mps::my_getBitArray() {

    vector<bool> ret;
    ret.reserve(1 + this->exponent_length + this->mantissa_length);

    ret.push_back(this->my_sign);
    ret.insert(ret.end(), this->my_exponent.begin(), this->my_exponent.end());
    ret.insert(ret.end(), this->my_mantissa.begin(), this->my_mantissa.end());

    return ret;
}

/**
 * Returns a pointer to the bit vector.
 *
 * @return pointer to bit vector
 */
vector<bool>* mps::getBitArrayReference() {
    return &this->bit_vector;
}

/**
 * Returns the value of the mps object as double.
 *
 * @return value as double.
 */
double mps::getValue() {

    // handle special cases
    if(isZero()){
        return 0;
    } else if (isInfinity() && isPositive()){
        return numeric_limits<double>::infinity();
    } else if (isInfinity()){
        return numeric_limits<double>::infinity() * -1;
    }

    double ret;

    // positive or negative
    if(bit_vector[0]){
        ret = -1;
    } else {
        ret = 1;
    }

    // handle mantissa
    for(auto i = exponent_length + 1; i < bit_vector.size(); i++){
        if(bit_vector[i]){
            if(ret >= 0){
                ret += pow(0.5, i - exponent_length);
            } else {
                ret -= pow(0.5, i - exponent_length);
            }
        }
    }

    // get exponent
    int exponent = 0;
    for(unsigned long i = 1; i <= exponent_length; i++){
        if(bit_vector[i]){
            exponent += (int) pow(2, exponent_length-i);
        }
    }

    // apply bias and apply exponent
    exponent -= getBias();
    ret *= pow(2, exponent);

    return ret;

}

/**
 * Returns true if the mps object is zero.
 *
 * @return true if zero.
 */
bool mps::isZero(){
    return all_of(bit_vector.begin(), bit_vector.end(), [](bool i){return !i;});
}

/**
 * Returns true if the mps object is positive or negative infinity.
 *
 * @return true if pos. or neg. infinity.
 */
bool mps::isInfinity() {

    for(unsigned long i = 1; i < exponent_length+1; i++){
        if(!bit_vector[i]){
            return false;
        }
    }

    for(unsigned long i = exponent_length+1; i < bit_vector.size(); i++){
        if(bit_vector[i]){
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
bool mps::isPositive(){

    if(bit_vector[0]){
        return false;
    } else {
        return true;
    }
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
        my_sign = true;
    } else {
        my_sign = false;
    }

    for(unsigned long i = 0; i < exponent_length; i++){
        my_exponent[i] = true;
    }

    for(unsigned long i = 0; i < mantissa_length; i++){
        my_mantissa[i] = false;
    }

    // TODO: Update Remove
    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    if(negative){
        bit_vector.push_back(true);
    } else {
        bit_vector.push_back(false);
    }

    for(unsigned long i = 0; i < exponent_length; i++){
        bit_vector.push_back(true);
    }

    for(unsigned long i = 0; i < mantissa_length; i++){
        bit_vector.push_back(false);
    }
}

/**
 * Sets the floating point number to zero.
 */
void mps::setZero(){

    my_sign = false;
    for(unsigned long i = 0; i < exponent_length; i++){
        my_exponent[i] = false;
    }
    for(unsigned long i = 0; i < mantissa_length; i++){
        my_mantissa[i] = false;
    }


    // TODO: Update Remove
    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    for(unsigned long i = 0; i < exponent_length + mantissa_length + 1; i++){
        bit_vector.push_back(false);
    }
}

/**
 * Sets the floating point number to NaN (not a number)
 */
void mps::setNaN(bool negative){

    if(negative){
        my_sign = true;
    } else {
        my_sign = false;
    }

    for(unsigned long i = 0; i < exponent_length; i++){
        my_exponent[i] = true;
    }

    my_mantissa[0] = true;
    for(unsigned long i = 1; i < mantissa_length; i++){
        my_mantissa[i] = false;
    }

    // TODO: Update Remove
    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    if(negative){
        bit_vector.push_back(true);
    } else {
        bit_vector.push_back(false);
    }

    for(unsigned long i = 0; i < exponent_length; i++){
        bit_vector.push_back(true);
    }

    bit_vector.push_back(true);

    for(unsigned long i = 1; i < mantissa_length; i++){
        bit_vector.push_back(false);
    }
}
//-------------------------------


// Converters
//-------------------------------

/**
 * Sets the bit vector of the mps object.
 *
 * @param value the value to which the bit array should be set.
 */
void mps::setBitArray(double value) {
// TODO: make value const

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
    my_exponent.clear();
    my_mantissa.clear();
    //-------------------------------


    // sign
    //-------------------------------
    if(value > 0){
        this->my_sign = false;
    } else {
        this->my_sign = true;
    }
    //-------------------------------


    // exponent
    //-------------------------------
    // calculate the exponent
    int mantissa_shift;
    if(abs(value) > numeric_limits<float>::max()){
        // When the value is too large rounding problems occur using log2.
        // (At least I think that is the problem)
        double tmp_value = abs(value);
        int tmp_count = 0;

        while(tmp_value > 1){
            tmp_value /= 2;
            tmp_count++;
        }

        mantissa_shift = tmp_count-1;
    } else {
        mantissa_shift = (int) floor(log2(abs(value)));
    }
    my_exponent_as_int =  (long) mantissa_shift; // TODO: remove casts and do better

    // Getting the exponent in binary format.
    // The sign is not relevant. Always returns a "positive" value.
    // TODO: Maybe prevent insert.
    for(auto i = my_exponent_as_int + getBias(); i > 0; i /= 2){
        my_exponent.insert(my_exponent.begin(), i%2);
    }

    // Fill not used but available bits with zero.
    if(my_exponent.size() > exponent_length) {
        cout << "ERROR: exponent too large" << endl;
        // TODO: add proper error handling.
    } else {
        for(unsigned long i = my_exponent.size(); i < exponent_length; i++){
            my_exponent.insert(my_exponent.begin(), false);
        }
    }

    //-------------------------------


    // mantissa
    //-------------------------------
    // TODO: replace tmpp_value
    auto tmpp_value = value / pow(2, mantissa_shift); // adjust the value so that everything is behind the decimal point.

    // Convert the part after the decimal point to a bit string.
    // The sign is not relevant. Always returns a "positive" value.
    double reminder = abs(tmpp_value) - floor(abs(tmpp_value));
    for(unsigned long i = 0; i < mantissa_length; i++){

        reminder *= 2;
        if(reminder >= 1){
            my_mantissa.push_back(true); reminder -= 1;
        } else{
            my_mantissa.push_back(false);
        }
    }
    //-------------------------------





    // TODO: Update Remove

    // prepare bit_vector
    //-------------------------------
    bit_vector.erase(bit_vector.begin(),bit_vector.end());
    //-------------------------------


    // exponent
    //-------------------------------
    // calculate the exponent
    mantissa_shift = 0;
    if(abs(value) > numeric_limits<float>::max()){
        // When the value is too large rounding problems occur using log2.
        // (At least I think that is the problem)
        double tmp_value = abs(value);
        int tmp_count = 0;

        while(tmp_value > 1){
            tmp_value /= 2;
            tmp_count++;
        }

        mantissa_shift = tmp_count-1;
    } else {
        mantissa_shift = (int) floor(log2(abs(value)));
    }
    int exponent_int =  mantissa_shift + getBias();

    // Getting the exponent in binary format.
    // The sign is not relevant. Always returns a "positive" value.
    vector<bool> exponent;
    for(int i = abs(exponent_int); i > 0; i /= 2){
        exponent.insert(exponent.begin(), i%2);
    }

    // Fill not used but available bits with zero.
    if(exponent.size() > exponent_length) {
        cout << "ERROR: exponent too large" << endl;
        // TODO: add proper error handling.
    } else {
        for(unsigned long i = exponent.size(); i < exponent_length; i++){
            exponent.insert(exponent.begin(), false);
        }
    }
    //-------------------------------


    // mantissa
    //-------------------------------
    value = value / pow(2, mantissa_shift); // adjust the value so that everything is behind the decimal point.

    // Convert the part after the decimal point to a bit string.
    // The sign is not relevant. Always returns a "positive" value.
    vector<bool> mantissa;
    reminder = (abs(value) - floor(abs(value)));
    for(unsigned long i = 0; i < mantissa_length; i++){

        reminder *= 2;
        if(reminder >= 1){
            mantissa.push_back(true); reminder -= 1;
        } else{
            mantissa.push_back(false);
        }
    }
    //-------------------------------


    // set everything together
    //-------------------------------
    if(value > 0){
        bit_vector.push_back(false);
    } else {
        bit_vector.push_back(true);
    }

    bit_vector.insert(bit_vector.end(), exponent.begin(), exponent.end());
    bit_vector.insert(bit_vector.end(), mantissa.begin(), mantissa.end());
    //-------------------------------

}
//-------------------------------

double mps::my_getValue() {

    // handle special cases
    if(isZero()){
        return 0;
    } else if (isInfinity() && isPositive()){
        return numeric_limits<double>::infinity();
    } else if (isInfinity()){
        return numeric_limits<double>::infinity() * -1;
    }

    //TODO: add NANs


    double ret;

    // positive or negative
    if(this->my_sign){
        ret = -1;
    } else {
        ret = 1;
    }

    // handle mantissa
    for(unsigned long i = 0; i < mantissa_length; i++){
        if(my_mantissa[i]){
            if(ret >= 0){
                ret += pow(0.5, i + 1);
            } else {
                ret -= pow(0.5, i + 1);
            }
        }
    }

    return ret * pow(2, my_exponent_as_int);
}










// operators
//-------------------------------

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

        this->my_exponent.resize(this->exponent_length);
        this->my_mantissa.resize(this->mantissa_length);
    } else {
        if (this->exponent_length != other.exponent_length) {
            cout << "ERROR: in = : Exponents do not match" << endl;
        }
        if (this->mantissa_length != other.mantissa_length) {
            cout << "ERROR: in = : Mantissas do not match" << endl;
        }
    }

    this->my_sign = other.my_sign;
    for(unsigned long i = 0; i < this->mantissa_length; i++){
        this->my_mantissa[i] = other.my_mantissa[i];
    }
    for(unsigned long i = 0; i < this->exponent_length; i++){
        this->my_exponent[i] = other.my_exponent[i];
    }
    this->my_exponent_as_int = other.my_exponent_as_int;


    // TODO: uplate delete

    this->bit_vector.erase(bit_vector.begin(), bit_vector.end());

    for(auto i : other.bit_vector){
        this->bit_vector.push_back(i);
    }

    this->mantissa_length = other.mantissa_length;
    this->exponent_length = other.exponent_length;

    return *this;
}


mps mps::addition(const mps &one, const mps &two, const bool sign) const {

    // Set up the return object.
    //-------------------------------
    mps ret;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    ret.my_sign = sign;
    //-------------------------------

    // Extract exponents and mantissas
    //-------------------------------
    vector<bool> a_mantissa = one.my_mantissa;
    a_mantissa.insert(a_mantissa.begin(), true);

    vector<bool> b_mantissa = two.my_mantissa;
    b_mantissa.insert(b_mantissa.begin(), true);
    //-------------------------------


    // Match mantissas and set exponent
    //-------------------------------
    unsigned long exponent_diff = 0;
    char larger_tmp = larger(one.my_exponent, two.my_exponent);
    if(1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(one.my_exponent, two.my_exponent));
        ret.my_exponent = one.my_exponent;
        ret.my_exponent_as_int = one.my_exponent_as_int;
        matchMantissas(&b_mantissa, &a_mantissa, exponent_diff);
    } else if(-1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(two.my_exponent, one.my_exponent));
        ret.my_exponent = two.my_exponent;
        ret.my_exponent_as_int = two.my_exponent_as_int;
        matchMantissas(&a_mantissa, &b_mantissa, exponent_diff);
    } else {
        ret.my_exponent = one.my_exponent;
        ret.my_exponent_as_int = one.my_exponent_as_int;
    }
    //-------------------------------

    // Actual addition and adjusting mantissa
    //-------------------------------
    bool carrier;
    vector<bool> mantissa = binaryAddition(a_mantissa, b_mantissa,true, &carrier);
    mantissa.erase(mantissa.begin(), mantissa.begin()+1);
    if(carrier){
        addOneToBinary(&ret.my_exponent);
        ret.my_exponent_as_int++;
    }
    //-------------------------------

    round(&mantissa, ret.mantissa_length);
    ret.my_mantissa = mantissa;

    return ret;
}
/**
 * Performs am addition to two mps floating point values.
 */
mps mps::operator+(mps& other) {

    if (this->exponent_length != other.exponent_length) {
        cout << "ERROR: in + : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in + : Mantissas do not match" << endl;
    }


    mps ret;
    if(this->isPositive() && other.isPositive()){
        ret = addition(*this, other, false);
    } else if(!this->isPositive() && !other.isPositive()){
        ret = addition(*this, other, true);
    } else if(!this->isPositive() && other.isPositive()){
        ret = subtraction(other, *this, false);
    } else if(this->isPositive() && !other.isPositive()){
        ret = subtraction(*this, other, false);
    } else {
        cout << "ERROR: in + : Sign problem" << endl;
    }






    // TODO: update delete


    // If signs are different perform Subtraction.
    //-------------------------------
    if(this->bit_vector[0] && !other.bit_vector[0]){
        this->bit_vector[0] = false;
        auto rett = other - *this;
        this->bit_vector[0] = true;
        return rett;
    } else if (!this->bit_vector[0] && other.bit_vector[0]) {
        other.bit_vector[0] = false;
        auto rett = *this - other;
        other.bit_vector[0] = true;
        return rett;
    }
    //-------------------------------

    // Set up the return object.
    //-------------------------------
    vector<bool>& ret_vector = ret.bit_vector;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    //-------------------------------


    // set sign
    //-------------------------------
    // TODO: Maybe simplify because of preceding if.
    if(this->isPositive() && other.isPositive()){
        ret.bit_vector.push_back(false);
    } else if(!this->isPositive() && !other.isPositive()){
        ret.bit_vector.push_back(true);
    }
    //-------------------------------


    // Handle special values.
    //-------------------------------
    if(this->isZero()){
        return other;
    } else if(other.isZero()){
        return *this;
    }
    //-------------------------------


    // Extract exponents and mantissas
    //-------------------------------
    vector<bool> a_mantissa(this->bit_vector.begin() + (long) exponent_length+1, this->bit_vector.end());
    a_mantissa.insert(a_mantissa.begin(), true);

    vector<bool> b_mantissa(other.bit_vector.begin() + (long) exponent_length+1, other.bit_vector.end());
    b_mantissa.insert(b_mantissa.begin(), true);

    vector<bool> a_exponent(this->bit_vector.begin()+1, this->bit_vector.begin()+1+ (long) this->exponent_length);
    vector<bool> b_exponent(other.bit_vector.begin()+1, other.bit_vector.begin()+1+ (long) other.exponent_length);
    vector<bool> exponent;
    //-------------------------------


    // Match mantissas and set exponent
    //-------------------------------
    unsigned long exponent_diff = 0;
    char larger_tmp = larger(a_exponent, b_exponent);
    if(1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(a_exponent, b_exponent));
        exponent.insert(exponent.end(), a_exponent.begin(), a_exponent.end());
        matchMantissas(&b_mantissa, &a_mantissa, exponent_diff);
    } else if(-1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(b_exponent, a_exponent));
        exponent.insert(exponent.end(), b_exponent.begin(), b_exponent.end());
        matchMantissas(&a_mantissa, &b_mantissa, exponent_diff);
    } else {
        exponent.insert(exponent.end(), a_exponent.begin(), a_exponent.end());
    }
    //-------------------------------


    // Actual addition and adjusting mantissa
    //-------------------------------
    bool carrier;
    vector<bool> mantissa = binaryAddition(a_mantissa, b_mantissa,true, &carrier);
    mantissa.erase(mantissa.begin(), mantissa.begin()+1);
    if(carrier){
        addOneToBinary(&exponent);
    }
    //-------------------------------


    round(&mantissa, ret.mantissa_length);
/*
    // Rounding and further adjustment of the mantissa
    //-------------------------------
    bool tmp = false;
    for(int i = ((int) mantissa.size())-exponent_diff+1 ; i < (int) mantissa.size(); i++){
        if (mantissa[i]){
            tmp = true;
            break;
        }
    }
    if(exponent_diff>0 && mantissa[mantissa.size()-exponent_diff] && tmp){
        mantissa.erase(mantissa.end()-exponent_diff, mantissa.end());
        if(addOneToBinary(&mantissa)){
            addOneToBinary(&exponent);
        }
    } else if(exponent_diff>0 && mantissa[mantissa.size()-exponent_diff]){
        if(mantissa[mantissa.size()-exponent_diff-1]){
            mantissa.erase(mantissa.end()-exponent_diff, mantissa.end());
            if(addOneToBinary(&mantissa)){
                addOneToBinary(&exponent);
            }
        } else {
            mantissa.erase(mantissa.end()-exponent_diff, mantissa.end());
        }
    }else {
        mantissa.erase(mantissa.end()-exponent_diff, mantissa.end());
    }
    //-------------------------------
*/

    // set everything together.
    //-------------------------------
    ret_vector.insert(ret_vector.end(), exponent.begin(), exponent.end());
    ret_vector.insert(ret_vector.end(), mantissa.begin(), mantissa.end());
    //-------------------------------

    return ret;
}

mps mps::subtraction(const mps &minued, const mps &subtrahend, bool sign) const {

    // Set up the return object.
    //-------------------------------
    mps ret;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    ret.my_sign = sign;
    //-------------------------------


    // Extract exponents and mantissas
    //-------------------------------
    vector<bool> a_mantissa = minued.my_mantissa;
    a_mantissa.insert(a_mantissa.begin(), true);

    vector<bool> b_mantissa = subtrahend.my_mantissa;
    b_mantissa.insert(b_mantissa.begin(), true);
    //-------------------------------


    // Match mantissas and set exponent
    //-------------------------------
    unsigned long exponent_diff = 0;
    char larger_tmp = larger(minued.my_exponent, subtrahend.my_exponent);
    if(1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(minued.my_exponent, subtrahend.my_exponent));
        ret.my_exponent = minued.my_exponent;
        ret.my_exponent_as_int = minued.my_exponent_as_int;
        matchMantissas(&b_mantissa, &a_mantissa, exponent_diff);
    } else if(-1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(subtrahend.my_exponent, minued.my_exponent));
        ret.my_exponent = subtrahend.my_exponent;
        ret.my_exponent_as_int = subtrahend.my_exponent_as_int;
        matchMantissas(&a_mantissa, &b_mantissa, exponent_diff);
    } else {
        ret.my_exponent = minued.my_exponent;
        ret.my_exponent_as_int = minued.my_exponent_as_int;
    }
    //-------------------------------


    // Actual Subtraction
    //-------------------------------
    larger_tmp = larger(a_mantissa, b_mantissa);
    if(1 == larger_tmp){
        ret.my_mantissa = binarySubtraction(a_mantissa, b_mantissa);
    } else if(-1 == larger_tmp){
        ret.my_mantissa = binarySubtraction(b_mantissa, a_mantissa);
        ret.my_sign = !ret.my_sign; // flip sign
    } else {
        ret.setZero();
        return ret;
    }
    //-------------------------------


    // Adjust mantissa and exponent
    //-------------------------------
    unsigned long exponent_shift = 0;
    for(unsigned long i = 0; i < ret.my_mantissa.size(); i++){
        if(ret.my_mantissa[i]){
            exponent_shift = i;
            break;
        }
    }

    ret.my_mantissa.erase(ret.my_mantissa.begin(), ret.my_mantissa.begin()+ (long) exponent_shift+1);
    ret.my_exponent_as_int -= (long) exponent_shift;

    // TODO: Place for improvement
    vector<bool> exponent_shift_binary = intToBinary(exponent_shift);
    for(unsigned long i = exponent_shift_binary.size(); i < ret.exponent_length; i++){
        exponent_shift_binary.insert(exponent_shift_binary.begin(), false);
    }
    ret.my_exponent = binarySubtraction(ret.my_exponent, exponent_shift_binary);

    //-------------------------------


    round(&ret.my_mantissa, ret.mantissa_length);


    return ret;
}
mps mps::operator-(mps& other) {

    if (this->exponent_length != other.exponent_length) {
        cout << "ERROR: in - : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in - : Mantissas do not match" << endl;
    }


    mps ret;
    if(this->isPositive() && other.isPositive()){
        ret = subtraction(*this, other, false);
    } else if(!this->isPositive() && !other.isPositive()){
        ret = subtraction(*this, other, true);
    } else if(this->isPositive() && !other.isPositive()) {
        ret = ret = addition(*this, other, true);
    } else if(!this->isPositive() && other.isPositive()) {
        ret = ret = addition(*this, other, false);
    } else {
        cout << "ERROR: in - : Sign problem" << endl;
    }





    // If signs are different perform Subtraction.
    //-------------------------------
    // TODO: write tests to confirm that the input values are const.
    if(this->bit_vector[0] && !other.bit_vector[0]){
        other.bit_vector[0] = true;
        auto rett = other + *this;
        other.bit_vector[0] = false;
        return rett;
    } else if (!this->bit_vector[0] && other.bit_vector[0]) {
        other.bit_vector[0] = false;
        auto rett = *this + other;
        other.bit_vector[0] = true;
        return rett;
    }
    //-------------------------------


    // Set up the return object.
    //-------------------------------
    vector<bool>& ret_vector = ret.bit_vector;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    //-------------------------------


    // set sign
    //-------------------------------
    // TODO: Maybe simplify because of preceding if.
    if(this->isPositive() && other.isPositive()){
        ret.bit_vector.push_back(false);
    } else if(!this->isPositive() && !other.isPositive()){
        ret.bit_vector.push_back(true);
    }
    //-------------------------------


    // Handle special values.
    //-------------------------------
    if(this->isZero()){
        return other;
    } else if(other.isZero()){
        return *this;
    }
    //-------------------------------

    // Extract exponents and mantissas
    //-------------------------------
    vector<bool> a_mantissa(this->bit_vector.begin()+ (long) exponent_length+1, this->bit_vector.end());
    a_mantissa.insert(a_mantissa.begin(), true);

    vector<bool> b_mantissa(other.bit_vector.begin()+ (long) exponent_length+1, other.bit_vector.end());
    b_mantissa.insert(b_mantissa.begin(), true);

    vector<bool> a_exponent(this->bit_vector.begin()+1, this->bit_vector.begin()+1+ (long) this->exponent_length);
    vector<bool> b_exponent(other.bit_vector.begin()+1, other.bit_vector.begin()+1+ (long) other.exponent_length);
    vector<bool> exponent;
    //-------------------------------


    // Match mantissas and set exponent
    //-------------------------------
    unsigned long exponent_diff;
    char larger_tmp = larger(a_exponent, b_exponent);
    if(1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(a_exponent, b_exponent));
        exponent.insert(exponent.end(), a_exponent.begin(), a_exponent.end());
        matchMantissas(&b_mantissa, &a_mantissa, exponent_diff);
    } else if(-1 == larger_tmp){
        exponent_diff = binaryToInt(binarySubtraction(b_exponent, a_exponent));
        exponent.insert(exponent.end(), b_exponent.begin(), b_exponent.end());
        matchMantissas(&a_mantissa, &b_mantissa, exponent_diff);
    } else {
        exponent.insert(exponent.end(), a_exponent.begin(), a_exponent.end());
    }
    //-------------------------------


    // Actual Subtraction
    //-------------------------------
    vector<bool> mantissa;
    larger_tmp = larger(a_mantissa, b_mantissa);
    if(1 == larger_tmp){
        mantissa = binarySubtraction(a_mantissa, b_mantissa);
    } else if(-1 == larger_tmp){
        mantissa = binarySubtraction(b_mantissa, a_mantissa);
        ret_vector[0] = !ret_vector[0]; // flip sign
    } else {
        ret.setZero();
        return ret;
    }
    //-------------------------------


    // Adjust mantissa and exponent
    //-------------------------------
    unsigned long exponent_shift = 0;
    for(unsigned long i = 0; i < mantissa.size(); i++){
        if(mantissa[i]){
            exponent_shift = i;
            break;
        }
    }

    mantissa.erase(mantissa.begin(), mantissa.begin()+ (long) exponent_shift+1);
    vector<bool> exponent_shift_binary = intToBinary(exponent_shift);
    for(unsigned long i = exponent_shift_binary.size(); i < ret.exponent_length; i++){
        exponent_shift_binary.insert(exponent_shift_binary.begin(), false);
    }
    exponent = binarySubtraction(exponent, exponent_shift_binary);
    //-------------------------------


    round(&mantissa, ret.mantissa_length);
    /*
    // rounding
    //-------------------------------
    if((int) mantissa.size() > ret.mantissa_length){
        bool tmp = false;
        for(int i = ret.mantissa_length+1 ; i < (int) mantissa.size(); i++){
            if (mantissa[i]){
                tmp = true;
                break;
            }
        }
        if(mantissa[ret.mantissa_length] && tmp){
            mantissa.erase(mantissa.end()-((int) mantissa.size()-ret.mantissa_length), mantissa.end());
            if(addOneToBinary(&mantissa)){
                addOneToBinary(&exponent);
            }
        } else if(mantissa[ret.mantissa_length]){
            if(mantissa[ret.mantissa_length-1]){
                mantissa.erase(mantissa.end()-((int) mantissa.size()-ret.mantissa_length), mantissa.end());
                if(addOneToBinary(&mantissa)){
                    addOneToBinary(&exponent);
                }
            } else {
                mantissa.erase(mantissa.end()-((int) mantissa.size()-ret.mantissa_length), mantissa.end());
            }
        }else {
            mantissa.erase(mantissa.end()-((int) mantissa.size()-ret.mantissa_length), mantissa.end());
        }
    }

    //-------------------------------
*/

    // set everything together.
    //-------------------------------
    ret_vector.insert(ret_vector.end(), exponent.begin(), exponent.end());
    ret_vector.insert(ret_vector.end(), mantissa.begin(), mantissa.end());
    //-------------------------------

    return ret;
}

mps mps::operator*(const mps& other) const {

    // Set up the return object.
    //-------------------------------
    mps ret;
    vector<bool>& ret_vector = ret.bit_vector;
    ret.exponent_length = this->exponent_length;
    ret.mantissa_length = this->mantissa_length;
    //-------------------------------


    // Set up sign.
    //-------------------------------
    if(this->bit_vector[0] == other.bit_vector[0]){
        ret_vector.push_back(false);
    } else {
        ret_vector.push_back(true);
    }
    //-------------------------------

    if(this->my_sign == other.my_sign){
        ret.my_sign = false;
    } else {
        ret.my_sign = true;
    }

    ret.my_sign = this->my_sign != other.my_sign;



    vector<bool> A(this->bit_vector.begin()+(long) exponent_length+1, this->bit_vector.end());
    vector<bool> S;

    A.reserve(A.size() + other.bit_vector.size() + 1 +2 +2);
    A.insert(A.begin(), true);
    A.insert(A.begin(), false);
    S.reserve(A.size() + other.bit_vector.size() + 1 +2 +2);

    for(unsigned long i = 0; i < A.size(); i++){
        S.push_back(!A[i]);
    }
    addOneToBinary(&S);

    for(unsigned long i = 0; i < other.mantissa_length + 1 +1 +1; i++){
        A.push_back(false);
        S.push_back(false);
    }

    vector<bool> P;
    P.reserve(A.size() + other.bit_vector.size() + 1 +2 +2);
    for(unsigned long i = 0; i < this->mantissa_length+1+1; i++){
        P.push_back(false);
    }
    P.push_back(false);
    P.push_back(true);
    for(unsigned long i = 0; i < other.mantissa_length; i++){
       P.push_back(other.bit_vector[i+1+other.exponent_length]);
    }
    P.push_back(false);


    for(unsigned long i = 0; i < other.mantissa_length+2; i++){


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

    /*
    // rounding
    //-------------------------------
    if((int) P.size() > ret.mantissa_length){
        bool tmp = false;
        for(int i = ret.mantissa_length+1 ; i < (int) P.size(); i++){
            if (P[i]){
                tmp = true;
                break;
            }
        }
        if(P[ret.mantissa_length] && tmp){
            P.erase(P.end()-((int) P.size()-ret.mantissa_length), P.end());
            if(addOneToBinary(&P)){
                addOneToBinary(&P);
            }
        } else if(P[ret.mantissa_length]){
            if(P[ret.mantissa_length-1]){
                P.erase(P.end()-((int) P.size()-ret.mantissa_length), P.end());
                if(addOneToBinary(&P)){
                    addOneToBinary(&P);
                }
            } else {
                P.erase(P.end()-((int) P.size()-ret.mantissa_length), P.end());
            }
        }else {
            P.erase(P.end()-((int) P.size()-ret.mantissa_length), P.end());
        }
    }
    //-------------------------------
*/



    vector<bool> a_exponent(this->bit_vector.begin()+1, this->bit_vector.begin()+1+ (long) this->exponent_length);
    vector<bool> b_exponent(other.bit_vector.begin()+1, other.bit_vector.begin()+1+ (long) other.exponent_length);

    // TODO: Check for carry
    b_exponent[0] = !b_exponent[0];
    addOneToBinary(&b_exponent);
    if(count <= 1){
        addOneToBinary(&b_exponent);
    }

    vector<bool> exponent = binaryAddition(a_exponent, b_exponent, false); // TODO: remove

    ret.my_exponent = binaryAddition(a_exponent, b_exponent, false);
    ret.my_exponent_as_int = (long) binaryToInt(ret.my_exponent) - ret.getBias();
    ret.my_mantissa = P;

    // set everything together.
    //-------------------------------
    ret_vector.insert(ret_vector.end(), exponent.begin(), exponent.end());
    ret_vector.insert(ret_vector.end(), P.begin(), P.end());
    //-------------------------------


    return ret;
}
//-------------------------------


// helper methods
//-------------------------------



/**
 * Returns the bias of the exponent.
 *
 * @return bias of the exponent
 */
int mps::getBias() const{
    return ((int) pow (2, exponent_length)) / 2 -1;
}


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

    //TODO: Remove when finished.
    if(a.size() != b.size()){
        cout << "ERROR: binary addition vectors must have same length" << endl;
        return ret;
    }

    // full adder
    // TODO: Use while loop
    for(long i = (long) a.size()-1; i >= 0; i--){
        ret.insert(ret.begin(), (a[(unsigned long)i] ^ b[(unsigned long)i]) ^ carrier);
        carrier = ((a[(unsigned long) i] && b[(unsigned long)i]) || (a[(unsigned long)i] && carrier)) || (b[(unsigned long)i] && carrier);
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

[[nodiscard]] long mps::getExponentAsInt(){
    return my_exponent_as_int;
}
//-------------------------------