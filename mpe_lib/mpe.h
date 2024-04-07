//
// Created by Jakob on 07.04.24.
//

#ifndef MPS_MPE_H
#define MPS_MPE_H

#include <vector>
#include <random>
#include <iostream>

#include "../mps_lib/mps.h"


class mpe {

private:
    double random_lower_bound;
    double random_upper_bound;

    unsigned long first_mantissa_size;
    unsigned long last_mantissa_size;
    unsigned long exponent_size;

public:

    // constructors and destructor
    //-------------------------------
    mpe();
    ~mpe();
    //-------------------------------

    // setter
    //-------------------------------
    void setRandomLimits(double lower_bound, double upper_bound);
    void setUpperRandomLimit(double upper_bound);

    void setFormatRange(unsigned long new_first_mantissa_size, unsigned long new_last_mantissa_size, unsigned long new_exponent_size);
    //-------------------------------

    // getter
    //-------------------------------
    [[nodiscard]] std::vector<unsigned long int> getMantissaAxis() const;
    //-------------------------------

    // operator evaluation
    //-------------------------------
    [[nodiscard]]  std::vector<long long int> evaluateAddition(unsigned long n_tests);
    [[nodiscard]]  std::vector<long long int> evaluateSubtraction(unsigned long n_tests);
    //-------------------------------

private:
    // helper functions
    //-------------------------------
    [[nodiscard]] double getPositiveRandomDouble() const;
};


#endif //MPS_MPE_H
