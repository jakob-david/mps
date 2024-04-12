//
// Created by Jakob on 07.04.24.
//

#include "mpe.h"

#include <../pybind11/include/pybind11/pybind11.h>
namespace py = pybind11;



// parameter setters
//-------------------------------
void mpe::setRandomLimits(double lower_bound, double upper_bound) {

    this->parameters.random_lower_bound = lower_bound;
    this->parameters.random_upper_bound = upper_bound;
}

void mpe::setUpperRandomLimit(double upper_bound){

    this->parameters.random_upper_bound = upper_bound;
}

void mpe::setLowerRandomLimit(double lower_bound){

    this->parameters.random_lower_bound = lower_bound;
}


void mpe::setDimension(unsigned long new_dimension){

    this->parameters.n = new_dimension;
    this->parameters.matrix_1D_size = new_dimension * new_dimension;
}

void mpe::setIterations(unsigned long new_iterations){

    this->parameters.iterations = new_iterations;
}

void mpe::setMaxIter(unsigned long new_max_iter){

    this->parameters.iter_max = new_max_iter;
}


void mpe::setLowerPrecision(unsigned long mantissa_length, unsigned long exponent_length){

    this->parameters.ul_m_l = mantissa_length;
    this->parameters.ul_e_l = exponent_length;
}

void mpe::setWorkingPrecision(unsigned long mantissa_length, unsigned long exponent_length){

    this->parameters.u_m_l = mantissa_length;
    this->parameters.u_e_l = exponent_length;
}

void mpe::setUpperPrecision(unsigned long mantissa_length, unsigned long exponent_length){

    this->parameters.ur_m_l = mantissa_length;
    this->parameters.ur_e_l = exponent_length;
}


void mpe::setLowerPrecisionMantissaRange(unsigned long lower_bound, unsigned long upper_bound){

    this->parameters.ul_m_r_lower = lower_bound;
    this->parameters.ul_m_r_upper = upper_bound;
}

void mpe::setWorkingPrecisionMantissaRange(unsigned long lower_bound, unsigned long upper_bound){

    this->parameters.u_m_r_lower = lower_bound;
    this->parameters.u_m_r_upper = upper_bound;
}

void mpe::setUpperPrecisionMantissaRange(unsigned long lower_bound, unsigned long upper_bound){

    this->parameters.ur_m_r_lower = lower_bound;
    this->parameters.ur_m_r_upper = upper_bound;
}
//-------------------------------


// getters
//-------------------------------
vector<unsigned long> mpe::getLowerPrecisionMantissaAxis() const {

    vector<unsigned long> ret;

    for(unsigned long m_size = this->parameters.ul_m_r_lower; m_size <= this->parameters.ul_m_r_upper; m_size++){
        ret.push_back(m_size);
    }

    return ret;
}

vector<unsigned long> mpe::getWorkingPrecisionMantissaAxis() const {

    vector<unsigned long> ret;

    for(unsigned long m_size = this->parameters.u_m_r_lower; m_size <= this->parameters.u_m_r_upper; m_size++){
        ret.push_back(m_size);
    }

    return ret;
}

vector<unsigned long> mpe::getUpperPrecisionMantissaAxis() const {

    vector<unsigned long> ret;

    for(unsigned long m_size = this->parameters.ur_m_r_lower; m_size <= this->parameters.ur_m_r_upper; m_size++){
        ret.push_back(m_size);
    }

    return ret;
}
//-------------------------------


// generators
//-------------------------------
double mpe::generatePositiveRandomDouble() const {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(numeric_limits<double>::min(), this->parameters.random_upper_bound);

    return dist(mt);
}
//-------------------------------


// operator evaluation
//-------------------------------
std::vector<long long int> mpe::evaluateAddition() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();

    for(unsigned long m_size = this->parameters.u_m_r_lower; m_size <= this->parameters.u_m_r_upper; m_size++){

        mps A(m_size, this->parameters.u_e_l, a);
        mps B(m_size, this->parameters.u_e_l, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < this->parameters.iterations; test++){
            A + B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();
        ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}

std::vector<long long int> mpe::evaluateSubtraction() const {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();
    a += b; // in order to get a non-negative result.

    for(unsigned long m_size = this->parameters.u_m_r_lower; m_size <= this->parameters.u_m_r_upper; m_size++){

        mps A(m_size, this->parameters.u_e_l, a);
        mps B(m_size, this->parameters.u_e_l, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < this->parameters.iterations; test++){
            A - B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();
        ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}

std::vector<long long int> mpe::evaluateMultiplication() const {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();

    for(unsigned long m_size = this->parameters.u_m_r_lower; m_size <= this->parameters.u_m_r_upper; m_size++){

        mps A(m_size, this->parameters.u_e_l, a);
        mps B(m_size, this->parameters.u_e_l, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < this->parameters.iterations; test++){
            A * B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();
        ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}

std::vector<long long int> mpe::evaluateDivision() const {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();

    for(unsigned long m_size = this->parameters.u_m_r_lower; m_size <= this->parameters.u_m_r_upper; m_size++){

        mps A(m_size, this->parameters.u_e_l, a);
        mps B(m_size, this->parameters.u_e_l, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < this->parameters.iterations; test++){
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
    ira IRA(this->irm.n, this->parameters.ur_m_r_upper, this->parameters.ur_e_l);
    // TODO: set randomness

    // set up linear system
    IRA.setRandomMatrix();
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
            IRA.iterativeRefinementLU(b);

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

std::vector<std::vector<long double>> mpe::evaluateConvergence_2D(double precision, bool output) const {

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
    ira IRA(this->irm.n, this->parameters.ur_m_r_upper, this->parameters.ur_e_l);
    // TODO: set randomness

    // set up linear system
    IRA.setRandomMatrix();
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
            IRA.iterativeRefinementLU(b);

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


