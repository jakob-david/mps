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
    unsigned long n;    // dimension of the matrix
    mps* matrix;        // the matrix which should be solved
    //-------------------------------

    // PLU_calculated_properties
    //-------------------------------
    mps* L;             // The resulting lower triangular Matrix after PLU decomposition.
    mps* U;             // The resulting upper triangular Matrix after PLU decomposition.
    mps* P;             // The resulting permutation matrix after PLU decomposition.
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
    [[nodiscard]] std::string to_string() const;
    //-------------------------------

    // algorithms
    //-------------------------------
    void PLU_decomposition() const;
    //-------------------------------

};


#endif //MPS_IRA_H
