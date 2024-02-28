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
    this->A = new mps[n * n];

    this->L = nullptr;
    this->U = nullptr;
    this->P = nullptr;
}

ira::~ira(){
    delete[] this->A;
}
//-------------------------------


// setter
//-------------------------------
void ira::unitary(unsigned long mantissa_length, unsigned long exponent_length) const {

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
        throw std::invalid_argument("ERROR: in setMatrix : new_matrix too large");
    }
    if (new_matrix.size() < this->n * this->n) {
        throw std::invalid_argument("ERROR: in setMatrix : new_matrix too small");
    }

    for(unsigned i = 0; i < new_matrix.size(); i++){
        this->A[i] = mps(mantissa_length, exponent_length, new_matrix[i]);
    }
}
//-------------------------------

// getter
//-------------------------------
[[nodiscard]] mps ira::getMatrixElement(unsigned long idx){

    return this->A[idx];
}

std::string ira::to_string(const char& matrix, const int precision) const {

    std::string ret;

    if('A' == matrix){

        ret += this->A[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->A[i].to_string(precision));
        }

    } else if('L' == matrix){

        if (nullptr == this->L) {
            throw std::invalid_argument("ERROR: in to_string : L matrix is nullptr");
        }

        ret += this->L[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->L[i].to_string(precision));
        }

    } else if('U' == matrix) {

        if (nullptr == this->U) {
            throw std::invalid_argument("ERROR: in to_string : U matrix is nullptr");
        }

        ret += this->U[0].to_string(precision);
        for(unsigned long i = 1; i < n*n; i++){
            ret.append(", ");
            ret.append(this->U[i].to_string(precision));
        }

    } else if('P' == matrix) {

        if (nullptr == this->P) {
            throw std::invalid_argument("ERROR: in to_string : P matrix is nullptr");
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
//-------------------------------


// algorithms
//-------------------------------
void ira::PLU_decomposition() {

    // TODO: maybe use different precision
    unsigned long mantissa_length = A[0].mantissa_length;
    unsigned long exponent_length = A[0].exponent_length;
    unsigned long matrix_1D_size = this->n * this->n;

    // set up L and P
    //-------------------------------
    // TODO: Maybe set bit array directly;
    this->L = new mps[matrix_1D_size];
    this->P= new mps[matrix_1D_size];
    for(unsigned long i = 0; i <  this->n; i++){
        for(unsigned long j = 0; j < this->n; j++){
            if(i == j){
                this->L[get_idx(i, j)] = mps(mantissa_length, exponent_length, 1);
                this->P[get_idx(i, j)] = this->L[get_idx(i, j)];
            } else {
                this->L[get_idx(i, j)] = mps(mantissa_length, exponent_length, 0);
                this->P[get_idx(i, j)] = this->L[get_idx(i, j)];
            }
        }
    }
    //-------------------------------

    // set up U
    //-------------------------------
    this->U = new mps[matrix_1D_size];
    for(unsigned long i = 0; i <  this->n; i++){
        for(unsigned long j = 0; j < this->n; j++){
            this->U[get_idx(i, j)] = A[get_idx(i, j)];
        }
    }
    //-------------------------------


    // algorithm
    //-------------------------------
    // TODO: probably k = 0 (also at interchange L and P)
    for(unsigned long k = 0; k < this->n; k++){

        auto max_row = get_max_U_idx(k, k, n);

        interchangeRow(this->U, k, max_row, k, n);
        interchangeRow(this->L, k, max_row, 0, k);
        interchangeRow(this->P, k, max_row, 0, n);

        for(unsigned long j = k+1; j < n; j++){

            this->L[get_idx(j, k)] = this->U[get_idx(j, k)] / this->U[get_idx(k, k)];

            for(unsigned long i = k; i < n; i++){
                this->U[get_idx(j, i)]  = this->U[get_idx(j, i)] - this->L[get_idx(j, k)] * this->U[get_idx(k, i)];
            }
        }

    }
    //-------------------------------
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

void ira::interchangeRow(mps* matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end){

    for(auto i = start; i < end; i++){
        auto tmp = matrix[get_idx(row_one, i)];
        matrix[get_idx(row_one, i)] = matrix[get_idx(row_two, i)];
        matrix[get_idx(row_two, i)] = tmp;
    }
}
//-------------------------------