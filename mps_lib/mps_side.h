#ifndef MPS_MPS_SIDE_H
#define MPS_MPS_SIDE_H


#include "mps.h"

template<typename T = double>
class mps_side : public mps {

private:
    T side_calculation_value;

public:
    mps_side(int mantisse, int exponent, T value);
    ~mps_side();

    [[nodiscard]] T getSideCalculationValue() const;
};







// constructors and destructor
//-------------------------------

/**
 * Constructor for the multiprecision simulator including a side calculation.
 *
 * @param mantisse Mantisse of the floating point representation.
 * @param exponent Exponent of the floating point representation.
 * @param value Value of the floating point number.
 */
template<typename T>
mps_side<T>::mps_side(int mantisse, int exponent, T value):mps(mantisse, exponent, value) {

    this->side_calculation_value = value;
}

/**
 * Destructor of mps_side
 */
template<typename T>
mps_side<T>::~mps_side() = default;
//-------------------------------

// getter
//-------------------------------

/**
 * Returns the value with is calculated in addition to the calculations concerning the calculator.
 *
 * @return side calculation value.
 */
template<typename T>
T mps_side<T>::getSideCalculationValue() const {
    return this->side_calculation_value;
}
//-------------------------------

#endif //MPS_MPS_SIDE_H
