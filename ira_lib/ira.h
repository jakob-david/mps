//
// Created by Jakob on 28.02.24.
//

#include <vector>
#include "mps.h"

#ifndef MPS_IRA_H
#define MPS_IRA_H

// TODO: collect data for iterative refinement.
// TODO: write minimisation algorithm.


class ira {

public:

    // evaluation struct
    //-------------------------------
    struct {

        long double IR_area;
        std::chrono::milliseconds IR_time_needed;

    } evaluation;
    //-------------------------------

private:

    // general_properties
    //-------------------------------
    unsigned long n;    // dimension of the A
    vector<mps> A;             // the A which should be solved
    //-------------------------------

    // PLU_calculated_properties
    //-------------------------------
    vector<mps> L;             // The resulting lower triangular Matrix after PLU decomposition.
    vector<mps> U;             // The resulting upper triangular Matrix after PLU decomposition.
    vector<mps> P;             // The resulting permutation A after PLU decomposition.
    //-------------------------------

public:

    // constructor and destructor
    //-------------------------------
    explicit ira(unsigned long n);
    ~ira();
    //-------------------------------

    // setter
    //-------------------------------
    void setUnitaryMatrix(unsigned long mantissa_length, unsigned long exponent_length);
    void setMatrix(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_matrix);
    void setRandomMatrix(unsigned long mantissa_length, unsigned long exponent_length);
    void setL(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_L);
    void setU(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_U);
    //-------------------------------

    // getter
    //-------------------------------
    [[nodiscard]] mps getMatrixElement(unsigned long idx);
    [[nodiscard]] std::string to_string(const char& matrix, int precision = -1) const;
    [[nodiscard]] static std::string to_string(vector<mps> vec, int precision = -1);
    //-------------------------------

    // converters
    //-------------------------------
    [[nodiscard]] static vector<mps> double_to_mps(unsigned long mantissa_length, unsigned long exponent_length, vector<double> double_vector);
    [[nodiscard]] static vector<double> mps_to_double(vector<mps> mps_vector);
    [[nodiscard]] static vector<float> mps_to_float(vector<mps> mps_vector);
    static void castVectorElements(unsigned long mantissa_length, unsigned long exponent_length, vector<mps>* vec);
    //-------------------------------

    // operators
    //-------------------------------
    [[nodiscard]] static mps vectorNorm_L1(const vector<mps>& a);
    [[nodiscard]] static vector<mps> vectorAddition(const vector<mps>& a, const vector<mps>& b);
    [[nodiscard]] static vector<mps> vectorSubtraction(const vector<mps>& a, const vector<mps>& b);
    [[nodiscard]] static vector<mps> matrixVectorProduct(const vector<mps>& D, const vector<mps>& x);
    //-------------------------------

    // algorithms
    //-------------------------------
    void PLU_decomposition(unsigned long mantissa_precision, unsigned long exponent_precision);
    [[nodiscard]] vector<mps> forwardSubstitution(const vector<mps>& b) const;
    [[nodiscard]] vector<mps> backwardSubstitution(const vector<mps>& b) const;
    [[nodiscard]] vector<mps> iterativeRefinementLU(const vector<mps>& b, unsigned long u[2], unsigned long ul[2], unsigned long n_max);
    [[nodiscard]] vector<mps> solveLU(const vector<mps>& b, unsigned long u[2]);
    //-------------------------------

    // "double" algorithms
    //-------------------------------
    [[nodiscard]] vector<double> solveLU_double(const vector<double>& b);
    //-------------------------------


private:

    // helper functions
    //-------------------------------
    [[nodiscard]] unsigned long get_idx(unsigned long row, unsigned long column) const;
    [[nodiscard]] static unsigned long get_idx(unsigned long row, unsigned long column, unsigned long n);
    [[nodiscard]] unsigned long get_max_U_idx(unsigned long column, unsigned long start) const;
    void interchangeRow(vector<mps>* matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end);
    //-------------------------------

};


#endif //MPS_IRA_H
