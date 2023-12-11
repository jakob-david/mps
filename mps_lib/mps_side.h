//
// Created by Jakob on 11.12.23.
//

#ifndef MPS_MPS_SIDE_H
#define MPS_MPS_SIDE_H


#include "mps.h"

template<typename T = double>
class mps_side : public mps {

private:
    T side_calculation_value{};

public:
    mps_side(int mantisse, int exponent, T value);

    [[nodiscard]] T getSideCalculationValue() const;
};

template<typename T>
T mps_side<T>::getSideCalculationValue() const {
    return this->side_calculation_value;
}

template<typename T>
mps_side<T>::mps_side(int mantisse, int exponent, T value):mps(mantisse, exponent, value) {

    this->side_calculation_value = value;
}


#endif //MPS_MPS_SIDE_H
