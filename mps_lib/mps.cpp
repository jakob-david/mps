//
// Created by Jakob on 11.12.23.
//

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
    this->bit_array_length = 1 + this->mantisse_length + this->exponent_length;

    this->bit_array = new bool[this->bit_array_length]();
    for(int i = 0; i < this->bit_array_length; i++){
        this->bit_array[i] = false;
    }
}

/**
 * Destructor for the multiprecision simulator.
 */
mps::~mps() {

    delete this->bit_array;
}

//-------------------------------


// getter methods
//-------------------------------

/**
 * Returns the length of the matisse.
 *
 * @return length matisse
 */
int mps::getMantisseLength() const {
    return mps::mantisse_length;
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
    return this->bit_array_length;
}

/**
 * Returns a pointer to the bit array.
 *
 * @return pointer to bit array.
 */
bool *mps::getBitArray() {
    return this->bit_array;
}

//-------------------------------
