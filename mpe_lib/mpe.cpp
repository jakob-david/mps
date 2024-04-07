//
// Created by Jakob on 07.04.24.
//

#include "mpe.h"

// constructors and destructor
//-------------------------------

/**
 * Simple constructor for a multiprecision evaluation object.
 */
mpe::mpe() {
    this->A = 4;
}

/**
 * Destructor for a multiprecision evaluation object.
 */
mpe::~mpe() = default;
//-------------------------------


// getter methods
//-------------------------------

int mpe::getA() {
    return this->A;
}
//-------------------------------
