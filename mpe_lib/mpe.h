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

public:

    // constructors and destructor
    //-------------------------------
    mpe();
    ~mpe();
    //-------------------------------

    // operator evaluation
    //-------------------------------
    [[nodiscard]]  std::vector<long long int>
    evaluateAddition(unsigned long m_start, unsigned long m_last, unsigned long e_size, unsigned long n_tests);
    //-------------------------------

private:
    // helper functions
    //-------------------------------
    [[nodiscard]] double getPositiveRandomDouble() const;
};


#endif //MPS_MPE_H
