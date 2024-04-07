//
// Created by Jakob on 07.04.24.
//

#include "mpe.h"

// constructors and destructor
//-------------------------------

/**
 * Simple constructor for a multiprecision evaluation object.
 */
mpe::mpe() {

    this->random_lower_bound = -10;
    this->random_upper_bound = 10;
}

/**
 * Destructor for a multiprecision evaluation object.
 */
mpe::~mpe() = default;
//-------------------------------


// operator evaluation
//-------------------------------
std::vector<long long int>
mpe::evaluateAddition(unsigned long m_start, unsigned long m_last, unsigned long e_size, unsigned long n_tests) {

    std::vector<long long> ret;

    double a = getPositiveRandomDouble();
    double b = getPositiveRandomDouble();

    for(unsigned long m_size = m_start; m_size <= m_last; m_size++){

        mps A(m_size, e_size, a);
        mps B(m_size, e_size, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < n_tests; test++){
            A + B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();
        ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    }

    return ret;
}
//-------------------------------


// helper functions
//-------------------------------
double mpe::getPositiveRandomDouble() const {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(numeric_limits<double>::min(), this->random_upper_bound);

    return dist(mt);
}
//-------------------------------
