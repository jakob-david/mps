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

double mps::getValue() {

    double ret;

    if(isZero()){
        return 0;
    } else if (isInfinity() && isPositive()){
        return numeric_limits<double>::infinity();
    } else if (isInfinity()){
        return numeric_limits<double>::infinity() * -1;
    }

    if(bit_vector[0]){
        ret = -1;
    } else {
        ret = 1;
    }

    for(int i = exponent_length + 1; i < bit_vector.size(); i++){
        if(bit_vector[i]){
            if(ret >= 0){
                ret += pow(0.5, i - exponent_length);
            } else {
                ret -= pow(0.5, i - exponent_length);
            }
        }
    }

    int exponent = 0;
    for(int i = 1; i <= exponent_length; i++){
        if(bit_vector[i]){
            exponent += (int) pow(2, exponent_length-i);
        }
    }

    exponent -= getBias();

    ret *= pow(2, exponent);

    return ret;

}

bool mps::isZero(){
    return all_of(bit_vector.begin(), bit_vector.end(), [](bool i){return !i;});
}

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




// helper methods
//-------------------------------

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

int mps::getBias() const{
    return ((int) pow (2, exponent_length)) / 2 -1;
}
//-------------------------------