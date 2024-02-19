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

    this->setValue(value);
}

/**
 * Constructor for a multiprecision simulator object. The value is set to NAN.
 * Info: That the value is set to NAN is probably not necessary but it maybe prevents errors because of false use.
 *
 * @param mantisse Mantisse of the floating point representation.
 * @param exponent Exponent of the floating point representation.
 */
mps::mps(unsigned long mantissa_length, unsigned long exponent_length) {
    this->mantissa_length = mantissa_length;
    this->exponent_length = exponent_length;

    this->exponent.resize(this->exponent_length);
    this->mantissa.resize(this->mantissa_length);

    this->sign = false;

    this->setNaN();     // Set it to be safe.
}

/**
 * Constructor for an empty multiprecision simulator object.
 */
mps::mps(){
    this->mantissa_length = 0;
    this->exponent_length = 0;

    this->sign = false;
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

    // get exponent
    long exp = 0;
    for(unsigned long i = 0; i < exponent_length; i++){
        if(this->exponent[i]){
            exp += (long) pow(2, exponent_length-i-1);
        }
    }

    // apply bias and apply exponent
    exp -= getBias();

    return ret * pow(2, exp);
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

    if( exponent.empty() || mantissa.empty()){
        exponent.resize(exponent_length);
        mantissa.resize(exponent_length);
    }

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

    if( exponent.empty() || mantissa.empty()){
        exponent.resize(exponent_length);
        mantissa.resize(exponent_length);
    }

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

    if( exponent.empty() || mantissa.empty()){
        exponent.resize(exponent_length);
        mantissa.resize(exponent_length);
    }

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


    if(this->isNaN() || other.isNaN()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setNaN();
        return ret;

    } else if(this->isInfinity() && other.isInfinity()){
        mps ret(this->mantissa_length, this->exponent_length);

        if(this->isPositive() == other.isPositive()){
            ret.setInf(!this->isPositive());
        } else {
            ret.setNaN();
        }

        return ret;
    } else if(this->isInfinity()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setInf(!this->isPositive());
        return ret;

    } else if(other.isInfinity()){

        mps ret(other.mantissa_length, other.exponent_length);
        ret.setInf(!other.isPositive());
        return ret;

    } else if(this->isZero()){
        return other;
    } else if(other.isZero()){
        return *this;
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


    if(this->isNaN() || other.isNaN()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setNaN();
        return ret;

    } else if(this->isInfinity() && other.isInfinity()){
        mps ret(this->mantissa_length, this->exponent_length);

        if(this->isPositive() == other.isPositive()){
            ret.setNaN();
        } else {
            ret.setInf(!this->isPositive());
        }

        return ret;
    } else if(this->isInfinity()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setInf(!this->isPositive());
        return ret;

    } else if(other.isInfinity()){

        mps ret(other.mantissa_length, other.exponent_length);
        ret.setInf(other.isPositive());
        return ret;

    } else if(this->isZero()){
        auto ret = other;
        ret.sign = !ret.sign;
        return ret;
    } else if(other.isZero()){
        return *this;
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
        cout << "ERROR: in * : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in * : Mantissas do not match" << endl;
    }


    if(this->isNaN() || other.isNaN()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setNaN();
        return ret;

    } else if(this->isInfinity() && other.isInfinity()){
        mps ret(this->mantissa_length, this->exponent_length);

        if(this->isPositive() == other.isPositive()){
            ret.setNaN();
        } else {
            ret.setInf(!this->isPositive());
        }

        return ret;
    } else if(this->isInfinity()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setInf(!this->isPositive());
        return ret;

    } else if(other.isInfinity()){

        mps ret(other.mantissa_length, other.exponent_length);
        ret.setInf(!other.isPositive());
        return ret;

    } else if(this->isZero() || other.isZero()){
        mps ret(other.mantissa_length, other.exponent_length);
        ret.setZero();
        return ret;
    }


    return multiplication(*this, other, this->sign != other.sign);
}

/**
 * Performs a division to two mps floating point values.
 *
 * It is responsible for error handling, special values and choosing with "calculation" to use.
 */
mps mps::operator/(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        cout << "ERROR: in / : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in / : Mantissas do not match" << endl;
    }


    if(this->isNaN() || other.isNaN()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setNaN();
        return ret;

    } else if(this->isInfinity() && other.isInfinity()){
        mps ret(this->mantissa_length, this->exponent_length);

        if(this->isPositive() == other.isPositive()){
            ret.setNaN();
        } else {
            ret.setInf(!this->isPositive());
        }

        return ret;
    } else if(this->isInfinity()){

        mps ret(this->mantissa_length, this->exponent_length);
        ret.setInf(!this->isPositive());
        return ret;

    } else if(other.isInfinity()){

        mps ret(other.mantissa_length, other.exponent_length);
        ret.setZero();
        return ret;

    } else if(this->isZero()){
        mps ret(other.mantissa_length, other.exponent_length);
        ret.setZero();
        return ret;
    } else if(other.isZero()){
        mps ret(other.mantissa_length, other.exponent_length);
        ret.setInf(!this->isPositive());
        return ret;
    }


    return division(*this, other, this->sign != other.sign);
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

        while(tmp_value >= 1){
            tmp_value /= 2;
            tmp_count++;
        }
        mantissa_shift = tmp_count-1;
    } else {
        mantissa_shift = (long) floor(log2(abs(value)));
    }

    // Getting the exponent in binary format.
    // The sign is not relevant. Always returns a "positive" value.
    for(auto i = mantissa_shift + getBias(); i > 0; i /= 2){
        exponent.insert(exponent.begin(), i % 2);
    }

    bool value_too_large = false;
    if(exponent.size() > exponent_length){
        value_too_large = true;
    } else if(exponent.size() == exponent_length){
        value_too_large = allTrue(this->exponent);
    }
    // Fill not used but available bits with zero.
    if  (value_too_large){

        exponent.resize(exponent_length);
        mantissa.resize(mantissa_length);

        if(value > 0){
            this->setInf();
        } else {
            this->setInf(true);
        }

        return;

    } else {
        exponent.insert(exponent.begin(), exponent_length-exponent.size(), false);
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
mps mps::addition(const mps &one, const mps &two, const bool set_sign) {

    // Set up the return object.
    //-------------------------------
    mps ret;
    ret.exponent_length = one.exponent_length;
    ret.mantissa_length = one.mantissa_length;
    ret.sign = set_sign;
    //-------------------------------


    // addition of mantissas.
    //-------------------------------
    auto add = []
            (const vector<bool> &first, const vector<bool> &second, unsigned long off_set, bool *carrier) -> vector<bool>{

        bool hd[2] = {true, true};
        bool p[2] = {false, false};

        return binaryOffsetAddition(first, second, off_set, true, p, hd, carrier);
    };
    //-------------------------------

    // set exponent and addition
    //-------------------------------
    bool carrier;
    unsigned long exponent_diff;
    char larger_tmp = larger(one.exponent, two.exponent);
    if(1 == larger_tmp){

        exponent_diff = binaryToInt(binarySubtraction(one.exponent, two.exponent));
        ret.exponent = one.exponent;

        if(exponent_diff <= one.mantissa.size()){
            ret.mantissa = add(two.mantissa, one.mantissa, exponent_diff, &carrier);
        } else {
            ret.mantissa = one.mantissa;
            return ret;
        }

    } else if(-1 == larger_tmp){

        exponent_diff = binaryToInt(binarySubtraction(two.exponent, one.exponent));
        ret.exponent = two.exponent;

        if(exponent_diff <= one.mantissa.size()){
            ret.mantissa = add(one.mantissa, two.mantissa, exponent_diff, &carrier);
        } else {
            ret.mantissa = two.mantissa;
            return ret;
        }

    } else {

        ret.exponent = two.exponent;
        ret.mantissa = add(one.mantissa, two.mantissa, 0, &carrier);
    }
    //-------------------------------

    // adjusting the mantissa
    //-------------------------------
    ret.mantissa.erase(ret.mantissa.begin(), ret.mantissa.begin()+1);
    if(carrier){
        addOneToBinary(&ret.exponent);
        if(allTrue(ret.exponent)){
            ret.setInf(set_sign);
            return ret;
        }
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
mps mps::subtraction(const mps &minued, const mps &subtrahend, bool set_sign) {

    // Set up the return object.
    //-------------------------------
    mps ret;
    ret.exponent_length = minued.exponent_length;
    ret.mantissa_length = minued.mantissa_length;
    ret.sign = set_sign;
    //-------------------------------


    // subtraction of mantissas.
    //-------------------------------
    auto subtract = []
            (const vector<bool> &first, const vector<bool> &sub, unsigned long off_set) -> vector<bool>{

            bool carrier;

            auto iSub = invertAndAddOne(sub, &carrier);
            bool hd[2] = {carrier, true};
            bool p[2] = {true, false};

            return binaryOffsetAddition(iSub, first, off_set, false, p, hd);
    };
    //-------------------------------


    // set exponent and do calculation.
    //-------------------------------
    char larger_tmp = larger(minued.exponent, subtrahend.exponent);
    if(1 == larger_tmp){

        unsigned long exponent_diff = binaryToInt(binarySubtraction(minued.exponent, subtrahend.exponent));
        ret.exponent = minued.exponent;

        if(exponent_diff <= minued.mantissa.size()){
            ret.mantissa = subtract(minued.mantissa, subtrahend.mantissa, exponent_diff);
        } else if (exponent_diff == minued.mantissa.size() + 1){
            ret.mantissa = minued.mantissa;
            subtractOneFromBinary(&ret.exponent);
            subtractOneFromBinary(&ret.mantissa);
            return ret;
        } else {
            ret.mantissa = minued.mantissa;
            return ret;
        }

    } else if(-1 == larger_tmp){

        unsigned long exponent_diff = binaryToInt(binarySubtraction(subtrahend.exponent, minued.exponent));
        ret.exponent = subtrahend.exponent;
        ret.sign = !ret.sign; // flip sign

        if(exponent_diff <= minued.mantissa.size()){
            ret.mantissa = subtract(subtrahend.mantissa, minued.mantissa, exponent_diff);
        } else if(exponent_diff == minued.mantissa.size() + 1){
            ret.mantissa = subtrahend.mantissa;
            subtractOneFromBinary(&ret.exponent);
            subtractOneFromBinary(&ret.mantissa);
            return ret;
        } else {
            ret.mantissa = subtrahend.mantissa;
            return ret;
        }

    } else {

        ret.exponent = minued.exponent;

        larger_tmp = larger(minued.mantissa, subtrahend.mantissa);
        if(1 == larger_tmp){

            ret.mantissa = subtract(minued.mantissa, subtrahend.mantissa, 0);

        } else if(-1 == larger_tmp){

            ret.mantissa = subtract(subtrahend.mantissa, minued.mantissa, 0);
            ret.sign = !ret.sign; // flip sign

        } else {
            ret.setZero();
            return ret;
        }

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

        // for every "right shift" pull one zero form the right.
        ret.mantissa.push_back(false);
    }

    ret.mantissa.erase(ret.mantissa.begin(), ret.mantissa.begin() + (long) exponent_shift + 1);


    vector<bool> exponent_shift_binary = intToBinary(exponent_shift);
    exponent_shift_binary.insert(exponent_shift_binary.begin(), ret.exponent_length - exponent_shift_binary.size(), false);
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
mps mps::multiplication(const mps& one, const mps& two, bool set_sign) {

    // Set up the return object.
    //-------------------------------
    mps ret(one.mantissa_length, one.exponent_length);
    ret.sign = set_sign;
    //-------------------------------


    // Calculate the exponent
    //-------------------------------
    if(one.exponent[0] && two.exponent[0]){ // Both exponents are positive.

        vector<bool> addend = two.exponent;

        addend[0] = !addend[0];
        addOneToBinary(&addend);    // Carrier bit must not be checked because of if-statement.

        bool tmp_carry;
        ret.exponent = binaryAddition(one.exponent, addend, &tmp_carry);

        // Check if the number will be more than the maximal allowed value.
        if(tmp_carry && one.exponent[0] && !addend[0]){
            ret.setInf(ret.sign);
            return ret;
        }

    } else {

        vector<bool> subtrahend;
        subtrahend.reserve(two.exponent.size());
        subtrahend.push_back(false);
        for(unsigned long i = 1; i < two.exponent.size(); i++){
            subtrahend.push_back(true);
        }

        if(one.exponent[0] && !two.exponent[0]){
            subtrahend = binarySubtraction(subtrahend, one.exponent);
            ret.exponent = binarySubtraction(two.exponent, subtrahend);
        } else {
            subtrahend = binarySubtraction(subtrahend, two.exponent);

            if(!one.exponent[0] && !two.exponent[0] && 1 == larger(subtrahend, one.exponent)){
                ret.setZero();
                return ret;
            }

            ret.exponent = binarySubtraction(one.exponent, subtrahend);
        }
    }
    //-------------------------------


    // Calculate the mantissa
    //-------------------------------
    //bool prefix[2] = {false, true};

    vector<bool> S;
    bool carrier;
    S = invertAndAddOne(one.mantissa, &carrier);
    S.insert(S.begin(), carrier);
    S.insert(S.begin(), true);


    // set up P vector (product)
    vector<bool> &P = ret.mantissa;     // Use reference P in order to keep the naming.
    P.clear();
    P.reserve(one.mantissa.size() + two.mantissa_length + 5);              // 3 => 2* (sign and "invisible 1") + 1
    for(unsigned long i = 0; i < one.mantissa_length + 2; i++){    // 2 => sign and "invisible 1"
        P.push_back(false);
    }
    P.push_back(false);
    P.push_back(true);
    for(unsigned long i = 0; i < two.mantissa_length; i++){
        P.push_back(two.mantissa[i]);
    }
    P.push_back(false);

    // main loop
    //unsigned long sum = 0;
    for(unsigned long i = 0; i < two.mantissa_length+2; i++){


        if(!P.end()[-2] && P.back()){
            binarySummation(&P, one.mantissa, true);
            //sum++;
        } else if(P.end()[-2] && !P.back()) {
            binarySummation(&P, S);
            //sum++;
        }

        P.pop_back();
        P.insert(P.begin(), P[0]);

    }

    P.pop_back();
    P.erase (P.begin());        // delete "invisible 1"

    // normalize
    int count = 0;
    for(unsigned long i = 0; i < P.size(); i++){
        if(P[0]){
            P.erase(P.begin());
            break;
        }
        P.erase(P.begin());
        count++;
    }
    //-------------------------------


    // rounding
    //-------------------------------
    round(&P, ret.mantissa_length);

    if(count <= 1){
        addOneToBinary(&ret.exponent);
    }
    //-------------------------------

    // cout << "Sum: " << sum << endl;
    return ret;
}

/**
 * Performs a division on two mps objects which have the same sign.
 *
 * @param dividend reference to the dividend of the division.
 * @param divisor reference to the divisor of the division.
 * @param set_sign the sign to which the final result should be set.
 * @return the resulting mps object.
 */
mps mps::division(const mps& dividend, const mps& divisor, bool set_sign) {

    // Set up the return object.
    //-------------------------------
    mps ret; //(dividend.mantissa_length, divisor.exponent_length);
    ret.mantissa_length = dividend.mantissa_length;
    ret.exponent_length = dividend.exponent_length;
    ret.sign = set_sign;
    //-------------------------------


    // Calculate the exponent
    //-------------------------------
    if(divisor.exponent[0]){ // Both exponents are positive.

        vector<bool> subtrahend = divisor.exponent;

        subtrahend[0] = !subtrahend[0];
        addOneToBinary(&subtrahend);    // Carrier bit must not be checked because of if-statement.

        ret.exponent = binarySubtraction(dividend.exponent, subtrahend);

        // TODO: is there a more intelligent way
        if(1 == larger(ret.exponent, dividend.exponent)){
            ret.setZero();
            return ret;
        }


    } else if(!divisor.exponent[0]){

        vector<bool> subtrahend;
        subtrahend.reserve(divisor.exponent.size());
        subtrahend.push_back(false);
        for(unsigned long i = 1; i < divisor.exponent.size(); i++){
            subtrahend.push_back(true);
        }

        subtrahend = binarySubtraction(subtrahend, divisor.exponent);

        bool carrier;
        ret.exponent = binaryAddition(dividend.exponent, subtrahend, &carrier);

        // TODO: is there a more intelligent way
        if(carrier || allTrue(ret.exponent)){
            ret.setInf(ret.sign);
            return ret;
        }

    }
    //-------------------------------


    // Division
    //-------------------------------

    // remainder
    vector<bool> R = dividend.mantissa;
    R.insert(R.begin(), true);
    R.insert(R.begin(), 2, false);

    // quotient
    vector<bool> &Q = ret.mantissa;         // reference for better naming.
    Q.resize(ret.mantissa_length, false);

    // subtrahend (used for binarySummation)
    auto S = invertAndAddOne(divisor.mantissa, nullptr, true);    // carry bit must not be checked because d must not be 0;


    // main loop
    for(auto && i : Q){
        shiftLeft(&R);

        char tmp = larger(R, divisor.mantissa, true);
        if(1 == tmp || 0 == tmp){
            binarySummation(&R, S);
            i = true;
        }
    }
    //-------------------------------


    // normalisation
    //-------------------------------
    unsigned long count = 0;
    vector<bool> count_vec(divisor.exponent.size(), false);

    for(unsigned long i = 0; i < Q.size(); i++){
        if(Q[0]){
            Q.erase(Q.begin());
            count++;
            //addOneToBinary(&count_vec);
            break;
        } else {
            Q.erase(Q.begin());
            count++;
            addOneToBinary(&count_vec);
        }
    }

    // rerun the algorithm for every leading bit removed.
    for(unsigned long i = 0; i < count; i++){
        shiftLeft(&R);

        char tmp = larger(R, divisor.mantissa, true);
        if(1 == tmp || 0 == tmp){
            // R = binarySubtraction(R, D);
            binarySummation(&R, S);
            Q.push_back(true);
        } else {
            Q.push_back(false);
        }
    }

    ret.exponent = binarySubtraction(ret.exponent, count_vec);
    //-------------------------------


    // rounding
    //-------------------------------
    shiftLeft(&R);

    char tmp = larger(R, divisor.mantissa, true);
    if(1 == tmp || 0 == tmp){
        addOneToBinary(&Q);
    }
    //-------------------------------

    return ret;
}
//-------------------------------


// comparators
//-------------------------------
bool mps::operator>(const mps& other) const{

    if (this->exponent_length != other.exponent_length) {
        cout << "ERROR: in > : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in > : Mantissas do not match" << endl;
    }

    if(this->isNaN() || other.isNaN()){
        return false;
    }

    if(!this->sign &&!other.sign) {             // positive positive case
        return larger(*this, other);
    } else if(!this->sign && other.sign) {      // positive negative case
        return true;
    } else if(this->sign && !other.sign){       // negative positive case
        return false;
    } else {                                    // negative negative case
        return larger(other, *this);
    }
}

bool mps::operator<(const mps& other) const{

    if (this->exponent_length != other.exponent_length) {
        cout << "ERROR: in < : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in < : Mantissas do not match" << endl;
    }

    if(this->isNaN() || other.isNaN()){
        return false;
    }

    if(!this->sign &&!other.sign) {             // positive positive case
        return smaller(*this, other);
    } else if(!this->sign && other.sign) {      // positive negative case
        return false;
    } else if(this->sign && !other.sign){       // negative positive case
        return true;
    } else {                                    // negative negative case
        return smaller(other, *this);
    }
}

bool mps::operator>=(const mps& other) const {

    if (this->exponent_length != other.exponent_length) {
        cout << "ERROR: in > : Exponents do not match" << endl;
    }
    if (this->mantissa_length != other.mantissa_length) {
        cout << "ERROR: in > : Mantissas do not match" << endl;
    }

    if(this->isNaN() || other.isNaN()){
        return false;
    }

    if(!this->sign &&!other.sign) {             // positive positive case
        return largerEqual(*this, other);
    } else if(!this->sign && other.sign) {      // positive negative case
        return true;
    } else if(this->sign && !other.sign){       // negative positive case
        return false;
    } else {                                    // negative negative case
        return largerEqual(other, *this);
    }
}



[[nodiscard]] bool mps::larger(const mps& one, const mps& two){

    auto res = compare(one, two);

    if(-1 == res || 0 == res) {
        return false;
    } else {
        return true;
    }
}

[[nodiscard]] bool mps::smaller(const mps& one, const mps& two){

    auto res = compare(one, two);

    if(1 == res || 0 == res){
        return false;
    } else {
        return true;
    }
}

[[nodiscard]] bool mps::largerEqual(const mps& one, const mps& two){

    auto res = compare(one, two);

    if(1 == res || 0 == res) {
        return true;
    } else {
        return false;
    }
}

[[nodiscard]] char mps::compare(const mps& one, const mps& two){

    // compare exponent
    for(unsigned long i = 0; i < one.exponent_length; i++){

        if(one.exponent[i] && !two.exponent[i]){
            return 1;
        }
        if(two.exponent[i] && !one.exponent[i]){
            return -1;
        }
    }

    // compare mantissa
    for(unsigned long i = 0; i < one.mantissa_length; i++){

        if(one.mantissa[i] && !two.mantissa[i]){
            return 1;
        }
        if(two.mantissa[i] && !one.mantissa[i]){
            return -1;
        }
    }

    // equal case
    return 0;
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
vector<bool> mps::binaryAddition(const vector<bool>& a, const vector<bool>& b, bool* carrier_return){

    vector<bool> ret;
    bool carrier = false;

    // full adder
    for(auto i = a.size(); i > 0;){
        i--;
        ret.insert(ret.begin(), (a[i] ^ b[i]) ^ carrier);
        carrier = ((a[i] && b[i]) || (a[i] && carrier)) || (b[i] && carrier);
    }

    /*
    // adjust if carrier bit is 1
    if(carry && carrier){
        ret.insert(ret.begin(), true);
        ret.pop_back();
    }
     */

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

    bool carrie;
    auto tmp = invertAndAddOne(subtrahend, &carrie);

    if(carrie){
        return minuend; // if there is a carrier bit present at the end the subtrahend is zero.
    }

    return binaryAddition(minuend, tmp);
}

/**
 * Performs an addition but adds directly to the summand. The addend can be smaller.
 * If so the addend will be "virtually" shifted to the left so the the first bits match.
 *
 * ATTENTION: The function does not check whether a carrier bit is present at the end,
 * since it is expected that the vectors either have an appropriate structure or actually a subtraction is performed.
 *
 * @param summand pointer to the vector to which the addend is added.
 * @param addend reference to the addend which is going to be added to the summand.
 */
void mps::binarySummation(vector<bool> *summand, const vector<bool> &addend, const bool prefix) {

    bool carrier = false;
    bool tmp;
    auto j = addend.size(); // + start

    if(prefix) {
        j += 2;
    }

    // full adder
    for(auto i = addend.size(); i > 0;){
        i--;
        j--;
        tmp = ((*summand)[j] ^ addend[i]) ^ carrier;
        carrier = (((*summand)[j] && addend[i]) || ((*summand)[j] && carrier)) || (addend[i] && carrier);
        (*summand)[j] = tmp;
    }

    if(prefix) { // prefix: false, true

        j--;
        tmp = !(*summand)[j] ^ carrier;
        carrier = ((*summand)[j] || ((*summand)[j] && carrier)) || carrier;
        (*summand)[j] = tmp;

        j--;
        (*summand)[j] = (*summand)[j] ^ carrier;
    }

    /*
    j = 0; // = start
    while(carrier && j > 0){
        j--;
        if(!(*summand)[j]){
            (*summand)[j] = true;
            carrier = false;
        }
    }
     */
}

vector<bool> mps::binaryOffsetAddition(const vector<bool>& lp, const vector<bool>& rp, unsigned long off_set, bool c, const bool p[2], const bool hd[2],  bool* cr){

    // Setting up basic variable.
    vector<bool> ret;
    bool carrier = false;

    // Calculate right padding part.
    //-------------------------------
    for(auto i = lp.size(); i > lp.size()-off_set;){
        i--;
        //ret.insert(ret.begin(), lp[i] ^ carrier);
        //carrier = ((lp[i] && false) || (lp[i] && carrier));
        ret.insert(ret.begin(), (lp[i] ^ p[1]) ^ carrier);
        carrier = ((lp[i] && p[1]) || (lp[i] && carrier)) || (p[1] && carrier);
    }
    //-------------------------------


    // Calculate part between the padding.
    //-------------------------------
    unsigned long j = rp.size();
    for(auto i = lp.size()-off_set; i > 0;){
        i--;
        j--;
        ret.insert(ret.begin(), (lp[i] ^ rp[j]) ^ carrier);
        carrier = ((lp[i] && rp[j]) || (lp[i] && carrier)) || (rp[j] && carrier);
    }
    //-------------------------------


    if(off_set > 0){

        // Calculate left parts hidden digit.
        j--;
        ret.insert(ret.begin(), (hd[0] ^ rp[j]) ^ carrier);
        carrier = ((hd[0] && rp[j]) || (hd[0] && carrier)) || (rp[j] && carrier);


        // Calculate left padding part.
        //-------------------------------
        for(; j > 0;){
            j--;
            //ret.insert(ret.begin(), rp[j] ^ carrier);
            //carrier = (rp[j] && carrier);
            ret.insert(ret.begin(), (p[0] ^ rp[j]) ^ carrier);
            carrier = ((p[0] && rp[j]) || (p[0] && carrier)) || (rp[j] && carrier);
        }
        //-------------------------------


        // Calculate right parts hidden digit.
        // ret.insert(ret.begin(), hd[1] ^ carrier);
        // carrier = (hd[1] && carrier);
        ret.insert(ret.begin(), (p[0] ^ hd[1]) ^ carrier);
        carrier = ((p[0]  && hd[1]) || (p[0]  && carrier)) || (hd[1] && carrier);

    } else {

        // Calculate hidden digit of both variables.
        ret.insert(ret.begin(), (hd[0] ^ hd[1]) ^ carrier);
        carrier = ((hd[0] && hd[1]) || (hd[0] && carrier)) || (hd[1] && carrier);
    }

    // Perform carrier step if wanted.
    if(c && carrier){
        ret.insert(ret.begin(), true);
        ret.pop_back();
    }

    // Save carrier bit if wanted.
    if(cr != nullptr) {
        *cr = carrier;
    }


    return ret;
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
long mps::getBias() const{
    return ((long) pow (2, exponent_length)) / 2 -1;
}

/**
 * To be read: Is the bit value a represents larger than the one of b.
 * 1 if a > b
 * 0 if a == b
 * -1 if a < b
 *
 * Only works for vectors of same size. ATTENTION: Does not check for same length!
 *
 * Division Case: In the case of a division the routine must account for "hidden" bits.
 *
 * @param a reference to the vector containing the first binary number
 * @param b reference to the vector containing the second binary number
 * @param division_case whether the division case is wanted or not.
 * @return 1 if a > b, 0 if a == b, -1 if a < b
 */
char mps::larger(const vector<bool>& a, const vector<bool>& b, const bool division_case){

    if(!division_case){
        for(unsigned long i = 0; i < a.size(); i++){
            if(a[i] && !b[i]) { return 1;}
            else if(b[i] && !a[i]) {return -1;}
        }
    } else {

        if (a[0]){
            return 1;
        } else if(!a[1]) {
            return -1;
        }

        for(unsigned long i = 0; i < b.size(); i++){
            if(a[i+2] && !b[i]) { return 1;}
            else if(b[i] && !a[i+2]) {return -1;}
        }

        if(a[a.size()-1]){
            return 1;
        }
    }

    return 0;
}

/**
 * Adds one to a binary number saved inside a vector.
 * The vector consists of booleans which represents a binary number.
 *
 * @param vector pointer to the vector containing the binary number where one should be added
 * @return true if a carrier bit was present in the last iteration, false otherwise
 */
bool mps::addOneToBinary(vector<bool>* vector){

    for(auto i = vector->size(); i > 0;){
        i--;
        (*vector)[i] = !(*vector)[i];
        if((*vector)[i]){
            return false;
        }
    }

    //vector->insert(vector->begin(), true);
    //vector->pop_back();   // TODO: maybe check if remove is justified everywhere.
    return true;
}

/**
 * Subtracts one to a binary number saved inside a vector.
 * The vector consists of booleans which represents a binary number.
 *
 * @param vector pointer to the vector containing the binary number where one should be subtracted
 * @return true if a carrier bit was present in the last iteration, false otherwise
 */
bool mps::subtractOneFromBinary(vector<bool> *vector){

    for(auto i = vector->size(); i > 0;){
        i--;
        (*vector)[i] = !(*vector)[i];
        if(!(*vector)[i]){
            return false;
        }
    }

    return true;
}

/**
 * Creates a copy of the vector vec. Then inverts the copy, adds one to it and returns it afterwards.
 *
 * @param vec reference to the vector which copy should be inverted and added one to it.
 * @param carrie pointer to a boolean value which will be set to true if a carrier bit is present at the end.
 * @return the resulting copied and tempered vector.
 */
vector<bool> mps::invertAndAddOne(const vector<bool> &vec, bool *carrie, const bool division_case){

    vector<bool> ret;

    if(!division_case){
        ret.reserve(vec.size());
    } else {
        ret.reserve(vec.size()+3);
        ret.push_back(true);
        ret.push_back(false);
    }

    for(auto && i : vec){
        ret.push_back(!i);
    }

    if(division_case){
        ret.push_back(true);
    }

    if(carrie != nullptr){
        *carrie = addOneToBinary(&ret);
    } else {
        addOneToBinary(&ret);
    }

    return ret;
}

/**
 * Checks if a vector consisting of only true booleans.
 *
 * @param vector reference to the vector which should be checked.
 * @return true is all entries of the vector are true.
 */
[[nodiscard]] bool mps::allTrue(const vector<bool>& vector) {
    return std::all_of(vector.begin(), vector.end(), [](bool i){return i;});
}

/**
 * Shifts a vector to the left.
 *
 * @param vector pointer to the vector which should be shifted to the left.
 */
void mps::shiftLeft(vector<bool>* vec){

    vec->erase(vec->begin());
    vec->push_back(false);
}
//-------------------------------