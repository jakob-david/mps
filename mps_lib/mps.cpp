//
// Created by Jakob on 11.12.23.
//

#include "mps.h"

mps::mps(int mantisse) {
    this->mantisse_length = mantisse;
}

int mps::getMantisseLength() const {
    return mps::mantisse_length;
}
