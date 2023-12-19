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

//-------------------------------


// setter methods
//-------------------------------
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

void mps::setZero(){

    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    for(int i = 0; i < exponent_length + mantissa_length + 1; i++){
        bit_vector.push_back(false);
    }
}

void mps::setNAN(){

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
void mps::setBitArray(double value) {

    /*
     * Small function to convert an integer to a bit string.
     * The sign is not relevant. Always returns a "positive" value.
     * */
    auto getIntegerPart = [](int value)
    {
        vector<bool> ret;

        value = abs(value);

        for(int i = value; i > 0; i /= 2){
            ret.insert(ret.begin(), i%2);
        }

        return ret;
    };

    /*
     * Small function to convert the part after the decimal point to a bit string.
     * The sign is not relevant. Always returns a "positive" value.
     * */
    auto getDecimalPart = [](double value, int length)
    {
        vector<bool> ret;

        value = abs(value);

        double reminder = value - floor(value);

        for(int i = 0; i < length; i++){

            reminder *= 2;

            if(reminder >= 1){
                ret.push_back(true);
                reminder -= 1;
            } else{
                ret.push_back(false);
            }
        }

        return ret;
    };


    bit_vector.erase(bit_vector.begin(),bit_vector.end());

    if(0 == value){

        setZero();
        return;

    } else if(numeric_limits<double>::infinity() == value || numeric_limits<double>::infinity() * -1 == value){

        if(value > 0){
            setInf();
        } else {
            setInf(true);
        }

        return;

    } else if (isnan(value)){

        setNAN();
        return;
    }

    int mantissa_shift;
    if(abs(value) > numeric_limits<float>::max()){
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

    int mantissa_adjustment = ((int) pow (2, exponent_length)) / 2 -1;
    int exponent_int =  mantissa_shift + mantissa_adjustment;

    vector<bool> exponent = getIntegerPart(exponent_int);

    if(exponent.size() > exponent_length) {
        cout << "ERROR: exponent too large" << endl;
        // TODO: add proper error handling.
    } else {
        for(int i = (int) exponent.size(); i < exponent_length; i++){
            exponent.insert(exponent.begin(), false);
        }
    }

    value = value / pow(2, mantissa_shift);
    auto tmp_mantissa = getDecimalPart(value, mantissa_length);

    if(value > 0){
        bit_vector.push_back(false);
    } else {
        bit_vector.push_back(true);
    }

    bit_vector.insert(bit_vector.end(), exponent.begin(), exponent.end());
    bit_vector.insert(bit_vector.end(), tmp_mantissa.begin(), tmp_mantissa.end());
}
//-------------------------------