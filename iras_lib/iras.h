//
// Created by Jakob on 30.04.24.
//

#ifndef MPS_IRAS_H
#define MPS_IRAS_H

#endif //MPS_IRAS_H


// generate random vector/matrix
//-------------------------------
template <typename T>
vector<T> generateRandomVector(unsigned long size, T lower_bound, T upper_bound);

template <typename T>
vector<T> generateRandomMatrix(unsigned long size, T lower_bound, T upper_bound, double sparsity_rate = 0);
//-------------------------------


// dot product
//-------------------------------
template <typename T>
vector<T> dotProduct(const vector<vector<T>> matrix, const vector<T> vec);

template <typename T>
vector<vector<T>> dotProduct(const vector<vector<T>> A, const vector<vector<T>> B);
//-------------------------------


// converter
//-------------------------------
template <typename from, typename to>
vector<to> convert(const vector<from> vec);

template <typename from, typename to>
vector<vector<to>> convert(const vector<vector<from>> matrix);
//-------------------------------
