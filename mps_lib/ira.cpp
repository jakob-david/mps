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
    this->matrix = new mps[n * n];

    this->L = nullptr;
    this->U = nullptr;
    this->P = nullptr;
}

ira::~ira(){
    delete[] this->matrix;
}
//-------------------------------


// setter
//-------------------------------
void ira::unitary(unsigned long mantissa_length, unsigned long exponent_length) const {

    for(unsigned long i = 0; i <  this->n; i++){
        for(unsigned long j = 0; j < this->n; j++){
            if(i == j){
                this->matrix[n*i + j] = mps(mantissa_length, exponent_length, 1);
            } else {
                this->matrix[n*i + j] = mps(mantissa_length, exponent_length, 0);
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
        this->matrix[i] = mps(mantissa_length, exponent_length, new_matrix[i]);
    }
}
//-------------------------------

// getter
//-------------------------------
std::string ira::to_string() const {

    std::string ret;

    ret += this->matrix[0].to_string();

    for(unsigned long i = 1; i < n*n; i++){
        ret.append(", ");
       ret.append(this->matrix[i].to_string());
    }

    return ret;
}
//-------------------------------


// algorithms
//-------------------------------
void ira::PLU_decomposition() const {

}
//-------------------------------