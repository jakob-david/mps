//
// Created by Jakob on 28.02.24.
//

#include "ira.h"
#include <iostream>

using namespace std;

// constructor and destructor
//-------------------------------
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

ira::~ira() = default;
//-------------------------------


// setter
//-------------------------------
void ira::unitary(unsigned long mantissa_length, unsigned long exponent_length) {

    for(unsigned long i = 0; i <  this->n; i++){
        for(unsigned long j = 0; j < this->n; j++){
            if(i == j){
                this->A[get_idx(i, j)] = mps(mantissa_length, exponent_length, 1);
            } else {
                this->A[get_idx(i, j)] = mps(mantissa_length, exponent_length, 0);
            }
        }
    }
}

void ira::setMatrix(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_matrix) {

    if (new_matrix.size() > this->n * this->n) {
        throw std::invalid_argument("ERROR: in setMatrix: new_matrix too large");
    }
    if (new_matrix.size() < this->n * this->n) {
        throw std::invalid_argument("ERROR: in setMatrix: new_matrix too small");
    }

    for(unsigned i = 0; i < new_matrix.size(); i++){
        this->A[i] = mps(mantissa_length, exponent_length, new_matrix[i]);
    }
}

void ira::setL(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_L) {

    if (new_L.size() > this->n * this->n) {
        throw std::invalid_argument("ERROR: in setL: new_L too large");
    }
    if (new_L.size() < this->n * this->n) {
        throw std::invalid_argument("ERROR: in setL: new_L too small");
    }

    for(unsigned long i = 0; i < new_L.size(); i++){
        this->L[i] = mps(mantissa_length, exponent_length, new_L[i]);
    }
}

void ira::setU(unsigned long mantissa_length, unsigned long exponent_length, vector<double> new_U) {

    if (new_U.size() > this->n * this->n) {
        throw std::invalid_argument("ERROR: in setU: new_U too large");
    }
    if (new_U.size() < this->n * this->n) {
        throw std::invalid_argument("ERROR: in setU: new_U too small");
    }

    for(unsigned long i = 0; i < new_U.size(); i++){
        this->U[i] = mps(mantissa_length, exponent_length, new_U[i]);
    }
}
//-------------------------------

// getter
//-------------------------------
[[nodiscard]] mps ira::getMatrixElement(unsigned long idx){

    return this->A[idx];
}

[[nodiscard]] std::string ira::to_string(const char& matrix, const int precision) const {

    std::string ret;

    if('A' == matrix){

        ret += this->A[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->A[i].to_string(precision));
        }

    } else if('L' == matrix){

        ret += this->L[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->L[i].to_string(precision));
        }

    } else if('U' == matrix) {

        ret += this->U[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->U[i].to_string(precision));
        }

    } else if('P' == matrix) {

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
//-------------------------------


// algorithms
//-------------------------------
[[nodiscard]] mps ira::vectorNorm_L1(const vector<mps>& a){

    if (a.empty()) {
        throw std::invalid_argument("ERROR: in vectorNorm: a is empty");
    }

    auto ret = a[0];

    for(unsigned long i = 1; i < a.size(); i++){
        ret = ret + a[i];
    }

    return ret;
}

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

[[nodiscard]] vector<mps> ira::matrixVectorProduct(const vector<mps>& D, const vector<mps>& x) const {

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
            y[i] = y[i] + (x[j] * D[get_idx(i, j)]);
        }
    }

    return y;
}

void ira::PLU_decomposition(unsigned long mantissa_precision, unsigned long exponent_precision) {

    //unsigned long matrix_1D_size = this->n * this->n;
    unsigned long idx;

    // set up L and P
    //-------------------------------
    //this->L = new mps[matrix_1D_size];
    //this->P = new mps[matrix_1D_size];

    mps mps_zero(mantissa_precision, exponent_precision, 0);
    mps mps_one(mantissa_precision, exponent_precision, 1);

    for(unsigned long i = 0; i <  this->n; i++){
        for(unsigned long j = 0; j < this->n; j++){

            idx = get_idx(i, j);

            if(i == j){
                this->L[idx] = mps_one;
                this->P[idx] = mps_one;
            } else {
                this->L[idx] = mps_zero;
                this->P[idx] = mps_zero;
            }
        }
    }
    //-------------------------------

    // set up U
    //-------------------------------
    //this->U = new mps[matrix_1D_size];
    for(unsigned long i = 0; i <  this->n; i++){
        for(unsigned long j = 0; j < this->n; j++){

            idx = get_idx(i, j);

            this->U[idx] = A[idx];
            this->U[idx].cast(mantissa_precision, exponent_precision);
        }
    }
    //-------------------------------


    // algorithm
    //-------------------------------
    for(unsigned long k = 0; k < this->n; k++){

        auto max_row = get_max_U_idx(k, k, n);

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

[[nodiscard]] vector<mps> ira::forwardSubstitution(const vector<mps>& b) const {

    // TODO: make sure that L is not empty
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

[[nodiscard]] vector<mps> ira::backwardSubstitution(const vector<mps>& b) const {

    // TODO: check that U is not null
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

[[nodiscard]] vector<mps> ira::iterativeRefinementLU(const vector<mps>& b){

    unsigned long exp_precision = b[0].exponent_length;
    unsigned long mant_precision = b[0].mantissa_length;

    this->PLU_decomposition(mant_precision, exp_precision);

    auto x = this->matrixVectorProduct(this->P, b);
    x = this->forwardSubstitution(x);
    x = this->backwardSubstitution(x);

    vector<mps> r(b.size(), mps(mant_precision, exp_precision));
    vector<mps> d(b.size(), mps(mant_precision, exp_precision));

    for(unsigned long i = 0; i < 10; i++){
        r = vectorSubtraction(b, this->matrixVectorProduct(this->A, x));
        d = this->forwardSubstitution(r);
        d = this->backwardSubstitution(d);
        // cout << vectorNorm_L1(d).to_string(3)<< endl;
        x = vectorAddition(x, d);
    }

    return x;
}
//-------------------------------




// helper functions
//-------------------------------
unsigned long ira::get_idx(unsigned long row, unsigned long column) const{
    return this->n * row + column;
}

unsigned long ira::get_max_U_idx(unsigned long column, unsigned long start, unsigned long end) const {

    unsigned long max_row = start;
    mps value = U[get_idx(start, column)];

    for(unsigned long i = start; i < end; i++){

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

// TODO: smartpointer....?
void ira::interchangeRow(vector<mps>* matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end){

    for(auto i = start; i < end; i++){
        auto tmp = (*matrix)[get_idx(row_one, i)];
        (*matrix)[get_idx(row_one, i)] = (*matrix)[get_idx(row_two, i)];
        (*matrix)[get_idx(row_two, i)] = tmp;
    }
}
//-------------------------------