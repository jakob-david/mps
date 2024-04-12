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

    struct {

        double random_lower_bound;              // the lower bound when getting a random value.
        double random_upper_bound;              // the upper bound when getting a random value.

        unsigned long n;                        // the dimension of the system
        unsigned long matrix_1D_size;           // The number of elements of the system matrix.
        unsigned long iter_max;                 // dimension of the system

        unsigned long ul_m_l;                   // lower precision mantissa length
        unsigned long ul_e_l;                   // lower precision exponent length
        unsigned long u_m_l;                    // working precision mantissa length
        unsigned long u_e_l;                    // working precision exponent length
        unsigned long ur_m_l;                   // upper precision mantissa length
        unsigned long ur_e_l;                   // upper precision exponent length

        unsigned long ul_m_r_lower;             // lower precision mantissa range lower limit
        unsigned long ul_m_r_upper;             // lower precision mantissa range upper limit
        unsigned long u_m_r_lower;              // working precision mantissa range lower limit
        unsigned long u_m_r_upper;              // working precision mantissa range upper limit
        unsigned long ur_m_r_lower;             // upper precision mantissa range lower limit
        unsigned long ur_m_r_upper;             // upper precision mantissa range upper limit

    } parameters ;

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
    mpe() = default;
    ~mpe() = default;
    //-------------------------------

    // parameter setters
    //-------------------------------
    void setRandomLimits(double lower_bound, double upper_bound);
    void setUpperRandomLimit(double upper_bound);
    void setLowerRandomLimit(double lower_bound);

    void setLowerPrecision(unsigned long mantissa_length, unsigned long exponent_length);
    void setWorkingPrecision(unsigned long mantissa_length, unsigned long exponent_length);
    void setUpperPrecision(unsigned long mantissa_length, unsigned long exponent_length);




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
    [[nodiscard]] std::vector<std::vector<long double>> evaluateConvergence_2D(double precision, bool output = false) const;
    //-------------------------------

private:
    // helper functions
    //-------------------------------
    [[nodiscard]] double getPositiveRandomDouble() const;
};


#endif //MPS_MPE_H
