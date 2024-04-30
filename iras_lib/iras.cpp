//
// Created by Jakob on 30.04.24.
//

#include <random>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;


// toString
//-------------------------------
template <typename T>
string toString(const vector<T>& vec, long precision){

    string ret;

    for(unsigned long idx = 0; idx < vec.size(); idx++){
        std::ostringstream out;
        out.precision(precision);
        out << std::fixed << vec[idx];

        ret.append(std::move(out).str());
        ret.append(", ");
    }

    ret.pop_back();
    ret.pop_back();

    return ret;
}

template <typename T>
string toString(const vector<vector<T>>& matrix, long precision){

    string ret;

    for(unsigned long idx = 0; idx < matrix.size(); idx++){
        ret.append(toString<T>(matrix[idx], precision));
        ret.append("\n");
    }

    return ret;
}
//-------------------------------


// generate random vector/matrix
//-------------------------------
template <typename T>
vector<T> generateRandomVector(unsigned long size, T lower_bound, T upper_bound){

    vector<T> ret;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<T> dist(lower_bound, upper_bound);

    for(unsigned long i = 0; i < (unsigned long) size; i++){
        ret.push_back(dist(mt));
    }

    return ret;
}

template <typename T>
vector<vector<T>> generateRandomMatrix(unsigned long size, T lower_bound, T upper_bound, double sparsity_rate = 0){

    vector<vector<T>> ret;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<T> dist(lower_bound, upper_bound);

    if(0 == sparsity_rate){
        for(unsigned long i = 0; i < size; i++){

            vector<T> new_row;
            for(unsigned long j = 0; j < size; j++){
                new_row.push_back(dist(mt));
            }

            ret.push_back(new_row);
        }
    } else {

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
        double adapted_sparsity_rate = (sparsity_rate * ((double) size)) / ((double) (size - 1));

        for(unsigned long i = 0; i < size; i++){

            vector<T> new_row;
            for(unsigned long j = 0; j < size; j++){

                if(j == random_vector[i]){

                    new_row.push_back(dist(mt));
                    while(new_row.back() == 0){
                        new_row.back() = dist(mt);
                    }
                } else if(sparsity_dist(sparsity_mt) < adapted_sparsity_rate){
                    new_row.push_back(0.0);
                } else {
                    new_row.push_back(dist(mt));
                }

            }

            ret.push_back(new_row);
        }
    }

    return ret;
}
//-------------------------------


// dot product
//-------------------------------
template <typename T>
vector<T> dotProduct(const vector<vector<T>>& matrix, const vector<T> vec){

    vector<T> ret;

    for(unsigned long i = 0; i < vec.size(); i++){

        T sum = 0;
        for(unsigned long j = 0; j < vec.size(); j++){
            sum += vec[j] * matrix[i][j];
        }

        ret.push_back(sum);
    }

    return ret;

}

template <typename T>
vector<vector<T>> dotProduct(const vector<vector<T>>& A, const vector<vector<T>> B){

    vector<vector<T>> ret;

    for(unsigned long row_idx = 0; row_idx < A[0].size(); row_idx++){

        vector<T> new_row;
        for(unsigned long col_idx = 0; col_idx < A[0].size(); col_idx++){

            T sum = 0;
            for(unsigned long idx = 0; idx < A[0].size(); idx++){
                sum += A[row_idx][idx] * B[idx][col_idx];
            }
            new_row.push_back(sum);
        }
        ret.push_back(new_row);
    }

    return ret;

}
//-------------------------------


// converter
//-------------------------------
template <typename from, typename to>
vector<to> convert(const vector<from>& vec){

    vector<to> ret;

    for(unsigned long idx = 0; idx < vec.size(); idx++){
        ret.push_back((to) vec[idx]);
    }

    return ret;
}

template <typename from, typename to>
vector<vector<to>> convert(const vector<vector<from>>& matrix){

    vector<vector<to>> ret;

    for(unsigned long row_idx = 0; row_idx < matrix.size(); row_idx++){
        vector<to> new_row;
        for(unsigned long col_idx = 0; col_idx < matrix.size(); col_idx++){
            new_row.push_back((to) matrix[row_idx][col_idx]);
        }
        ret.push_back(new_row);
    }

    return ret;
}
//-------------------------------


// PLU solver
//-------------------------------
template <typename T>
void interchangeRow(vector<vector<T>>& matrix, unsigned long row_one, unsigned long row_two){

    for(unsigned long idx = 0; idx < matrix.size(); idx++){
        T tmp = matrix[row_one][idx];
        matrix[row_one][idx] = matrix[row_two][idx];
        matrix[row_two][idx] = tmp;
    }
}

template <typename T>
unsigned long get_max_U_idx(const vector<T>& row, unsigned long start){

    unsigned long max_row = start;
    T value = abs(row[start]);

    for(unsigned long idx = start; idx < row.size(); idx++){

        if(abs(row[idx]) > value){
            max_row = idx;
            value = abs(row[idx]);
        }
    }

    return max_row;
}


template <typename from, typename to>
vector<vector<vector<from>>> PLU(const vector<vector<from>>& A, vector<unsigned long>* P){


    // set up P
    //-------------------------------
    P->resize(A.size());
    for(unsigned long idx = 0; idx < A.size(); idx++){
        P->push_back(idx);
    }
    //-------------------------------

    // set up L
    //-------------------------------
    vector<vector<to>> L;
    for(unsigned long row_idx = 0; row_idx < A.size(); row_idx++){

        vector<to> new_row;
        for(unsigned long col_idx = 0; col_idx < A.size(); col_idx++){

            if(row_idx == col_idx){
                new_row.push_back(1);
            } else {
                new_row.push_back(0);
            }
        }
        L.push_back(new_row);
    }
    //-------------------------------

    // set up U
    //-------------------------------
    vector<vector<to>> U;
    for(unsigned long row_idx = 0; row_idx < A.size(); row_idx++){

        vector<to> new_row;
        for(unsigned long col_idx = 0; col_idx < A.size(); col_idx++){
            new_row.push_back((to) A[row_idx][col_idx]);
        }
        L.push_back(new_row);
    }
    //-------------------------------


    for(unsigned long k = 0; k < A.size(); k++){
        // cout << "iteration: " << k << "/" << this->n << endl;

        auto max_row = get_max_U_idx(A[k], k);

        interchangeRow(&U, k, max_row, k, A.size());
        interchangeRow(&L, k, max_row, 0, k);

        auto tmp = (*P)[k]; (*P)[k] = (*P)[max_row]; (*P)[max_row] = tmp;
    }
}
//-------------------------------