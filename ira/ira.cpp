//
// Created by Jakob on 28.02.24.
// ira => Iterative Refinement Algorithm
//

#include "ira.h"
#include <iostream>
#include <random>

using namespace std;

// constructor and destructor
//-------------------------------
/**
 * Constructor for an "iterative refinement algorithm" object (ira).
 *
 * The vector for the system matrix and the vectors for the matrices L, U, and P are initialized using resize,
 * but are not set to any meaningful value.
 *
 * @param n the size of the system matrix.
 */
ira::ira(unsigned long n, unsigned long ur_mantissa_length, unsigned long ur_exponent_length){

    if (ur_mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in ira Constructor : mantissa size too small");
    }
    if (ur_exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in ira Constructor : exponent size too small");
    }


    setDimension(n);

    // set up parameters
    //-------------------------------
    this->parameters.random_lower_bound = -10;
    this->parameters.random_upper_bound = 10;
    this->parameters.sparsity_rate = 0;

    this->parameters.max_iter = 10;     // Must be 10 because of unit tests.

    this->parameters.ur_m_l = ur_mantissa_length;
    this->parameters.ur_e_l = ur_exponent_length;

    this->parameters.working_precision_set = false;         // after construction no working precision is set.
    this->parameters.expected_result_present = false;       // after construction no result vector is present.
    this->parameters.expected_error_present = false;    // after construction no expected precision is present.


    // set up evaluation struct
    //-------------------------------
    this->evaluation.IR_relativeErrors.resize(0);
    this->evaluation.IR_relativeError_sum = 0.0;
    this->evaluation.milliseconds = 0;

    this->evaluation.iterations_needed = 0;

    this->evaluation.IR_precisionErrors.resize(0);
    this->evaluation.IR_precisionError_sum = 0;
}

/**
 * Default destructor.
 */
ira::~ira() = default;
//-------------------------------


// parameter setters and getters
//-------------------------------
/**
 * Sets the lower and upper bound for random value generators.
 *
 * Throws Exception:    When lower bound >= upper bound.
 *
 * @param lower_bound the lower bound for the random number generator.
 * @param upper_bound the upper bound for the random number generator.
 */
void ira::setRandomRange(double lower_bound, double upper_bound){

    if(lower_bound >= upper_bound){
        throw std::invalid_argument("ERROR: setRandomRange: upper bound smaller/equal than/to lower bound ");
    }

    this->parameters.random_lower_bound = lower_bound;
    this->parameters.random_upper_bound = upper_bound;
}

/**
 * Sets the sparsity rate which is the amount of zeros in the system matrix in percent.
 *
 * Throws Exception:    When the new sparsity rate is lower than 0 or
 *                      When the new sparsity rate is greater than 1
 *
 * @param new_sparsity_rate the new sparsity rate
 */
void ira::setSparsityRate(double new_sparsity_rate) {

    // TODO: check
    if(new_sparsity_rate < 0 || new_sparsity_rate > (1 - (1/(double) this->parameters.n))){
        throw std::invalid_argument("ERROR: setSparsityRate: sparsity rate must be between 0 and 0.9 ");
    }

    this->parameters.sparsity_rate = new_sparsity_rate;
}

/**
 * Sets the maximal iteration.
 *
 * @param max_iter the new maximal iteration.
 */
void ira::setMaxIter(unsigned long new_max_iter){

    this->parameters.max_iter = new_max_iter;
}

/**
 * Sets the dimension of the system.
 *
 * @param new_dimension the new dimension of the system.
 */
void ira::setDimension(unsigned long new_dimension){

    this->parameters.n = new_dimension;
    this->parameters.matrix_1D_size = new_dimension * new_dimension;
}

/**
 * Sets the size of the mantissa and exponent of the lower precision (ul)
 *
 * Throws Exception:    When the mantissa is smaller than 1.
 *                      When the exponent is smaller than 2.
 *
 * @param mantissa_length the new mantissa size
 * @param exponent_length the new exponent size
 */
void ira::setLowerPrecision(unsigned long mantissa_length, unsigned long exponent_length){

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in setLowerPrecision : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in setLowerPrecision : exponent size too small");
    }

    this->parameters.ul_m_l = mantissa_length;
    this->parameters.ul_e_l = exponent_length;
}

/**
 * Sets the size of the mantissa of the lower precision (ul)
 *
 * Throws Exception:    When the mantissa is smaller than 1.
 *
 * @param mantissa_length the new mantissa size.
 */
void ira::setLowerPrecisionMantissa(unsigned long mantissa_length){

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in setLowerPrecisionMantissa : mantissa size too small");
    }

    this->parameters.ul_m_l = mantissa_length;
}

/**
 * Sets the size of the exponent of the lower precision (ul).
 *
 * Throws Exception:    When the exponent is smaller than 2.
 *
 * @param exponent_length the new exponent size
 */
void ira::setLowerPrecisionExponent(unsigned long exponent_length){

    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in setLowerPrecisionExponent : exponent size too small");
    }

    this->parameters.ul_e_l = exponent_length;
}

/**
 * Sets the size of the mantissa and exponent of the working precision (u)
 *
 * Throws Exception:    When the mantissa is smaller than 1.
 *                      When the exponent is smaller than 2.
 *
 * @param mantissa_length the new mantissa size.
 * @param exponent_length the new exponent size. .
 */
void ira::setWorkingPrecision(unsigned long mantissa_length, unsigned long exponent_length){

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in setWorkingPrecision : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in setWorkingPrecision : exponent size too small");
    }

    this->parameters.working_precision_set = true;
    this->parameters.u_m_l = mantissa_length;
    this->parameters.u_e_l = exponent_length;
}

/**
 * Sets the size of the mantissa of the working precision (u)
 *
 * Throws Exception:    When the mantissa is smaller than 1.
 *
 * @param mantissa_length the new mantissa size
 */
void ira::setWorkingPrecisionMantissa(unsigned long mantissa_length){

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in setWorkingPrecisionMantissa : mantissa size too small");
    }

    this->parameters.u_m_l = mantissa_length;
}

/**
 * Sets the size of the exponent of the working precision (u)
 *
 * Throws Exception:    When the exponent is smaller than 2.
 *
 * @param exponent_length the new exponent size
 */
void ira::setWorkingPrecisionExponent(unsigned long exponent_length){

    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in setWorkingPrecisionExponent : exponent size too small");
    }

    this->parameters.u_e_l = exponent_length;
}

/**
 * Sets the size of the mantissa and exponent of the upper precision (ur).
 *
 * Throws Exception:    When the mantissa is smaller than 1.
 *                      When the exponent is smaller than 2.
 *
 * @param mantissa_length the new mantissa size.
 * @param exponent_length the new exponent size. .
 */
void ira::setUpperPrecision(unsigned long mantissa_length, unsigned long exponent_length){

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in setUpperPrecision : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in setUpperPrecision : exponent size too small");
    }

    this->parameters.ur_m_l = mantissa_length;
    this->parameters.ur_e_l = exponent_length;
}

/**
 * Sets the size of the mantissa of the upper precision (ur).
 *
 * Throws Exception:    When the mantissa is smaller than 1.
 *
 * @param mantissa_length the new mantissa size
 */
void ira::setUpperPrecisionMantissa(unsigned long mantissa_length){

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in setUpperPrecisionMantissa : mantissa size too small");
    }

    this->parameters.ur_m_l = mantissa_length;
}

/**
 * Sets the size of the exponent of the upper precision (ur).
 *
 * Throws Exception:    When the exponent is smaller than 2.
 *
 * @param exponent_length the new exponent size
 */
void ira::setUpperPrecisionExponent(unsigned long exponent_length){

    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in setUpperPrecisionExponent : exponent size too small");
    }

    this->parameters.ur_e_l = exponent_length;
}

/**
 * Sets the expected result of the linear system x. (Ax=b)
 * The expected x vector is casted to working precision before being saved in ur.
 * Its also additionally converts the vector to a double vector and saves it separately.
 *
 * Throws Exception:    When the vector is empty.
 *                      When the dimensions do not match.
 *
 * @param new_expected_result
 */
void ira::setExpectedResult(const vector<mps>& new_expected_result){

    if (new_expected_result.empty()) {
        throw std::invalid_argument("ERROR: in setExpectedResult : input vector is empty");
    }
    if (new_expected_result.size() != this->parameters.n) {
        throw std::invalid_argument("ERROR: in setExpectedResult : dimensions do not match");
    }
    if(not this->parameters.working_precision_set){
        throw std::invalid_argument("ERROR: in setExpectedResult : working precision must be set beforehand.");
    }

    this->parameters.expected_result_present = true;

    this->parameters.expected_result_mps.clear();
    for(const auto & idx : new_expected_result){
        this->parameters.expected_result_mps.emplace_back(idx);
    }

    castExpectedResult(this->parameters.u_m_l, this->parameters.u_e_l);
    castExpectedResult(this->parameters.ur_m_l, this->parameters.ur_e_l);
    this->parameters.expected_result_double = ira::mps_to_double(this->parameters.expected_result_mps);
}

/**
 * Sets the expected error which is maximal distance between the expected result and the actual result.
 * If the Floating Point Format does not match with the set upper precision it will be converted accordingly.
 *
 * Throws Exception:    When no expected result was set beforehand.
 *
 * @param new_expected_error the expected result.
 */
void ira::setExpectedError(const mps& new_expected_error){

    if(not this->parameters.expected_result_present){
        throw std::invalid_argument("ERROR: in setExpectedError: expected result must be set before expected error!");
    }

    this->parameters.expected_error_present = true;

    this->parameters.expected_error |= new_expected_error;
    this->parameters.expected_error.cast(this->parameters.ur_m_l, this->parameters.ur_e_l);
}

/**
 * Sets the expected precision which is the number of mantissa bits expected to match.
 *
 * Throws Exception:    When no expected result was set beforehand.
 *
 * @param new_expected_precision the new expected precision.
 */
void ira::setExpectedPrecision(const mps& new_expected_precision){

    if(not this->parameters.expected_result_present){
        throw std::invalid_argument("ERROR: in setExpectedPrecision: expected result must be set before expected precision!");
    }

    this->parameters.expected_precision_present = true;


    this->parameters.ep_mantissa_length = new_expected_precision.getMantisseLength();
    this->parameters.ep_exponent_length = new_expected_precision.getExponentLength();

    this->parameters.expected_precision |= new_expected_precision;
}


/**
 * Gets the lower and upper bound for random value generators inside a n=2 vector.
 * The first entry is the lower bound and the second the upper bound.
 *
 * @return vector containing lower and upper bound.
 */
vector<double> ira::getRandomRange() const{

    vector<double> ret;

    ret.push_back(this->parameters.random_lower_bound);
    ret.push_back(this->parameters.random_upper_bound);

    return ret;
}


/**
 * Gets the sparsity rate which is the amount of zeros in the system matrix in percent.
 *
 * @return the sparsity rate
 */
double ira::getSparsityRate() const {

    return this->parameters.sparsity_rate;
}

/**
 * Gets the maximal iteration.
 *
 * @return the maximal iteration
 */
unsigned long ira::getMaxIter() const {

    return this->parameters.max_iter;
}

/**
 * Gets the dimension of the system.
 *
 * @return the dimension of the system
 */
unsigned long ira::getDimension() const {

    return this->parameters.n;
}

/**
 * Gets the number of elements of the system matrix (n*n).
 *
 * @return the number of elements of the system matrix
 */
unsigned long ira::get1DMatrixSize() const {

    return this->parameters.matrix_1D_size;
}

/**
 * Gets the length of the mantissa and exponent of the lower precision (ul) inside a n=2 vector.
 * The first entry is the mantissa length and the second the exponent length.
 *
 * @return vector containing the sizes for mantissa and exponent.
 */
vector<unsigned long> ira::getLowerPrecision() const {

    vector<unsigned long> ret;

    ret.push_back(this->parameters.ul_m_l);
    ret.push_back(this->parameters.ul_e_l);

    return ret;
}

/**
 * Gets the length of the mantissa and exponent of the working precision (u) inside a n=2 vector.
 * The first entry is the mantissa length and the second the exponent length.
 *
 * @return vector containing the sizes for mantissa and exponent.
 */
vector<unsigned long> ira::getWorkingPrecision() const {

    vector<unsigned long> ret;

    ret.push_back(this->parameters.u_m_l);
    ret.push_back(this->parameters.u_e_l);

    return ret;
}

/**
 * Gets the length of the mantissa and exponent of the upper precision (ur) inside a n=2 vector.
 * The first entry is the mantissa length and the second the exponent length.
 *
 * @return vector containing the sizes for mantissa and exponent.
 */
vector<unsigned long> ira::getUpperPrecision() const {

    vector<unsigned long> ret;

    ret.push_back(this->parameters.ur_m_l);
    ret.push_back(this->parameters.ur_e_l);

    return ret;
}

/**
 * Gets the expected result (x) as an vector consisting of mps objects.
 *
 * Throws Exception:    When no expected result was set.
 *
 * @return the expected result as vector<mps>
 */
vector<mps> ira::getExpectedResult_mps() const{

    if (not this->parameters.expected_result_present) {
        throw std::invalid_argument("ERROR: in getExpectedResult_mps : no expected result present");
    }

    vector<mps> ret;
    ret.reserve(this->parameters.expected_result_mps.size());
    for(const auto & element : this->parameters.expected_result_mps){
        ret.push_back(element);
    }

    return ret;
}

/**
 * Gets the expected result (x) as an vector consisting of doubles.
 *
 * Throws Exception:    When no expected result was set.
 *
 * @return the expected result as vector<double>
 */
vector<double> ira::getExpectedResult_double() const{

    if (not this->parameters.expected_result_present) {
        throw std::invalid_argument("ERROR: in getExpectedResult_double : no expected result present");
    }

    vector<double> ret;
    ret.reserve(this->parameters.expected_result_mps.size());
    for(const auto & element : this->parameters.expected_result_mps){
        ret.push_back(element.getValue());
    }

    return ret;
}

/**
 * Gets the expected error as an mps object.
 *
 * Throws Exception:    When no expected error was set.
 *
 * @return the expected error
 */
mps ira::getExpectedError() const{

    if (not this->parameters.expected_error_present) {
        throw std::invalid_argument("ERROR: in getExpectedError : no expected error present");
    }

    mps ret;
    ret |= this->parameters.expected_error;

    return ret;
}

/**
 * Gets the expected precision as an mps object.
 *
 * Throws Exception:    When no expected precision was set.
 *
 * @return the expected precision
 */
mps ira::getExpectedPrecision() const{

    if (not this->parameters.expected_precision_present) {
        throw std::invalid_argument("ERROR: in getExpectedError : no expected precision present");
    }

    mps ret;
    ret |= this->parameters.expected_precision;

    return ret;
}
//-------------------------------


// matrix setters
//-------------------------------
/**
 * Sets the system matrix of the ira object to an identity matrix of a custom size.
 *
 * @param mantissa_length the size of the mantissa of the elements of the matrix
 * @param exponent_length the size of the exponent of the elements of the matrix
 */
void ira::setUnitaryMatrix() {

    mps zero(this->parameters.ur_m_l, this->parameters.ur_e_l, 0);
    mps one(this->parameters.ur_m_l, this->parameters.ur_e_l, 1);

    this->A.resize(this->parameters.n);
    for(unsigned long i = 0; i <  this->parameters.n; i++){
        this->A[i].resize(this->parameters.n);
        for(unsigned long j = 0; j < this->parameters.n; j++){
            if(i == j){
                this->A[i][j] |= one;
            } else {
                this->A[i][j] |= zero;
            }
        }
    }
}

/**
 * Sets the system matrix of the ira object to an arbitrary matrix.
 *
 * @param mantissa_length the size of the mantissa of the elements of the matrix
 * @param exponent_length the size of the exponent of the elements of the matrix
 * @param new_matrix the new matrix to which the system matrix should be set.
 */
void ira::setMatrix(vector<double> new_matrix) {

    if (new_matrix.size() > this->parameters.matrix_1D_size) {
        throw std::invalid_argument("ERROR: in setMatrix: new_matrix too large");
    }
    if (new_matrix.size() < this->parameters.matrix_1D_size) {
        throw std::invalid_argument("ERROR: in setMatrix: new_matrix too small");
    }

    this->A.resize(this->parameters.n);
    for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
        this->A[row_idx].resize(this->parameters.n);
        for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){
            this->A[row_idx][col_idx] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, new_matrix[get_idx(row_idx, col_idx)]);
        }
    }
}

/**
 * Sets the system matrix of the ira object to a random generated matrix.
 * All randomly generated variables are between -10 and 10.
 *
 * @param mantissa_length the size of the mantissa of the elements of the matrix
 * @param exponent_length the size of the exponent of the elements of the matrix
 */
void ira::setRandomMatrix(){

    this->A.resize(this->parameters.n);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(this->parameters.random_lower_bound, this->parameters.random_upper_bound);

    if(0 == this->parameters.sparsity_rate) {

        for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
            this->A[row_idx].resize(this->parameters.n);
            for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){
                this->A[row_idx][col_idx] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, dist(mt));
            }
        }

    } else {

        std::random_device sparsity_device;
        std::mt19937 sparsity_mt(rd());
        std::uniform_real_distribution<double> sparsity_dist(0.0, 1.0);

        // generate random vector
        vector<unsigned long> random_vector;
        for(unsigned long idx = 0; idx < this->parameters.n; idx++){
            random_vector.push_back(idx);
        }
        auto random_dev = std::random_device {};
        auto rng = std::default_random_engine {random_dev()};
        std::shuffle(std::begin(random_vector), std::end(random_vector), rng);


        double adapted_sparsity_rate = (this->parameters.sparsity_rate * ((double) this->parameters.n)) / ((double) (this->parameters.n - 1));
        mps zero(this->parameters.ur_m_l, this->parameters.ur_e_l, 0);

        for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
            this->A[row_idx].resize(this->parameters.n);
            for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){

                if(col_idx == random_vector[row_idx]){

                    this->A[row_idx][col_idx] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, dist(mt));
                    while(this->A[row_idx][col_idx].isZero()){
                        this->A[row_idx][col_idx] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, dist(mt));
                    }

                } else if(sparsity_dist(sparsity_mt) < adapted_sparsity_rate){
                    this->A[row_idx][col_idx] |= zero;
                } else {
                    this->A[row_idx][col_idx] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, dist(mt));
                }
            }
        }
    }
}

/**
 * Sets the lower triangular matrix of the ira object to an arbitrary matrix.
 * This should be done with caution since this matrix should actually only be set by performing the PLU decomposition.
 *
 * @param mantissa_length the size of the mantissa of the elements of the matrix
 * @param exponent_length the size of the exponent of the elements of the matrix
 * @param new_L the new matrix to which the lower triangular matrix should be set.
 */
void ira::setL(vector<double> new_L) {

    if (new_L.size() > this->parameters.matrix_1D_size) {
        throw std::invalid_argument("ERROR: in setL: new_L too large");
    }
    if (new_L.size() < this->parameters.matrix_1D_size) {
        throw std::invalid_argument("ERROR: in setL: new_L too small");
    }

    this->L.resize(this->parameters.n);
    for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
        this->L[row_idx].resize(this->parameters.n);
        for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){
            this->L[row_idx][col_idx] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, new_L[get_idx(row_idx, col_idx)]);
        }
    }
}

/**
 * Sets the upper triangular matrix of the ira object to an arbitrary matrix.
 * This should be done with caution since this matrix should actually only be set by performing the PLU decomposition.
 *
 * @param mantissa_length the size of the mantissa of the elements of the matrix
 * @param exponent_length the size of the exponent of the elements of the matrix
 * @param new_U the new matrix to which the upper triangular matrix should be set.
 */
void ira::setU(vector<double> new_U) {

    if (new_U.size() > this->parameters.matrix_1D_size) {
        throw std::invalid_argument("ERROR: in setU: new_U too large");
    }
    if (new_U.size() < this->parameters.matrix_1D_size) {
        throw std::invalid_argument("ERROR: in setU: new_U too small");
    }

    this->U.resize(this->parameters.n);
    for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
        this->U[row_idx].resize(this->parameters.n);
        for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){
            this->U[row_idx][col_idx] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, new_U[get_idx(row_idx, col_idx)]);
        }
    }
}
//-------------------------------


// matrix getter
//-------------------------------
/**
 * Returns one element of the system matrix.
 *
 * @param idx the index of the element in the array.
 * @return the element at the index.
 */
mps ira::getMatrixElement(unsigned long row_idx, unsigned long col_idx){

    if (row_idx >= this->parameters.n) {
        throw std::invalid_argument("ERROR: getMatrixElement: row_idx too large");
    }
    if (col_idx >= this->parameters.n) {
        throw std::invalid_argument("ERROR: getMatrixElement: col_idx too large");
    }

    return this->A[row_idx][col_idx];
}

mps ira::getMatrixElement(unsigned long idx){

    if (idx >= this->parameters.n*this->parameters.n) {
        throw std::invalid_argument("ERROR: getMatrixElement: idx too large");
    }

    return this->A[idx / this->parameters.n][idx % this->parameters.n];
}
//-------------------------------


// toString converters
//-------------------------------
/**
 * Takes one of the matrices of the ira object and converts it into an std::string.
 *
 * A...system matrix
 * L...lower triangular matrix after PLU decomposition
 * U...upper triangular matrix after PLU decomposition
 *
 * @param matrix the letter referencing to the matrix which should be printed.
 * @param precision the precision in which the values should be displayed. (-1 = "normal" precision)
 * @return the matrix in an std::string format
 */
string ira::toString(const char& matrix, const int precision) const {

    std::string ret;

    if('A' == matrix){

        if(this->A.empty() || this->A[0].empty() || (this->A[0][0].getExponentLength() == 0 && this->A[0][0].getMantisseLength() == 0)){
            throw std::invalid_argument("ERROR: toString: A is empty");
        }

        for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
            for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){
                ret.append(this->A[row_idx][col_idx].toString(precision));
                ret.append(", ");
            }
        }

        ret.pop_back();
        ret.pop_back();

    } else if('L' == matrix){

        if(this->L.empty() || this->L[0].empty() || (this->L[0][0].getExponentLength() == 0 && this->L[0][0].getMantisseLength() == 0)){
            throw std::invalid_argument("ERROR: toString: L is empty");
        }

        for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
            for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){
                ret.append(this->L[row_idx][col_idx].toString(precision));
                ret.append(", ");
            }
        }

        ret.pop_back();
        ret.pop_back();

    } else if('U' == matrix) {

        if(this->U.empty() || this->U[0].empty() || (this->U[0][0].getExponentLength() == 0 && this->U[0][0].getMantisseLength() == 0)){
            throw std::invalid_argument("ERROR: toString: U is empty");
        }

        for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
            for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){
                ret.append(this->U[row_idx][col_idx].toString(precision));
                ret.append(", ");
            }
        }

        ret.pop_back();
        ret.pop_back();

    } else if('P' == matrix) {

        if(this->P.empty() || (this->P[0].getExponentLength() == 0 && this->P[0].getMantisseLength() == 0)){
            throw std::invalid_argument("ERROR: toString: P is empty");
        }


        vector<unsigned long> P_int;
        P_int.reserve(P.size());
        for(const auto & i : P){
            P_int.push_back((unsigned long) i.getValue());
        }

        string tmp_zero = "0.";
        string tmp_one = "1.";

        for(int i = 0; i < precision; i++){
            tmp_zero.append("0");
            tmp_one.append("0");
        }

        for(unsigned long i = 0; i < P_int.size(); i++){
            for(unsigned long j = 0; j < P_int.size(); j++){

                if(j == P_int[i]){
                    ret.append(tmp_one);
                } else {
                    ret.append(tmp_zero);
                }

                if(i < P_int.size()-1 || j < P_int.size()-1){
                    ret.append(", ");
                }
            }
        }


    } else {
        throw std::invalid_argument("ERROR: in toString : invalid matrix parameter");
    }

    return ret;
}

/**
 * Takes a vector of mps objects and returns the vector in an std::string format.
 *
 * @param vec the vector consisting of mps objects.
 * @param precision the precision in which the values should be displayed. (-1 = "normal" precision)
 * @return the vector in an std::string format.
 */
string ira::toString(vector<mps> vec, int precision) {

    if (vec.empty()) {
        throw std::invalid_argument("ERROR: toString (vector): a is empty");
    }

    auto ret = vec[0].toString(precision);
    for(unsigned long i = 1; i < vec.size(); i++) {
        ret.append(", ");
        ret.append(vec[i].toString(precision));
    }

    return ret;
}
//-------------------------------


// cast functions
//-------------------------------
/**
 * Given a vector of mps objects this function casts all of its elements to new mantissa and exponent sizes.
 * This works also for the matrices in the ira object since they are internally saved as vectors.
 *
 * @param mantissa_length the new mantissa length of the mps objects
 * @param exponent_length the new exponent length of the mps objects
 * @param vec the vector of mps objects which should be converted
 */
void ira::cast(vector<mps>& vec, unsigned long mantissa_length, unsigned long exponent_length){

    if (vec.empty()) {
        throw std::invalid_argument("ERROR: in cast: vector is empty");
    }
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in cast : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in cast : exponent size too small");
    }


    if(mantissa_length == vec[0].getMantisseLength() && exponent_length == vec[0].getExponentLength()){
        return;
    }

    for(auto & i : vec){
        i.cast(mantissa_length, exponent_length);
    }
}

/**
 * Given a matrix of mps objects this function casts all of its elements to new mantissa and exponent sizes.
 *
 * @param mantissa_length the new mantissa length of the mps objects
 * @param exponent_length the new exponent length of the mps objects
 * @param matrix the matrix of mps objects which should be converted
 */
void ira::cast(vector<vector<mps>>& matrix, unsigned long mantissa_length, unsigned long exponent_length){

    if (matrix.empty()) {
        throw std::invalid_argument("ERROR: in cast: matrix is empty");
    }
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in cast : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in cast : exponent size too small");
    }

    if(mantissa_length == matrix[0][0].getMantisseLength() && exponent_length == matrix[0][0].getExponentLength()){
        return;
    }

    for(unsigned long row_idx = 0; row_idx < matrix.size(); row_idx++){
        for(unsigned long col_idx = 0; col_idx < matrix.size(); col_idx++){
            matrix[row_idx][col_idx].cast(mantissa_length, exponent_length);
        }
    }

}

/**
 * Casts all elements of the system matrix to a new mantissa an exponent length.
 *
 * Throws Exception:    When the system matrix is empty.
 *                      When the mantissa length is too small.
 *                      When the exponent length is too small.
 *
 * @param mantissa_length the new mantissa length of the mps objects
 * @param exponent_length the new exponent length of the mps objects
 */
void ira::castSystemMatrix(unsigned long mantissa_length, unsigned long exponent_length){

    if (this->A.empty()) {
        throw std::invalid_argument("ERROR: in castSystemMatrix: system matrix is empty");
    }
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in castSystemMatrix : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in castSystemMatrix : exponent size too small");
    }

    if(mantissa_length == this->A[0][0].getMantisseLength() && exponent_length == this->A[0][0].getExponentLength()){
        return;
    }

    for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
        for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){
            A[row_idx][col_idx].cast(mantissa_length, exponent_length);
        }
    }

}

/**
 * Casts all elements of the expected result to a new mantissa an exponent length.
 *
 * Throws Exception:    When the expected result is empty.
 *                      When the mantissa length is too small.
 *                      When the exponent length is too small.
 *
 * @param mantissa_length the new mantissa length of the mps objects
 * @param exponent_length the new exponent length of the mps objects
 */
void ira::castExpectedResult(unsigned long mantissa_length, unsigned long exponent_length){

    if (this->parameters.expected_result_mps.empty()) {
        throw std::invalid_argument("ERROR: in castExpectedResult: expected result is empty");
    }
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in castExpectedResult : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in castExpectedResult : exponent size too small");
    }

    if(mantissa_length == this->parameters.expected_result_mps[0].getMantisseLength() && exponent_length == this->parameters.expected_result_mps[0].getExponentLength()){
        return;
    }

    for(auto & element : this->parameters.expected_result_mps){
        element.cast(mantissa_length, exponent_length);
    }
}

/**
 * Casts the expected error to a new mantissa an exponent length.
 *
 * Throws Exception:    When the mantissa length is too small.
 *                      When the exponent length is too small.
 *
 * @param mantissa_length the new mantissa length of the mps object
 * @param exponent_length the new exponent length of the mps object
 */
void ira::castExpectedError(unsigned long mantissa_length, unsigned long exponent_length){

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in castExpectedResult : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in castExpectedResult : exponent size too small");
    }

    this->parameters.expected_error.cast(mantissa_length, exponent_length);
}
//-------------------------------


// array converters
//-------------------------------
/**
 * Given a vector consisting of doubles the function returns a new vector consisting of mps objects.
 * The mantissa and exponent length oft the mps objects can be set
 *
 * Throws Exception:    When the input vector is empty.
 *                      When the mantissa length is too small.
 *                      When the exponent length is too small.
 *
 * @param mantissa_length the new mantissa length of the mps objects
 * @param exponent_length the new exponent length of the mps objects
 * @param double_vector the vector of double objects
 * @return a new vector consisting of mps elements
 */
vector<mps> ira::double_to_mps(unsigned long mantissa_length, unsigned long exponent_length, vector<double> double_vector){

    if (double_vector.empty()) {
        throw std::invalid_argument("ERROR: in double_to_mps: double_vector is empty");
    }
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in double_to_mps : mantissa length too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in double_to_mps : exponent length too small");
    }

    vector<mps> ret(double_vector.size(), mps(mantissa_length, exponent_length));

    for(unsigned long i = 0; i < double_vector.size(); i++){
        ret[i] = double_vector[i];
    }

    return ret;
}

vector<vector<mps>> ira::double_to_mps(unsigned long mantissa_length, unsigned long exponent_length, vector<vector<double>> double_matrix){

    if (double_matrix.empty() || double_matrix[0].empty()) {
        throw std::invalid_argument("ERROR: in double_to_mps: double_vector is empty");
    }
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in double_to_mps : mantissa length too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in double_to_mps : exponent length too small");
    }

    vector<vector<mps>> ret;
    ret.resize(double_matrix.size());
    for(unsigned long row_idx = 0; row_idx < double_matrix.size(); row_idx++){
        ret[row_idx].resize(double_matrix.size());
        for(unsigned long col_idx = 0; col_idx < double_matrix.size(); col_idx++){
            ret[row_idx][col_idx] |= mps(mantissa_length, exponent_length, double_matrix[row_idx][col_idx]);
        }
    }

    return ret;
}

/**
 * Given a vector consisting of mps objects the function returns a new vector consisting of double objects.
 *
 * Throws Exception:    When the input vector is empty.
 *
 * @param mps_vector the vector of mps objects.
 * @return a vector new vector consisting of doubles.
 */
vector<double> ira::mps_to_double(vector<mps> mps_vector){

    if (mps_vector.empty()) {
        throw std::invalid_argument("ERROR: in mps_to_double: mps_vector is empty");
    }

    vector<double> ret(mps_vector.size(), 0.0);

    for(unsigned long i = 0; i < mps_vector.size(); i++){
        ret[i] = mps_vector[i].getValue();
    }

    return ret;
}

/**
 * Given a vector consisting of mps objects the function returns a new vector consisting of float objects.
 *
 * Throws Exception:    When the input vector is empty.
 *
 * @param mps_vector the vector of mps objects.
 * @return a vector new vector consisting of floats.
 */
vector<float> ira::mps_to_float(vector<mps> mps_vector){

    if (mps_vector.empty()) {
        throw std::invalid_argument("ERROR: in mps_to_float: mps_vector is empty");
    }

    vector<float> ret(mps_vector.size(), 0.0);

    for(unsigned long i = 0; i < mps_vector.size(); i++){
        ret[i] = (float) mps_vector[i].getValue();
    }

    return ret;
}
//-------------------------------


// generators
//-------------------------------
/**
 * Generates a random vector consisting of mps objects.
 * The value range can be set by changing the random range parameters.
 *
 * Throws Exception:    When the mantissa length is too small.
 *                      When the exponent length is too small.
 *
 * @param mantissa_length the mantissa length of the mps objects
 * @param exponent_length the exponent length of the mps objects
 * @param size the size of the generated vector
 * @return a randomly created vector consisting of mps objects.
 */
vector<mps> ira::generateRandomVector(unsigned long size, unsigned long mantissa_length, unsigned long exponent_length) const {

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in generateRandomVector : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in generateRandomVector : exponent size too small");
    }

    vector<mps> ret;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(this->parameters.random_lower_bound, this->parameters.random_upper_bound);

    for(unsigned i = 0; i < size; i++){
        ret.emplace_back(mantissa_length, exponent_length, dist(mt));
    }

    return ret;
}

/**
 * Generates a random matrix consisting of mps objects.
 * The value range can be set by changing the random range parameters.
 * The sparsity range can be set by changing the sparsity parameter.
 *
 * Throws Exception:    When the mantissa length is too small.
 *                      When the exponent length is too small.
 *
 * @param mantissa_length the mantissa length of the mps objects
 * @param exponent_length the exponent length of the mps objects
 * @param size the size of the generated vector
 * @return a randomly created vector consisting of mps objects.
 */
vector<vector<mps>> ira::generateRandomMatrix(unsigned long size, unsigned long mantissa_length, unsigned long exponent_length) const {

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in generateRandomMatrix : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in generateRandomMatrix : exponent size too small");
    }

    vector<vector<mps>> ret;
    ret.resize(size);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(this->parameters.random_lower_bound, this->parameters.random_upper_bound);

    if(0 == this->parameters.sparsity_rate){

        for(unsigned long i = 0; i < size; i++){

            ret[i].resize(size);
            for(unsigned long j = 0; j < size; j++){
                ret[i][j] |= mps(mantissa_length, exponent_length, dist(mt));
            }
        }
    } else {

        mps mps_zero(mantissa_length, exponent_length, 0.0);

        std::random_device sparsity_device;
        std::mt19937 sparsity_mt(rd());
        std::uniform_real_distribution<double> sparsity_dist(0.0, 1.0);

        // generate random vector
        vector<unsigned long> random_vector;
        for(unsigned long idx = 0; idx < size; idx++){
            random_vector.push_back(idx);
        }
        auto random_dev = std::random_device {};
        auto rng = std::default_random_engine {random_dev()};
        std::shuffle(std::begin(random_vector), std::end(random_vector), rng);

        // calculate new sparsity rate
        double adapted_sparsity_rate = (this->parameters.sparsity_rate * ((double) size)) / ((double) (size - 1));

        for(unsigned long i = 0; i < size; i++){

            ret[i].resize(size);
            for(unsigned long j = 0; j < size; j++){

                if(j == random_vector[i]){

                    ret[i][j] |= mps(mantissa_length, exponent_length, dist(mt));
                    while(ret[i][j].isZero()){
                        ret[i][j] |= mps(mantissa_length, exponent_length, dist(mt));
                    }

                } else if(sparsity_dist(sparsity_mt) < adapted_sparsity_rate){
                    ret[i][j] |= mps_zero;
                } else {
                    ret[i][j] |= mps(mantissa_length, exponent_length, dist(mt));
                }

            }
        }
    }

    return ret;
}

/**
 * Generates a random rhs for the linear system.
 * Generates the vector x and calculates the vector b (Ax=b). Also sets the expected result.
 *
 * @return the b vector of the system
 */
vector<mps> ira::generateRandomRHS() {

    auto x = generateRandomVector(this->parameters.n, this->parameters.ur_m_l, this->parameters.ur_e_l);
    auto b = multiplyWithSystemMatrix(x);
    setExpectedResult(x);

    return b;
}

/**
 * Generates a complete random linear system.
 * Generates A and x calculates vectors the vector b (Ax=b). Also sets the expected result.
 *
 * @return the b vector of the system
 */
vector<mps> ira::generateRandomLinearSystem() {

    setRandomMatrix();
    return generateRandomRHS();
}
//-------------------------------

// evaluators and norms
//-------------------------------
/**
 * Returns the L1 norm of a vector consisting of mps objects.
 *
 * @param a the vector for which the L1 norm should be calculated
 * @return the L1 norm of the vector
 */
mps ira::calculateNorm_L1(const vector<mps>& a){

    if (a.empty()) {
        throw std::invalid_argument("ERROR: in vectorNorm: a is empty");
    }

    auto ret = a[0];
    ret.setSign(false);

    for(unsigned long i = 1; i < a.size(); i++){

        if(!a[i].isZero()){
            if(a[i].isPositive()){
                ret = ret + a[i];
            } else {
                ret = ret - a[i];
            }
        }
    }

    return ret;
}

/**
 * Returns the mean absolute value of all elements elements of the vector.
 *
 * @param a the vector for which the mean absolute value should be calculated
 * @return the mean absolute value of the vector
 */
mps ira::calculateVectorMean(const vector<mps>& a){

    auto mantissa_length = a[0].getMantisseLength();
    auto exponent_length = a[0].getExponentLength();

    mps sum(mantissa_length, exponent_length, 0.0);
    mps size(mantissa_length, exponent_length, (double) a.size());

    for(const auto& element : a){

        if(element.isPositive()){
            sum = sum + element;
        } else {
            sum = sum - element;
        }
    }

    return sum / size;


}

/**
 * Calculates the precision of each vector element and calculates the mean from them.
 *
 * Throws Exception:    When the is vector is empty.
 *                      When the should vector is empty.
 *                      When no working precision is set.
 *                      When no expected precision is set.
 *
 * @param x the vector for the multiplication
 * @return the resulting vector from the multiplication
 */
mps ira::calculateMeanPrecision(const vector<mps>& is, const vector<mps>& should) const {

    if (is.empty()) {
        throw std::invalid_argument("ERROR: in generateRandomVector : is vector is empty");
    }
    if (should.empty()) {
        throw std::invalid_argument("ERROR: in calculateMeanPrecision : should vector is empty");
    }
    if (not this->parameters.working_precision_set) {
        throw std::invalid_argument("ERROR: in calculateMeanPrecision : working precision must be set beforehand.");
    }
    if (not this->parameters.expected_precision_present) {
        throw std::invalid_argument("ERROR: in calculateMeanPrecision : expected precision must be set beforehand.");
    }

    mps sum(is[0].getMantisseLength(), is[0].getExponentLength(), 0.0);
    mps size(this->parameters.ep_mantissa_length, this->parameters.ep_exponent_length, (double) is.size());

    for(unsigned long idx = 0; idx < is.size(); idx++){

        mps precision(is[0].getMantisseLength(), is[0].getExponentLength(), (double) is[idx].getPrecision(should[idx]));
        sum = sum + precision;

    }

    sum.cast(this->parameters.ep_mantissa_length, this->parameters.ep_exponent_length);
    return sum / size;
}
//-------------------------------

// operators
//-------------------------------
/**
 * Adds two vectors together. The vectors consist of mps objects.
 *
 * @param a the first vector.
 * @param b the second vector.
 * @return the resulting vector after the addition.
 */
vector<mps> ira::add(const vector<mps>& a, const vector<mps>& b) {

    if (a.empty()) {
        throw std::invalid_argument("ERROR: in add: a is empty");
    }
    if (b.empty()) {
        throw std::invalid_argument("ERROR: in add: b is empty");
    }
    if (a.size() != b.size()) {
        throw std::invalid_argument("ERROR: in add: dimensions of a and b do not match");
    }
    if (a[0].getExponentLength() != b[0].getExponentLength()) {
        throw std::invalid_argument("ERROR: in add: exponents do not match");
    }
    if (a[0].getMantisseLength() != b[0].getMantisseLength()) {
        throw std::invalid_argument("ERROR: in add: mantissas do not match");
    }

    vector<mps> result(a.size(), mps(a[0].getMantisseLength(), a[0].getExponentLength(), 0.0));

    for(unsigned long i = 0; i < a.size(); i++){
        result[i] = a[i] + b[i];
    }

    return result;
}

/**
 * Subtracts one vector from another. The vectors consist of mps objects.
 *
 * @param a the first vector from which will be subtracted.
 * @param b the second vector which is the amount to subtract.
 * @return the resulting vector after the subtraction.
 */
vector<mps> ira::subtract(const vector<mps>& a, const vector<mps>& b) {

    if (a.empty()) {
        throw std::invalid_argument("ERROR: in subtract: a is empty");
    }
    if (b.empty()) {
        throw std::invalid_argument("ERROR: in subtract: b is empty");
    }
    if (a.size() != b.size()) {
        throw std::invalid_argument("ERROR: in subtract: dimensions of a and b do not match");
    }
    if (a[0].getExponentLength() != b[0].getExponentLength()) {
        throw std::invalid_argument("ERROR: in subtract: exponents do not match");
    }
    if (a[0].getMantisseLength() != b[0].getMantisseLength()) {
        throw std::invalid_argument("ERROR: in subtract: mantissas do not match");
    }

    vector<mps> result(a.size(), mps(a[0].getMantisseLength(), a[0].getExponentLength(), 0.0));

    for(unsigned long i = 0; i < a.size(); i++){
        result[i] = a[i] - b[i];
    }

    return result;
}

/**
 * Performs a matrix vector product.
 * The elements of the matrix and the vector are mps objects.
 *
 * @param D the matrix for the multiplication
 * @param x the vector for the multiplication
 * @return the resulting vector from the multiplication.
 */

vector<mps> ira::dotProduct(const vector<vector<mps>>& D, const vector<mps>& x) {

    if (D.empty()) {
        throw std::invalid_argument("ERROR: in dotProduct: D is empty");
    }
    if (x.empty()) {
        throw std::invalid_argument("ERROR: in dotProduct: x is empty");
    }
    if (D.size() != x.size()) {
        throw std::invalid_argument("ERROR: in dotProduct: dimensions of D and x do not match");
    }
    if (D[0][0].getExponentLength() != x[0].getExponentLength()) {
        throw std::invalid_argument("ERROR: in dotProduct: exponents do not match");
    }
    if (D[0][0].getMantisseLength() != x[0].getMantisseLength()) {
        throw std::invalid_argument("ERROR: in dotProduct: mantissas do not match");
    }
    vector<mps> y(x.size(), mps(D[0][0].getMantisseLength(), D[0][0].getExponentLength(), 0.0));

    for(unsigned long i = 0; i < x.size(); i++){
        for(unsigned long j = 0; j < x.size(); j++){
            y[i] = y[i] + (x[j] * D[i][j]);
        }
    }

    return y;
}

/**
 * Performs a matrix matrix product.
 * The elements of the matrix and the vector are mps objects.
 *
 * @param A the first matrix for the multiplication
 * @param B the first matrix for the multiplication
 * @return the resulting vector from the multiplication.
 */
vector<vector<mps>> ira::dotProduct(const vector<vector<mps>>& A, const vector<vector<mps>>& B){

    if (A.empty()) {
        throw std::invalid_argument("ERROR: in dotProduct: A is empty");
    }
    if (B.empty()) {
        throw std::invalid_argument("ERROR: in dotProduct: B is empty");
    }
    if (A.size() != B.size()) {
        throw std::invalid_argument("ERROR: in dotProduct: dimensions of A and B do not match");
    }
    if (A[0][0].getExponentLength() != B[0][0].getExponentLength()) {
        throw std::invalid_argument("ERROR: in dotProduct: exponents do not match");
    }
    if (B[0][0].getMantisseLength() != B[0][0].getMantisseLength()) {
        throw std::invalid_argument("ERROR: in dotProduct: mantissas do not match");
    }

    unsigned long mantissa_length = A[0][0].getMantisseLength();
    unsigned long exponent_length = A[0][0].getExponentLength();

    vector<vector<mps>> ret;
    ret.resize(A.size());


    for(unsigned long row_idx = 0; row_idx < A[0].size(); row_idx++){

        ret[row_idx].resize(A.size());
        for(unsigned long col_idx = 0; col_idx < A[0].size(); col_idx++){

            mps sum (mantissa_length, exponent_length, 0.0);
            for(unsigned long idx = 0; idx < A[0].size(); idx++){
                sum = sum + ( A[row_idx][idx] * B[idx][col_idx] );
            }
            ret[row_idx][col_idx] |= sum;
        }
    }

    return ret;
}

/**
 * Performs a matrix vector product. The matrix with which the vector is multiplies is the system matrix.
 *
 * Throws Exception:    When the system matrix is empty.
 *                      When the vector x is empty.
 *                      When the dimensions of the system matrix and the vector x do not match.
 *                      When the exponents of the system matrix and the vector x do not match.
 *                      When the mantissas of the system matrix and the vector x do not match.
 *
 * @param x the vector for the multiplication
 * @return the resulting vector from the multiplication
 */
vector<mps> ira::multiplyWithSystemMatrix(vector<mps> x) const {

    if (this->A.empty()) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: system matrix is empty");
    }
    if (x.empty()) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: x is empty");
    }
    if (this->A.size() != x.size()) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: dimensions of A and x do not match");
    }
    if (this->A[0][0].getExponentLength() != x[0].getExponentLength()) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: exponents do not match");
    }
    if (this->A[0][0].getMantisseLength() != x[0].getMantisseLength()) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: mantissas do not match");
    }

    return dotProduct(this->A, x);
}
//-------------------------------


// algorithms
//-------------------------------
/**
 * Performs a PLU-Decomposition of the form PA = LU.
 * The result is saved into internal variables of the ira object, namely L, U and P.
 *
 * @param mantissa_precision the precision of the mantissa for the PLU-decomposition.
 * @param exponent_precision the precision of the exponent for the PLU-decomposition.
 */
void ira::decompPLU(unsigned long mantissa_precision, unsigned long exponent_precision) {

    if (mantissa_precision <= 0) {
        throw std::invalid_argument("ERROR: in decompPLU : mantissa size too small");
    }
    if (mantissa_precision <= 1) {
        throw std::invalid_argument("ERROR: in decompPLU : exponent size too small");
    }

    // set up L
    //-------------------------------
    mps mps_zero(mantissa_precision, exponent_precision, 0);
    mps mps_one(mantissa_precision, exponent_precision, 1);

    this->L.resize(this->parameters.n);
    for(unsigned long row_idx = 0; row_idx <  this->parameters.n; row_idx++){
        this->L[row_idx].resize(this->parameters.n);
        for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){

            if(row_idx == col_idx){
                this->L[row_idx][col_idx] |= mps_one;
            } else {
                this->L[row_idx][col_idx] |= mps_zero;
            }
        }
    }
    //-------------------------------

    // set up P
    //-------------------------------
    this->P.resize(this->parameters.n);
    for(unsigned long i = 0; i < this->parameters.n; i++){
        P[i] |= mps(mantissa_precision, exponent_precision, (double) i);
    }
    //-------------------------------


    // set up U
    //-------------------------------
    this->U.resize(this->parameters.n);
    for(unsigned long row_idx = 0; row_idx < this->parameters.n; row_idx++){
        this->U[row_idx].resize(this->parameters.n);
        for(unsigned long col_idx = 0; col_idx < this->parameters.n; col_idx++){

            this->U[row_idx][col_idx] |= A[row_idx][col_idx];
            this->U[row_idx][col_idx].cast(mantissa_precision, exponent_precision);
        }
    }
    //-------------------------------


    // algorithm
    //-------------------------------
    for(unsigned long k = 0; k < this->parameters.n; k++){
        // cout << "iteration: " << k << "/" << this->n << endl;

        auto max_row = get_max_U_idx(k, k);

        interchangeRow(this->U, k, max_row, k, this->parameters.n);
        interchangeRow(this->L, k, max_row, 0, k);

        auto tmp = P[k]; P[k] = P[max_row]; P[max_row] = tmp;

        for(unsigned long j = k+1; j < this->parameters.n; j++){

            //idx = get_idx(j, k);
            this->L[j][k] = this->U[j][k] / this->U[k][k];

            for(unsigned long i = k; i < this->parameters.n; i++){

                this->U[j][i]  = this->U[j][i] - (this->L[j][k] * this->U[k][i]);
            }
        }

    }
    //-------------------------------
}

/**
 * Performs a forward substitution.
 * The values of the needed lower triangular matrix are taken from the internal matrix L of the ira object.
 *
 * @param b the b vector needed for the substitution.
 * @return the resulting x vector.
 */
vector<mps> ira::forwardSubstitution(const vector<mps>& b) const {

    if (this->L.empty()) {
        throw std::invalid_argument("ERROR: in forwardSubstitution: L is empty");
    }
    if (b.empty()) {
        throw std::invalid_argument("ERROR: in forwardSubstitution: b is empty");
    }

    vector<mps> x(b.size(), mps(this->L[0][0].getMantisseLength(), this->L[0][0].getExponentLength()));

    x[0] = b[0]/L[0][0];

    mps tmp_sum(this->L[0][0].getMantisseLength(), this->L[0][0].getExponentLength());

    for(unsigned long i = 1; i < this->parameters.n; i++){

        tmp_sum = 0;
        for(unsigned long j = 0; j < i; j++){
            tmp_sum =  tmp_sum + (L[i][j] * x[j]);
        }

        x[i] = (b[i] - tmp_sum) / L[i][i];
    }

    return x;
}

/**
 * Performs a backward substitution.
 * The values of the needed upper triangular matrix are taken from the internal matrix U of the ira object.
 *
 * @param b the b vector needed for the substitution.
 * @return the resulting x vector.
 */
vector<mps> ira::backwardSubstitution(const vector<mps>& b) const {

    if (this->U.empty()) {
        throw std::invalid_argument("ERROR: in backwardSubstitution: U is empty");
    }
    if (b.empty()) {
        throw std::invalid_argument("ERROR: in backwardSubstitution: b is empty");
    }

    auto n_minus_one = this->parameters.n-1;

    vector<mps> x(b.size(), mps(this->U[0][0].getMantisseLength(), this->U[0][0].getExponentLength()));

    x[n_minus_one] = b[n_minus_one]/U[n_minus_one][n_minus_one];

    mps tmp_sum(this->U[0][0].getMantisseLength(), this->U[0][0].getExponentLength());

    for(unsigned long i = n_minus_one; i > 0;){

        i--;

        tmp_sum = 0;
        for(unsigned long j = n_minus_one; j > i; j--){

            tmp_sum =  tmp_sum + (U[i][j] * x[j]);
        }

        x[i] = (b[i] - tmp_sum) / U[i][i];
    }

    return x;
}

/**
 * Solves a system of equation using a PLU-Factorisation.
 * The system matrix needs not to be a parameter since it must set beforehand.
 * The precision in which the system is solved is the upper precision (ur).
 *
 * Throws Exception:    When b is empty.
 *
 * @param b the solution vector of the system.
 * @return the solution of the system as an mps object.
 */
vector<mps> ira::directPLU(const vector<mps>& b){

    if (b.empty()) {
        throw std::invalid_argument("ERROR: in directPLU: b is empty");
    }

    this->decompPLU(this->parameters.ur_m_l, this->parameters.ur_e_l);
    auto tmp_b = b;
    ira::cast(tmp_b, this->parameters.ur_m_l, this->parameters.ur_e_l);



    auto x = ira::permuteVector(this->P, tmp_b);
    x = this->forwardSubstitution(x);
    x = this->backwardSubstitution(x);

    return x;
}

/**
 * Solves a system of equation using a iterative refinement with LU-decomposition.
 * The system matrix needs not to be a parameter since it must set beforehand.
 *
 * @param b the solution vector of the system. Needs to be same precision as A
 * @param u the precision in which the system should be solved.
 * @param ul the precision in which the LU-decomposition should be performed.
 * @return the approximate solution of the system as an mps object.
 */
vector<mps> ira::irPLU(const vector<mps> &b) {

    // set evaluation parameters to zero
    //-------------------------------
    if(this->parameters.expected_result_present) {
        this->evaluation.IR_relativeErrors.clear();
        this->evaluation.IR_relativeError_sum = 0;

        this->evaluation.IR_precisionErrors.clear();
        this->evaluation.IR_precisionError_sum = 0;
    }
    //-------------------------------

    // set precisions (for easier naming)
    //-------------------------------
    vector<unsigned long> ur{this->parameters.ur_m_l, this->parameters.ur_e_l};
    vector<unsigned long> u{this->parameters.u_m_l, this->parameters.u_e_l};
    vector<unsigned long> ul{this->parameters.ul_m_l, this->parameters.ul_e_l};
    //-------------------------------

    // start timer
    //-------------------------------
    const auto start = std::chrono::high_resolution_clock::now();
    //-------------------------------

    // perform PLU decomposition
    //-------------------------------
    this->decompPLU(ul[0], ul[1]);
    //-------------------------------

    // perform substitution to gain x_0
    //-------------------------------
    auto tmp_b = b;
    ira::cast(tmp_b, ul[0], ul[1]);
    auto x = ira::permuteVector(this->P, tmp_b);

    x = this->forwardSubstitution(x);
    x = this->backwardSubstitution(x);
    ira::cast(x, u[0], u[1]);
    //-------------------------------


    for(unsigned long i = 0; i < this->parameters.max_iter; i++){

        // calculate: r_i = b − A * x_i
        // in precision: ur
        //-------------------------------
        auto x_in_ur = x;
        ira::cast(x_in_ur, ur[0], ur[1]);
        auto b_approx = ira::dotProduct(this->A, x_in_ur);
        auto r = subtract(b, b_approx);
        //-------------------------------

        // check convergence (precision)
        //-------------------------------
        if(this->parameters.expected_precision_present){
            auto mean_precision = ira::calculateMeanPrecision(b_approx, b);
            //cout << "iteration " << i << ":   " << mean_precision << endl;
            if(mean_precision >= this->parameters.expected_precision){
                this->evaluation.iterations_needed = i+1;
                break;
            } else if(i == this->parameters.max_iter-1){
                this->evaluation.iterations_needed = this->parameters.max_iter;
            }
        }
        //-------------------------------

        // check convergence (error)
        //-------------------------------
        if(this->parameters.expected_error_present){
            //auto norm = calculateNorm_L1(r);
            auto norm = calculateVectorMean(r);
            if(norm <= this->parameters.expected_error){
                this->evaluation.iterations_needed = i+1;
                break;
            } else if(i == this->parameters.max_iter-1){
                this->evaluation.iterations_needed = this->parameters.max_iter;
            }
        }
        //-------------------------------


        // solve: A * d_i = r_i
        // in precision: ul
        //-------------------------------
        ira::cast(r, ul[0], ul[1]);
        r = ira::permuteVector(this->P, r);
        auto d = this->forwardSubstitution(r);
        d = this->backwardSubstitution(d);
        //-------------------------------


        // calculate: x_i+1 = x_i + d_i i
        // n precision u.
        //-------------------------------
        ira::cast(d, u[0], u[1]);
        x = add(x, d);
        //-------------------------------


        // evaluation
        //-------------------------------
        if(this->parameters.expected_result_present) {

            // evaluate using relative error
            //-------------------------------
            long double sum = 0.0;
            for (unsigned long element_id = 0; element_id < this->parameters.n; element_id++) {
                sum += x[element_id].getRelativeError_double(this->parameters.expected_result_double[element_id]);
            }
            sum /= (long double) this->parameters.n;
            this->evaluation.IR_relativeErrors.push_back(sum);
            this->evaluation.IR_relativeError_sum += sum;
            //-------------------------------

            // evaluate using precision
            //-------------------------------
            sum = 0.0;
            for (unsigned long idx = 0; idx < this->parameters.n; idx++) {
                auto precision = (long double) x_in_ur[idx].getPrecision(this->parameters.expected_result_mps[idx]);
                if(precision < (long double) parameters.u_m_l){
                    sum += precision;
                } else {
                    sum += (long double) parameters.u_m_l;
                }
            }
            sum /= (long double) this->parameters.n;

            sum = (long double) this->parameters.u_m_l - sum;
            this->evaluation.IR_precisionErrors.push_back(sum);
            this->evaluation.IR_precisionError_sum += sum;
            //-------------------------------

            // evaluate using absolute error
            //-------------------------------
            sum = 0.0;
            for (unsigned long element_id = 0; element_id < this->parameters.n; element_id++) {
                sum += x[element_id].getAbsoluteError_double(this->parameters.expected_result_double[element_id]);
            }
            sum /= (long double) this->parameters.n;
            this->evaluation.IR_absoluteError_sum += sum;
            //-------------------------------

        }
        //-------------------------------


    }

    const auto finish = std::chrono::high_resolution_clock::now();

    auto result_in_microseconds = (std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count());
    this->evaluation.milliseconds = ((long double) result_in_microseconds) / 1000;

    return x;
}

vector<mps> ira::irPLU_2(const vector<mps> &b) {

    // set evaluation parameters to zero
    //-------------------------------
    if(this->parameters.expected_result_present) {
        this->evaluation.IR_relativeErrors.clear();
        this->evaluation.IR_relativeError_sum = 0;

        this->evaluation.sum_milliseconds_ul = 0.0;
        this->evaluation.sum_milliseconds_u = 0.0;
        this->evaluation.sum_milliseconds_ur = 0.0;
    }
    //-------------------------------

    // set precisions (for easier naming)
    //-------------------------------
    vector<unsigned long> ur{this->parameters.ur_m_l, this->parameters.ur_e_l};
    vector<unsigned long> u{this->parameters.u_m_l, this->parameters.u_e_l};
    vector<unsigned long> ul{this->parameters.ul_m_l, this->parameters.ul_e_l};
    //-------------------------------

    // start timer
    //-------------------------------
    const auto start = std::chrono::high_resolution_clock::now();
    //-------------------------------

    // perform PLU decomposition
    //-------------------------------
    const auto a1 = std::chrono::high_resolution_clock::now();
    this->decompPLU(ul[0], ul[1]);
    //-------------------------------

    // perform substitution to gain x_0
    //-------------------------------
    auto tmp_b = b;
    ira::cast(tmp_b, ul[0], ul[1]);
    auto x = ira::permuteVector(this->P, tmp_b);

    x = this->forwardSubstitution(x);
    x = this->backwardSubstitution(x);
    ira::cast(x, u[0], u[1]);
    const auto a2 = std::chrono::high_resolution_clock::now();
    this->evaluation.sum_milliseconds_ul += (long double) std::chrono::duration_cast<std::chrono::nanoseconds>(a2 - a1).count();
    //-------------------------------


    for(unsigned long i = 0; i < this->parameters.max_iter; i++){

        // calculate: r_i = b − A * x_i
        // in precision: ur
        //-------------------------------
        const auto b1 = std::chrono::high_resolution_clock::now();
        auto x_in_ur = x;
        ira::cast(x_in_ur, ur[0], ur[1]);
        auto b_approx = ira::dotProduct(this->A, x_in_ur);
        auto r = subtract(b, b_approx);
        const auto b2 = std::chrono::high_resolution_clock::now();
        this->evaluation.sum_milliseconds_ur += (long double) std::chrono::duration_cast<std::chrono::nanoseconds>(b2 - b1).count();
        //-------------------------------


        // solve: A * d_i = r_i
        // in precision: ul
        //-------------------------------
        const auto c1 = std::chrono::high_resolution_clock::now();
        ira::cast(r, ul[0], ul[1]);
        r = ira::permuteVector(this->P, r);
        auto d = this->forwardSubstitution(r);
        d = this->backwardSubstitution(d);
        const auto c2 = std::chrono::high_resolution_clock::now();
        this->evaluation.sum_milliseconds_ul += (long double) std::chrono::duration_cast<std::chrono::nanoseconds>(c2 - c1).count();
        //-------------------------------


        // calculate: x_i+1 = x_i + d_i i
        // n precision u.
        //-------------------------------
        const auto d1 = std::chrono::high_resolution_clock::now();
        ira::cast(d, u[0], u[1]);
        x = add(x, d);
        const auto d2 = std::chrono::high_resolution_clock::now();
        this->evaluation.sum_milliseconds_u += (long double) std::chrono::duration_cast<std::chrono::nanoseconds>(d2 - d1).count();
        //-------------------------------


        // evaluation
        //-------------------------------
        if(this->parameters.expected_result_present) {

            // evaluate using relative error
            //-------------------------------
            long double sum = 0.0;
            for (unsigned long element_id = 0; element_id < this->parameters.n; element_id++) {
                sum += x[element_id].getRelativeError_double(this->parameters.expected_result_double[element_id]);
            }
            sum /= (long double) this->parameters.n;
            this->evaluation.IR_relativeErrors.push_back(sum);
            this->evaluation.IR_relativeError_sum += sum;
            //------------------------------

        }
        //-------------------------------


    }

    const auto finish = std::chrono::high_resolution_clock::now();

    auto result_in_microseconds = (std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count());
    this->evaluation.milliseconds = ((long double) result_in_microseconds) / 1000;

    this->evaluation.sum_milliseconds_ul /= 1000000;
    this->evaluation.sum_milliseconds_u /= 1000000;
    this->evaluation.sum_milliseconds_ur /= 1000000;

    return x;
}
//-------------------------------


// algorithms using double data types
//-------------------------------
/**
 * Solves a system of equation using a PLU-Factorisation and "normal" double variables.
 * The system matrix needs not to be a parameter since it must set beforehand.
 *
 * @param b the solution vector of the system.
 * @return the solution of the system.
 */
vector<double> ira::solveLU_double(const vector<double>& b){

    // operators   (to avoid subnormal numbers)
    //-------------------------------
    auto add = [](double a, double b) {

        auto result = a + b;

        if(abs(result) < std::numeric_limits<double>::min()){
            return 0.0;
        } else {
            return result;
        }
    };

    auto sub = [](double a, double b) {

        auto result = a - b;

        if(abs(result) < std::numeric_limits<double>::min()){
            return 0.0;
        } else {
            return result;
        }
    };

    auto mul = [](double a, double b) {

        auto result = a * b;

        if(abs(result) < std::numeric_limits<double>::min()){
            return 0.0;
        } else {
            return result;
        }
    };

    auto div = [](double a, double b) {

        auto result = a / b;

        if(abs(result) < std::numeric_limits<double>::min()){
            return 0.0;
        } else {
            return result;
        }
    };
    //-------------------------------

    // functions
    //-------------------------------
    auto interchange = [](vector<vector<double>>* matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end) {
        for(auto i = start; i < end; i++){
            auto tmp = (*matrix)[row_one][i];
            (*matrix)[row_one][i] = (*matrix)[row_two][i];
            (*matrix)[row_two][i] = tmp;
        }
    };

    auto get_max_U = [](const vector<vector<double>>& UU, unsigned long nn, unsigned long column, unsigned long start) {

        unsigned long max_row = start;
        double value = UU[start][column];

        for(unsigned long i = start; i < nn; i++){

            if(abs(UU[i][column]) > value){
                max_row = i;
                value = abs(UU[i][column]);
            }
        }

        return max_row;
    };
    //-------------------------------


    // set up L and P
    //-------------------------------
    vector<vector<double>> L_;
    vector<vector<double>> P_;

    for(unsigned long i = 0; i <  this->parameters.n; i++){

        vector<double> row;

        for(unsigned long j = 0; j < this->parameters.n; j++){

            if(i == j){
                row.push_back(1);
            } else {
                row.push_back(0);
            }
        }

        L_.push_back(row);
        P_.push_back(row);
    }
    //-------------------------------

    // set up U
    //-------------------------------
    vector<vector<double>> U_;

    for(unsigned long i = 0; i <  this->parameters.n; i++){

        vector<double> row;

        for(unsigned long j = 0; j < this->parameters.n; j++){

            row.push_back(this->A[i][j].getValue());
        }

        U_.push_back(row);
    }
    //-------------------------------


    // PLU decomposition algorithm
    //-------------------------------
    for(unsigned long k = 0; k < this->parameters.n; k++){

        auto max_row = get_max_U(U_, this->parameters.n, k, k);

        interchange(&U_, k, max_row, k, this->parameters.n);
        interchange(&L_, k, max_row, 0, k);
        interchange(&P_, k, max_row, 0, this->parameters.n);

        for(unsigned long j = k+1; j < this->parameters.n; j++){

            L_[j][k] = div(U_[j][k], U_[k][k]);

            for(unsigned long i = k; i < this->parameters.n; i++){
                U_[j][i]  = sub(U_[j][i], mul(L_[j][k], U_[k][i]));
            }
        }

    }
    //-------------------------------


    // matrix multiplication
    //-------------------------------
    vector<double> permut_b(b.size(), 0);

    for(unsigned long i = 0; i < permut_b.size(); i++){
        for(unsigned long j = 0; j < permut_b.size(); j++){
            permut_b[i] = add(permut_b[i], mul(b[j], P_[i][j]));
        }
    }
    //-------------------------------


    // forward substitution algorithm
    //-------------------------------
    vector<double> xf;

    xf.push_back(div(permut_b[0], L_[0][0]));
    for(unsigned long i = 1; i < this->parameters.n; i++){

        double tmp_sum = 0;
        for(unsigned long j = 0; j < i; j++){
            tmp_sum =  add(tmp_sum, mul(L_[i][j], xf[j]));
        }

        xf.push_back(div(sub(permut_b[i], tmp_sum), L_[i][i]));
    }
    //-------------------------------

    // backward substitution algorithm
    //-------------------------------
    vector<double> xb(xf.size(), 0);

    xb[this->parameters.n-1] = div(xf[this->parameters.n-1], U_[this->parameters.n-1][this->parameters.n-1]);
    for(unsigned long i = this->parameters.n-1; i > 0;){

        i--;

        double tmp_sum = 0;
        for(unsigned long j = this->parameters.n-1; j > i; j--){

            tmp_sum =  add(tmp_sum, mul(U_[i][j], xb[j]));
        }

        xb[i] = div(sub(xf[i], tmp_sum), U_[i][i]);
    }
    //-------------------------------

    return xb;
}
//-------------------------------


// helper functions
//-------------------------------
/**
 * Since the matrices are saved as a vector this function converts 2D-coordinates of the matrix to the 1D-index
 * used for the vector.
 *
 * The needed variable n is taken from the ira object.
 *
 * @param row the row index of the element of the matrix
 * @param column the column index of the element of the matrix
 * @return the resulting 1D-index.
 */
unsigned long ira::get_idx(unsigned long row, unsigned long column) const{
    return this->parameters.n * row + column;
}

/**
 * This function searches for the maximal element (abs) of the matrix U for a given column and returns its row index.
 * It can start at an arbitrary row index and thereby ignoring all values previous to this index.
 *
 * It returns the index of the element represented as a 1D-index usable for a matrix saved inside a vector.
 *
 * @param column the column in which the max element should be determined.
 * @param start the index of the starting column.
 * @return the 1D-index of the largest element.
 */
unsigned long ira::get_max_U_idx(unsigned long column, unsigned long start) const {

    unsigned long max_row = start;
    mps value = U[start][column];

    for(unsigned long i = start; i < this->parameters.n; i++){

        if(U[i][column].isPositive()){
            value.setSign(false);
            if(U[i][column] > value){
                max_row = i;
                value = U[i][column];
            }
        } else {
            value.setSign(true);
            if(U[i][column] < value){
                max_row = i;
                value = U[i][column];
            }
        }
    }

    return max_row;
}

/**
 * Interchanges two rows of a given matrix.
 * A column index can be set to omit all elements before that index.
 * A second index (argument: end) can be set to omit all elements after and including that index.
 *
 * @param matrix pointer to the matrix for which rows should be switched
 * @param row_one the index of the first row
 * @param row_two the index of the second row
 * @param start the index of the starting column
 * @param start the index of the ending column
 */
void ira::interchangeRow(vector<vector<mps>>& matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end) {

    for(auto i = start; i < end; i++){
        auto tmp = matrix[row_one][i];
        matrix[row_one][i] = matrix[row_two][i];
        matrix[row_two][i] = tmp;
    }
}

/**
 * Permutes a vector according to a permutation vector.
 *
 * @param permutation_vector the permutation vector.
 * @param input_vector the vector that should be permuted.
 * @return the permuted vector.
 */
vector<mps> ira::permuteVector(const vector<mps>& permutation_vector, const vector<mps>& input_vector) {

    vector<mps> ret;
    ret.resize(input_vector.size(), mps());

    for(unsigned long i = 0; i < permutation_vector.size(); i++){
        auto idx = (unsigned long) permutation_vector[i].getValue();
        ret[i] |= input_vector[idx];
    }

    return ret;
}
//-------------------------------