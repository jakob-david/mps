//
// Created by Jakob on 30.04.24.
//

#ifndef HELPER_ALGORITHMS_H
#define HELPER_ALGORITHMS_H

#include <random>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;


// rounding
//-------------------------------
template<typename T>
T round(T value, T precision)
{
    return std::round(value / precision) * precision;
}

template<typename T>
vector<T> round(vector<T> vec, T precision)
{
    vector<T> ret;
    ret.resize(vec.size());

    for(unsigned long idx = 0; idx < vec.size(); idx++){
        ret[idx] = round(vec[idx], precision);
    }

    return ret;
}
//-------------------------------


// toString
//-------------------------------
template <typename T>
string toString(const vector<T>& vec, long precision){

    string ret;
    for(unsigned long idx = 0; idx < vec.size(); idx++){

        std::ostringstream out;
        out.precision(precision);
        out << std::fixed << vec[idx];

        //ret.append(std::move(out).str());

        auto number= std::move(out).str();
        bool negative_zero = false;
        if('-' == number[0] && '0' == number[1] && '.' == number[2]){
            negative_zero = true;
            for(long pos = 0; pos < precision; pos++){
                if('0' != number[3+pos]){
                    negative_zero = false;
                    break;
                }
            }
        }
        if(negative_zero){
            number = number.substr(1);
        }

        ret.append(number);
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


// operators
//-------------------------------
template<typename T>
vector<T> add(const vector<T>& a, const vector<T>& b){

    vector<T> result;
    result.resize(a.size());

    for(unsigned long idx = 0; idx < result.size(); idx++){
        result[idx] = a[idx] + b[idx];
    }

    return result;
}

template<typename T>
vector<T> subtract(const vector<T>& minuend, const vector<T>& subtrahend){

    vector<T> result;
    result.resize(minuend.size());

    for(unsigned long idx = 0; idx < result.size(); idx++){
        result[idx] = minuend[idx] - subtrahend[idx];
    }

    return result;
}

template <typename T>
vector<T> dotProduct(const vector<vector<T>>& matrix, const vector<T>& vec){

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
vector<vector<T>> dotProduct(const vector<vector<T>>& A, const vector<vector<T>>& B){

    vector<vector<T>> ret;
    ret.resize(A.size());

    for(unsigned long row_idx = 0; row_idx < A.size(); row_idx++){

        ret[row_idx].resize(A.size());
        for(unsigned long col_idx = 0; col_idx < A.size(); col_idx++){

            T sum = 0;
            for(unsigned long idx = 0; idx < A.size(); idx++){
                sum += A[row_idx][idx] * B[idx][col_idx];
            }
            ret[row_idx][col_idx] = sum;
        }
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


// PLU decomposition
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
vector<vector<vector<to>>> PLU(const vector<vector<from>>& A, vector<unsigned long>& P){

    vector<vector<vector<to>>> ret;
    ret.resize(2);
    vector<vector<to>>& L = ret[0];
    vector<vector<to>>& U = ret[1];


    // set up P
    //-------------------------------
    P.resize(A.size());
    for(unsigned long idx = 0; idx < A.size(); idx++){
        P[idx] = idx;
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

        auto tmp = P[k]; P[k] = P[max_row]; P[max_row] = tmp;

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
//-------------------------------


// fw and bw substitution
//-------------------------------
template<typename T>
vector<T> fS(const vector<vector<T>>& L, const vector<T>& b){

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
vector<T> bS(const vector<vector<T>>& U, const vector<T>& b){

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


// solver
//-------------------------------
template<typename T>
vector<T> permuteVector(const vector<unsigned long>& P, const vector<T>& x){

    vector<T> result;
    result.resize(x.size());

    for(unsigned long idx = 0; idx < x.size(); idx++){
        result[idx] = x[P[idx]];
    }

    return result;
}


template<typename T>
vector<T> directPLU(const vector<vector<T>>& A, const vector<T>& b){

    vector<unsigned long> P;
    auto LU = PLU<T, T>(A, P);


    auto x = permuteVector<T>(P, b);
    x = fS<T>(LU[0], x);
    x = bS<T>(LU[1], x);

    return x;
}

template<typename ul, typename u, typename ur>
vector<u> irPLU(const vector<vector<ur>>& A, const vector<ur>& b, unsigned long max_iter){

    vector<unsigned long> P;
    auto LU = PLU<ur, ul>(A, P);

    // calculate x_0
    //-------------------------------
    auto x_ul = permuteVector<ul>(P, convert<ur, ul>(b));
    x_ul = fS<ul>(LU[0], x_ul);
    x_ul = bS<ul>(LU[1], x_ul);
    auto x_u = convert<ul, u>(x_ul);
    //-------------------------------


    for(unsigned long iter = 0; iter < max_iter; iter++){

        // calculate: r_i = b − A * x_i
        // in precision: ur
        //-------------------------------
        auto x_in_ur = convert<u, ur>(x_u);
        auto b_approx = dotProduct<ur>(A, x_in_ur);
        auto r_ur = subtract<ur>(b, b_approx);
        //-------------------------------

        // solve: A * d_i = r_i
        // in precision: ul
        //-------------------------------
        auto r_ul = convert<ur, ul>(r_ur);
        r_ul = permuteVector<ul>(P, r_ul);
        auto d = fS<ul>(LU[0], r_ul);
        d = bS<ul>(LU[1], d);
        //-------------------------------

        // calculate: x_i+1 = x_i + d_i i
        // n precision u.
        //-------------------------------
        auto d_u = convert<ul, u>(d);
        x_u = add<u>(x_u, d_u);
        //-------------------------------
    }

    return x_u;
}
//-------------------------------

#endif // HELPER_ALGORITHMS_H