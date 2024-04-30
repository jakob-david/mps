//
// Created by Jakob on 30.04.24.
//

#include <random>
#include <vector>

using namespace std;

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