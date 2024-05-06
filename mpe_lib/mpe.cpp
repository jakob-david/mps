//
// Created by Jakob on 07.04.24.
//

#include "mpe.h"
#include "../iras_lib/iras.cpp"

#include <../pybind11/include/pybind11/pybind11.h>
namespace py = pybind11;

// constructor
//-------------------------------
mpe::mpe() {

    this->parameters.sparsity_rate = 0;

    this->controllers.working_precision_mantissa_set = false;
    this->controllers.working_precision_exponent_set = false;

    this->controllers.expected_error_set = false;
    this->controllers.expected_precision_set = false;

    this->controllers.gil = true;

    this->parameters.mantissa_step_size = 1;
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

void mpe::setSparsityRate(double new_sparsity_rate) {

    this->parameters.sparsity_rate = new_sparsity_rate;
}

void mpe::setSparsityPointsAmount(unsigned long new_sparsity_points_amount) {

    this->parameters.sparsity_points_amount = new_sparsity_points_amount;
}


void mpe::setMatrixSizeRange(unsigned long lower_bound, unsigned long upper_bound) {

    this->parameters.matrix_size_lower_limit = lower_bound;
    this->parameters.matrix_size_upper_limit = upper_bound;
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


void mpe::setWorkingPrecisionExponentRange(unsigned long lower_bound, unsigned long upper_bound) {

    this->parameters.u_e_r_lower = lower_bound;
    this->parameters.u_e_r_upper = upper_bound;
}


void mpe::setExpectedError(double new_expected_error){

    if(!this->controllers.working_precision_mantissa_set || !this->controllers.working_precision_exponent_set){
        throw std::invalid_argument("ERROR: in setExpectedError (mpe) : working precision must be set beforehand");
    }

    this->controllers.expected_error_set = true;

    mps ret(this->parameters.u_m_l, this->parameters.u_e_l, new_expected_error);
    this->parameters.expected_error |= ret;
}

void mpe::setExpectedPrecision(long long new_expected_precision, unsigned long mantissa_length, unsigned long exponent_length){

    this->controllers.expected_precision_set = true;

    this->parameters.expected_precision = new_expected_precision;
    this->parameters.ep_mantissa_length = mantissa_length;
    this->parameters.ep_exponent_length = exponent_length;
}


void mpe::setMatrixSizes(vector<unsigned long> matrix_sizes){

    this->parameters.matrix_sizes.resize(matrix_sizes.size());

    for(unsigned long idx = 0; idx < matrix_sizes.size(); idx++){
        this->parameters.matrix_sizes[idx] = matrix_sizes[idx];
    }
}

void mpe::setMantissaStepSize(unsigned long new_step_size){

    this->parameters.mantissa_step_size = new_step_size;
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

    for(unsigned long m_size = this->parameters.ur_m_r_lower; m_size <= this->parameters.ur_m_r_upper; m_size+=this->parameters.mantissa_step_size){
        ret.push_back(m_size);
    }

    return ret;
}


vector<unsigned long> mpe::getWorkingPrecisionExponentAxis() const {

    vector<unsigned long> ret;

    for(unsigned long e_size = this->parameters.u_e_r_lower; e_size <= this->parameters.u_e_r_upper; e_size++){
        ret.push_back(e_size);
    }

    return ret;
}


vector<double> mpe::getSparsityAxis() const{

    vector<double> sparsity_rates;
    auto sparsity_points_amount = (double) this->parameters.sparsity_points_amount;
    for(unsigned long i = 0; i <= this->parameters.sparsity_points_amount; i++){
        sparsity_rates.push_back((((double) i)/(sparsity_points_amount)) * 0.9);
    }

    return sparsity_rates;
}

vector<unsigned long> mpe::getMatrixSizesAxis() const {

    return this->parameters.matrix_sizes;
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
vector<long double> mpe::evaluateAddition() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long double> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();

    a = 100;
    b = 100;

    for(unsigned long m_size = this->parameters.u_m_r_lower; m_size <= this->parameters.u_m_r_upper; m_size++){

        mps A(m_size, this->parameters.u_e_l, a);
        mps B(m_size, this->parameters.u_e_l, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < this->parameters.iterations; test++){
            A + B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();

        auto result_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
        ret.push_back(((long double) result_in_microseconds) / 1000) ;
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long double> mpe::evaluateSubtraction() const {

    // variable for python multithreading.

    py::gil_scoped_release release; // noqa

    std::vector<long double> ret;

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

        auto result_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
        ret.push_back(((long double) result_in_microseconds) / 1000) ;
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long double> mpe::evaluateMultiplication() const {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long double> ret;

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

        auto result_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
        ret.push_back(((long double) result_in_microseconds) / 1000) ;
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long double> mpe::evaluateDivision() const {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long double> ret;

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

        auto result_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
        ret.push_back(((long double) result_in_microseconds) / 1000) ;
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}

vector<long double> mpe::evaluateAdditionExponent() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long double> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();

    for(unsigned long e_size = this->parameters.u_e_r_lower; e_size <= this->parameters.u_e_r_upper; e_size++){

        mps A(this->parameters.u_m_l, e_size, a);
        mps B(this->parameters.u_m_l, e_size, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < this->parameters.iterations; test++){
            A + B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();

        auto result_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
        ret.push_back(((long double) result_in_microseconds) / 1000) ;
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long double> mpe::evaluateSubtractionExponent() const {

    // variable for python multithreading.

    py::gil_scoped_release release; // noqa

    std::vector<long double> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();
    a += b; // in order to get a non-negative result.

    for(unsigned long e_size = this->parameters.u_e_r_lower; e_size <= this->parameters.u_e_r_upper; e_size++){

        mps A(this->parameters.u_m_l, e_size, a);
        mps B(this->parameters.u_m_l, e_size, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < this->parameters.iterations; test++){
            A - B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();

        auto result_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
        ret.push_back(((long double) result_in_microseconds) / 1000) ;
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long double> mpe::evaluateMultiplicationExponent() const {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long double> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();

    for(unsigned long e_size = this->parameters.u_e_r_lower; e_size <= this->parameters.u_e_r_upper; e_size++){

        mps A(this->parameters.u_m_l, e_size, a);
        mps B(this->parameters.u_m_l, e_size, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < this->parameters.iterations; test++){
            A * B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();

        auto result_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
        ret.push_back(((long double) result_in_microseconds) / 1000) ;
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long double> mpe::evaluateDivisionExponent() const {

    // variable for python multithreading.

    py::gil_scoped_release release;

    std::vector<long double> ret;

    double a = generatePositiveRandomDouble();
    double b = generatePositiveRandomDouble();

    for(unsigned long e_size = this->parameters.u_e_r_lower; e_size <= this->parameters.u_e_r_upper; e_size++){

        mps A(this->parameters.u_m_l, e_size, a);
        mps B(this->parameters.u_m_l, e_size, b);

        const auto start = std::chrono::high_resolution_clock::now();

        for(unsigned long test = 0; test < this->parameters.iterations; test++){
            A / B;
        }

        const auto finish = std::chrono::high_resolution_clock::now();

        auto result_in_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
        ret.push_back(((long double) result_in_microseconds) / 1000) ;
    }

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
//-------------------------------


// operator evaluation
//-------------------------------
vector<long double> mpe::evaluateAdditionDouble() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long double> ret;
    long long result_in_nanoseconds;

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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
    //-------------------------------

    cout << sum_f + sum_d + sum_ld << endl;

    pybind11::gil_scoped_acquire acquire;

    return ret;

}
vector<long double> mpe::evaluateSubtractionDouble() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long double> ret;
    long long result_in_nanoseconds;

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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
    //-------------------------------

    cout << sum_f + sum_d + sum_ld << endl;

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long double> mpe::evaluateMultiplicationDouble() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long double> ret;
    long long result_in_nanoseconds;

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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
    //-------------------------------

    cout << sum_f + sum_d + sum_ld << endl;

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
vector<long double> mpe::evaluateDivisionDouble() const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    std::vector<long double> ret;
    long long result_in_nanoseconds;

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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
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

    result_in_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    ret.push_back(((long double) result_in_nanoseconds) / 1000);
    //-------------------------------

    cout << sum_f + sum_d + sum_ld << endl;

    pybind11::gil_scoped_acquire acquire;

    return ret;
}
//-------------------------------


// evaluate sparsity
//-------------------------------
vector<vector<long double>> mpe::evaluateSparsity(bool output) const {

    if(output){
        cout << "STARTING: evaluateArea" << endl;
    }

    vector<vector<long double>> result;

    vector<long double> result_relative_error;
    vector<long double> result_precision;
    vector<long double> run_time;

    py::gil_scoped_release release;

    ira IRA(this->parameters.n, this->parameters.ur_m_l, this->parameters.ur_e_l);
    IRA.setRandomRange(this->parameters.random_lower_bound, this->parameters.random_upper_bound);
    IRA.setWorkingPrecision(this->parameters.u_m_l, this->parameters.u_e_l);
    IRA.setLowerPrecision(this->parameters.ul_m_l, this->parameters.ul_e_l);
    IRA.setMaxIter(this->parameters.iter_max);

    auto sparsity_rates = getSparsityAxis();

    for(auto sparsity_rate : sparsity_rates){

        IRA.setSparsityRate(sparsity_rate);

        auto b = IRA.generateRandomLinearSystem();

        IRA.irPLU(b);

        result_relative_error.push_back(IRA.evaluation.IR_relativeError_sum);
        result_precision.push_back(IRA.evaluation.IR_precisionError_sum);
        run_time.push_back(IRA.evaluation.milliseconds);
    }

    result.push_back(result_relative_error);
    result.push_back(result_precision);
    result.push_back(run_time);

    // acquire GIL
    pybind11::gil_scoped_acquire acquire;

    return result;
}

vector<vector<long double>> mpe::evaluateSparsity_2D(bool output) const {

    if(output){
        cout << "STARTING: evaluateArea_2D" << endl;
    }

    vector<vector<long double>> result;

    py::gil_scoped_release release;

    for(unsigned long m_size = this->parameters.ur_m_r_lower; m_size <= this->parameters.ur_m_r_upper; m_size += this->parameters.mantissa_step_size){

        if(output){
            cout << "\tevaluating mantissa: " << m_size << endl;
        }

        vector<long double> sub_result;

        ira IRA(this->parameters.n, m_size, this->parameters.ur_e_l);
        IRA.setRandomRange(this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        IRA.setWorkingPrecision(this->parameters.u_m_l, this->parameters.u_e_l);
        IRA.setLowerPrecision(this->parameters.ul_m_l, this->parameters.ul_e_l);
        IRA.setMaxIter(this->parameters.iterations);

        auto sparsity_rates = getSparsityAxis();

        for(auto sparsity_rate : sparsity_rates){

            if(output){
                cout << "\t\tevaluating sparsity: " << sparsity_rate << endl;
            }

            IRA.setSparsityRate(sparsity_rate);

            auto b = IRA.generateRandomLinearSystem();

            IRA.irPLU(b);

            sub_result.push_back(IRA.evaluation.milliseconds);
        }

        result.push_back(sub_result);
    }

    // acquire GIL
    pybind11::gil_scoped_acquire acquire;

    return result;
}
//-------------------------------

// compare operators double/float
//-------------------------------
vector<vector<long double>> mpe::compareMVM(unsigned long iter_system, unsigned long iter_mps) const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    auto largest_matrix = this->parameters.matrix_sizes.back();
    unsigned long number_of_computations_system = (unsigned long) pow(largest_matrix, 2) * iter_system;
    unsigned long number_of_computations_mps = (unsigned long) pow(largest_matrix, 2) * iter_mps;

    vector<long double> results_system;
    vector<long double> results_mps;

    for(auto matrix_size : this->parameters.matrix_sizes){

        cout << "matrix_size: " << matrix_size << endl;

        // perform test system
        //-------------------------------
        unsigned long iterations = number_of_computations_system / (unsigned long) pow(matrix_size, 2);

        auto A = generateRandomMatrix<double>(matrix_size, this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        auto x = generateRandomVector<double>(matrix_size, this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        auto start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            dotProduct(A, x);
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto result_d = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        auto A_f = convert<double, float>(A);
        auto x_f = convert<double, float>(x);
        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            dotProduct(A_f, x_f);
        }
        finish = std::chrono::high_resolution_clock::now();
        auto result_f = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        results_system.push_back((long double) result_d / (long double) result_f);
        //-------------------------------

        // perform test mps
        //-------------------------------
        iterations = number_of_computations_mps / (unsigned long) pow(matrix_size, 2);

        ira IRA(matrix_size, 52, 11);
        IRA.setRandomRange(this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        IRA.setRandomMatrix();
        auto x_mps = IRA.generateRandomVector(matrix_size, 52, 11);
        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            IRA.multiplyWithSystemMatrix(x_mps);
        }
        finish = std::chrono::high_resolution_clock::now();
        result_d = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        IRA.castSystemMatrix(23, 8);
        ira::cast(x_mps, 23, 8);
        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            IRA.multiplyWithSystemMatrix(x_mps);
        }
        finish = std::chrono::high_resolution_clock::now();
        result_f = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        results_mps.push_back((long double) result_d / (long double) result_f);
        //-------------------------------
    }

    vector<vector<long double>> results;
    results.push_back(results_system);
    results.push_back(results_mps);

    pybind11::gil_scoped_acquire acquire;

    return results;
}

vector<vector<long double>> mpe::compareMMM(unsigned long iter_system, unsigned long iter_mps) const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    auto largest_matrix = this->parameters.matrix_sizes.back();
    unsigned long number_of_computations_system = (unsigned long) pow(largest_matrix, 3) * iter_system;
    unsigned long number_of_computations_mps = (unsigned long) pow(largest_matrix, 3) * iter_mps;

    vector<long double> results_system;
    vector<long double> results_mps;

    for(auto matrix_size : this->parameters.matrix_sizes){

        cout << "matrix_size: " << matrix_size << endl;

        // perform test system
        //-------------------------------
        unsigned long iterations = number_of_computations_system / (unsigned long) pow(matrix_size, 3);

        auto A = generateRandomMatrix<double>(matrix_size, this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        auto B = generateRandomMatrix<double>(matrix_size, this->parameters.random_lower_bound, this->parameters.random_upper_bound);

        auto start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            dotProduct<double>(A, B);
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto result_d = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        auto A_f = convert<double, float>(A);
        auto B_f = convert<double, float>(B);
        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            dotProduct<float>(A_f, B_f);
        }
        finish = std::chrono::high_resolution_clock::now();
        auto result_f = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        results_system.push_back((long double) result_d / (long double) result_f);
        //-------------------------------

        // perform test mps
        //-------------------------------
        iterations = number_of_computations_mps / (unsigned long) pow(matrix_size, 3);

        ira IRA(matrix_size, 52, 11);
        IRA.setRandomRange(this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        auto A_mps = IRA.generateRandomMatrix(matrix_size, 52, 11);
        auto B_mps = IRA.generateRandomMatrix(matrix_size, 52, 11);
        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            ira::dotProduct(A_mps, B_mps);
        }
        finish = std::chrono::high_resolution_clock::now();
        result_d = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        ira::cast(A_mps, 23, 8);
        ira::cast(B_mps, 23, 8);
        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            ira::dotProduct(A_mps, B_mps);
        }
        finish = std::chrono::high_resolution_clock::now();
        result_f = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        results_mps.push_back((long double) result_d / (long double) result_f);
        //-------------------------------
    }

    vector<vector<long double>> results;
    results.push_back(results_system);
    results.push_back(results_mps);

    pybind11::gil_scoped_acquire acquire;

    return results;
}

vector<vector<long double>> mpe::comparePLU(unsigned long iter_system, unsigned long iter_mps) const {

    // variable for python multithreading.
    py::gil_scoped_release release;

    auto largest_matrix = this->parameters.matrix_sizes.back();
    unsigned long number_of_computations_system = (unsigned long) pow(largest_matrix, 3) * iter_system;
    unsigned long number_of_computations_mps = (unsigned long) pow(largest_matrix, 3) * iter_mps;

    vector<long double> results_system;
    vector<long double> results_mps;

    for(auto matrix_size : this->parameters.matrix_sizes){

        cout << "matrix_size: " << matrix_size << endl;

        // perform test system
        //-------------------------------
        unsigned long iterations = number_of_computations_system / (unsigned long) pow(matrix_size, 3);

        auto A = generateRandomMatrix<double>(matrix_size, this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        vector<unsigned long> P;

        auto start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            PLU<double, double>(A, P);
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto result_d = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        auto A_f = convert<double, float>(A);
        P.clear();

        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            PLU<float, float>(A_f, P);
        }
        finish = std::chrono::high_resolution_clock::now();
        auto result_f = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        results_system.push_back((long double) result_d / (long double) result_f);
        //-------------------------------

        // perform test mps
        //-------------------------------
        iterations = number_of_computations_mps / (unsigned long) pow(matrix_size, 3);

        ira IRA(matrix_size, 52, 11);
        IRA.setRandomRange(this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        IRA.setRandomMatrix();

        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            IRA.decompPLU(52, 11);
        }
        finish = std::chrono::high_resolution_clock::now();
        result_d = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        IRA.castSystemMatrix(23, 8);
        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            IRA.decompPLU(23, 8);
        }
        finish = std::chrono::high_resolution_clock::now();
        result_f = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        results_mps.push_back((long double) result_d / (long double) result_f);
        //-------------------------------
    }

    vector<vector<long double>> results;
    results.push_back(results_system);
    results.push_back(results_mps);

    pybind11::gil_scoped_acquire acquire;

    return results;
}

vector<vector<long double>> mpe::compareIR(unsigned long max_iter, unsigned long iter_system, unsigned long iter_mps) const {

    // variable for python multithreading.
    if(this->controllers.gil){
        py::gil_scoped_release release;
    }

    auto largest_matrix = this->parameters.matrix_sizes.back();
    unsigned long number_of_computations_system = (unsigned long) pow(largest_matrix, 3) * iter_system;
    unsigned long number_of_computations_mps = (unsigned long) pow(largest_matrix, 3) * iter_mps;

    vector<long double> results_system;
    vector<long double> results_mps;

    for(auto matrix_size : this->parameters.matrix_sizes){

        cout << "matrix_size: " << matrix_size << endl;

        // perform test system
        //-------------------------------
        unsigned long iterations = number_of_computations_system / (unsigned long) pow(matrix_size, 3);

        auto A = generateRandomMatrix<double>(matrix_size, this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        auto b = generateRandomVector<double>(matrix_size, this->parameters.random_lower_bound, this->parameters.random_upper_bound);

        auto start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            directPLU<double>(A, b);
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto result_d = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();


        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            irPLU<float, double, double>(A, b, max_iter);
        }
        finish = std::chrono::high_resolution_clock::now();
        auto result_f = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        results_system.push_back((long double) result_d / (long double) result_f);
        //-------------------------------

        // perform test mps
        //-------------------------------
        iterations = number_of_computations_mps / (unsigned long) pow(matrix_size, 3);

        ira IRA(matrix_size, 52, 11);
        IRA.setRandomRange(this->parameters.random_lower_bound, this->parameters.random_upper_bound);
        IRA.setRandomMatrix();
        IRA.setWorkingPrecision(52, 11);
        IRA.setLowerPrecision(23, 8);

        auto b_mps = IRA.generateRandomVector(matrix_size, 52, 11);

        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            IRA.directPLU(b_mps);
        }
        finish = std::chrono::high_resolution_clock::now();
        result_d = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();


        start = std::chrono::high_resolution_clock::now();
        for(unsigned long i = 0; i < iterations; i++){
            IRA.irPLU(b_mps);
        }
        finish = std::chrono::high_resolution_clock::now();
        result_f = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

        results_mps.push_back((long double) result_d / (long double) result_f);
        //-------------------------------
    }

    vector<vector<long double>> results;
    results.push_back(results_system);
    results.push_back(results_mps);

    if(this->controllers.gil){
        pybind11::gil_scoped_acquire acquire;
    }

    return results;
}

vector<vector<vector<long double>>> mpe::compareMultipleIR(vector<unsigned long> iterations, unsigned long iter_system, unsigned long iter_mps) {

    this->controllers.gil = false;
    vector<vector<vector<long double>>> results;


    py::gil_scoped_release release;

    for(auto iter : iterations){
        results.push_back(compareIR(iter, iter_system, iter_mps));
    }

    pybind11::gil_scoped_acquire acquire;

    return results;
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
    IRA.irPLU(b);

    // acquire GIL
    pybind11::gil_scoped_acquire acquire;

    ret.push_back(IRA.evaluation.IR_relativeErrors);
    ret.push_back(IRA.evaluation.IR_precisionErrors);

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
        ira::cast(b, ur_mantissa_size, this->parameters.u_e_l);

        // loop over all different mantissa sizes of u_l
        for(unsigned long ul_mantissa_size = this->parameters.ul_m_r_lower; ul_mantissa_size <= this->parameters.ul_m_r_upper; ul_mantissa_size++){

            // perform iterative refinement algorithm
            IRA.setLowerPrecisionMantissa(ul_mantissa_size);
            IRA.irPLU(b);

            // save data relative error
            auto subsubresult_error = IRA.evaluation.IR_relativeError_sum * IRA.evaluation.milliseconds;
            subresult_error.push_back(subsubresult_error);

            // save data precision error
            auto subsubresult_precision = IRA.evaluation.IR_precisionError_sum * IRA.evaluation.milliseconds;
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

vector<vector<vector<long double>>> mpe::evaluateConvergence_2D(bool output) const {

    vector<vector<vector<long double>>> result;
    vector<vector<long double>> result_iterations;
    vector<vector<long double>> result_time;

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
        mps expected_precision(this->parameters.ep_mantissa_length, this->parameters.ep_exponent_length, (double) this->parameters.expected_precision);
        IRA.setExpectedPrecision(expected_precision);
    } else {
        throw std::invalid_argument("ERROR: in evaluateConvergence_2D: neither expected error or precision set");
    }

    // loop over all different mantissa sizes of u_r
    for(unsigned long ur_mantissa_size = this->parameters.ur_m_r_upper; ur_mantissa_size >= this->parameters.ur_m_r_lower; ur_mantissa_size--){

        if(output){
            cout << "\t ur_mantissa_size: " << ur_mantissa_size;
        }

        std::vector<long double> subresult_iterations;
        std::vector<long double> subresult_time;
        IRA.setUpperPrecisionMantissa(ur_mantissa_size);

        // convert the system into the new precision
        IRA.castSystemMatrix(ur_mantissa_size, this->parameters.u_e_l);
        IRA.castExpectedResult(ur_mantissa_size, this->parameters.u_e_l);

        if(this->controllers.expected_error_set){
            IRA.castExpectedError(ur_mantissa_size, this->parameters.u_e_l);
        }

        ira::cast(b, ur_mantissa_size, this->parameters.u_e_l);

        // loop over all different mantissa sizes of u_l
        for(unsigned long ul_mantissa_size = this->parameters.ul_m_r_lower; ul_mantissa_size <= this->parameters.ul_m_r_upper; ul_mantissa_size++){

            // perform iterative refinement algorithm
            IRA.setLowerPrecisionMantissa(ul_mantissa_size);
            IRA.irPLU(b);

            // save data iterations
            auto subsubresult_iterations = (double) IRA.evaluation.iterations_needed;
            subresult_iterations.push_back(subsubresult_iterations);

            // save data time
            auto subsubresult_time = IRA.evaluation.milliseconds;
            subresult_time.push_back(subsubresult_time);
        }

        result_iterations.insert(result_iterations.begin(), subresult_iterations);
        result_time.insert(result_time.begin(), subresult_time);

        if(output){
            cout << "\tdone\t\tlast: " << this->parameters.ur_m_r_lower << endl;
        }
    }

    // acquire GIL
    pybind11::gil_scoped_acquire acquire;

    result.push_back(result_iterations);
    result.push_back(result_time);

    return result;
}
//-------------------------------


