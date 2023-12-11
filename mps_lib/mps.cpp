//
// Created by Jakob on 11.12.23.
//

#include "mps.h"



int mps::getMantisseLength() const {
    return mps::mantisse_length;
}


int mps::getExponentLength() const {
    return this->exponent_length;
}

mps::mps(int mantisse, int exponent, long double value) {
    this->mantisse_length = mantisse;
    this->exponent_length = exponent;
    this->double_value = value;
}

long double mps::getDoubleValue() const {
    return this->double_value;
}
