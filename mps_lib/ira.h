//
// Created by Jakob on 28.02.24.
//

#include <vector>
#include "mps.h"

#ifndef MPS_IRA_H
#define MPS_IRA_H


class ira {

private:

    // general_properties
    //-------------------------------
    unsigned long n;    // dimension of the A
    mps* A;             // the A which should be solved
    //-------------------------------

    // PLU_calculated_properties
    //-------------------------------
    mps* L;             // The resulting lower triangular Matrix after PLU decomposition.
    mps* U;             // The resulting upper triangular Matrix after PLU decomposition.
    mps* P;             // The resulting permutation A after PLU decomposition.
    //-------------------------------

public:

    // constructor and destructor
    //-------------------------------
    explicit ira(unsigned long n);
    ~ira();
    //-------------------------------

    // setter
    //-------------------------------
    void unitary(unsigned long mantissa_length, unsigned long exponent_length) const;
    void setMatrix(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_matrix);
    //-------------------------------

    // getter
    //-------------------------------
    [[nodiscard]] mps getMatrixElement(unsigned long idx);
    [[nodiscard]] std::string to_string(const char& matrix, int precision = -1) const;
    //-------------------------------

    // algorithms
    //-------------------------------
    void PLU_decomposition();
    //-------------------------------


private:

    // helper functions
    //-------------------------------
    unsigned long get_idx(unsigned long row, unsigned long column) const;
    unsigned long get_max_U_idx(unsigned long column, unsigned long start, unsigned long end) const;
    void interchangeRow(mps* matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end);
    //-------------------------------

};


#endif //MPS_IRA_H
