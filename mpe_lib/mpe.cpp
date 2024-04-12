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

    this->irm.n = 10;
    this->irm.iter_max = 10;
    this->irm.u_mantissa_size = 23;
    this->irm.u_exponent_size = 8;
    this->irm.ul_first_mantissa_size = 10;
    this->irm.ul_last_mantissa_size = 22;
    this->irm.ur_first_mantissa_size = 24;
    this->irm.ur_last_mantissa_size = 40;
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

// irm setter
void mpe::setBasicParameters_irm(unsigned long new_n, unsigned long new_iter_max) {

    this->irm.n = new_n;
    this->irm.iter_max = new_iter_max;
}

void mpe::setWorkingPrecision_irm(unsigned long new_u_mantissa_size, unsigned long new_u_exponent_size){

    this->irm.u_mantissa_size = new_u_mantissa_size;
    this->irm.u_exponent_size = new_u_exponent_size;
}

void mpe::setRange_ul_irm(unsigned long new_ul_first_mantissa_size, unsigned long new_ul_last_mantissa_size){

    this->irm.ul_first_mantissa_size = new_ul_first_mantissa_size;
    this->irm.ul_last_mantissa_size = new_ul_last_mantissa_size;
}

void mpe::setRange_ur_irm(unsigned long new_ur_first_mantissa_size, unsigned long new_ur_last_mantissa_size){

    this->irm.ur_first_mantissa_size = new_ur_first_mantissa_size;
    this->irm.ur_last_mantissa_size = new_ur_last_mantissa_size;
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

// irm getter
std::vector<unsigned long int> mpe::getAxis_ul_irm() const {

    std::vector<unsigned long> ret;

    for(unsigned long m_size = this->irm.ul_first_mantissa_size; m_size <= this->irm.ul_last_mantissa_size; m_size++){
        ret.push_back(m_size);
    }

    return ret;
}

std::vector<unsigned long int> mpe::getAxis_ur_irm() const {

    std::vector<unsigned long> ret;

    for(unsigned long m_size = this->irm.ur_first_mantissa_size; m_size <= this->irm.ur_last_mantissa_size; m_size++){
        ret.push_back(m_size);
    }

    return ret;
}
//-------------------------------


// operator evaluation
//-------------------------------
std::vector<long long int> mpe::evaluateAddition(unsigned long n_tests) const {

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

std::vector<long long int> mpe::evaluateSubtraction(unsigned long n_tests) const {

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

std::vector<long long int> mpe::evaluateMultiplication(unsigned long n_tests) const {

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

std::vector<long long int> mpe::evaluateDivision(unsigned long n_tests) const {

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

// iterative refinement evaluation
//-------------------------------
std::vector<std::vector<long double>> mpe::evaluateArea_2D(bool output) const {

    std::vector<std::vector<long double>> result;

    if(output){
        cout << "STARTING: evaluateArea_2D" << endl;
    }

    // init FP precision objects
    unsigned long u[2] = {this->irm.u_mantissa_size, this->irm.u_exponent_size};
    unsigned long ul[2] = {0, this->irm.u_exponent_size};

    // release GIL
    py::gil_scoped_release release;

    // init ira object.
    ira IRA(this->irm.n);
    // TODO: set randomness

    // set up linear system
    IRA.setRandomMatrix(this->irm.ur_last_mantissa_size, this->irm.u_exponent_size);
    auto x_mps = IRA.generateRandomVector(this->irm.ur_last_mantissa_size, this->irm.u_exponent_size, this->irm.n);
    auto b = IRA.multiplyWithSystemMatrix(x_mps);

    // set x_mps to working precision
    ira::castVectorElements(this->irm.u_mantissa_size, this->irm.u_exponent_size, &x_mps);

    // loop over all different mantissa sizes of u_r
    for(unsigned long ur_mantissa_size = this->irm.ur_last_mantissa_size; ur_mantissa_size >= this->irm.ur_first_mantissa_size; ur_mantissa_size--){

        if(output){
            cout << "\t ur_mantissa_size: " << ur_mantissa_size;
        }

        std::vector<long double> tmp;

        // convert the system into the new precision
        IRA.castSystemMatrix(ur_mantissa_size, this->irm.u_exponent_size);
        ira::castVectorElements(ur_mantissa_size, this->irm.u_exponent_size, &b);

        // loop over all different mantissa sizes of u_l
        for(unsigned long ul_mantissa_size = this->irm.ul_first_mantissa_size; ul_mantissa_size <= this->irm.ul_last_mantissa_size; ul_mantissa_size++){

            // set new u_l mantissa size
            ul[0] = ul_mantissa_size;

            // perform iterative refinement algorithm
            IRA.iterativeRefinementLU(b, u, ul, this->irm.iter_max, x_mps);

            // save data
            auto tmp_result = IRA.evaluation.IR_area_relativeError * (double) IRA.evaluation.milliseconds;
             tmp.push_back(tmp_result);
        }

        result.insert(result.begin(), tmp);

        if(output){
            cout << "\tdone\t\tlast: " << this->irm.ur_first_mantissa_size << endl;
        }
    }

    // acquire GIL
    pybind11::gil_scoped_acquire acquire;

    return result;
}

std::vector<std::vector<long double>> mpe::evaluateConvergence_2D(double precision, unsigned long max_iter, bool output) const {

    std::vector<std::vector<long double>> result;

    if(output){
        cout << "STARTING: evaluateConvergence_2D" << endl;
    }

    // init FP precision objects
    unsigned long u[2] = {this->irm.u_mantissa_size, this->irm.u_exponent_size};
    unsigned long ul[2] = {0, this->irm.u_exponent_size};

    // init target precision
    mps target_precision(this->irm.u_mantissa_size, this->irm.u_exponent_size, precision);

    // release GIL
    py::gil_scoped_release release;

    // init ira object.
    ira IRA(this->irm.n);
    // TODO: set randomness

    // set up linear system
    IRA.setRandomMatrix(this->irm.ur_last_mantissa_size, this->irm.u_exponent_size);
    auto x_mps = IRA.generateRandomVector(this->irm.ur_last_mantissa_size, this->irm.u_exponent_size, this->irm.n);
    auto b = IRA.multiplyWithSystemMatrix(x_mps);

    // set x_mps to working precision
    ira::castVectorElements(this->irm.u_mantissa_size, this->irm.u_exponent_size, &x_mps);

    // loop over all different mantissa sizes of u_r
    for(unsigned long ur_mantissa_size = this->irm.ur_last_mantissa_size; ur_mantissa_size >= this->irm.ur_first_mantissa_size; ur_mantissa_size--){

        if(output){
            cout << "\t ur_mantissa_size: " << ur_mantissa_size;
        }

        std::vector<long double> tmp;

        // convert the system into the new precision
        IRA.castSystemMatrix(ur_mantissa_size, this->irm.u_exponent_size);
        ira::castVectorElements(ur_mantissa_size, this->irm.u_exponent_size, &b);

        // loop over all different mantissa sizes of u_l
        for(unsigned long ul_mantissa_size = this->irm.ul_first_mantissa_size; ul_mantissa_size <= this->irm.ul_last_mantissa_size; ul_mantissa_size++){

            // set new u_l mantissa size
            ul[0] = ul_mantissa_size;

            // perform iterative refinement algorithm
            IRA.iterativeRefinementLU(b, u, ul, max_iter, x_mps, target_precision);

            // save data
            auto tmp_result = (double) IRA.evaluation.iterations_needed;
            tmp.push_back(tmp_result);
        }

        result.insert(result.begin(), tmp);

        if(output){
            cout << "\tdone\t\tlast: " << this->irm.ur_first_mantissa_size << endl;
        }
    }

    // acquire GIL
    pybind11::gil_scoped_acquire acquire;

    return result;
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
