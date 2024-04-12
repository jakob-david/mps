//
// Created by Jakob on 07.04.24.
//

#ifndef MPS_MPE_H
#define MPS_MPE_H

#include <vector>
#include <random>
#include <iostream>

#include "../mps_lib/mps.h"
#include "../ira_lib/ira.h"


class mpe {

private:
    double random_lower_bound;
    double random_upper_bound;

    unsigned long first_mantissa_size;
    unsigned long last_mantissa_size;
    unsigned long exponent_size;

    struct {
        unsigned long n; // TODO: remove n
        unsigned long iter_max;

        unsigned long u_exponent_size;
        unsigned long u_mantissa_size;

        unsigned long ul_first_mantissa_size;
        unsigned long ul_last_mantissa_size;
        unsigned long ur_first_mantissa_size;
        unsigned long ur_last_mantissa_size;
    } irm{};

public:

    // constructors and destructor
    //-------------------------------
    mpe();
    ~mpe();
    //-------------------------------

    // setter
    //-------------------------------

    // randomness parameter
    void setRandomLimits(double lower_bound, double upper_bound);
    void setUpperRandomLimit(double upper_bound);

    // operator evaluation
    void setFormatRange(unsigned long new_first_mantissa_size, unsigned long new_last_mantissa_size, unsigned long new_exponent_size);

    // irm setter
    void setBasicParameters_irm(unsigned long new_n, unsigned long new_iter_max);
    void setWorkingPrecision_irm(unsigned long new_u_exponent_size, unsigned long new_u_mantissa_size);
    void setRange_ul_irm(unsigned long new_ul_first_mantissa_size, unsigned long new_ul_last_mantissa_size);
    void setRange_ur_irm(unsigned long new_ur_first_mantissa_size, unsigned long new_ur_last_mantissa_size);
    //-------------------------------

    // getter
    //-------------------------------
    [[nodiscard]] std::vector<unsigned long int> getMantissaAxis() const;

    // irm getter
    [[nodiscard]] std::vector<unsigned long int> getAxis_ul_irm() const;
    [[nodiscard]] std::vector<unsigned long int> getAxis_ur_irm() const;
    //-------------------------------

    // operator evaluation
    //-------------------------------
    [[nodiscard]] std::vector<long long int> evaluateAddition(unsigned long n_tests) const ;
    [[nodiscard]] std::vector<long long int> evaluateSubtraction(unsigned long n_tests) const ;
    [[nodiscard]] std::vector<long long int> evaluateMultiplication(unsigned long n_tests) const ;
    [[nodiscard]] std::vector<long long int> evaluateDivision(unsigned long n_tests) const ;
    //-------------------------------

    // iterative refinement evaluation
    //-------------------------------
    [[nodiscard]] std::vector<std::vector<long double>> evaluateArea_2D(bool output = false) const;
    [[nodiscard]] std::vector<std::vector<long double>> evaluateConvergence_2D(double precision, unsigned long max_iter, bool output = false) const;
    //-------------------------------

private:
    // helper functions
    //-------------------------------
    [[nodiscard]] double getPositiveRandomDouble() const;
};


#endif //MPS_MPE_H
