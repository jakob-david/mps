//
// Created by Jakob on 07.04.24.
//

#include "mpe.h"

#include <../pybind11/include/pybind11/pybind11.h>
namespace py = pybind11;

// constructor
//-------------------------------
mpe::mpe() {

    this->controllers.working_precision_mantissa_set = false;
    this->controllers.working_precision_exponent_set = false;

    this->controllers.expected_error_set = false;
    this->controllers.expected_precision_set = false;
}
//-------------------------------

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

    this->controllers.working_precision_mantissa_set = true;
    this->controllers.working_precision_exponent_set = true;

    this->parameters.u_m_l = mantissa_length;
    this->parameters.u_e_l = exponent_length;
}

void mpe::setUpperPrecision(unsigned long mantissa_length, unsigned long exponent_length){

    this->parameters.ur_m_l = mantissa_length;
    this->parameters.ur_e_l = exponent_length;
}

void mpe::setLowerPrecisionExponent(unsigned long exponent_length){

    this->parameters.ul_e_l = exponent_length;
}

void mpe::setWorkingPrecisionExponent(unsigned long exponent_length){

    this->controllers.working_precision_exponent_set = true;

    this->parameters.u_e_l = exponent_length;
}

void mpe::setUpperPrecisionExponent(unsigned long exponent_length){

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


void mpe::setExpectedError(double new_expected_error){

    if(!this->controllers.working_precision_mantissa_set || !this->controllers.working_precision_exponent_set){
        throw std::invalid_argument("ERROR: in setExpectedError (mpe) : working precision must be set beforehand");
    }

    this->controllers.expected_error_set = true;

    mps ret(this->parameters.u_m_l, this->parameters.u_e_l, new_expected_error);
    this->parameters.expected_error |= ret;
}

void mpe::setExpectedPrecision(long long new_expected_precision){

    this->controllers.expected_precision_set = true;

    this->parameters.expected_precision = new_expected_precision;
}
//-------------------------------


// getters
//-------------------------------
unsigned long mpe::getIterations() const {

    return this->parameters.iterations;
}

vector<unsigned long> mpe::getIterationAxis() const {

    vector<unsigned long> ret;

    for(unsigned long iteration = 1; iteration <= this->parameters.iterations; iteration++){
        ret.push_back(iteration);
    }

    return ret;
}

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
vector<long long int> mpe::evaluateAddition() const {

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

vector<long long int> mpe::evaluateSubtraction() const {

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

vector<long long int> mpe::evaluateMultiplication() const {

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

vector<long long int> mpe::evaluateDivision() const {

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


// operator evaluation
//-------------------------------
vector<long long int> mpe::evaluateAdditionDouble() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();


    // float
    //-------------------------------
    auto A_f = (float) a;
    auto B_f = (float) b;
    float sum_f = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        //#pragma GCC diagnostic push
        //#pragma GCC diagnostic ignored "-Wunused-value"
        sum_f += (A_f + B_f);
        //#pragma GCC diagnostic pop
    }
    auto finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    cout << sum_f << endl;
    //-------------------------------


    // double
    //-------------------------------
    auto A_d = (double) a;
    auto B_d = (double) b;
    double sum_d = 0;
    start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_d += (A_d + B_d);
    }
    finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    cout << sum_d << endl;
    //-------------------------------


    // long double
    //-------------------------------
    auto A_ld = (long double) a;
    auto B_ld = (long double) b;
    long double sum_ld = 0;
    start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_ld += (A_ld + B_ld);
    }
    finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    cout << sum_ld << endl;
    //-------------------------------

    cout << sum_f + sum_d + sum_ld << endl;

    pybind11::gil_scoped_acquire acquire;

    return ret;

}
vector<long long int> mpe::evaluateSubtractionDouble() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();
    a += b; // in order to get a non-negative result.

    // float
    //-------------------------------
    auto A_f = (float) a;
    auto B_f = (float) b;
    float sum_f = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_f -= (A_f - B_f);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    //-------------------------------


    // double
    //-------------------------------
    auto A_d = (double) a;
    auto B_d = (double) b;
    double sum_d = 0;
    start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_d -= (A_d - B_d);
    }
    finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    //-------------------------------


    // long double
    //-------------------------------
    auto A_ld = (long double) a;
    auto B_ld = (long double) b;
    long double sum_ld = 0;
    start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_ld -= (A_ld - B_ld);
    }
    finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    //-------------------------------

    cout << sum_f + sum_d + sum_ld << endl;

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long long int> mpe::evaluateMultiplicationDouble() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();

    // float
    //-------------------------------
    auto A_f = (float) a;
    auto B_f = (float) b;
    float sum_f = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_f *= (A_f * B_f);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    //-------------------------------


    // double
    //-------------------------------
    auto A_d = (double) a;
    auto B_d = (double) b;
    double sum_d = 0;
    start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_d *= (A_d * B_d);
    }
    finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    //-------------------------------


    // long double
    //-------------------------------
    auto A_ld = (long double) a;
    auto B_ld = (long double) b;
    long double sum_ld = 0;
    start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_ld *= (A_ld * B_ld);
    }
    finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    //-------------------------------

    cout << sum_f + sum_d + sum_ld << endl;

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long long int> mpe::evaluateDivisionDouble() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long long> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();

    // float
    //-------------------------------
    auto A_f = (float) a;
    auto B_f = (float) b;
    float sum_f = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_f /= (A_f / B_f);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    //-------------------------------


    // double
    //-------------------------------
    auto A_d = (double) a;
    auto B_d = (double) b;
    double sum_d = 0;
    start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_d /= (A_d / B_d);
    }
    finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    //-------------------------------


    // long double
    //-------------------------------
    auto A_ld = (long double) a;
    auto B_ld = (long double) b;
    long double sum_ld = 0;
    start = std::chrono::high_resolution_clock::now();
    for(unsigned long test = 0; test < this->parameters.iterations; test++){
        sum_ld /= (A_ld / B_ld);
    }
    finish = std::chrono::high_resolution_clock::now();
    ret.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count());
    //-------------------------------

    cout << sum_f + sum_d + sum_ld << endl;

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
//-------------------------------


// iterative refinement evaluation
//-------------------------------
vector<vector<long double>> mpe::evaluateArea(bool output) const {

    if(output){
        cout << "STARTING: evaluateArea" << endl;
    }

    vector<vector<long double>> ret;

    // release GIL
    py::gil_scoped_release release;

    // init ira object.
    ira IRA(this->parameters.n, this->parameters.ur_m_l, this->parameters.ur_e_l);
    IRA.setRandomRange(this->parameters.random_lower_bound, this->parameters.random_upper_bound);
    IRA.setMaxIter(this->parameters.iterations);
    IRA.setLowerPrecision(this->parameters.ul_m_l, this->parameters.ul_e_l);
    IRA.setWorkingPrecision(this->parameters.u_m_l, this->parameters.u_e_l);
    IRA.setUpperPrecision(this->parameters.ur_m_l, this->parameters.ur_e_l);

    // generate linear system
    auto b = IRA.generateRandomLinearSystem();

    // perform iterative refinement algorithm
    IRA.iterativeRefinementLU(b);

    // acquire GIL
    pybind11::gil_scoped_acquire acquire;

    ret.push_back(IRA.evaluation.IR_relativeError);
    ret.push_back(IRA.evaluation.IR_precision_errors);

    return ret;
}

vector<vector<vector<long double>>> mpe::evaluateArea_2D(bool output) const {

    vector<vector<vector<long double>>> result;
    vector<vector<long double>> result_error;
    vector<vector<long double>> result_precision;

    if(output){
        cout << "STARTING: evaluateArea_2D" << endl;
    }

    // release GIL
    py::gil_scoped_release release;

    // init ira object.
    ira IRA(this->parameters.n, this->parameters.ur_m_r_upper, this->parameters.ur_e_l);
    IRA.setRandomRange(this->parameters.random_lower_bound, this->parameters.random_upper_bound);
    IRA.setMaxIter(this->parameters.iterations);
    IRA.setLowerPrecisionExponent(this->parameters.ul_e_l);
    IRA.setWorkingPrecision(this->parameters.u_m_l, this->parameters.u_e_l);

    // generate linear system
    auto b = IRA.generateRandomLinearSystem();

    // loop over all different mantissa sizes of u_r
    for(unsigned long ur_mantissa_size = this->parameters.ur_m_r_upper; ur_mantissa_size >= this->parameters.ur_m_r_lower; ur_mantissa_size--){

        if(output){
            cout << "\t ur_mantissa_size: " << ur_mantissa_size;
        }

        std::vector<long double> subresult_error;
        std::vector<long double> subresult_precision;

        IRA.setUpperPrecisionMantissa(ur_mantissa_size);

        // convert the system into the new precision
        IRA.castSystemMatrix(ur_mantissa_size, this->parameters.u_e_l);
        IRA.castExpectedResult(ur_mantissa_size, this->parameters.u_e_l);
        ira::castVectorElements(ur_mantissa_size, this->parameters.u_e_l, &b);

        // loop over all different mantissa sizes of u_l
        for(unsigned long ul_mantissa_size = this->parameters.ul_m_r_lower; ul_mantissa_size <= this->parameters.ul_m_r_upper; ul_mantissa_size++){

            // perform iterative refinement algorithm
            IRA.setLowerPrecisionMantissa(ul_mantissa_size);
            IRA.iterativeRefinementLU(b);

            // save data relative error
            auto subsubresult_error = IRA.evaluation.IR_area_relativeError * (double) IRA.evaluation.milliseconds;
            subresult_error.push_back(subsubresult_error);

            // save data precision error
            auto subsubresult_precision = IRA.evaluation.IR_precision_error_sum * (double) IRA.evaluation.milliseconds;
            subresult_precision.push_back(subsubresult_precision);
        }

        result_error.insert(result_error.begin(), subresult_error);
        result_precision.insert(result_precision.begin(), subresult_precision);

        if(output){
            cout << "\tdone\t\tlast: " << this->parameters.ur_m_r_lower << endl;
        }
    }

    // acquire GIL
    pybind11::gil_scoped_acquire acquire;

    result.push_back(result_error);
    result.push_back(result_precision);

    return result;
}

vector<std::vector<long double>> mpe::evaluateConvergence_2D(bool output) const {

    std::vector<std::vector<long double>> result;

    if(output){
        cout << "STARTING: evaluateConvergence_2D" << endl;
    }

    // release GIL
    py::gil_scoped_release release;

    // init ira object.
    ira IRA(this->parameters.n, this->parameters.ur_m_r_upper, this->parameters.ur_e_l);
    IRA.setRandomRange(this->parameters.random_lower_bound, this->parameters.random_upper_bound);
    IRA.setMaxIter(this->parameters.iterations);
    IRA.setLowerPrecisionExponent(this->parameters.ul_e_l);
    IRA.setWorkingPrecision(this->parameters.u_m_l, this->parameters.u_e_l);

    // generate linear system
    auto b = IRA.generateRandomLinearSystem();

    // set up expected error or precision
    if(this->controllers.expected_error_set && this->controllers.expected_precision_set){
        throw std::invalid_argument("ERROR: in evaluateConvergence_2D: both expected error and precision set");
    } else if(this->controllers.expected_error_set){
        IRA.setExpectedError(this->parameters.expected_error);
    } else if(this->controllers.expected_precision_set){
        IRA.setExpectedPrecision(this->parameters.expected_precision);
    } else {
        throw std::invalid_argument("ERROR: in evaluateConvergence_2D: neither expected error or precision set");
    }



    // loop over all different mantissa sizes of u_r
    for(unsigned long ur_mantissa_size = this->parameters.ur_m_r_upper; ur_mantissa_size >= this->parameters.ur_m_r_lower; ur_mantissa_size--){

        if(output){
            cout << "\t ur_mantissa_size: " << ur_mantissa_size;
        }

        std::vector<long double> tmp;
        IRA.setUpperPrecisionMantissa(ur_mantissa_size);

        // convert the system into the new precision
        IRA.castSystemMatrix(ur_mantissa_size, this->parameters.u_e_l);
        IRA.castExpectedResult(ur_mantissa_size, this->parameters.u_e_l);

        if(this->controllers.expected_error_set){
            IRA.castExpectedError(ur_mantissa_size, this->parameters.u_e_l);
        }

        ira::castVectorElements(ur_mantissa_size, this->parameters.u_e_l, &b);

        // loop over all different mantissa sizes of u_l
        for(unsigned long ul_mantissa_size = this->parameters.ul_m_r_lower; ul_mantissa_size <= this->parameters.ul_m_r_upper; ul_mantissa_size++){

            // perform iterative refinement algorithm
            IRA.setLowerPrecisionMantissa(ul_mantissa_size);
            IRA.iterativeRefinementLU(b);

            // save data;
            auto tmp_result = (double) IRA.evaluation.iterations_needed;
            tmp.push_back(tmp_result);
        }

        result.insert(result.begin(), tmp);

        if(output){
            cout << "\tdone\t\tlast: " << this->parameters.ur_m_r_lower << endl;
        }
    }

    // acquire GIL
    pybind11::gil_scoped_acquire acquire;

    return result;
}

//-------------------------------


