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
vector<bool> mps::intToBinary(int value) {

    vector<bool> ret;

    for(int i = value; i >0; i /= 2){
        ret.insert(ret.begin(), i%2);
    }

    return ret;
}

vector<bool> mps::getDecimalPart(double value, int length){

    vector<bool> ret;

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

vector<bool> mps::getFloatingPointRepresentation(double value, int exponent, int mantissa) {

    vector<bool> ret;


    return ret;
}
//-------------------------------