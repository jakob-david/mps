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
mps::mps(int mantisse, int exponent, double value) {
    this->mantisse_length = mantisse;
    this->exponent_length = exponent;

    int length = 1 + this->mantisse_length + this->exponent_length;

    for(int i = 0; i < length; i++){
        this->bit_vector.push_back(false);
    }
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
    return this->mantisse_length;
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
unsigned long mps::getBitArrayLength() const {
    return this->bit_vector.size();
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


// helper methods
//-------------------------------
vector<bool> mps::getDecimalPart(double value, int length){

    vector<bool> ret;

    if(value < 0){
        value *= -1;
    }

    int int_part = (int) value;
    double reminder = value - int_part;

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
}

vector<bool> mps::getFloatingPointRepresentation(double value, int exponent_length, int mantissa_length) {

    /*
     * Small function to convert an integer to a bit string.
     * The sign is not relevant. Always returns a "positive" value.
     * */
    auto getIntegerPart = [](int value)
    {
        vector<bool> ret;

        if(value < 0){value *= -1;}

        for(int i = value; i > 0; i /= 2){
            ret.insert(ret.begin(), i%2);
        }

        return ret;
    };

    vector<bool> ret;

    auto integerPart = getIntegerPart((int) value);

    int decimal_length = mantissa_length - (int) integerPart.size() + 1;
    vector<bool> decimalPart = this->getDecimalPart(value, decimal_length);

    int mantissa_shift = (int) integerPart.size() - 1;
    int mantissa_adjustment = ((int) pow (2, exponent_length))/2 - 1;
    int exponent_int = mantissa_shift + mantissa_adjustment;

    vector<bool> exponent = getIntegerPart(exponent_int);

    if(exponent.size() > exponent_length) {
        cout << "ERROR: exponent too large" << endl;
        // TODO: add propper error handling.
    } else {
        for(int i = (int) exponent.size(); i < exponent_length; i++){
            exponent.insert(exponent.begin(), false);
        }
    }


    if(value > 0){
        ret.push_back(false);
    } else {
        ret.push_back(true);
    }

    ret.insert(ret.end(), exponent.begin(), exponent.end());
    ret.insert(ret.end(), ++integerPart.begin(), integerPart.end());
    ret.insert(ret.end(), decimalPart.begin(), decimalPart.end());

    return ret;
}
//-------------------------------