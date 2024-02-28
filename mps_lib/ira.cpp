//
// Created by Jakob on 28.02.24.
//

#include "ira.h"
#include <iostream>

using namespace std;

ira::ira(unsigned long n){

    this->n = n;
    this->matrix = new mps[n * n];
}

ira::~ira(){
    delete[] this->matrix;
}

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

std::string ira::to_string() const {

    std::string ret;

    ret += this->matrix[0].to_string();

    for(unsigned long i = 1; i < n*n; i++){
        ret.append(", ");
       ret.append(this->matrix[i].to_string());
    }

    return ret;
}

