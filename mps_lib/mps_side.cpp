//
// Created by Jakob on 11.12.23.
//

#include "mps_side.h"


mps_side::mps_side(int mantisse, int exponent, long double value): mps(mantisse, exponent, value) {
    this->side_calculation_value = value;
}

long double mps_side::getSideCalculationValue() const {
    return this->side_calculation_value;
}