//
// Created by Jakob on 07.04.24.
//

#include "mpe.h"

#include <../pybind11/include/pybind11/pybind11.h>
namespace py = pybind11;


// constructors and destructor
//-------------------------------

/**
 * Simple constructor for a multiprecision evaluation object.
 */
mpe::mpe() {

    this->random_lower_bound = -10;
    this->random_upper_bound = 10;

    this->first_mantissa_size = 10;
    this->last_mantissa_size = 52;
    this->exponent_size = 11;
}

/**
 * Destructor for a multiprecision evaluation object.
 */
mpe::~mpe() = default;
//-------------------------------

// setter
//-------------------------------
void mpe::setRandomLimits(double lower_bound, double upper_bound) {

    this->random_lower_bound = lower_bound;
    this->random_upper_bound = upper_bound;
}

void mpe::setUpperRandomLimit(double upper_bound){

    this->random_upper_bound = upper_bound;
}

void mpe::setFormatRange(unsigned long new_first_mantissa_size, unsigned long new_last_mantissa_size, unsigned long new_exponent_size){

    this->first_mantissa_size = new_first_mantissa_size;
    this->last_mantissa_size = new_last_mantissa_size;
    this->exponent_size = new_exponent_size;
}
//-------------------------------

// getter
//-------------------------------
std::vector<unsigned long int> mpe::getMantissaAxis() const {
    std::vector<unsigned long> ret;

    for(unsigned long m_size = this->first_mantissa_size; m_size <= this->last_mantissa_size; m_size++){
        ret.push_back(m_size);
    }

    return ret;
}
//-------------------------------


// operator evaluation
//-------------------------------
std::vector<long long int> mpe::evaluateAddition(unsigned long n_tests) {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = getPositiveRandomDouble();
    double b = getPositiveRandomDouble();

    for(unsigned long m_size = this->first_mantissa_size; m_size <= this->last_mantissa_size; m_size++){

        mps A(m_size, this->exponent_size, a);
        mps B(m_size, this->exponent_size, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < n_tests; test++){
            A + B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();
        ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}

std::vector<long long int> mpe::evaluateSubtraction(unsigned long n_tests) {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = getPositiveRandomDouble();
    double b = getPositiveRandomDouble();
    a += b; // in order to get a non-negative result.

    for(unsigned long m_size = this->first_mantissa_size; m_size <= this->last_mantissa_size; m_size++){

        mps A(m_size, this->exponent_size, a);
        mps B(m_size, this->exponent_size, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < n_tests; test++){
            A - B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();
        ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}

std::vector<long long int> mpe::evaluateMultiplication(unsigned long n_tests) {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = getPositiveRandomDouble();
    double b = getPositiveRandomDouble();

    for(unsigned long m_size = this->first_mantissa_size; m_size <= this->last_mantissa_size; m_size++){

        mps A(m_size, this->exponent_size, a);
        mps B(m_size, this->exponent_size, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < n_tests; test++){
            A * B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();
        ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}

std::vector<long long int> mpe::evaluateDivision(unsigned long n_tests) {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = getPositiveRandomDouble();
    double b = getPositiveRandomDouble();

    for(unsigned long m_size = this->first_mantissa_size; m_size <= this->last_mantissa_size; m_size++){

        mps A(m_size, this->exponent_size, a);
        mps B(m_size, this->exponent_size, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < n_tests; test++){
            A / B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();
        ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    }

    pybind11::gil_scoped_acquire acquire;

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
