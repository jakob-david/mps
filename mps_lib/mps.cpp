#include "mps.h"
#include <iostream>


// constructors and destructor
//-------------------------------

/**
 * Constructor for the multiprecision simulator.
 *
 * @param mantisse Mantisse of the floating point representation.
 * @param exponent Exponent of the floating point representation.
 * @param value Value of the floating point number.
 */
mps::mps(int mantissa_length, int exponent_length, double value) {
    this->mantissa_length = mantissa_length;
    this->exponent_length = exponent_length;

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
int mps::getMantisseLength() const {
    return this->mantissa_length;
}

/**
 * Returns the length of the exponent.
 *
 * @return length exponent
 */
int mps::getExponentLength() const {
    return this->exponent_length;
}

/**
 * Returns the length of the whole bit array.
 * (sign + matisse + exponent)
 *
 * @return length matisse
 */
int mps::getBitArrayLength() const {
    return (int) this->bit_vector.size();
}

/**
 * Returns the bit vector.
 *
 * @return bit vector
 */
vector<bool> mps::getBitArray() {
    return this->bit_vector;
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
    for(int i = exponent_length + 1; i < bit_vector.size(); i++){
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
    for(int i = 1; i <= exponent_length; i++){
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

    for(int i = 1; i < exponent_length+1; i++){
        if(!bit_vector[i]){
            return false;
        }
    }

    for(int i = exponent_length+1; i < bit_vector.size(); i++){
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

    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    if(negative){
        bit_vector.push_back(true);
    } else {
        bit_vector.push_back(false);
    }

    for(int i = 0; i < exponent_length; i++){
        bit_vector.push_back(true);
    }

    for(int i = 0; i < mantissa_length; i++){
        bit_vector.push_back(false);
    }
}

/**
 * Sets the floating point number to zero.
 */
void mps::setZero(){

    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    for(int i = 0; i < exponent_length + mantissa_length + 1; i++){
        bit_vector.push_back(false);
    }
}

/**
 * Sets the floating point number to NaN (not a number)
 */
void mps::setNaN(){

    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    bit_vector.push_back(false);

    for(int i = 0; i < exponent_length; i++){
        bit_vector.push_back(true);
    }

    bit_vector.push_back(true);

    for(int i = 1; i < mantissa_length; i++){
        bit_vector.push_back(false);
    }
}
//-------------------------------

// operators
//-------------------------------
mps& mps::operator=(const mps& other) {

    if (this == &other){
        return *this;
    }

    this->bit_vector.erase(bit_vector.begin(), bit_vector.end());

    for(auto i : other.bit_vector){
        this->bit_vector.push_back(i);
    }

    this->mantissa_length = other.mantissa_length;
    this->exponent_length = other.exponent_length;

    return *this;
}

mps mps::operator+(mps other) {

    mps ret;
    vector<bool> value;

    if(this->exponent_length > other.exponent_length){
        ret.exponent_length = this->exponent_length;
    } else {
        ret.exponent_length = other.exponent_length;
    }

    if(this->mantissa_length > other.mantissa_length){
        ret.mantissa_length = this->mantissa_length;
    } else {
        ret.mantissa_length = other.mantissa_length;
    }

    if(this->isZero() || other.isZero()){
        ret.setZero();
        return ret;
    }

    vector<bool> a_mantissa(this->bit_vector.begin()+exponent_length+1, this->bit_vector.end());
    vector<bool> b_mantissa(other.bit_vector.begin()+exponent_length+1, other.bit_vector.end());
    vector<bool> mantissa = binaryAddition(a_mantissa, b_mantissa);

    //value.insert(value.begin(), mantissa.begin(), mantissa.end());

    ret.setBitArray(mantissa);

    return ret;
}
//-------------------------------


// helper methods
//-------------------------------

void mps::setBitArray(vector<bool> value) {

    this->bit_vector.erase(this->bit_vector.begin(),this->bit_vector.end());

    for(int i = 0; i < value.size(); i++){
        this->bit_vector.push_back(value[i]);
    }
}

/**
 * Sets the bit vector of the mps object.
 */
void mps::setBitArray(double value) {


    // Handle special values.
    //-------------------------------
    if(0 == value){
        setZero(); return;
    } else if(numeric_limits<double>::infinity() == value) {
        setInf(); return;
    } else if (numeric_limits<double>::infinity() * -1 == value){
        setInf(true); return;
    } else if (isnan(value)){
        setNaN(); return;
    }
    //-------------------------------


    // prepare bit_vector
    //-------------------------------
    bit_vector.erase(bit_vector.begin(),bit_vector.end());
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
        mantissa_shift = floor(log2(abs(value)));
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
        for(int i = (int) exponent.size(); i < exponent_length; i++){
            exponent.insert(exponent.begin(), false);
        }
    }
    //-------------------------------


    // mantissa
    //-------------------------------

    // adjust the value so that everything is behind the decimal point.
    value = value / pow(2, mantissa_shift);

    // Convert the part after the decimal point to a bit string.
    // The sign is not relevant. Always returns a "positive" value.
    vector<bool> mantissa;
    double reminder = abs(value) - floor(abs(value));
    for(int i = 0; i < mantissa_length; i++){

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

/**
 * Returns the bias of the exponent.
 *
 * @return bias of the exponent.
 */
int mps::getBias() const{
    return ((int) pow (2, exponent_length)) / 2 -1;
}

vector<bool> mps::binaryAddition(vector<bool> a, vector<bool> b){

    vector<bool> ret;
    bool carrier = false;

    if(a.size() < b.size()){

        for(int i = (int) a.size(); i < b.size(); i++){
            a.insert(a.begin(), false);
        }
    } else if (b.size() < a.size()) {
        for(int i = (int) b.size(); i < a.size(); i++){
            b.insert(b.begin(), false);
        }
    }

    // full adder
    for(int i = (int) a.size()-1; i >= 0; i--){
        ret.insert(ret.begin(), (a[i] ^ b[i]) ^ carrier);
        carrier = ((a[i] & b[i]) | (a[i] & carrier)) | (b[i] & carrier);
    }

    if(carrier){
        ret.insert(ret.begin(), true);
    }

    return ret;
}
//-------------------------------