//
// Created by Jakob on 12.03.24.
//

#include "gtest/gtest.h"

#include "ira.h"
#include "../functions/functions.h"

TEST(solve_LU, auto_1_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 14;        // the extra mantissa bits which are needed to achieve double precision.
    unsigned long start = 100;
    unsigned long number_of_tests = 100; // the number of test runs. Each run with a larger matrix.
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

TEST(solve_LU, auto_1_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 13;        // the extra mantissa bits which are needed to achieve double precision.
    unsigned long start = 100;
    unsigned long number_of_tests = 100; // the number of test runs. Each run with a larger matrix.
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


TEST(solve_LU, auto_2_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 41;        // the extra mantissa bits which are needed to achieve double precision.
    unsigned long start = 100;
    unsigned long number_of_tests = 100; // the number of test runs. Each run with a larger matrix.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {52, 11};

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

