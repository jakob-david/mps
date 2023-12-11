//
// Created by Jakob on 11.12.23.
//

#ifndef MPS_MPS_SIDE_H
#define MPS_MPS_SIDE_H


#include "mps.h"

class mps_side : public mps {

private:
    long double side_calculation_value;

public:
    mps_side(int mantisse, int exponent, long double value);

    [[nodiscard]] long double getSideCalculationValue() const;
};

#endif //MPS_MPS_SIDE_H
