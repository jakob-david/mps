//
// Created by Jakob on 07.04.24.
//

#ifndef MPS_MPE_H
#define MPS_MPE_H

#include <vector>
#include <random>
#include <iostream>
#include <chrono>

#include "../mps_lib/mps.h"
#include "../ira_lib/ira.h"

using namespace std;


class mpe {

private:

    struct {

        double random_lower_bound;              // the lower bound when getting a random value.
        double random_upper_bound;              // the upper bound when getting a random value.
        double sparsity_rate;                  // percentage of zeros in the system matrix.

        unsigned long n;                        // the dimension of the system
        unsigned long matrix_1D_size;           // the number of elements of the system matrix
        unsigned long iterations;               // the number of iterations
        unsigned long iter_max;                 // the maximal number of iterations

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

        unsigned long u_e_r_lower;               // working precision exponent range lower limit
        unsigned long u_e_r_upper;               // working precision exponent range upper limit

        mps expected_error;                     // the expected error the refinement method should achieve.
        long long expected_precision;           // the expected precision the refinement method should achieve.
        unsigned long ep_mantissa_length;       // the mantissa length in which the expected precision should be saved.
        unsigned long ep_exponent_length;       // the mantissa length in which the expected precision should be saved.

    } parameters;

    struct {

        bool working_precision_mantissa_set;
        bool working_precision_exponent_set;

        bool expected_error_set;
        bool expected_precision_set;

    } controllers;


public:

    // constructors and destructor
    //-------------------------------
    mpe();
    ~mpe() = default;
    //-------------------------------

    // parameter setters
    //-------------------------------
    void setRandomLimits(double lower_bound, double upper_bound);
    void setUpperRandomLimit(double upper_bound);
    void setLowerRandomLimit(double lower_bound);
    void setSparsityRate(double new_sparsity_rate);

    void setDimension(unsigned long new_dimension);
    void setIterations(unsigned long new_iterations);
    void setMaxIter(unsigned long new_max_iter);

    void setLowerPrecision(unsigned long mantissa_length, unsigned long exponent_length);
    void setWorkingPrecision(unsigned long mantissa_length, unsigned long exponent_length);
    void setUpperPrecision(unsigned long mantissa_length, unsigned long exponent_length);
    void setLowerPrecisionExponent(unsigned long exponent_length);
    void setWorkingPrecisionExponent(unsigned long exponent_length);
    void setUpperPrecisionExponent(unsigned long exponent_length);

    void setLowerPrecisionMantissaRange(unsigned long lower_bound, unsigned long upper_bound);
    void setWorkingPrecisionMantissaRange(unsigned long lower_bound, unsigned long upper_bound);
    void setUpperPrecisionMantissaRange(unsigned long lower_bound, unsigned long upper_bound);

    void setWorkingPrecisionExponentRange(unsigned long lower_bound, unsigned long upper_bound);

    void setExpectedError(double new_expected_error);
    void setExpectedPrecision(long long new_expected_precision, unsigned long mantissa_length, unsigned long exponent_length);
    //-------------------------------


    // getters
    //-------------------------------
    [[nodiscard]] unsigned long getIterations() const;

    [[nodiscard]] vector<unsigned long> getIterationAxis() const;

    [[nodiscard]] vector<unsigned long> getLowerPrecisionMantissaAxis() const;
    [[nodiscard]] vector<unsigned long> getWorkingPrecisionMantissaAxis() const;
    [[nodiscard]] vector<unsigned long> getUpperPrecisionMantissaAxis() const;

    [[nodiscard]] vector<unsigned long> getWorkingPrecisionExponentAxis() const;
    //-------------------------------

    // operator evaluation
    //-------------------------------
    [[nodiscard]] vector<long double> evaluateAddition() const ;
    [[nodiscard]] vector<long double> evaluateSubtraction() const ;
    [[nodiscard]] vector<long double> evaluateMultiplication() const ;
    [[nodiscard]] vector<long double> evaluateDivision() const ;

    [[nodiscard]] vector<long double> evaluateAdditionExponent() const;
    [[nodiscard]] vector<long double> evaluateSubtractionExponent() const;
    [[nodiscard]] vector<long double> evaluateMultiplicationExponent() const;
    [[nodiscard]] vector<long double> evaluateDivisionExponent() const;
    //-------------------------------

    // operator evaluation system
    //-------------------------------
    [[nodiscard]] vector<long double> evaluateAdditionDouble() const ;
    [[nodiscard]] vector<long double> evaluateSubtractionDouble() const ;
    [[nodiscard]] vector<long double> evaluateMultiplicationDouble() const ;
    [[nodiscard]] vector<long double> evaluateDivisionDouble() const ;
    //-------------------------------


    // iterative refinement evaluation
    //-------------------------------
    [[nodiscard]] vector<vector<long double>> evaluateArea(bool output = false) const;
    [[nodiscard]] vector<vector<std::vector<long double>>> evaluateArea_2D(bool output = false) const;
    [[nodiscard]] vector<vector<std::vector<long double>>> evaluateConvergence_2D(bool output = false) const;
    //-------------------------------

private:

    // generators
    //-------------------------------
    [[nodiscard]] double generatePositiveRandomDouble() const;
    //-------------------------------
};


#endif //MPS_MPE_H
