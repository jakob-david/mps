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
                this->A[n * i + j] = mps(mantissa_length, exponent_length, 1);
            } else {
                this->A[n * i + j] = mps(mantissa_length, exponent_length, 0);
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
void ira::PLU_decomposition() const {

}
//-------------------------------