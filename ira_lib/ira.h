//
// Created by Jakob on 28.02.24.
//

#include <vector>
#include "mps.h"

#ifndef MPS_IRA_H
#define MPS_IRA_H

class ira {

public:

    // parameters struct
    //-------------------------------
    struct {

        double random_lower_bound;              // the lower bound when getting a random value.
        double random_upper_bound;              // the upper bound when getting a random value.

        unsigned long max_iter;                 // The maximal number of refinement steps.
        unsigned long n;                        // dimension of the system
        unsigned long matrix_1D_size;           // The number of elements of the system matrix.

        // TODO: Test
        bool working_precision_set;             // true if a working precision was set.

        unsigned long u_m_l;                    // working precision mantissa length
        unsigned long u_e_l;                    // working precision exponent length
        unsigned long ul_m_l;                   // lower precision mantissa length
        unsigned long ul_e_l;                   // lower precision exponent length
        unsigned long ur_m_l;                   // upper precision mantissa length
        unsigned long ur_e_l;                   // upper precision exponent length

        bool expected_result_present;           // true if an expected result is set
        vector<mps> expected_result_mps;        // the expected x vector saved as mps
        vector<double> expected_result_double;  // the expected x vector saved as double

        bool expected_precision_present;        // true if an expected precision is set
        mps expected_precision;                 // the expected precision

    } parameters{};
    //-------------------------------


    // evaluation struct
    //-------------------------------
    struct {
        vector<long double> IR_relativeError;
        long double IR_area_relativeError;
        long double IR_area_precision;
        long long milliseconds;
        unsigned long iterations_needed;
    } evaluation{};
    //-------------------------------


    // variables
    //-------------------------------
    vector<mps> A;             // the A which should be solved

    vector<mps> L;             // The resulting lower triangular Matrix after PLU decomposition.
    vector<mps> U;             // The resulting upper triangular Matrix after PLU decomposition.
    vector<mps> P;             // The resulting permutation vector P after PLU decomposition.
    //-------------------------------

public:

    // constructor and destructor
    //-------------------------------
    explicit ira(unsigned long n, unsigned long u_mantissa_length, unsigned long u_exponent_length);
    ~ira();
    //-------------------------------

    // parameter setters and getters
    //-------------------------------
    void setRandomRange(double lower_bound, double upper_bound);
    void setMaxIter(unsigned long new_max_iter);
    void setDimension(unsigned long new_dimension);
    void setLowerPrecision(unsigned long mantissa_length, unsigned long exponent_length);
    void setLowerPrecisionMantissa(unsigned long mantissa_length);
    void setLowerPrecisionExponent(unsigned long exponent_length);
    void setUpperPrecision(unsigned long mantissa_length, unsigned long exponent_length);
    void setUpperPrecisionMantissa(unsigned long mantissa_length);
    void setUpperPrecisionExponent(unsigned long exponent_length);
    void setWorkingPrecision(unsigned long mantissa_length, unsigned long exponent_length);
    void setWorkingPrecisionMantissa(unsigned long mantissa_length);
    void setWorkingPrecisionExponent(unsigned long exponent_length);
    void setExpectedResult(const vector<mps>& new_expected_result);
    void setExpectedPrecision(const mps& new_expected_precision);

    [[nodiscard]] vector<double> getRandomRange() const;
    [[nodiscard]] unsigned long getMaxIter() const;
    [[nodiscard]] unsigned long getDimension();
    [[nodiscard]] unsigned long get1DMatrixSize();
    [[nodiscard]] vector<unsigned long> getLowerPrecision() const;
    [[nodiscard]] vector<unsigned long> getUpperPrecision() const;
    [[nodiscard]] vector<unsigned long> getWorkingPrecision() const;
    [[nodiscard]] vector<mps> getExpectedResult_mps() const;
    [[nodiscard]] vector<double> getExpectedResult_double() const;
    [[nodiscard]] mps getExpectedPrecision() const;
    //-------------------------------

    // matrix setters
    //-------------------------------
    void setUnitaryMatrix();
    void setMatrix(vector<double> new_matrix);
    void setRandomMatrix();
    void setL(vector<double> new_L);
    void setU(vector<double> new_U);
    //-------------------------------

    // matrix getter
    //-------------------------------
    [[nodiscard]] mps getMatrixElement(unsigned long idx);
    //-------------------------------

    // to_string converters
    //-------------------------------
    [[nodiscard]] std::string to_string(const char& matrix, int precision = -1) const;
    [[nodiscard]] static std::string to_string(vector<mps> vec, int precision = -1);
    //-------------------------------

    // cast functions
    //-------------------------------
    static void castVectorElements(unsigned long mantissa_length, unsigned long exponent_length, vector<mps>* vec);
    // TODO: Test
    void castSystemMatrix(unsigned long mantissa_length, unsigned long exponent_length);
    // TODO: Test
    void castExpectedResult(unsigned long mantissa_length, unsigned long exponent_length);
    // TODO: Test
    void castExpectedPrecision(unsigned long mantissa_length, unsigned long exponent_length);
    //-------------------------------

    // array converters
    //-------------------------------
    [[nodiscard]] static vector<mps> double_to_mps(unsigned long mantissa_length, unsigned long exponent_length, vector<double> double_vector);
    [[nodiscard]] static vector<double> mps_to_double(vector<mps> mps_vector);
    [[nodiscard]] static vector<float> mps_to_float(vector<mps> mps_vector);
    //-------------------------------

    // generators
    //-------------------------------
    // TODO: test
    [[nodiscard]] vector<mps> generateRandomVector(unsigned long mantissa_length, unsigned long exponent_length, unsigned long size) const;
    // TODO: test
    [[nodiscard]] vector<mps> generateRandomRHS();
    // TODO: test
    [[nodiscard]] vector<mps> generateRandomLinearSystem();
    //-------------------------------

    // operators
    //-------------------------------
    [[nodiscard]] static mps vectorNorm_L1(const vector<mps>& a);
    // TODO: test
    [[nodiscard]] static mps calculateVectorMean(const vector<mps>& a);
    [[nodiscard]] static vector<mps> vectorAddition(const vector<mps>& a, const vector<mps>& b);
    [[nodiscard]] static vector<mps> vectorSubtraction(const vector<mps>& a, const vector<mps>& b);
    [[nodiscard]] static vector<mps> matrixVectorProduct(const vector<mps>& D, const vector<mps>& x);
    // TODO: test
    [[nodiscard]] vector<mps> multiplyWithSystemMatrix(vector<mps> x) const;
    //-------------------------------

    // algorithms
    //-------------------------------
    void PLU_decomposition(unsigned long mantissa_precision, unsigned long exponent_precision);
    [[nodiscard]] vector<mps> forwardSubstitution(const vector<mps>& b) const;
    [[nodiscard]] vector<mps> backwardSubstitution(const vector<mps>& b) const;
    vector<mps> iterativeRefinementLU(const vector<mps> &b);
    [[nodiscard]] vector<mps> solveLU(const vector<mps>& b, unsigned long u[2]);
    //-------------------------------

    // algorithms using double data types
    //-------------------------------
    [[nodiscard]] vector<double> solveLU_double(const vector<double>& b);
    //-------------------------------


private:

    // helper functions
    //-------------------------------
    [[nodiscard]] unsigned long get_idx(unsigned long row, unsigned long column) const;
    [[nodiscard]] static unsigned long get_idx(unsigned long row, unsigned long column, unsigned long n);
    [[nodiscard]] unsigned long get_max_U_idx(unsigned long column, unsigned long start) const;
    void interchangeRow(vector<mps>* matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end) const;
    static vector<mps> permuteVector(const vector<mps> &permutation_vector, const vector<mps> &matrix);
    //-------------------------------

};


#endif //MPS_IRA_H
