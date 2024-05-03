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
    ret.resize(size);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<T> dist(lower_bound, upper_bound);

    if(0 == sparsity_rate){

        for(unsigned long i = 0; i < size; i++){

            ret[i].resize(size);
            for(unsigned long j = 0; j < size; j++){
                ret[i][j] = dist(mt);
            }
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

            ret[i].resize(size);
            for(unsigned long j = 0; j < size; j++){

                if(j == random_vector[i]){

                    ret[i][j] = dist(mt);
                    while(ret[i][j] == 0){
                        ret[i][j] = dist(mt);
                    }

                } else if(sparsity_dist(sparsity_mt) < adapted_sparsity_rate){
                    ret[i][j] = 0.0;
                } else {
                    ret[i][j] = dist(mt);
                }

            }
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

    ret.resize(matrix.size());
    for(unsigned long row_idx = 0; row_idx < matrix.size(); row_idx++){
        ret[row_idx].resize(matrix.size());
        for(unsigned long col_idx = 0; col_idx < matrix.size(); col_idx++){
            ret[row_idx][col_idx] = (to) matrix[row_idx][col_idx];
        }
    }

    return ret;
}
//-------------------------------


// PLU solver
//-------------------------------
template <typename T>
void interchangeRow(vector<vector<T>>& matrix, unsigned long row_one, unsigned long row_two, unsigned long start, unsigned long end){

    for(unsigned long idx = start; idx < end; idx++){
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
vector<vector<vector<to>>> PLU(const vector<vector<from>>& A, vector<unsigned long>* P){

    vector<vector<vector<to>>> ret;
    ret.resize(2);
    vector<vector<to>>& L = ret[0];
    vector<vector<to>>& U = ret[1];


    // set up P
    //-------------------------------
    P->resize(A.size());
    for(unsigned long idx = 0; idx < A.size(); idx++){
        (*P)[idx] = idx;
    }
    //-------------------------------

    // set up L
    //-------------------------------
    L.resize(A.size());
    for(unsigned long row_idx = 0; row_idx < A.size(); row_idx++){

        L[row_idx].resize(A.size());
        for(unsigned long col_idx = 0; col_idx < A.size(); col_idx++){

            if(row_idx == col_idx){
                L[row_idx][col_idx] = 1;
            } else {
                L[row_idx][col_idx] = 0;
            }
        }
    }
    //-------------------------------

    // set up U
    //-------------------------------
    U.resize(A.size());
    for(unsigned long row_idx = 0; row_idx < A.size(); row_idx++){

        U[row_idx].resize(A.size());
        for(unsigned long col_idx = 0; col_idx < A.size(); col_idx++){
            U[row_idx][col_idx] = (to) A[row_idx][col_idx];
        }
    }
    //-------------------------------

    // algorithm
    //-------------------------------
    for(unsigned long k = 0; k < A.size(); k++){

        auto max_row = get_max_U_idx(A[k], k);

        interchangeRow<to>(U, k, max_row, k, A.size());
        interchangeRow<to>(L, k, max_row, 0, k);

        auto tmp = (*P)[k]; (*P)[k] = (*P)[max_row]; (*P)[max_row] = tmp;

        for(unsigned long j = k+1; j < A.size(); j++){

            L[j][k] = U[j][k]/ U[k][k];

            for(unsigned long i = k; i < A.size(); i++){

                U[j][i]  = U[j][i] - (L[j][k] * U[k][i]);
            }
        }
    }
    //-------------------------------

    //ret.push_back(L);
    //ret.push_back(U);

    return ret;
}

template<typename T>
vector<T> fS(vector<vector<T>> L, vector<T> b){

    vector<T> x;
    x.resize(b.size());


    x[0] = b[0]/L[0][0];

    T sum = 0;

    for(unsigned long i = 1; i < b.size(); i++){

        sum = 0;
        for(unsigned long j = 0; j < i; j++){
            sum += (L[i][j] * x[j]);
        }

        x[i] = (b[i] - sum) / L[i][i];
    }

    return x;
}

template<typename T>
vector<T> bS(vector<vector<T>> U, vector<T> b){

    vector<T> x;
    x.resize(b.size());

    auto n_minus_one = b.size()-1;

    x[n_minus_one] = b[n_minus_one]/U[n_minus_one][n_minus_one];

    T sum = 0;

    for(unsigned long i = n_minus_one; i > 0;){

        i--;

        sum = 0;
        for(unsigned long j = n_minus_one; j > i; j--){

            sum += (U[i][j] * x[j]);
        }

        x[i] = (b[i] - sum) / U[i][i];
    }

    return x;
}
//-------------------------------