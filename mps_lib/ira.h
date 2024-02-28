//
// Created by Jakob on 28.02.24.
//

#include <vector>
#include "mps.h"

#ifndef MPS_IRA_H
#define MPS_IRA_H

struct PLU {

    unsigned long one;
    unsigned long two;

    //std::vector<std::vector<int>> P;
    //std::string firstName;
};


class ira {

public:

    unsigned long n;
    mps* matrix;

    explicit ira(unsigned long n);
    ~ira();

    void unitary(unsigned long mantissa_length, unsigned long exponent_length) const;
    [[nodiscard]] std::string to_string() const;

};


#endif //MPS_IRA_H
