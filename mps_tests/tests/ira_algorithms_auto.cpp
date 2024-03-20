//
// Created by Jakob on 12.03.24.
//

#include "gtest/gtest.h"
#include <random>

#include "ira.h"
#include "../functions/functions.h"


TEST(solve_LU, auto_overprecision_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 14;        // the extra mantissa bits which are needed to achieve double precision.
    unsigned long start = 40;
    unsigned long number_of_tests = 40; // the number of test runs. Each run with a larger matrix.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {52 + precision, 11};

    for(unsigned long n = start; n <= number_of_tests; n++){

        ira IRA(n);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(u[0], u[1], new_A);
        //--------------------------------

        // Set up x_should;
        //--------------------------------
        vector<double> x_should;
        for(unsigned long i = 0 + 1; i <= n; i++){
            x_should.push_back((double) i);
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        unsigned long tmp;
        for(unsigned long i = 0; i < n; i++){
            tmp = 0;
            for(unsigned long j = 0; j < n; j++){
                tmp += (unsigned long) (x_should[j] * new_A[(n * i) + j]);
            }
            b.emplace_back(u[0], u[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.solve_LU(b, u);
        auto x_result = ira::mps_to_double(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        EXPECT_EQ(x_should, x_result);
        for(unsigned long i = 0; i < n; i++){
            EXPECT_EQ(should_value(x_should[i]), should_value(x_result[i]));
        }
        //--------------------------------

    }
}

TEST(solve_LU, auto_pverprecision_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 13;        // the extra mantissa bits which are needed to achieve double precision.
    unsigned long start = 40;
    unsigned long number_of_tests = 40; // the number of test runs. Each run with a larger matrix.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {23 + precision, 11};

    for(unsigned long n = start; n <= number_of_tests; n++){

        ira IRA(n);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(u[0], u[1], new_A);
        //--------------------------------

        // Set up x_should;
        //--------------------------------
        vector<float> x_should;
        for(unsigned long i = 0 + 1; i <= n; i++){
            x_should.push_back((float) i);
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        unsigned long tmp;
        for(unsigned long i = 0; i < n; i++){
            tmp = 0;
            for(unsigned long j = 0; j < n; j++){
                tmp += (unsigned long) (x_should[j] * new_A[(n * i) + j]);
            }
            b.emplace_back(u[0], u[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.solve_LU(b, u);
        auto x_result = ira::mps_to_float(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        EXPECT_EQ(x_should, x_result);
        for(unsigned long i = 0; i < n; i++){
            EXPECT_EQ(should_value(x_should[i]), should_value(x_result[i]));
        }
        //--------------------------------

    }
}

TEST(solve_LU, auto_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 43;           // the number of  mantissa bits which should be checked.
    unsigned long start = 40;               // the size of the first matrix which should be set.
    unsigned long number_of_tests = 40;     // the number of test runs. Each run with a larger matrix.
    unsigned long u[2] = {52, 11};  // the precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    for(unsigned long n = start; n <= number_of_tests; n++){

        ira IRA(n);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(u[0], u[1], new_A);
        //--------------------------------

        // Set up x_should;
        //--------------------------------
        vector<double> x_should;
        vector<mps> x_should_mps;
        for(unsigned long i = 0 + 1; i <= n; i++){
            x_should.push_back((double) i);
            x_should_mps.emplace_back(u[0], u[1], (double) i);
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        unsigned long tmp;
        for(unsigned long i = 0; i < n; i++){
            tmp = 0;
            for(unsigned long j = 0; j < n; j++){
                tmp += (unsigned long) (x_should[j] * new_A[(n * i) + j]);
            }
            b.emplace_back(u[0], u[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.solve_LU(b, u);
        //auto x_result = ira::mps_to_double(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < n; i++){

            auto result = x[i].check_precision(x_should_mps[i], precision);
            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should_mps[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(solve_LU, auto_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 15;           // the number of  mantissa bits which should be checked.
    unsigned long start = 40;               // the size of the first matrix which should be set.
    unsigned long number_of_tests = 40;     // the number of test runs. Each run with a larger matrix.
    unsigned long u[2] = {23, 8};  // the precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    for(unsigned long n = start; n <= number_of_tests; n++){

        ira IRA(n);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(u[0], u[1], new_A);
        //--------------------------------

        // Set up x_should;
        //--------------------------------
        vector<double> x_should;
        vector<mps> x_should_mps;
        for(unsigned long i = 0 + 1; i <= n; i++){
            x_should.push_back((double) i);
            x_should_mps.emplace_back(u[0], u[1], (double) i);
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        unsigned long tmp;
        for(unsigned long i = 0; i < n; i++){
            tmp = 0;
            for(unsigned long j = 0; j < n; j++){
                tmp += (unsigned long) (x_should[j] * new_A[(n * i) + j]);
            }
            b.emplace_back(u[0], u[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.solve_LU(b, u);
        //auto x_result = ira::mps_to_double(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < n; i++){

            auto result = x[i].check_precision(x_should_mps[i], precision);
            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should_mps[i].print() << endl;
            }
        }
        //--------------------------------

    }
}



TEST(solve_LU, random_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 9;           // The number of  mantissa bits which should be checked.
    unsigned long number_of_tests = 2;     // The number of test runs.
    unsigned long matrix_size = 30;         // The size of the system-matrix.
    unsigned long u[2] = {23, 8};  // The precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    for(unsigned long m = 0; m <= number_of_tests; m++){

        ira IRA(matrix_size);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix(u[0], u[1]);
        //--------------------------------

        // Set up x_should;
        // Set up x_should;
        //--------------------------------
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(-10.0, 10.0);

        vector<mps> x_should;
        for(unsigned long i = 0 + 1; i <= matrix_size; i++){
            x_should.emplace_back(u[0], u[1], dist(mt));
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        double tmp;
        for(unsigned long i = 0; i < matrix_size; i++){
            tmp = 0;
            for(unsigned long j = 0; j < matrix_size; j++){
                tmp += x_should[j].getValue() * IRA.getMatrixElement((matrix_size * i) + j).getValue();
            }
            b.emplace_back(u[0], u[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.solve_LU(b, u);
        //--------------------------------

        // perform tests
        //--------------------------------
        vector<unsigned long> precision_dist;
        for(unsigned long i = 0; i < matrix_size; i++){

            auto result = x[i].check_precision(x_should[i], precision);

            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(solve_LU, random_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 39;           // The number of  mantissa bits which should be checked.
    unsigned long number_of_tests = 2;     // The number of test runs.
    unsigned long matrix_size = 30;         // The size of the system-matrix.
    unsigned long u[2] = {52, 11};  // The precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    for(unsigned long m = 0; m <= number_of_tests; m++){

        ira IRA(matrix_size);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix(u[0], u[1]);
        //--------------------------------

        // Set up x_should;
        // Set up x_should;
        //--------------------------------
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(-10.0, 10.0);

        vector<mps> x_should;
        for(unsigned long i = 0 + 1; i <= matrix_size; i++){
            x_should.emplace_back(u[0], u[1], dist(mt));
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        double tmp;
        for(unsigned long i = 0; i < matrix_size; i++){
            tmp = 0;
            for(unsigned long j = 0; j < matrix_size; j++){
                tmp += x_should[j].getValue() * IRA.getMatrixElement((matrix_size * i) + j).getValue();
            }
            b.emplace_back(u[0], u[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.solve_LU(b, u);
        //--------------------------------

        // perform tests
        //--------------------------------
        vector<unsigned long> precision_dist;
        for(unsigned long i = 0; i < matrix_size; i++){

            auto result = x[i].check_precision(x_should[i], precision);

            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(solve_LU, random_distana_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long number_of_tests = 10;     // The number of test runs.
    unsigned long matrix_size = 20;         // The size of the system-matrix.
    unsigned long u[2] = {23, 8};  // The precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    vector<unsigned long> precision_dist(u[0], 0);

    for(unsigned long m = 0; m <= number_of_tests; m++){

        ira IRA(matrix_size);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix(u[0], u[1]);
        //--------------------------------

        // Set up x_should;
        //--------------------------------
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(-10.0, 10.0);

        vector<mps> x_should;
        for(unsigned long i = 0 + 1; i <= matrix_size; i++){
            x_should.emplace_back(u[0], u[1], dist(mt));
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        double tmp;
        for(unsigned long i = 0; i < matrix_size; i++){
            tmp = 0;
            for(unsigned long j = 0; j < matrix_size; j++){
                tmp += x_should[j].getValue() * IRA.getMatrixElement((matrix_size * i) + j).getValue();
            }
            b.emplace_back(u[0], u[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.solve_LU(b, u);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < matrix_size; i++){

            for(unsigned long p = u[0]; p > 0; p--){
                if(x[i].check_precision(x_should[i], p)){
                    precision_dist[u[0]-p]++;
                    break;
                }
            }
        }
        //--------------------------------

    }

    for(unsigned long i = 0; i < precision_dist.size(); i++){
        if(precision_dist[i] != 0){
            if(i < 10){
                cout << "precision  " << i << ": " << precision_dist[i] << endl;
            } else {
                cout << "precision " << i << ": " << precision_dist[i] << endl;
            }

        }
    }
}

TEST(solve_LU, random_distana_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long number_of_tests = 10;     // The number of test runs.
    unsigned long matrix_size = 20;         // The size of the system-matrix.
    unsigned long u[2] = {52, 11};  // The precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    vector<unsigned long> precision_dist(u[0], 0);

    for(unsigned long m = 0; m <= number_of_tests; m++){

        ira IRA(matrix_size);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix(u[0], u[1]);
        //--------------------------------

        // Set up x_should;
        //--------------------------------
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(-10.0, 10.0);

        vector<mps> x_should;
        for(unsigned long i = 0 + 1; i <= matrix_size; i++){
            x_should.emplace_back(u[0], u[1], dist(mt));
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        double tmp;
        for(unsigned long i = 0; i < matrix_size; i++){
            tmp = 0;
            for(unsigned long j = 0; j < matrix_size; j++){
                tmp += x_should[j].getValue() * IRA.getMatrixElement((matrix_size * i) + j).getValue();
            }
            b.emplace_back(u[0], u[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.solve_LU(b, u);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < matrix_size; i++){

            for(unsigned long p = u[0]; p > 0; p--){
                if(x[i].check_precision(x_should[i], p)){
                    precision_dist[u[0]-p]++;
                    break;
                }
            }
        }
        //--------------------------------

    }

    for(unsigned long i = 0; i < precision_dist.size(); i++){
        if(precision_dist[i] != 0){
            if(i < 10){
                cout << "precision  " << i << ": " << precision_dist[i] << endl;
            } else {
                cout << "precision " << i << ": " << precision_dist[i] << endl;
            }

        }
    }
}
