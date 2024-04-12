//
// Created by Jakob on 28.02.24.
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

    this->parameters.max_iter = 10;     // Must be 10 because of unit tests.

    this->parameters.ur_m_l = ur_mantissa_length;
    this->parameters.ur_e_l = ur_exponent_length;

    this->parameters.working_precision_set = false;         // after construction no working precision is set.
    this->parameters.expected_result_present = false;       // after construction no result vector is present.
    this->parameters.expected_precision_present = false;    // after construction no expected precision is present.


    // set up matrices
    //-------------------------------
    this->A.resize(this->parameters.matrix_1D_size);
    this->L.resize(this->parameters.matrix_1D_size);
    this->U.resize(this->parameters.matrix_1D_size);

    // set up permutation vector
    //-------------------------------
    this->P.resize(this->parameters.n);

    // set up evaluation struct
    //-------------------------------
    this->evaluation.IR_relativeError.resize(0);
    this->evaluation.IR_area_relativeError = 0.0;
    this->evaluation.IR_area_precision = 0.0;
    this->evaluation.milliseconds = 0;

    this->evaluation.iterations_needed = 0;
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
 * @param mantissa_length the new mantissa size.
 * @param exponent_length the new exponent size. .
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
 * Sets the size of the mantissa and exponent of the upper precision (ur)
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

    // TODO: test
    castExpectedResult(this->parameters.u_m_l, this->parameters.u_e_l);
    castExpectedResult(this->parameters.ur_m_l, this->parameters.ur_e_l);
    this->parameters.expected_result_double = ira::mps_to_double(this->parameters.expected_result_mps);
}

/**
 * Sets the expected precision which is maximal distance between the expected result and the actual result.
 * If the Floating Point Format does not match with the set upper precision it will be converted accordingly.
 *
 * Throws Exception:    When no expected precision was set beforehand.
 *
 * @param new_expected_precision the expected precision.
 */
void ira::setExpectedPrecision(const mps& new_expected_precision){

    if(not this->parameters.expected_result_present){
        throw std::invalid_argument("ERROR: in setExpectedPrecision: expected result must be set before expected precision!");
    }

    this->parameters.expected_precision_present = true;

    this->parameters.expected_precision |= new_expected_precision;
    this->parameters.expected_precision.cast(this->parameters.ur_m_l, this->parameters.ur_e_l);
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
unsigned long ira::getDimension(){

    return this->parameters.n;
}

/**
 * Gets the number of elements of the system matrix (n*n).
 *
 * @return the number of elements of the systemmatrix
 */
unsigned long ira::get1DMatrixSize(){

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
 * Gets the expected result (x) as an vector consisting of doubles.
 *
 * Throws Exception:    When no expected precision was set.
 *
 * @return the expected result as vector<double>
 */
mps ira::getExpectedPrecision() const{

    if (not this->parameters.expected_precision_present) {
        throw std::invalid_argument("ERROR: in getExpectedPrecision : no expected precision present");
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

    for(unsigned long i = 0; i <  this->parameters.n; i++){
        for(unsigned long j = 0; j < this->parameters.n; j++){
            if(i == j){
                this->A[get_idx(i, j)] |= one;
            } else {
                this->A[get_idx(i, j)] |= zero;
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

    for(unsigned i = 0; i < new_matrix.size(); i++){
        this->A[i] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, new_matrix[i]);
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

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(this->parameters.random_lower_bound, this->parameters.random_upper_bound);


    for(unsigned i = 0; i < this->parameters.matrix_1D_size; i++){
        this->A[i] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, dist(mt));
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

    for(unsigned long i = 0; i < new_L.size(); i++){
        this->L[i] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, new_L[i]);
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

    for(unsigned long i = 0; i < new_U.size(); i++){
        this->U[i] |= mps(this->parameters.ur_m_l, this->parameters.ur_e_l, new_U[i]);
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
mps ira::getMatrixElement(unsigned long idx){

    if (idx >= this->parameters.matrix_1D_size) {
        throw std::invalid_argument("ERROR: getMatrixElement: idx too large");
    }

    return this->A[idx];
}
//-------------------------------


// to_string converters
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
string ira::to_string(const char& matrix, const int precision) const {

    std::string ret;

    if('A' == matrix){

        if(this->A.empty() || (this->A[0].exponent_length == 0 && this->A[0].mantissa_length == 0)){
            throw std::invalid_argument("ERROR: to_string: A is empty");
        }

        ret += this->A[0].to_string(precision);
        for(unsigned long i = 1; i < this->parameters.matrix_1D_size; i++){
            ret.append(", ");
            ret.append(this->A[i].to_string(precision));
        }

    } else if('L' == matrix){

        if(this->L.empty() || (this->L[0].exponent_length == 0 && this->L[0].mantissa_length == 0)){
            throw std::invalid_argument("ERROR: to_string: L is empty");
        }

        ret += this->L[0].to_string(precision);
        for(unsigned long i = 1; i < this->parameters.matrix_1D_size; i++){
            ret.append(", ");
            ret.append(this->L[i].to_string(precision));
        }

    } else if('U' == matrix) {

        if(this->U.empty() || (this->U[0].exponent_length == 0 && this->U[0].mantissa_length == 0)){
            throw std::invalid_argument("ERROR: to_string: U is empty");
        }

        ret += this->U[0].to_string(precision);
        for(unsigned long i = 1; i < this->parameters.matrix_1D_size; i++){
            ret.append(", ");
            ret.append(this->U[i].to_string(precision));
        }

    } else if('P' == matrix) {

        if(this->P.empty() || (this->P[0].exponent_length == 0 && this->P[0].mantissa_length == 0)){
            throw std::invalid_argument("ERROR: to_string: P is empty");
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
        throw std::invalid_argument("ERROR: in to_string : invalid matrix parameter");
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
string ira::to_string(vector<mps> vec, int precision) {

    if (vec.empty()) {
        throw std::invalid_argument("ERROR: to_string (vector): a is empty");
    }

    auto ret = vec[0].to_string(precision);
    for(unsigned long i = 1; i < vec.size(); i++) {
        ret.append(", ");
        ret.append(vec[i].to_string(precision));
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
 * @param double_vector the vector of mos objects which should be converted
 */
void ira::castVectorElements(unsigned long mantissa_length, unsigned long exponent_length, vector<mps>* vec){

    if ((*vec).empty()) {
        throw std::invalid_argument("ERROR: in castVectorElements: vector is empty");
    }
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in castVectorElements : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in castVectorElements : exponent size too small");
    }


    if(mantissa_length == (*vec)[0].mantissa_length && exponent_length == (*vec)[0].exponent_length){
        return;
    }

    for(auto & i : *vec){
        i.cast(mantissa_length, exponent_length);
    }
}

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

    if(mantissa_length == this->A[0].mantissa_length && exponent_length == this->A[0].exponent_length){
        return;
    }

    for(auto & element : this->A){
        element.cast(mantissa_length, exponent_length);
    }

}

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

    if(mantissa_length == this->parameters.expected_result_mps[0].mantissa_length && exponent_length == this->parameters.expected_result_mps[0].exponent_length){
        return;
    }

    for(auto & element : this->parameters.expected_result_mps){
        element.cast(mantissa_length, exponent_length);
    }
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
vector<mps> ira::generateRandomVector(unsigned long mantissa_length, unsigned long exponent_length, unsigned long size) const {

    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in generateRandomVector : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in generateRandomVector : exponent size too small");
    }
    if (exponent_length < 1) {
        throw std::invalid_argument("ERROR: generateRandomVector: exponent too small");
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
 * Generates a random rhs for the linear system.
 * Generates the vector x and calculates the vector b (Ax=b). Also sets the expected result.
 *
 * @return the b vector of the system
 */
vector<mps> ira::generateRandomRHS() {

    auto x = generateRandomVector(this->parameters.ur_m_l, this->parameters.ur_e_l, this->parameters.n);
    auto b = multiplyWithSystemMatrix(x);
    setExpectedResult(x);

    return b;
}

/**
 * Generates a complete random linear system.
 * Generates A and x calulases vectors the vector b (Ax=b). Also sets the expected result.
 *
 * @return the b vector of the system
 */
vector<mps> ira::generateRandomLinearSystem() {

    setRandomMatrix();
    return generateRandomRHS();
}
//-------------------------------


// operators
//-------------------------------
/**
 * Returns the L1 norm of a vector consisting of mps objects.
 *
 * @param a the vector for which the L1 norm should be calculated
 * @return the L1 norm of the vector
 */
mps ira::vectorNorm_L1(const vector<mps>& a){

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
 * Adds two vectors together. The vectors consist of mps objects.
 *
 * @param a the first vector.
 * @param b the second vector.
 * @return the resulting vector after the addition.
 */
vector<mps> ira::vectorAddition(const vector<mps>& a, const vector<mps>& b) {

    if (a.empty()) {
        throw std::invalid_argument("ERROR: in vectorAddition: a is empty");
    }
    if (b.empty()) {
        throw std::invalid_argument("ERROR: in vectorAddition: b is empty");
    }
    if (a.size() != b.size()) {
        throw std::invalid_argument("ERROR: in vectorAddition: dimensions of a and b do not match");
    }
    if (a[0].exponent_length != b[0].exponent_length) {
        throw std::invalid_argument("ERROR: in vectorAddition: exponents do not match");
    }
    if (a[0].mantissa_length != b[0].mantissa_length) {
        throw std::invalid_argument("ERROR: in vectorAddition: mantissas do not match");
    }

    vector<mps> result(a.size(), mps(a[0].mantissa_length, a[0].exponent_length, 0.0));

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
vector<mps> ira::vectorSubtraction(const vector<mps>& a, const vector<mps>& b) {

    if (a.empty()) {
        throw std::invalid_argument("ERROR: in vectorSubtraction: a is empty");
    }
    if (b.empty()) {
        throw std::invalid_argument("ERROR: in vectorSubtraction: b is empty");
    }
    if (a.size() != b.size()) {
        throw std::invalid_argument("ERROR: in vectorSubtraction: dimensions of a and b do not match");
    }
    if (a[0].exponent_length != b[0].exponent_length) {
        throw std::invalid_argument("ERROR: in vectorSubtraction: exponents do not match");
    }
    if (a[0].mantissa_length != b[0].mantissa_length) {
        throw std::invalid_argument("ERROR: in vectorSubtraction: mantissas do not match");
    }

    vector<mps> result(a.size(), mps(a[0].mantissa_length, a[0].exponent_length, 0.0));

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
vector<mps> ira::matrixVectorProduct(const vector<mps>& D, const vector<mps>& x) {

    if (D.empty()) {
        throw std::invalid_argument("ERROR: in matrixVectorProduct: D is empty");
    }
    if (x.empty()) {
        throw std::invalid_argument("ERROR: in matrixVectorProduct: x is empty");
    }
    if (D.size() != (x.size() * x.size())) {
        throw std::invalid_argument("ERROR: in matrixVectorProduct: dimensions of D and x do not match");
    }
    if (D[0].exponent_length != x[0].exponent_length) {
        throw std::invalid_argument("ERROR: in matrixVectorProduct: exponents do not match");
    }
    if (D[0].mantissa_length != x[0].mantissa_length) {
        throw std::invalid_argument("ERROR: in matrixVectorProduct: mantissas do not match");
    }

    vector<mps> y(x.size(), mps(D[0].mantissa_length, D[0].exponent_length, 0.0));

    for(unsigned long i = 0; i < x.size(); i++){
        for(unsigned long j = 0; j < x.size(); j++){
            y[i] = y[i] + (x[j] * D[get_idx(i, j, x.size())]);
        }
    }

    return y;
}

/**
 * Performs a matrix vector product. The matrix is the system matrix A.
 *
 * @param x the vector for the multiplication
 * @return the resulting vector from the multiplication.
 */
vector<mps> ira::multiplyWithSystemMatrix(vector<mps> x) const {

    if (this->A.empty()) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: system matrix is empty");
    }
    if (x.empty()) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: x is empty");
    }
    if (this->A.size() != (x.size() * x.size())) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: dimensions of A and x do not match");
    }
    if (this->A[0].exponent_length != x[0].exponent_length) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: exponents do not match");
    }
    if (this->A[0].mantissa_length != x[0].mantissa_length) {
        throw std::invalid_argument("ERROR: in multiplyWithSystemMatrix: mantissas do not match");
    }

    return matrixVectorProduct(this->A, x);
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
void ira::PLU_decomposition(unsigned long mantissa_precision, unsigned long exponent_precision) {

    if (mantissa_precision <= 0) {
        throw std::invalid_argument("ERROR: in PLU_decomposition : mantissa size too small");
    }
    if (mantissa_precision <= 1) {
        throw std::invalid_argument("ERROR: in PLU_decomposition : exponent size too small");
    }

    unsigned long idx;

    // set up L
    //-------------------------------
    mps mps_zero(mantissa_precision, exponent_precision, 0);
    mps mps_one(mantissa_precision, exponent_precision, 1);

    for(unsigned long i = 0; i <  this->parameters.n; i++){
        for(unsigned long j = 0; j < this->parameters.n; j++){

            idx = get_idx(i, j);

            if(i == j){
                this->L[idx] |= mps_one;
            } else {
                this->L[idx] |= mps_zero;
            }
        }
    }
    //-------------------------------

    // set up P
    //-------------------------------
    for(unsigned long i = 0; i < this->parameters.n; i++){
        P[i] |= mps(mantissa_precision, exponent_precision, (double) i);
    }
    //-------------------------------


    // set up U
    //-------------------------------
    for(unsigned long i = 0; i <  this->parameters.n; i++){
        for(unsigned long j = 0; j < this->parameters.n; j++){

            idx = get_idx(i, j);

            this->U[idx] |= A[idx];
            this->U[idx].cast(mantissa_precision, exponent_precision);
        }
    }
    //-------------------------------


    // algorithm
    //-------------------------------
    for(unsigned long k = 0; k < this->parameters.n; k++){
        // cout << "iteration: " << k << "/" << this->n << endl;

        auto max_row = get_max_U_idx(k, k);

        interchangeRow(&this->U, k, max_row, k, this->parameters.n);
        interchangeRow(&this->L, k, max_row, 0, k);

        auto tmp = P[k]; P[k] = P[max_row]; P[max_row] = tmp;

        for(unsigned long j = k+1; j < this->parameters.n; j++){

            idx = get_idx(j, k);
            this->L[idx] = this->U[idx] / this->U[get_idx(k, k)];

            for(unsigned long i = k; i < this->parameters.n; i++){

                this->U[get_idx(j, i)]  = this->U[get_idx(j, i)] - (this->L[idx] * this->U[get_idx(k, i)]);
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

    vector<mps> x(b.size(), mps(this->L[0].mantissa_length, this->L[0].exponent_length));

    x[0] = b[0]/L[get_idx(0, 0)];

    mps tmp_sum(this->L[0].mantissa_length, this->L[0].exponent_length);

    for(unsigned long i = 1; i < this->parameters.n; i++){

        tmp_sum = 0;
        for(unsigned long j = 0; j < i; j++){
            tmp_sum =  tmp_sum + (L[get_idx(i,j)] * x[j]);
        }

        x[i] = (b[i] - tmp_sum) / L[get_idx(i, i)];
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

    // TODO: maybe precalculate n-1

    vector<mps> x(b.size(), mps(this->U[0].mantissa_length, this->U[0].exponent_length));

    x[this->parameters.n-1] = b[this->parameters.n-1]/U[get_idx(this->parameters.n-1, this->parameters.n-1)];

    mps tmp_sum(this->U[0].mantissa_length, this->U[0].exponent_length);

    for(unsigned long i = this->parameters.n-1; i > 0;){

        i--;

        tmp_sum = 0;
        for(unsigned long j = this->parameters.n-1; j > i; j--){

            tmp_sum =  tmp_sum + (U[get_idx(i,j)] * x[j]);
        }

        x[i] = (b[i] - tmp_sum) / U[get_idx(i, i)];
    }

    return x;
}

/**
 * Solves a system of equation using a PLU-Factorisation.
 * The system matrix needs not to be a parameter since it must set beforehand.
 *
 * @param b the solution vector of the system.
 * @param u the precision in which the system should be solved.
 * @return the solution of the system as an mps object.
 */
vector<mps> ira::solveLU(const vector<mps>& b, unsigned long u[2]){
// TODO: delete u

    this->PLU_decomposition(u[0], u[1]);
    auto tmp_b = b;
    ira::castVectorElements(u[0], u[1], &tmp_b);



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
vector<mps> ira::iterativeRefinementLU(const vector<mps> &b) {

    // set evaluation parameters to zero
    //-------------------------------
    if(this->parameters.expected_result_present) {
        this->evaluation.IR_area_relativeError = 0;
        this->evaluation.IR_area_precision = 0;
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
    this->PLU_decomposition(ul[0], ul[1]);
    //-------------------------------

    // perform substitution to gain x_0
    //-------------------------------
    auto tmp_b = b;
    ira::castVectorElements(ul[0], ul[1], &tmp_b);
    auto x = ira::permuteVector(this->P, tmp_b);

    x = this->forwardSubstitution(x);
    x = this->backwardSubstitution(x);
    ira::castVectorElements(u[0], u[1], &x);
    //-------------------------------



    for(unsigned long i = 0; i < this->parameters.max_iter; i++){

        // calculate: r_i = b − A * x_i
        // in precision: ur
        //-------------------------------
        auto tmp_x = x;
        ira::castVectorElements(ur[0], ur[1], &tmp_x);
        auto r = vectorSubtraction(b, ira::matrixVectorProduct(this->A, tmp_x));
        //-------------------------------


        // check convergence
        //-------------------------------
        if(this->parameters.expected_precision_present){
            auto norm = vectorNorm_L1(r);
            if(norm < this->parameters.expected_precision){
                this->evaluation.iterations_needed = i;
                break;
            }
        }
        //-------------------------------


        // solve: A * d_i = r_i
        // in precision: ul
        //-------------------------------
        ira::castVectorElements(ul[0], ul[1], &r);
        r = ira::permuteVector(this->P, r);
        auto d = this->forwardSubstitution(r);
        d = this->backwardSubstitution(d);
        //-------------------------------


        // calculate: x_i+1 = x_i + d_i i
        // n precision u.
        //-------------------------------
        ira::castVectorElements(u[0], u[1], &d);
        x = vectorAddition(x, d);
        //-------------------------------


        // evaluation
        //-------------------------------
        if(this->parameters.expected_result_present) {
            for (unsigned long element_id = 0; element_id < this->parameters.n; element_id++) {
                this->evaluation.IR_relativeError.push_back(
                        x[element_id].getRelativeError_double(this->parameters.expected_result_mps[element_id]));
                this->evaluation.IR_area_relativeError += this->evaluation.IR_relativeError.back();
            }
        }
        //-------------------------------


    }

    const auto finish = std::chrono::high_resolution_clock::now();
    this->evaluation.milliseconds = (std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count()) / 1000;

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

            auto idx = get_idx(i, j);

            row.push_back(this->A[idx].getValue());
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
 * Since the matrices are saved as a vector this function converts 2D-coordinates of the matrix to the 1D-index
 * used for the vector.
 *
 * The needed variable n is given via a variable.
 *
 * @param row the row index of the element of the matrix
 * @param column the column index of the element of the matrix
 * @param n the dimension of the matrix.
 * @return the resulting 1D-index.
 */
unsigned long ira::get_idx(unsigned long row, unsigned long column, unsigned long n){
    return n * row + column;
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
    mps value = U[get_idx(start, column)];

    for(unsigned long i = start; i < this->parameters.n; i++){

        unsigned long idx = get_idx(i, column);

        if(U[idx].isPositive()){
            value.setSign(false);
            if(U[idx] > value){
                max_row = i;
                value = U[idx];
            }
        } else {
            value.setSign(true);
            if(U[idx] < value){
                max_row = i;
                value = U[idx];
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
void ira::interchangeRow(vector<mps>* matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end) const{

    for(auto i = start; i < end; i++){
        auto tmp = (*matrix)[get_idx(row_one, i)];
        (*matrix)[get_idx(row_one, i)] = (*matrix)[get_idx(row_two, i)];
        (*matrix)[get_idx(row_two, i)] = tmp;
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