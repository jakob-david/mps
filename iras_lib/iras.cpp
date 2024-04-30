//
// Created by Jakob on 30.04.24.
//

#include <random>
#include <vector>

using namespace std;


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
vector<T> dotProduct(const vector<vector<T>> matrix, const vector<T> vec){

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
vector<vector<T>> dotProduct(const vector<vector<T>> A, const vector<vector<T>> B){

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
vector<to> convert(const vector<from> vec){

    vector<to> ret;

    for(unsigned long idx = 0; idx < vec.size(); idx++){
        ret.push_back((to) vec[idx]);
    }

    return ret;
}

template <typename from, typename to>
vector<vector<to>> convert(const vector<vector<from>> matrix){

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