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
ira::ira(unsigned long n){

    this->n = n;
    unsigned long matrix_1D_size = this->n * this->n;


    // set up matrices
    //-------------------------------
    this->A.resize(matrix_1D_size);

    this->L.resize(matrix_1D_size);
    this->U.resize(matrix_1D_size);
    this->P.resize(matrix_1D_size);
}

/**
 * Default destructor.
 */
ira::~ira() = default;
//-------------------------------


// setter
//-------------------------------
/**
 * Sets the system matrix of the ira object to an identity matrix of a custom size.
 *
 * @param mantissa_length the size of the mantissa of the elements of the matrix
 * @param exponent_length the size of the exponent of the elements of the matrix
 */
void ira::setUnitaryMatrix(unsigned long mantissa_length, unsigned long exponent_length) {

    for(unsigned long i = 0; i <  this->n; i++){
        for(unsigned long j = 0; j < this->n; j++){
            if(i == j){
                this->A[get_idx(i, j)] |= mps(mantissa_length, exponent_length, 1);
            } else {
                this->A[get_idx(i, j)] |= mps(mantissa_length, exponent_length, 0);
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
void ira::setMatrix(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_matrix) {

    if (new_matrix.size() > this->n * this->n) {
        throw std::invalid_argument("ERROR: in setMatrix: new_matrix too large");
    }
    if (new_matrix.size() < this->n * this->n) {
        throw std::invalid_argument("ERROR: in setMatrix: new_matrix too small");
    }

    for(unsigned i = 0; i < new_matrix.size(); i++){
        this->A[i] |= mps(mantissa_length, exponent_length, new_matrix[i]);
    }
}

/**
 * Sets the system matrix of the ira object to a random generated matrix.
 * All randomly generated variables are between -10 and 10.
 *
 * @param mantissa_length the size of the mantissa of the elements of the matrix
 * @param exponent_length the size of the exponent of the elements of the matrix
 */
void ira::setRandomMatrix(unsigned long mantissa_length, unsigned long exponent_length){

    if (exponent_length < 1) {
        throw std::invalid_argument("ERROR: setRandomMatrix: exponent too small");
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);


    for(unsigned i = 0; i < (this->n * this->n); i++){
        this->A[i] |= mps(mantissa_length, exponent_length, dist(mt));
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
void ira::setL(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_L) {

    if (new_L.size() > this->n * this->n) {
        throw std::invalid_argument("ERROR: in setL: new_L too large");
    }
    if (new_L.size() < this->n * this->n) {
        throw std::invalid_argument("ERROR: in setL: new_L too small");
    }

    for(unsigned long i = 0; i < new_L.size(); i++){
        this->L[i] |= mps(mantissa_length, exponent_length, new_L[i]);
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
void ira::setU(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_U) {

    if (new_U.size() > this->n * this->n) {
        throw std::invalid_argument("ERROR: in setU: new_U too large");
    }
    if (new_U.size() < this->n * this->n) {
        throw std::invalid_argument("ERROR: in setU: new_U too small");
    }

    for(unsigned long i = 0; i < new_U.size(); i++){
        this->U[i] |= mps(mantissa_length, exponent_length, new_U[i]);
    }
}
//-------------------------------


// getter
//-------------------------------
/**
 * Returns one element of the system matrix.
 *
 * @param idx the index of the element in the array.
 * @return the element at the index.
 */
[[nodiscard]] mps ira::getMatrixElement(unsigned long idx){

    if (idx >= (this->n * this->n)) {
        throw std::invalid_argument("ERROR: getMatrixElement: idx too large");
    }

    return this->A[idx];
}

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
[[nodiscard]] std::string ira::to_string(const char& matrix, const int precision) const {

    std::string ret;

    if('A' == matrix){

        if(this->A.empty() || (this->A[0].exponent_length == 0 && this->A[0].mantissa_length == 0)){
            throw std::invalid_argument("ERROR: to_string: A is empty");
        }

        ret += this->A[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->A[i].to_string(precision));
        }

    } else if('L' == matrix){

        if(this->L.empty() || (this->L[0].exponent_length == 0 && this->L[0].mantissa_length == 0)){
            throw std::invalid_argument("ERROR: to_string: L is empty");
        }

        ret += this->L[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->L[i].to_string(precision));
        }

    } else if('U' == matrix) {

        if(this->U.empty() || (this->U[0].exponent_length == 0 && this->U[0].mantissa_length == 0)){
            throw std::invalid_argument("ERROR: to_string: U is empty");
        }

        ret += this->U[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->U[i].to_string(precision));
        }

    } else if('P' == matrix) {

        if(this->P.empty() || (this->P[0].exponent_length == 0 && this->P[0].mantissa_length == 0)){
            throw std::invalid_argument("ERROR: to_string: P is empty");
        }

        ret += this->P[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->P[i].to_string(precision));
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
[[nodiscard]] std::string ira::to_string(vector<mps> vec, int precision) {

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


// converters
//-------------------------------
/**
 * Converts a vector of booleans to a vector of mps objects.
 * The double vector is not destroyed but a new vector consisting of mps objects is created.
 *
 * @param mantissa_length the mantissa lengths of the mps objects
 * @param exponent_length the exponent lengths of the mps objects
 * @param double_vector the vector of booleans which should be converted.
 * @return vector consisting of mps objects.
 */
[[nodiscard]] vector<mps> ira::double_to_mps(unsigned long mantissa_length, unsigned long exponent_length, vector<double> double_vector){

    if (double_vector.empty()) {
        throw std::invalid_argument("ERROR: in vectorNorm: double_vector is empty");
    }
    if (mantissa_length <= 0) {
        throw std::invalid_argument("ERROR: in double_to_mps : mantissa size too small");
    }
    if (exponent_length <= 1) {
        throw std::invalid_argument("ERROR: in double_to_mps : exponent size too small");
    }

    vector<mps> ret(double_vector.size(), mps(mantissa_length, exponent_length));

    for(unsigned long i = 0; i < double_vector.size(); i++){
        ret[i] = double_vector[i];
    }

    return ret;
}

/**
 * Converts a vector of mps objects to a vector consisting of doubles.
 *
 * @param mps_vector the vector of mps objects which should be converted.
 * @return a vector consisting of doubles.
 */
[[nodiscard]] vector<double> ira::mps_to_double(vector<mps> mps_vector){

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
 * Converts a vector of mps objects to a vector consisting of floats.
 *
 * @param mps_vector the vector of mps objects which should be converted.
 * @return a vector consisting of floats.
 */
[[nodiscard]] vector<float> ira::mps_to_float(vector<mps> mps_vector){

    if (mps_vector.empty()) {
        throw std::invalid_argument("ERROR: in mps_to_float: mps_vector is empty");
    }

    vector<float> ret(mps_vector.size(), 0.0);

    for(unsigned long i = 0; i < mps_vector.size(); i++){
        ret[i] = (float) mps_vector[i].getValue();
    }

    return ret;
}

/**
 * Given a vector of mps objects this function casts all of its elements to new mantissa and exponent sizes.
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
//-------------------------------


// operators
//-------------------------------
/**
 * Returns the L1 norm of a vector consisting of mps objects.
 *
 * @param a the vector for which the L1 norm should be calculated
 * @return the L1 norm of the vector
 */
[[nodiscard]] mps ira::vectorNorm_L1(const vector<mps>& a){

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
[[nodiscard]] vector<mps> ira::vectorAddition(const vector<mps>& a, const vector<mps>& b) {

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
[[nodiscard]] vector<mps> ira::vectorSubtraction(const vector<mps>& a, const vector<mps>& b) {

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
 * Performs a vector matrix product.
 * The elements of the matrix and the vector are mps objects.
 *
 * @param D the matrix for the multiplication
 * @param x the vector for the multiplication
 * @return the resulting vector after the multiplication.
 */
[[nodiscard]] vector<mps> ira::matrixVectorProduct(const vector<mps>& D, const vector<mps>& x) {

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

    // set up L and P
    //-------------------------------
    mps mps_zero(mantissa_precision, exponent_precision, 0);
    mps mps_one(mantissa_precision, exponent_precision, 1);

    for(unsigned long i = 0; i <  this->n; i++){
        for(unsigned long j = 0; j < this->n; j++){

            idx = get_idx(i, j);

            if(i == j){
                this->L[idx] |= mps_one;
                this->P[idx] |= mps_one;
            } else {
                this->L[idx] |= mps_zero;
                this->P[idx] |= mps_zero;
            }
        }
    }
    //-------------------------------


    // set up U
    //-------------------------------
    for(unsigned long i = 0; i <  this->n; i++){
        for(unsigned long j = 0; j < this->n; j++){

            idx = get_idx(i, j);

            this->U[idx] |= A[idx];
            this->U[idx].cast(mantissa_precision, exponent_precision);
        }
    }
    //-------------------------------


    // algorithm
    //-------------------------------
    for(unsigned long k = 0; k < this->n; k++){
        // cout << "iteration: " << k << "/" << this->n << endl;

        auto max_row = get_max_U_idx(k, k);

        interchangeRow(&this->U, k, max_row, k, n);
        interchangeRow(&this->L, k, max_row, 0, k);
        interchangeRow(&this->P, k, max_row, 0, n);

        for(unsigned long j = k+1; j < n; j++){

            idx = get_idx(j, k);
            this->L[idx] = this->U[idx] / this->U[get_idx(k, k)];

            for(unsigned long i = k; i < n; i++){

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
[[nodiscard]] vector<mps> ira::forwardSubstitution(const vector<mps>& b) const {

    if (this->L.empty()) {
        throw std::invalid_argument("ERROR: in forwardSubstitution: L is empty");
    }
    if (b.empty()) {
        throw std::invalid_argument("ERROR: in forwardSubstitution: b is empty");
    }

    vector<mps> x(b.size(), mps(this->L[0].mantissa_length, this->L[0].exponent_length));

    x[0] = b[0]/L[get_idx(0, 0)];


    // TODO: maybe do a performance test if summation is needed
    mps tmp_sum(this->L[0].mantissa_length, this->L[0].exponent_length);

    for(unsigned long i = 1; i < this->n; i++){

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
[[nodiscard]] vector<mps> ira::backwardSubstitution(const vector<mps>& b) const {

    if (this->U.empty()) {
        throw std::invalid_argument("ERROR: in backwardSubstitution: U is empty");
    }
    if (b.empty()) {
        throw std::invalid_argument("ERROR: in backwardSubstitution: b is empty");
    }

    vector<mps> x(b.size(), mps(this->U[0].mantissa_length, this->U[0].exponent_length));

    x[this->n-1] = b[this->n-1]/U[get_idx(this->n-1, this->n-1)];

    // TODO: maybe do a performance test if summation is needed
    mps tmp_sum(this->U[0].mantissa_length, this->U[0].exponent_length);

    for(unsigned long i = this->n-1; i > 0;){

        i--;

        tmp_sum = 0;
        for(unsigned long j = this->n-1; j > i; j--){

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
[[nodiscard]] vector<mps> ira::solve_LU(const vector<mps>& b, unsigned long u[2]){


    this->PLU_decomposition(u[0], u[1]);
    auto tmp_b = b;
    ira::castVectorElements(u[0], u[1], &tmp_b);



    auto x = ira::matrixVectorProduct(this->P, tmp_b);
    x = this->forwardSubstitution(x);
    x = this->backwardSubstitution(x);

    return x;
}

[[nodiscard]] vector<mps> ira::iterativeRefinementLU(const vector<mps>& b, unsigned long u[2], unsigned long uf[2]){

    //unsigned long exp_precision = b[0].exponent_length;
    //unsigned long mant_precision = b[0].mantissa_length;

    vector<unsigned long> ur{A[0].mantissa_length, A[0].exponent_length};

    this->PLU_decomposition(uf[0], uf[1]);

    // initialize x vector
    // calculate in precision: uf
    // save in precision: u
    //-------------------------------
    auto tmp_b = b;
    ira::castVectorElements(uf[0], uf[1], &tmp_b);
    auto x = ira::matrixVectorProduct(this->P, tmp_b);
    x = this->forwardSubstitution(x);
    x = this->backwardSubstitution(x);
    ira::castVectorElements(u[0], u[1], &x);
    //-------------------------------

    // initialize r and d vector
    //-------------------------------
    //vector<mps> r(b.size(), mps(mant_precision, exp_precision));
    //vector<mps> d(b.size(), mps(mant_precision, exp_precision));
    //-------------------------------

    for(unsigned long i = 0; i < 10; i++){

        // calculate: r_i = b − A * x_i
        // in precision: ur
        //-------------------------------
        auto tmp_x = x;
        ira::castVectorElements(ur[0], ur[1], &tmp_x);
        auto r = vectorSubtraction(b, ira::matrixVectorProduct(this->A, tmp_x));
        //-------------------------------

        //cout << "------------------------" << endl;
        //cout << i << ": Ax: " << ira::to_string(ira::matrixVectorProduct(this->A, tmp_x), 30) << endl;
        //cout << i << ": r: " << ira::to_string(r, 30) << endl;
        cout << i << ": r: " << vectorNorm_L1(r).to_string(30)<< endl;

        // solve: A * d_i = r_i
        // in precision: uf
        //-------------------------------
        ira::castVectorElements(uf[0], uf[1], &r);
        r = ira::matrixVectorProduct(this->P, r);
        auto d = this->forwardSubstitution(r);
        d = this->backwardSubstitution(d);
        //-------------------------------

        // cout << i << ": d: " << ira::to_string(d, 30) << endl;

        // calculate: x_i+1 = x_i + d_i i
        // n precision u.
        //-------------------------------
        ira::castVectorElements(u[0], u[1], &d);
        //cout << i << ": d: " << ira::to_string(d, 30) << endl;
        //auto tmp = x[1] + d[1];
        //cout << i << ": x_1: " << x[1].print() << endl;
        //cout << i << ": d_1: " << d[1].print() << endl;
        //cout << i << ": tmp: " << tmp.to_string(30) << endl;
        //cout << i << ": tmp: " << tmp.print() << endl;
        x = vectorAddition(x, d);
        //-------------------------------

        // cout << i << ": x: " << ira::to_string(x, 30) << endl;
    }

    return x;
}
//-------------------------------


// algorithms which use "normal" double
//-------------------------------
/**
 * Solves a system of equation using a PLU-Factorisation and "normal" double variables.
 * The system matrix needs not to be a parameter since it must set beforehand.
 *
 * @param b the solution vector of the system.
 * @return the solution of the system.
 */
[[nodiscard]] vector<double> ira::solve_LU_double(const vector<double>& b){

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

    for(unsigned long i = 0; i <  this->n; i++){

        vector<double> row;

        for(unsigned long j = 0; j < this->n; j++){

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

    for(unsigned long i = 0; i <  this->n; i++){

        vector<double> row;

        for(unsigned long j = 0; j < this->n; j++){

            auto idx = get_idx(i, j);

            row.push_back(this->A[idx].getValue());
        }

        U_.push_back(row);
    }
    //-------------------------------


    // PLU decomposition algorithm
    //-------------------------------
    for(unsigned long k = 0; k < this->n; k++){

        auto max_row = get_max_U(U_, this->n, k, k);

        interchange(&U_, k, max_row, k, n);
        interchange(&L_, k, max_row, 0, k);
        interchange(&P_, k, max_row, 0, n);

        for(unsigned long j = k+1; j < n; j++){

            L_[j][k] = div(U_[j][k], U_[k][k]);

            for(unsigned long i = k; i < n; i++){
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
    for(unsigned long i = 1; i < this->n; i++){

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

    xb[this->n-1] = div(xf[this->n-1], U_[this->n-1][this->n-1]);
    for(unsigned long i = this->n-1; i > 0;){

        i--;

        double tmp_sum = 0;
        for(unsigned long j = this->n-1; j > i; j--){

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
    return this->n * row + column;
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

    for(unsigned long i = start; i < this->n; i++){

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
void ira::interchangeRow(vector<mps>* matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end){

    for(auto i = start; i < end; i++){
        auto tmp = (*matrix)[get_idx(row_one, i)];
        (*matrix)[get_idx(row_one, i)] = (*matrix)[get_idx(row_two, i)];
        (*matrix)[get_idx(row_two, i)] = tmp;
    }
}
//-------------------------------