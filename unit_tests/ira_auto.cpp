//
// Created by Jakob on 12.03.24.
//

#include "gtest/gtest.h"

#include "ira.h"
#include "helper_functions.h"

#include <random>


TEST(directPLU, auto_overprecision_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 14;        // the extra mantissa bits which are needed to achieve double precision.
    unsigned long start = 35;
    unsigned long number_of_tests = 35; // the number of test runs. Each run with a larger matrix.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {52 + precision, 11};

    for(unsigned long n = start; n <= number_of_tests; n++){

        ira IRA(n, u[0], u[1]);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(new_A);
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
        auto x = IRA.directPLU(b);
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

TEST(directPLU, auto_overprecision_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 13;        // the extra mantissa bits which are needed to achieve double precision.
    unsigned long start = 35;
    unsigned long number_of_tests = 35; // the number of test runs. Each run with a larger matrix.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {23 + precision, 11};

    for(unsigned long n = start; n <= number_of_tests; n++){

        ira IRA(n, u[0], u[1]);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(new_A);
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
        auto x = IRA.directPLU(b);
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

TEST(directPLU, auto_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 43;           // the number of  mantissa bits which should be checked.
    unsigned long start = 35;               // the size of the first matrix which should be set.
    unsigned long number_of_tests = 35;     // the number of test runs. Each run with a larger matrix.
    unsigned long u[2] = {52, 11};  // the precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    for(unsigned long n = start; n <= number_of_tests; n++){

        ira IRA(n, u[0], u[1]);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(new_A);
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
        auto x = IRA.directPLU(b);
        //auto x_result = ira::mps_to_double(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < n; i++){

            auto result = x[i].checkPrecision(x_should_mps[i], precision);
            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should_mps[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(directPLU, auto_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 15;           // the number of  mantissa bits which should be checked.
    unsigned long start = 35;               // the size of the first matrix which should be set.
    unsigned long number_of_tests = 35;     // the number of test runs. Each run with a larger matrix.
    unsigned long u[2] = {23, 8};  // the precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    for(unsigned long n = start; n <= number_of_tests; n++){

        ira IRA(n, u[0], u[1]);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(new_A);
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
        auto x = IRA.directPLU(b);
        //auto x_result = ira::mps_to_double(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < n; i++){

            auto result = x[i].checkPrecision(x_should_mps[i], precision);
            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should_mps[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(directPLU, random_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 5;           // The number of  mantissa bits which should be checked.
    unsigned long number_of_tests = 2;     // The number of test runs.
    unsigned long matrix_size = 10;         // The size of the system-matrix.
    unsigned long u[2] = {23, 8};  // The precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    for(unsigned long m = 0; m <= number_of_tests; m++){

        ira IRA(matrix_size, u[0], u[1]);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix();
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
        auto x = IRA.directPLU(b);
        //--------------------------------

        // perform tests
        //--------------------------------
        vector<unsigned long> precision_dist;
        for(unsigned long i = 0; i < matrix_size; i++){

            auto result = x[i].checkPrecision(x_should[i], precision);

            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(directPLU, random_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 35;           // The number of  mantissa bits which should be checked.
    unsigned long number_of_tests = 2;     // The number of test runs.
    unsigned long matrix_size = 10;         // The size of the system-matrix.
    unsigned long u[2] = {52, 11};  // The precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    for(unsigned long m = 0; m <= number_of_tests; m++){

        ira IRA(matrix_size, u[0], u[1]);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix();
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
        auto x = IRA.directPLU(b);
        //--------------------------------

        // perform tests
        //--------------------------------
        vector<unsigned long> precision_dist;
        for(unsigned long i = 0; i < matrix_size; i++){

            auto result = x[i].checkPrecision(x_should[i], precision);

            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(directPLU, random_distana_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long number_of_tests = 10;     // The number of test runs.
    unsigned long matrix_size = 20;         // The size of the system-matrix.
    unsigned long u[2] = {23, 8};  // The precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    vector<unsigned long> precision_dist(u[0], 0);

    for(unsigned long m = 0; m <= number_of_tests; m++){

        ira IRA(matrix_size, u[0], u[1]);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix();
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
        auto x = IRA.directPLU(b);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < matrix_size; i++){

            for(unsigned long p = u[0]; p > 0; p--){
                if(x[i].checkPrecision(x_should[i], p)){
                    precision_dist[u[0]-p]++;
                    break;
                }
            }
        }
        //--------------------------------

    }

    /*
    for(unsigned long i = 0; i < precision_dist.size(); i++){
        if(precision_dist[i] != 0){
            if(i < 10){
                cout << "precision  " << i << ": " << precision_dist[i] << endl;
            } else {
                cout << "precision " << i << ": " << precision_dist[i] << endl;
            }

        }
    }
    */
}

TEST(directPLU, random_distana_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long number_of_tests = 10;     // The number of test runs.
    unsigned long matrix_size = 20;         // The size of the system-matrix.
    unsigned long u[2] = {52, 11};  // The precision of the mps objects.
    //------------------------------------------------------------------------------------------------------

    vector<unsigned long> precision_dist(u[0], 0);

    for(unsigned long m = 0; m <= number_of_tests; m++){

        ira IRA(matrix_size, u[0], u[1]);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix();
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
        auto x = IRA.directPLU(b);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < matrix_size; i++){

            for(unsigned long p = u[0]; p > 0; p--){
                if(x[i].checkPrecision(x_should[i], p)){
                    precision_dist[u[0]-p]++;
                    break;
                }
            }
        }
        //--------------------------------

    }

    /*
    for(unsigned long i = 0; i < precision_dist.size(); i++){
        if(precision_dist[i] != 0){
            if(i < 10){
                cout << "precision  " << i << ": " << precision_dist[i] << endl;
            } else {
                cout << "precision " << i << ": " << precision_dist[i] << endl;
            }

        }
    }
    */
}

TEST(directPLU, random_LUcompare_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long number_of_tests = 1;      // The number of test runs.
    unsigned long matrix_size = 30;             // The size of the system-matrix.
    //------------------------------------------------------------------------------------------------------

    for(unsigned long m = 0; m <= number_of_tests; m++){

        unsigned long u[2] = {52, 11};
        ira IRA(matrix_size, u[0], u[1]);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix();
        //--------------------------------

        // Set up x_should
        //--------------------------------
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(-10.0, 10.0);

        vector<mps> x_should;
        for(unsigned long i = 0 + 1; i <= matrix_size; i++){
            x_should.emplace_back(52, 11, dist(mt));
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
            b.emplace_back(52, 11, tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x_result = IRA.directPLU(b);
        auto x_should_double = IRA.solveLU_double(ira::mps_to_double(b));
        //--------------------------------

        // perform tests
        //--------------------------------
        vector<unsigned long> precision_dist;
        for(unsigned long i = 0; i < matrix_size; i++){
            EXPECT_EQ(x_should_double[i], x_result[i].getValue());
            EXPECT_EQ(should_value(x_should_double[i]), x_result[i].print());
        }
        //--------------------------------
    }
}





TEST(irPLU, auto_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 51;                // the number of  mantissa bits which should be checked.
    unsigned long start_matrix_size = 35;
    unsigned long last_matrix_size = 35;         // the number of test runs. Each run with a larger matrix.

    unsigned long ul[2] = { 23, 11};    // precision: LU
    unsigned long u[2] = {52, 11};      // precision: working
    unsigned long ur[2] = {60, 11};     // precision: A
    //------------------------------------------------------------------------------------------------------


    for(unsigned long n = start_matrix_size; n <= last_matrix_size; n++){

        ira IRA(n, ur[0], ur[1]);
        IRA.setWorkingPrecision(u[0], u[1]);
        IRA.setLowerPrecision(ul[0], ul[1]);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(new_A);
        //--------------------------------

         // Set up x_should;
        //--------------------------------
        vector<double> x_should_d;
        for(unsigned long i = 0 + 1; i <= n; i++){
            x_should_d.push_back((double) i);
        }
        auto x_should = ira::double_to_mps(u[0], u[1], x_should_d);
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        unsigned long tmp;
        for(unsigned long i = 0; i < n; i++){
            tmp = 0;
            for(unsigned long j = 0; j < n; j++){
                tmp += (unsigned long) (x_should_d[j] * new_A[(n * i) + j]);
            }
            b.emplace_back(ur[0], ur[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.irPLU(b);
        auto x_result = ira::mps_to_double(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < x.size(); i++){

            auto result = x[i].checkPrecision(x_should[i], precision);
            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(irPLU, auto_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 21;                // the number of  mantissa bits which should be checked.
    unsigned long start_matrix_size = 35;
    unsigned long last_matrix_size = 35;         // the number of test runs. Each run with a larger matrix.

    unsigned long ul[2] = { 12, 8};    // precision: LU
    unsigned long u[2] = {23, 8};       // precision: working
    unsigned long ur[2] = {30, 8};     // precision: A
    //------------------------------------------------------------------------------------------------------


    for(unsigned long n = start_matrix_size; n <= last_matrix_size; n++){

        ira IRA(n, ur[0], ur[1]);
        IRA.setWorkingPrecision(u[0], u[1]);
        IRA.setLowerPrecision(ul[0], ul[1]);

        // Set up A
        //--------------------------------
        vector<double> new_A;
        new_A.reserve(n*n);
        for(unsigned long i = 0; i < n; i++){
            for(unsigned long j = 0; j < n; j++){
                new_A.push_back((double) ((j+i)%n));
            }
        }
        IRA.setMatrix(new_A);
        //--------------------------------

        // Set up x_should;
        //--------------------------------
        vector<double> x_should_d;
        for(unsigned long i = 0 + 1; i <= n; i++){
            x_should_d.push_back((double) i);
        }
        auto x_should = ira::double_to_mps(u[0], u[1], x_should_d);
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        unsigned long tmp;
        for(unsigned long i = 0; i < n; i++){
            tmp = 0;
            for(unsigned long j = 0; j < n; j++){
                tmp += (unsigned long) (x_should_d[j] * new_A[(n * i) + j]);
            }
            b.emplace_back(ur[0], ur[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.irPLU(b);
        auto x_result = ira::mps_to_double(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < x.size(); i++){

            auto result = x[i].checkPrecision(x_should[i], precision);
            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(irPLU, random_double){

    //------------------------------------------------------------------------------------------------------
    unsigned long n_max = 15;

    unsigned long precision = 34;                // the number of  mantissa bits which should be checked.
    unsigned long start_matrix_size = 35;
    unsigned long last_matrix_size = 35;         // the number of test runs. Each run with a larger matrix.

    unsigned long ul[2] = { 23, 11};    // precision: LU
    unsigned long u[2] = {52, 11};      // precision: working
    unsigned long ur[2] = {60, 11};     // precision: A
    //------------------------------------------------------------------------------------------------------


    for(unsigned long n = start_matrix_size; n <= last_matrix_size; n++){

        ira IRA(n, ur[0], ur[1]);
        IRA.setWorkingPrecision(u[0], u[1]);
        IRA.setLowerPrecision(ul[0], ul[1]);
        IRA.setMaxIter(n_max);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix();
        //--------------------------------

        // Set up x_should;
        //--------------------------------
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(-10.0, 10.0);

        vector<mps> x_should;
        for(unsigned long i = 0 + 1; i <= n; i++){
            x_should.emplace_back(u[0], u[1], dist(mt));
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        double tmp;
        for(unsigned long i = 0; i < n; i++){
            tmp = 0;
            for(unsigned long j = 0; j < n; j++){
                tmp += x_should[j].getValue() * IRA.getMatrixElement((n * i) + j).getValue();
            }
            b.emplace_back(ur[0], ur[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.irPLU(b);
        auto x_result = ira::mps_to_double(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < x.size(); i++){

            auto result = x[i].checkPrecision(x_should[i], precision);
            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should[i].print() << endl;
            }
        }
        //--------------------------------

    }
}

TEST(irPLU, random_float){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 10;                // the number of  mantissa bits which should be checked.
    unsigned long start_matrix_size = 35;
    unsigned long last_matrix_size = 35;         // the number of test runs. Each run with a larger matrix.

    unsigned long ul[2] = { 12, 8};     // precision: LU
    unsigned long u[2] = {23, 8};       // precision: working
    unsigned long ur[2] = {30, 8};      // precision: A
    //------------------------------------------------------------------------------------------------------


    for(unsigned long n = start_matrix_size; n <= last_matrix_size; n++){

        ira IRA(n, ur[0], ur[1]);
        IRA.setWorkingPrecision(u[0], u[1]);
        IRA.setLowerPrecision(ul[0], ul[1]);

        // Set up A
        //--------------------------------
        IRA.setRandomMatrix();
        //--------------------------------

        // Set up x_should;
        //--------------------------------
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(-10.0, 10.0);

        vector<mps> x_should;
        for(unsigned long i = 0 + 1; i <= n; i++){
            x_should.emplace_back(u[0], u[1], dist(mt));
        }
        //--------------------------------

        // Set up b
        //--------------------------------
        vector<mps> b;
        double tmp;
        for(unsigned long i = 0; i < n; i++){
            tmp = 0;
            for(unsigned long j = 0; j < n; j++){
                tmp += x_should[j].getValue() * IRA.getMatrixElement((n * i) + j).getValue();
            }
            b.emplace_back(ur[0], ur[1], tmp);
        }
        //--------------------------------

        // solve system
        //--------------------------------
        auto x = IRA.irPLU(b);
        auto x_result = ira::mps_to_double(x);
        //--------------------------------

        // perform tests
        //--------------------------------
        for(unsigned long i = 0; i < x.size(); i++){

            auto result = x[i].checkPrecision(x_should[i], precision);
            EXPECT_TRUE(result);

            if(!result){
                cout << "x_i:   " << x[i].print() << endl;
                cout << "x_i_s  " << x_should[i].print() << endl;
            }
        }
        //--------------------------------

    }
}