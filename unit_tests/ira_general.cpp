//
// Created by Jakob on 12.03.24.
//

#include "gtest/gtest.h"

#include "ira.h"


// constructor
// -------------------------------------
TEST(Constructor, simple_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long dimension = 2;

    ira IRA(dimension, mantissa_length, exponent_length);

    auto result_1 = IRA.getUpperPrecision();
    auto result_2 = IRA.getDimension();
    auto result_3 = IRA.get1DMatrixSize();

    auto random_range = IRA.getRandomRange();
    auto sparsity_rate = IRA.getSparsityRate();

    EXPECT_EQ(mantissa_length, result_1[0]);
    EXPECT_EQ(exponent_length, result_1[1]);
    EXPECT_EQ(dimension, result_2);
    EXPECT_EQ(dimension * dimension, result_3);

    EXPECT_EQ(-10, random_range[0]);
    EXPECT_EQ(10, random_range[1]);
    EXPECT_EQ(0, sparsity_rate);
}

TEST(Constructor, exception_wrong_input) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long dimension = 2;

    EXPECT_ANY_THROW(ira IRA(dimension, 0, exponent_length));
    EXPECT_ANY_THROW(ira IRA(dimension, mantissa_length, 1));
}


// parameter setter and parameter getter
// -------------------------------------
TEST(RandomRange, simple_1) {

    double lower_bound = -345.0;
    double upper_bound = 5634.0;

    ira IRA(2, 23, 8);
    IRA.setRandomRange(lower_bound, upper_bound);

    auto result = IRA.getRandomRange();

    EXPECT_EQ(lower_bound, result[0]);
    EXPECT_EQ(upper_bound, result[1]);
}

TEST(RandomRange, exception_1) {

    double lower_bound = 345.0;
    double upper_bound = -5634.0;

    ira IRA(2, 23, 8);

    EXPECT_ANY_THROW(IRA.setRandomRange(lower_bound, upper_bound));
}

TEST(SparsityRate, simple_1) {

    double sparsity_rate = 0.45;

    ira IRA(2, 23, 8);
    IRA.setSparsityRate(sparsity_rate);

    auto result = IRA.getSparsityRate();

    EXPECT_EQ(sparsity_rate, result);
}

TEST(SparsityRate, exception_wrong_input) {

    ira IRA(2, 23, 8);

    EXPECT_ANY_THROW(IRA.setSparsityRate(0.91));
    EXPECT_ANY_THROW(IRA.setSparsityRate(-0.01));
}

TEST(MaxIter, simple_1) {

    unsigned long max_iter = 24;

    ira IRA(2, 23, 8);
    IRA.setMaxIter(max_iter);

    auto result = IRA.getMaxIter();

    EXPECT_EQ(max_iter, result);
}

TEST(Dimension, simple_1) {

    unsigned long dimension = 4;

    ira IRA(2, 23, 8);
    IRA.setDimension(dimension);

    auto result_1 = IRA.getDimension();
    auto result_2 = IRA.get1DMatrixSize();

    EXPECT_EQ(dimension, result_1);
    EXPECT_EQ(dimension * dimension, result_2);
}

TEST(LowerPrecision, simple_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(2, 2, 2);
    IRA.setLowerPrecision(mantissa_length, exponent_length);

    auto result = IRA.getLowerPrecision();

    EXPECT_EQ(mantissa_length, result[0]);
    EXPECT_EQ(exponent_length, result[1]);
}

TEST(LowerPrecision, simple_2) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(2, 2, 2);
    IRA.setLowerPrecisionMantissa(mantissa_length);
    IRA.setLowerPrecisionExponent(exponent_length);

    auto result = IRA.getLowerPrecision();

    EXPECT_EQ(mantissa_length, result[0]);
    EXPECT_EQ(exponent_length, result[1]);
}

TEST(LowerPrecision, exception_wrong_input_1) {

    ira IRA(2, 2, 2);

    EXPECT_ANY_THROW(IRA.setLowerPrecision(0, 12));
    EXPECT_ANY_THROW(IRA.setLowerPrecision(12, 1));
}

TEST(LowerPrecision, exception_wrong_input_2) {

    ira IRA(2, 2, 2);

    EXPECT_ANY_THROW(IRA.setLowerPrecisionMantissa(0));
    EXPECT_ANY_THROW(IRA.setLowerPrecisionExponent(1));
}

TEST(WorkingPrecision, simple_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(2, 2, 2);
    IRA.setWorkingPrecision(mantissa_length, exponent_length);

    auto result = IRA.getWorkingPrecision();

    EXPECT_EQ(mantissa_length, result[0]);
    EXPECT_EQ(exponent_length, result[1]);
}

TEST(WorkingPrecision, simple_2) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(2, 2, 2);
    IRA.setWorkingPrecisionMantissa(mantissa_length);
    IRA.setWorkingPrecisionExponent(exponent_length);

    auto result = IRA.getWorkingPrecision();

    EXPECT_EQ(mantissa_length, result[0]);
    EXPECT_EQ(exponent_length, result[1]);
}

TEST(WorkingPrecision, exception_wrong_input_1) {

    ira IRA(2, 2, 2);

    EXPECT_ANY_THROW(IRA.setWorkingPrecision(0, 12));
    EXPECT_ANY_THROW(IRA.setWorkingPrecision(12, 1));
}

TEST(WorkingPrecision, exception_wrong_input_2) {

    ira IRA(2, 2, 2);

    EXPECT_ANY_THROW(IRA.setWorkingPrecisionMantissa(0));
    EXPECT_ANY_THROW(IRA.setWorkingPrecisionExponent(1));
}

TEST(UpperPrecision, simple_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(2, 2, 2);
    IRA.setUpperPrecision(mantissa_length, exponent_length);

    auto result = IRA.getUpperPrecision();

    EXPECT_EQ(mantissa_length, result[0]);
    EXPECT_EQ(exponent_length, result[1]);
}

TEST(UpperPrecision, simple_2) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(2, 2, 2);
    IRA.setUpperPrecision(mantissa_length, exponent_length);
    IRA.setUpperPrecisionMantissa(mantissa_length);
    IRA.setUpperPrecisionExponent(exponent_length);

    auto result = IRA.getUpperPrecision();

    EXPECT_EQ(mantissa_length, result[0]);
    EXPECT_EQ(exponent_length, result[1]);
}

TEST(UpperPrecision, exception_wrong_input_1) {

    ira IRA(2, 2, 2);

    EXPECT_ANY_THROW(IRA.setUpperPrecision(0, 12));
    EXPECT_ANY_THROW(IRA.setUpperPrecision(12, 1));
}

TEST(UpperPrecision, exception_wrong_input_2) {

    ira IRA(2, 2, 2);

    EXPECT_ANY_THROW(IRA.setUpperPrecisionMantissa(0));
    EXPECT_ANY_THROW(IRA.setUpperPrecisionExponent(1));
}

TEST(ExpectedResult, simple_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    vector<mps> expected_result_mps;
    expected_result_mps.emplace_back(mantissa_length, exponent_length, 4);
    expected_result_mps.emplace_back(mantissa_length, exponent_length, -2);

    vector<double> expected_result_double = ira::mps_to_double(expected_result_mps);
    IRA.setExpectedResult(expected_result_mps);
    ira::cast(expected_result_mps, u_m_l, u_m_e);
    ira::cast(expected_result_mps, mantissa_length, exponent_length);

    EXPECT_EQ(expected_result_mps, IRA.getExpectedResult_mps());
    EXPECT_EQ(expected_result_double, IRA.getExpectedResult_double());
}

TEST(ExpectedResult, correct_rounding){

    unsigned long ur_m_l = 7;
    unsigned long u_m_l = 5;
    unsigned long exponent_length = 10;
    unsigned long size = 2;

    ira IRA(size, ur_m_l, exponent_length);
    IRA.setWorkingPrecision(u_m_l, exponent_length);

    vector<double> x_d = {8, 8};
    auto x_mps = ira::double_to_mps(ur_m_l, exponent_length, x_d);
    vector<bool> m_zero = {1, 0, 0, 0, 1, 0, 1};
    x_mps[0].setMantissa(m_zero);
    vector<bool> m_one = {1, 0, 0, 0, 1, 1, 1};
    x_mps[0].setMantissa(m_one);

    auto xs_mps = ira::double_to_mps(ur_m_l, exponent_length, x_d);
    vector<bool> ms_zero = {1, 0, 0, 0, 1, 0, 0};
    xs_mps[0].setMantissa(ms_zero);
    vector<bool> ms_one = {1, 0, 0, 1, 0, 0, 0};
    xs_mps[0].setMantissa(ms_one);

    IRA.setExpectedResult(x_mps);

    auto result = IRA.getExpectedResult_mps();

    for(unsigned long i = 0; i < size; i++){
        EXPECT_EQ(xs_mps[i].print(), result[i].print());
    }
}

TEST(ExpectedResult, exception_empty_vector) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    vector<mps> expected_result_mps;

    EXPECT_ANY_THROW(IRA.setExpectedResult(expected_result_mps));
}

TEST(ExpectedResult, exception_wrong_dimensions) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    vector<mps> expected_result_mps;
    expected_result_mps.emplace_back(mantissa_length, exponent_length, 4);
    expected_result_mps.emplace_back(mantissa_length, exponent_length, -2);
    expected_result_mps.emplace_back(mantissa_length, exponent_length, -3);

    EXPECT_ANY_THROW(IRA.setExpectedResult(expected_result_mps));
}

TEST(ExpectedResult, exception_expected_result_not_set) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    EXPECT_ANY_THROW(auto tmp_1 = IRA.getExpectedResult_mps());
    EXPECT_ANY_THROW(auto tmp_2 = IRA.getExpectedResult_double());
}

TEST(ExpectedResult, exception_working_precision_not_set) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    EXPECT_ANY_THROW(auto tmp_1 = IRA.getExpectedResult_mps());
    EXPECT_ANY_THROW(auto tmp_2 = IRA.getExpectedResult_double());
}

TEST(ExpectedError, simple_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    vector<mps> expected_result_mps;
    expected_result_mps.emplace_back(mantissa_length, exponent_length, 4);
    expected_result_mps.emplace_back(mantissa_length, exponent_length, -2);
    IRA.setExpectedResult(expected_result_mps);

    mps expected_error(mantissa_length, exponent_length, 0.01);
    IRA.setExpectedError(expected_error);

    EXPECT_EQ(expected_error, IRA.getExpectedError());
}

TEST(ExpectedError, exception_no_expected_result_set) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    mps expected_error(mantissa_length, exponent_length, 0.01);

    EXPECT_ANY_THROW(IRA.setExpectedError(expected_error));
}

TEST(ExpectedError, exception_no_expected_precision_set) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    vector<mps> expected_result_mps;
    expected_result_mps.emplace_back(mantissa_length, exponent_length, 4);
    expected_result_mps.emplace_back(mantissa_length, exponent_length, -2);
    IRA.setExpectedResult(expected_result_mps);

    EXPECT_ANY_THROW(auto tp = IRA.getExpectedError());
}

TEST(ExpectedPrecision, simple_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    vector<mps> expected_result_mps;
    expected_result_mps.emplace_back(mantissa_length, exponent_length, 4);
    expected_result_mps.emplace_back(mantissa_length, exponent_length, -2);
    IRA.setExpectedResult(expected_result_mps);

    mps expected_precision(mantissa_length, exponent_length, 24);
    IRA.setExpectedPrecision(expected_precision);

    EXPECT_EQ(expected_precision, IRA.getExpectedPrecision());
}

TEST(ExpectedPrecision, exception_no_expected_result_set) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    mps expected_precision(mantissa_length, exponent_length, 24);

    EXPECT_ANY_THROW(IRA.setExpectedPrecision(expected_precision));
}

TEST(ExpectedPrecision, exception_no_expected_precision_set) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;
    unsigned long u_m_l = 12;
    unsigned long u_m_e = 5;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setWorkingPrecision(u_m_l, u_m_e);

    vector<mps> expected_result_mps;
    expected_result_mps.emplace_back(mantissa_length, exponent_length, 4);
    expected_result_mps.emplace_back(mantissa_length, exponent_length, -2);
    IRA.setExpectedResult(expected_result_mps);

    EXPECT_ANY_THROW(auto tp = IRA.getExpectedPrecision());
}




// setter for matrix
// -------------------------------------
TEST(unitary_matrix, init_2x2) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setUnitaryMatrix();

    EXPECT_EQ(IRA.toString('A'), "1.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).getMantisseLength());
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).getExponentLength());
}

TEST(unitary_matrix, init_3x3) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setUnitaryMatrix();

    EXPECT_EQ(IRA.toString('A'), "1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).getMantisseLength());
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).getExponentLength());
}

TEST(custom_matrix, init_2x2) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40 };

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_EQ(IRA.toString('A'), "10.000000, 20.000000, 30.000000, 40.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).getMantisseLength());
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).getExponentLength());
}

TEST(custom_matrix, init_3x3) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_EQ(IRA.toString('A'), "10.000000, 20.000000, 30.000000, 40.000000, 50.000000, 60.000000, 70.000000, 80.000000, 90.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).getMantisseLength());
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).getExponentLength());
}

TEST(custom_matrix, new_matrix_too_large) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    ira IRA(3, mantissa_length, exponent_length);

    bool test = false;

    try
    {
        IRA.setMatrix(new_matrix);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(custom_matrix, new_matrix_too_small) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80};

    ira IRA(3, mantissa_length, exponent_length);

    bool test = false;

    try
    {
        IRA.setMatrix(new_matrix);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(setRandomMatrix, simple_1) {

    unsigned long n = 3;

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(n, mantissa_length, exponent_length);
    IRA.setRandomMatrix();

    for(unsigned long i = 0; i < n * n; i++){
        EXPECT_TRUE(IRA.getMatrixElement(i).getValue() <= 10);
        EXPECT_TRUE(IRA.getMatrixElement(i).getValue() >= -10);
    }

    bool test = false;
    try
    {
        auto tmp = IRA.getMatrixElement(n*n+1);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_TRUE(test);
}

TEST(setRandomMatrix, simple_2) {

    unsigned long n = 6;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(n, mantissa_length, exponent_length);
    IRA.setRandomMatrix();

    for(unsigned long i = 0; i < n * n; i++){
        EXPECT_TRUE(IRA.getMatrixElement(i).getValue() <= 10);
        EXPECT_TRUE(IRA.getMatrixElement(i).getValue() >= -10);
    }

    bool test = false;
    try
    {
        auto tmp = IRA.getMatrixElement(n*n+1);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_TRUE(test);
}

TEST(setRandomMatrix, uniqueness_1) {

    unsigned long n = 6;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA_1(n, mantissa_length, exponent_length);
    ira IRA_2(n, mantissa_length, exponent_length);
    IRA_1.setRandomMatrix();
    IRA_2.setRandomMatrix();

    for(unsigned long i = 0; i < n * n; i++){
        EXPECT_TRUE(IRA_1.getMatrixElement(i).getValue() <= 10);
        EXPECT_TRUE(IRA_1.getMatrixElement(i).getValue() >= -10);
        EXPECT_TRUE(IRA_2.getMatrixElement(i).getValue() <= 10);
        EXPECT_TRUE(IRA_2.getMatrixElement(i).getValue() >= -10);
        EXPECT_TRUE(IRA_2.getMatrixElement(i).getValue() != IRA_1.getMatrixElement(i).getValue());
    }

    bool test = false;
    try
    {
        auto tmp = IRA_1.getMatrixElement(n*n+1);
        tmp = IRA_2.getMatrixElement(n*n+1);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_TRUE(test);
}

TEST(setRandomMatrix, sparcity_1){

    unsigned long n = 15;
    double sparsity_rate = 0.5;

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(n, mantissa_length, exponent_length);
    IRA.setSparsityRate(sparsity_rate);
    IRA.setRandomMatrix();

    unsigned long sum = 0;
    for(unsigned long idx = 0; idx < (n*n); idx++){
        if(0 == IRA.getMatrixElement(idx).getValue()){
            sum++;
        }
    }
    double actual_rate = (double) sum / ((double)(n*n));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.1);

    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
            if(0 != IRA.getMatrixElement(row_idx * IRA.getDimension() + column_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
            if(0 != IRA.getMatrixElement(column_idx * IRA.getDimension() + row_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(setRandomMatrix, sparcity_2){

    unsigned long n = 15;
    double sparsity_rate = 0.25;

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(n, mantissa_length, exponent_length);
    IRA.setSparsityRate(sparsity_rate);
    IRA.setRandomMatrix();

    unsigned long sum = 0;
    for(unsigned long idx = 0; idx < (n*n); idx++){
        if(0 == IRA.getMatrixElement(idx).getValue()){
            sum++;
        }
    }
    double actual_rate = (double) sum / ((double)(n*n));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.1);


    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
            if(0 != IRA.getMatrixElement(row_idx * IRA.getDimension() + column_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
            if(0 != IRA.getMatrixElement(column_idx * IRA.getDimension() + row_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(setRandomMatrix, sparcity_3){

    unsigned long n = 15;
    double sparsity_rate = 0.75;

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(n, mantissa_length, exponent_length);
    IRA.setSparsityRate(sparsity_rate);
    IRA.setRandomMatrix();

    unsigned long sum = 0;
    for(unsigned long idx = 0; idx < (n*n); idx++){
        if(0 == IRA.getMatrixElement(idx).getValue()){
            sum++;
        }
    }
    double actual_rate = (double) sum / ((double)(n*n));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.07);


    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
            if(0 != IRA.getMatrixElement(row_idx * IRA.getDimension() + column_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
            if(0 != IRA.getMatrixElement(column_idx * IRA.getDimension() + row_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(setRandomMatrix, sparcity_4){

    unsigned long n = 15;
    double sparsity_rate = 0.9;

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(n, mantissa_length, exponent_length);
    IRA.setSparsityRate(sparsity_rate);
    IRA.setRandomMatrix();

    unsigned long sum = 0;
    for(unsigned long idx = 0; idx < (n*n); idx++){
        if(0 == IRA.getMatrixElement(idx).getValue()){
            sum++;
        }
    }
    double actual_rate = (double) sum / ((double)(n*n));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.07);


    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
            if(0 != IRA.getMatrixElement(row_idx * IRA.getDimension() + column_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
            if(0 != IRA.getMatrixElement(column_idx * IRA.getDimension() + row_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(setRandomMatrix, sparcity_5){

    unsigned long n = 15;
    double sparsity_rate = 0.8;

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(n, mantissa_length, exponent_length);
    IRA.setSparsityRate(sparsity_rate);
    IRA.setRandomMatrix();

    unsigned long sum = 0;
    for(unsigned long idx = 0; idx < (n*n); idx++){
        if(0 == IRA.getMatrixElement(idx).getValue()){
            sum++;
        }
    }
    double actual_rate = (double) sum / ((double)(n*n));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.07);


    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
            if(0 != IRA.getMatrixElement(row_idx * IRA.getDimension() + column_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
            if(0 != IRA.getMatrixElement(column_idx * IRA.getDimension() + row_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(setRandomMatrix, sparcity_6){

    unsigned long n = 15;
    double sparsity_rate = 0;

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(n, mantissa_length, exponent_length);
    IRA.setSparsityRate(sparsity_rate);
    IRA.setRandomMatrix();

    unsigned long sum = 0;
    for(unsigned long idx = 0; idx < (n*n); idx++){
        if(0 == IRA.getMatrixElement(idx).getValue()){
            sum++;
        }
    }
    double actual_rate = (double) sum / ((double)(n*n));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.07);


    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
            if(0 != IRA.getMatrixElement(row_idx * IRA.getDimension() + column_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < IRA.getDimension(); column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < IRA.getDimension(); row_idx++){
            if(0 != IRA.getMatrixElement(column_idx * IRA.getDimension() + row_idx).getValue()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(getMatrixElement, idx_too_large) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    bool test = false;

    try
    {
        auto tmp = IRA.getMatrixElement(9);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(getMatrixElement, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    auto tmp = IRA.getMatrixElement(8);

    EXPECT_EQ("90.00", tmp.toString(2));
}

TEST(setL, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_L{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);

    IRA.setL(new_L);


    EXPECT_EQ("10, 20, 30, 40, 50, 60, 70, 80, 90", IRA.toString('L', 0));
}

TEST(setL, exception_L_too_large) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_L{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    ira IRA(3, mantissa_length, exponent_length);

    EXPECT_ANY_THROW(IRA.setL(new_L));
}

TEST(setL, exception_L_too_small) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_L{ 10, 20, 30, 40, 50, 60, 70, 80};

    ira IRA(3, mantissa_length, exponent_length);

    EXPECT_ANY_THROW(IRA.setL(new_L));
}

TEST(setU, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_U{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);

    IRA.setU(new_U);


    EXPECT_EQ("10, 20, 30, 40, 50, 60, 70, 80, 90", IRA.toString('U', 0));
}

TEST(setL, exception_U_too_large) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_U{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    ira IRA(3, mantissa_length, exponent_length);

    EXPECT_ANY_THROW(IRA.setU(new_U));
}

TEST(setL, exception_U_too_small) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_U{ 10, 20, 30, 40, 50, 60, 70, 80};

    ira IRA(3, mantissa_length, exponent_length);

    EXPECT_ANY_THROW(IRA.setU(new_U));
}



// casts
// -------------------------------------
TEST(double_to_mps, exception_vector_empty) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> double_vector;

    EXPECT_ANY_THROW(auto ret = ira::double_to_mps(mantissa_length, exponent_length, double_vector));
}

TEST(double_to_mps, exception_mantissa_too_small) {

    unsigned long mantissa_length = 0;
    unsigned long exponent_length = 11;

    vector<double> double_vector;

    EXPECT_ANY_THROW(auto ret = ira::double_to_mps(mantissa_length, exponent_length, double_vector));
}

TEST(double_to_mps, exception_exponent_too_small) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 0;

    vector<double> double_vector;

    EXPECT_ANY_THROW(auto ret = ira::double_to_mps(mantissa_length, exponent_length, double_vector));
}

TEST(double_to_mps, simple_float) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(mantissa_length, exponent_length, double_vector);

    EXPECT_EQ(ira::toString(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(mantissa_length, mps_vector[0].getMantisseLength());
    EXPECT_EQ(exponent_length, mps_vector[0].getExponentLength());
}

TEST(double_to_mps, simple_double) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(mantissa_length, exponent_length, double_vector);

    EXPECT_EQ(ira::toString(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(mantissa_length, mps_vector[0].getMantisseLength());
    EXPECT_EQ(exponent_length, mps_vector[0].getExponentLength());
}

TEST(mps_to_double, exception_vector_empty) {

    vector<mps> mps_vector;

    EXPECT_ANY_THROW(auto double_vector = ira::mps_to_double(mps_vector));
}

TEST(mps_to_double, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;
    vector<double> should_vector{45.34, -32, 3463246, -0.34345};

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[0]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[1]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[2]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[3]);

    auto double_vector = ira::mps_to_double(mps_vector);


    for(unsigned long i = 0; i < should_vector.size(); i++){
        EXPECT_EQ(should_vector[i], double_vector[i]);
    }
}

TEST(mps_to_float, exception_vector_empty) {

    vector<mps> mps_vector;

    EXPECT_ANY_THROW(auto double_vector = ira::mps_to_float(mps_vector));
}

TEST(mps_to_float, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;
    vector<float> should_vector{45.34f, -32, 3463246, -0.34345f};

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[0]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[1]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[2]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[3]);

    auto float_vector = ira::mps_to_float(mps_vector);


    for(unsigned long i = 0; i < should_vector.size(); i++){
        EXPECT_EQ(should_vector[i], float_vector[i]);
    }
}

TEST(cast, exception_vector_empty) {

    vector<mps> mps_vector;

    EXPECT_ANY_THROW(ira::cast(mps_vector, 52, 11));
}

TEST(cast, exception_mantissa_too_small) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(23, 8, double_vector);

    EXPECT_ANY_THROW(ira::cast(mps_vector, 0, 11));
}

TEST(cast, exception_exponent_too_small) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(23, 8, double_vector);

    EXPECT_ANY_THROW(ira::cast(mps_vector, 52, 1));
}

TEST(cast, float_to_double_1) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(23, 8, double_vector);
    ira::cast(mps_vector, 52, 11);

    EXPECT_EQ(ira::toString(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(52, mps_vector[0].getMantisseLength());
    EXPECT_EQ(11, mps_vector[0].getExponentLength());
}

TEST(cast, double_to_float_1) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(52, 11, double_vector);
    ira::cast(mps_vector, 23, 8);

    EXPECT_EQ(ira::toString(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(23, mps_vector[0].getMantisseLength());
    EXPECT_EQ(8, mps_vector[0].getExponentLength());
}

TEST(castVector, double_to_float_1){

    ira IRA(4, 52, 11);
    IRA.setRandomRange(-500, 500);

    auto matrix = IRA.generateRandomMatrix(4, 52, 11);

    ira::cast(matrix, 23, 8);

    for(auto row : matrix){
        for(auto element : row){
            EXPECT_EQ(23, element.getMantisseLength());
            EXPECT_EQ(8, element.getExponentLength());
        }
    }
}

TEST(castSystemMatrix, simple_1) {

    unsigned long wanted_mantissa = 12;
    unsigned long wanted_exponent = 5;

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();

    IRA.castSystemMatrix(wanted_mantissa, wanted_exponent);

    EXPECT_EQ(wanted_mantissa, IRA.getMatrixElement(0).getMantisseLength());
    EXPECT_EQ(wanted_exponent, IRA.getMatrixElement(0).getExponentLength());
}

TEST(castSystemMatrix, simple_2) {

    unsigned long wanted_mantissa = 52;
    unsigned long wanted_exponent = 11;

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();

    IRA.castSystemMatrix(wanted_mantissa, wanted_exponent);

    EXPECT_EQ(wanted_mantissa, IRA.getMatrixElement(0).getMantisseLength());
    EXPECT_EQ(wanted_exponent, IRA.getMatrixElement(0).getExponentLength());
}

TEST(castSystemMatrix, exception_wrong_input) {

    unsigned long wanted_mantissa = 0;
    unsigned long wanted_exponent = 1;



    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();

    EXPECT_ANY_THROW(IRA.castSystemMatrix(wanted_mantissa, 8));
    EXPECT_ANY_THROW(IRA.castSystemMatrix(13, wanted_exponent));
}

TEST(castSystemMatrix, exception_system_matrix_not_set) {

    unsigned long wanted_mantissa = 12;
    unsigned long wanted_exponent = 4;

    ira IRA(5, 23, 8);
    EXPECT_ANY_THROW(IRA.castSystemMatrix(wanted_mantissa, wanted_exponent));
}

TEST(castExpectedResult, simple_1) {

    unsigned long wanted_mantissa = 12;
    unsigned long wanted_exponent = 5;

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();
    IRA.setWorkingPrecision(20, 8);
    auto b = IRA.generateRandomLinearSystem();

    IRA.castExpectedResult(wanted_mantissa, wanted_exponent);

    auto x = IRA.getExpectedResult_mps();

    EXPECT_EQ(wanted_mantissa, x[0].getMantisseLength());
    EXPECT_EQ(wanted_exponent, x[0].getExponentLength());
}

TEST(castExpectedResult, simple_2) {

    unsigned long wanted_mantissa = 52;
    unsigned long wanted_exponent = 11;

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();
    IRA.setWorkingPrecision(20, 8);
    auto b = IRA.generateRandomLinearSystem();

    IRA.castExpectedResult(wanted_mantissa, wanted_exponent);

    auto x = IRA.getExpectedResult_mps();

    EXPECT_EQ(wanted_mantissa, x[0].getMantisseLength());
    EXPECT_EQ(wanted_exponent, x[0].getExponentLength());
}

TEST(castExpectedResult, exception_wrong_input) {

    unsigned long wanted_mantissa = 0;
    unsigned long wanted_exponent = 1;

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();
    IRA.setWorkingPrecision(20, 8);
    auto b = IRA.generateRandomLinearSystem();

    EXPECT_ANY_THROW(IRA.castExpectedResult(wanted_mantissa, 8););
    EXPECT_ANY_THROW(IRA.castExpectedResult(13, wanted_exponent));
}

TEST(castExpectedResult, exception_system_matrix_not_set) {

    unsigned long wanted_mantissa = 12;
    unsigned long wanted_exponent = 4;

    ira IRA(5, 23, 8);
    EXPECT_ANY_THROW(IRA.castExpectedResult(wanted_mantissa, wanted_exponent));
}

TEST(castExpectedError, simple_1) {

    unsigned long wanted_mantissa = 12;
    unsigned long wanted_exponent = 5;
    mps expected_error(23, 8, 0.01);

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();
    IRA.setWorkingPrecision(20, 8);
    auto b = IRA.generateRandomLinearSystem();

    IRA.setExpectedError(expected_error);

    IRA.castExpectedError(wanted_mantissa, wanted_exponent);

    EXPECT_EQ(wanted_mantissa, IRA.getExpectedError().getMantisseLength());
    EXPECT_EQ(wanted_exponent, IRA.getExpectedError().getExponentLength());
}

TEST(castExpectedError, simple_2) {

    unsigned long wanted_mantissa = 52;
    unsigned long wanted_exponent = 11;
    mps expected_error(23, 8, 0.01);

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();
    IRA.setWorkingPrecision(20, 8);
    auto b = IRA.generateRandomLinearSystem();

    IRA.setExpectedError(expected_error);

    IRA.castExpectedError(wanted_mantissa, wanted_exponent);

    EXPECT_EQ(wanted_mantissa, IRA.getExpectedError().getMantisseLength());
    EXPECT_EQ(wanted_exponent, IRA.getExpectedError().getExponentLength());
}

TEST(castExpectedError, exception_wrong_input) {

    unsigned long wanted_mantissa = 0;
    unsigned long wanted_exponent = 1;
    mps expected_error(23, 8, 0.01);

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();
    IRA.setWorkingPrecision(20, 8);
    auto b = IRA.generateRandomLinearSystem();

    IRA.setExpectedError(expected_error);

    EXPECT_ANY_THROW(IRA.castExpectedError(wanted_mantissa, 8));
    EXPECT_ANY_THROW(IRA.castExpectedError(11, wanted_exponent));
}


// generators
// -------------------------------------
TEST(generateRandomVector, simple_1){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;
    unsigned long size = 4;

    ira IRA(2, 54,12);

    auto vec = IRA.generateRandomVector(size, mantissa_length, exponent_length);
    auto random_range = IRA.getRandomRange();
    auto lower_limit = random_range[0];
    auto upper_limit = random_range[1];

    EXPECT_EQ(mantissa_length, vec[0].getMantisseLength());
    EXPECT_EQ(exponent_length, vec[0].getExponentLength());
    EXPECT_EQ(size, vec.size());

    for(const auto& element : vec){
        EXPECT_TRUE(element.getValue() < upper_limit);
        EXPECT_TRUE(element.getValue() > lower_limit);
    }
}

TEST(generateRandomVector, zero_size){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;
    unsigned long size = 0;

    ira IRA(2, 54,12);

    auto vec = IRA.generateRandomVector(size, mantissa_length, exponent_length);

    EXPECT_TRUE(vec.empty());
}

TEST(generateRandomVector, exception_wrong_input){

    unsigned long mantissa_length = 0;
    unsigned long exponent_length = 1;
    unsigned long size = 4;

    ira IRA(2, 54,12);

    EXPECT_ANY_THROW(auto x = IRA.generateRandomVector(size, mantissa_length, 12));
    EXPECT_ANY_THROW(auto x = IRA.generateRandomVector(size, 12, exponent_length));
}

TEST(generateRandomMatrix, simple_double_1){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    unsigned long size = 4;
    double lower_bound = -10;
    double upper_bound = 10;

    ira IRA(size, mantissa_length, exponent_length);
    IRA.setRandomRange(lower_bound, upper_bound);
    IRA.setSparsityRate(0);
    auto matrix = IRA.generateRandomMatrix(size, mantissa_length, exponent_length);


    EXPECT_EQ(mantissa_length, matrix[0][0].getMantisseLength());
    EXPECT_EQ(mantissa_length, matrix[0][0].getMantisseLength());
    EXPECT_EQ(size, matrix.size());

    for(const auto& row : matrix){

        EXPECT_EQ(size, row.size());

        for(const auto& element : row){
            EXPECT_TRUE(element.getValue() <= upper_bound);
            EXPECT_TRUE(element.getValue() >= lower_bound);
        }
    }
}

TEST(generateRandomMatrix, simple_float_1){

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    unsigned long size = 4;
    double lower_bound = -10;
    double upper_bound = 10;

    ira IRA(size, mantissa_length, exponent_length);
    IRA.setRandomRange(lower_bound, upper_bound);
    IRA.setSparsityRate(0);
    auto matrix = IRA.generateRandomMatrix(size, mantissa_length, exponent_length);


    EXPECT_EQ(mantissa_length, matrix[0][0].getMantisseLength());
    EXPECT_EQ(mantissa_length, matrix[0][0].getMantisseLength());
    EXPECT_EQ(size, matrix.size());

    for(const auto& row : matrix){

        EXPECT_EQ(size, row.size());

        for(const auto& element : row){
            EXPECT_TRUE(element.getValue() <= upper_bound);
            EXPECT_TRUE(element.getValue() >= lower_bound);
        }
    }
}

TEST(generateRandomMatrix, sparcity_1){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    unsigned long size = 15;
    double lower_bound = -10;
    double upper_bound = 10;
    double sparsity_rate = 0.25;


    ira IRA(size, mantissa_length, exponent_length);
    IRA.setRandomRange(lower_bound, upper_bound);
    IRA.setSparsityRate(sparsity_rate);
    auto matrix = IRA.generateRandomMatrix(size, mantissa_length, exponent_length);

    unsigned long sum = 0;
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        for(unsigned long col_idx = 0; col_idx < size; col_idx++){
            if(matrix[row_idx][col_idx].isZero()){
                sum++;
            }
        }
    }

    double actual_rate = (double) sum / ((double)(size*size));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.1);

    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < size; column_idx++){
            if(not matrix[row_idx][column_idx].isZero()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < size; column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < size; row_idx++){
            if(not matrix[row_idx][column_idx].isZero()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(generateRandomMatrix, sparcity_2){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    unsigned long size = 15;
    double lower_bound = -10;
    double upper_bound = 10;
    double sparsity_rate = 0.5;


    ira IRA(size, mantissa_length, exponent_length);
    IRA.setRandomRange(lower_bound, upper_bound);
    IRA.setSparsityRate(sparsity_rate);
    auto matrix = IRA.generateRandomMatrix(size, mantissa_length, exponent_length);

    unsigned long sum = 0;
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        for(unsigned long col_idx = 0; col_idx < size; col_idx++){
            if(matrix[row_idx][col_idx].isZero()){
                sum++;
            }
        }
    }

    double actual_rate = (double) sum / ((double)(size*size));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.1);

    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < size; column_idx++){
            if(not matrix[row_idx][column_idx].isZero()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < size; column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < size; row_idx++){
            if(not matrix[row_idx][column_idx].isZero()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(generateRandomMatrix, sparcity_3){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    unsigned long size = 15;
    double lower_bound = -10;
    double upper_bound = 10;
    double sparsity_rate = 0.75;


    ira IRA(size, mantissa_length, exponent_length);
    IRA.setRandomRange(lower_bound, upper_bound);
    IRA.setSparsityRate(sparsity_rate);
    auto matrix = IRA.generateRandomMatrix(size, mantissa_length, exponent_length);

    unsigned long sum = 0;
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        for(unsigned long col_idx = 0; col_idx < size; col_idx++){
            if(matrix[row_idx][col_idx].isZero()){
                sum++;
            }
        }
    }

    double actual_rate = (double) sum / ((double)(size*size));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.1);

    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < size; column_idx++){
            if(not matrix[row_idx][column_idx].isZero()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < size; column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < size; row_idx++){
            if(not matrix[row_idx][column_idx].isZero()){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}





TEST(generateRandomLinearSystem, simple_1){
    // also tests generateRandomRHS implicitly.

    unsigned long size = 4;
    unsigned long ur_m_l = 52;
    unsigned long ur_e_l = 11;
    unsigned long u_m_l = 52;
    unsigned long u_e_l = 11;

    ira IRA(size, ur_m_l,ur_e_l);
    IRA.setWorkingPrecision(u_m_l, u_e_l);
    auto b = IRA.generateRandomLinearSystem();
    auto x = IRA.getExpectedResult_mps();

    vector<mps> b_recalculated;

    for(unsigned long i = 0; i < size; i++){
        mps sum(u_m_l, u_e_l, 0);
        for(unsigned j = 0; j < size; j++){
            sum = sum + (IRA.getMatrixElement(i*size + j) * x[j]);
        }
        b_recalculated.push_back(sum);
    }

    for(unsigned long i = 0; i < size; i++){
        EXPECT_EQ(b_recalculated[i].getValue(), b[i].getValue());
    }
}

TEST(generateRandomLinearSystem, simple_2){
    // also tests generateRandomRHS implicitly.

    unsigned long size = 5;
    unsigned long ur_m_l = 52;
    unsigned long ur_e_l = 11;
    unsigned long u_m_l = 52;
    unsigned long u_e_l = 11;

    ira IRA(size, ur_m_l,ur_e_l);
    IRA.setWorkingPrecision(u_m_l, u_e_l);
    auto b = IRA.generateRandomLinearSystem();
    auto x = IRA.getExpectedResult_mps();

    vector<mps> b_recalculated;

    for(unsigned long i = 0; i < size; i++){
        mps sum(u_m_l, u_e_l, 0);
        for(unsigned j = 0; j < size; j++){
            sum = sum + (IRA.getMatrixElement(i*size + j) * x[j]);
        }
        b_recalculated.push_back(sum);
    }

    for(unsigned long i = 0; i < size; i++){
        EXPECT_EQ(b_recalculated[i].getValue(), b[i].getValue());
    }
}

TEST(generateRandomLinearSystem, simple_3){
    // also tests generateRandomRHS implicitly.

    unsigned long size = 6;
    unsigned long ur_m_l = 52;
    unsigned long ur_e_l = 11;
    unsigned long u_m_l = 52;
    unsigned long u_e_l = 11;

    ira IRA(size, ur_m_l,ur_e_l);
    IRA.setWorkingPrecision(u_m_l, u_e_l);
    auto b = IRA.generateRandomLinearSystem();
    auto x = IRA.getExpectedResult_mps();

    vector<mps> b_recalculated;

    for(unsigned long i = 0; i < size; i++){
        mps sum(u_m_l, u_e_l, 0);
        for(unsigned j = 0; j < size; j++){
            sum = sum + (IRA.getMatrixElement(i*size + j) * x[j]);
        }
        b_recalculated.push_back(sum);
    }

    for(unsigned long i = 0; i < size; i++){
        EXPECT_EQ(b_recalculated[i].getValue(), b[i].getValue());
    }
}

TEST(generateRandomLinearSystem, test_precisions){
    // also tests generateRandomRHS implicitly.

    unsigned long size = 3;
    unsigned long ur_m_l = 52;
    unsigned long ur_e_l = 11;
    unsigned long u_m_l = 23;
    unsigned long u_e_l = 8;

    ira IRA(size, ur_m_l,ur_e_l);
    IRA.setWorkingPrecision(u_m_l, u_e_l);
    auto b = IRA.generateRandomLinearSystem();
    auto x = IRA.getExpectedResult_mps();

    for(unsigned i = 0; i < size * size; i++){
        auto element = IRA.getMatrixElement(i);
        EXPECT_EQ(element.getMantisseLength(), ur_m_l);
        EXPECT_EQ(element.getExponentLength(), ur_e_l);
    }

    for(const auto& element : b){
        EXPECT_EQ(element.getMantisseLength(), ur_m_l);
        EXPECT_EQ(element.getExponentLength(), ur_e_l);
    }

    for(const auto& element : x){
        EXPECT_EQ(element.getMantisseLength(), ur_m_l);
        EXPECT_EQ(element.getExponentLength(), ur_e_l);
    }

}


// evaluators and norms
//-------------------------------
TEST(calculateVectorMean, simple_pos){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<mps> vec;
    vec.emplace_back(mantissa_length, exponent_length, 3);
    vec.emplace_back(mantissa_length, exponent_length, 5);
    vec.emplace_back(mantissa_length, exponent_length, 1);
    vec.emplace_back(mantissa_length, exponent_length, 0);

    auto result =  ira::calculateVectorMean(vec);

    EXPECT_EQ(2.25, result.getValue());
    EXPECT_EQ(mantissa_length, result.getMantisseLength());
    EXPECT_EQ(exponent_length, result.getExponentLength());
}

TEST(calculateVectorMean, simple_neg){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<mps> vec;
    vec.emplace_back(mantissa_length, exponent_length, -3);
    vec.emplace_back(mantissa_length, exponent_length, -5);
    vec.emplace_back(mantissa_length, exponent_length, -1);
    vec.emplace_back(mantissa_length, exponent_length, -0);

    auto result =  ira::calculateVectorMean(vec);

    EXPECT_EQ(2.25, result.getValue());
    EXPECT_EQ(mantissa_length, result.getMantisseLength());
    EXPECT_EQ(exponent_length, result.getExponentLength());
}

TEST(calculateVectorMean, simple_pos_neg){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<mps> vec;
    vec.emplace_back(mantissa_length, exponent_length, -3);
    vec.emplace_back(mantissa_length, exponent_length, 5);
    vec.emplace_back(mantissa_length, exponent_length, 1);
    vec.emplace_back(mantissa_length, exponent_length, 0);

    auto result =  ira::calculateVectorMean(vec);

    EXPECT_EQ(2.25, result.getValue());
    EXPECT_EQ(mantissa_length, result.getMantisseLength());
    EXPECT_EQ(exponent_length, result.getExponentLength());
}

TEST(calculateMeanPrecision, simple_1){


    unsigned long mantissa_length = 5;
    unsigned long exponent_length = 11;
    double init_value = 8;
    unsigned long ira_mantissa_length = 52;
    unsigned long ira_exponent_length = 11;

    vector<mps> x_should;
    vector<bool> xs_mantissa = {1,0,0,0,0};         // NOLINT(*-use-bool-literals)
    for(unsigned long i = 0; i < 4; i++){
        mps xs_value(mantissa_length, exponent_length, init_value);
        xs_value.setMantissa(xs_mantissa);
        x_should.push_back(xs_value);
    }

    vector<mps> x_is;
    for(unsigned long i = 0; i < 4; i++){
        mps xi_value(mantissa_length, exponent_length, init_value);
        x_is.push_back(xi_value);
    }
    vector<bool> xi_zero_mantissa = {1,0,0,1,0};    // NOLINT(*-use-bool-literals)
    x_is[0].setMantissa(xi_zero_mantissa);
    vector<bool> xi_one_mantissa = {1,0,0,0,0};     // NOLINT(*-use-bool-literals)
    x_is[1].setMantissa(xi_one_mantissa);
    vector<bool> xi_two_mantissa = {1,0,0,0,1};     // NOLINT(*-use-bool-literals)
    x_is[2].setMantissa(xi_two_mantissa);
    vector<bool> xi_three_mantissa = {1,0,1,0,1};   // NOLINT(*-use-bool-literals)
    x_is[3].setMantissa(xi_three_mantissa);

    ira IRA(4, ira_mantissa_length, ira_exponent_length);
    IRA.setWorkingPrecision(ira_mantissa_length, ira_exponent_length);
    auto b = IRA.generateRandomLinearSystem();
    mps expected_precision(ira_mantissa_length, ira_exponent_length, 0.001);
    IRA.setExpectedPrecision(expected_precision);

    auto result = IRA.calculateMeanPrecision(x_is, x_should);

    EXPECT_EQ(3.5, result.getValue());
    EXPECT_EQ(ira_mantissa_length, result.getMantisseLength());
    EXPECT_EQ(ira_exponent_length, result.getExponentLength());
}

TEST(calculateMeanPrecision, exception_empty_vector){


    unsigned long mantissa_length = 5;
    unsigned long exponent_length = 11;
    unsigned long ira_mantissa_length = 52;
    unsigned long ira_exponent_length = 11;

    ira IRA(4, ira_mantissa_length, ira_exponent_length);
    IRA.setWorkingPrecision(ira_mantissa_length, ira_exponent_length);
    auto b = IRA.generateRandomLinearSystem();
    mps expected_precision(ira_mantissa_length, ira_exponent_length, 0.001);
    IRA.setExpectedPrecision(expected_precision);

    vector<mps> not_empty_vector;
    not_empty_vector.emplace_back(mantissa_length, exponent_length, 6.0);

    vector<mps> empty_vector;

    EXPECT_NO_THROW(auto x = IRA.calculateMeanPrecision(not_empty_vector, not_empty_vector));
    EXPECT_ANY_THROW(auto x_1 = IRA.calculateMeanPrecision(empty_vector, not_empty_vector));
    EXPECT_ANY_THROW(auto x_2 = IRA.calculateMeanPrecision(not_empty_vector, empty_vector));
}

TEST(calculateMeanPrecision, exception_no_working_precision_set){


    unsigned long mantissa_length = 5;
    unsigned long exponent_length = 11;
    unsigned long ira_mantissa_length = 52;
    unsigned long ira_exponent_length = 11;

    ira IRA(4, ira_mantissa_length, ira_exponent_length);

    vector<mps> not_empty_vector;
    not_empty_vector.emplace_back(mantissa_length, exponent_length, 6.0);

    vector<mps> empty_vector;

    EXPECT_ANY_THROW(auto x = IRA.calculateMeanPrecision(not_empty_vector, not_empty_vector));

    IRA.setWorkingPrecision(ira_mantissa_length, ira_exponent_length);
    auto b = IRA.generateRandomLinearSystem();
    mps expected_precision(ira_mantissa_length, ira_exponent_length, 0.001);
    IRA.setExpectedPrecision(expected_precision);

    EXPECT_NO_THROW(auto x = IRA.calculateMeanPrecision(not_empty_vector, not_empty_vector));
}

TEST(calculateMeanPrecision, exception_no_expected_precision_set){


    unsigned long mantissa_length = 5;
    unsigned long exponent_length = 11;
    unsigned long ira_mantissa_length = 52;
    unsigned long ira_exponent_length = 11;

    ira IRA(4, ira_mantissa_length, ira_exponent_length);
    IRA.setWorkingPrecision(ira_mantissa_length, ira_exponent_length);
    auto b = IRA.generateRandomLinearSystem();

    vector<mps> not_empty_vector;
    not_empty_vector.emplace_back(mantissa_length, exponent_length, 6.0);

    vector<mps> empty_vector;

    EXPECT_ANY_THROW(auto x = IRA.calculateMeanPrecision(not_empty_vector, not_empty_vector));

    mps expected_precision(ira_mantissa_length, ira_exponent_length, 0.001);
    IRA.setExpectedPrecision(expected_precision);

    EXPECT_NO_THROW(auto x = IRA.calculateMeanPrecision(not_empty_vector, not_empty_vector));
}



// printing
// -------------------------------------
TEST(toString, exception_nullptr) {

    ira IRA(3, 53, 11);

    EXPECT_ANY_THROW(auto tmp = IRA.toString('A'));
    EXPECT_ANY_THROW(auto tmp = IRA.toString('L'));
    EXPECT_ANY_THROW(auto tmp = IRA.toString('U'));
    EXPECT_ANY_THROW(auto tmp = IRA.toString('P'));
}

TEST(toString, exception_invalid_argument) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_ANY_THROW(auto tmp = IRA.toString('Z'));
}

TEST(toString, round_to_precision_zero) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_EQ(IRA.toString('A', 0), "10, 20, 30, 40, 50, 60, 70, 80, 90");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).getMantisseLength());
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).getExponentLength());
}

TEST(toString, round_to_precision_two) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_EQ(IRA.toString('A', 2), "10.00, 20.00, 30.00, 40.00, 50.00, 60.00, 70.00, 80.00, 90.00");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).getMantisseLength());
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).getExponentLength());
}

TEST(to_string_vector, exception_vector_empty) {

    vector<mps> mps_vector;

    EXPECT_ANY_THROW(auto ret = ira::toString(mps_vector));
}

TEST(to_string_vector, simple_float) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, 45.34);
    mps_vector.emplace_back(mantissa_length, exponent_length, -32);
    mps_vector.emplace_back(mantissa_length, exponent_length, 3463246);
    mps_vector.emplace_back(mantissa_length, exponent_length, -0.34345);

    EXPECT_EQ(ira::toString(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(mantissa_length, mps_vector[0].getMantisseLength());
    EXPECT_EQ(exponent_length, mps_vector[0].getExponentLength());
}

TEST(to_string_vector, simple_double) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, 45.34);
    mps_vector.emplace_back(mantissa_length, exponent_length, -32);
    mps_vector.emplace_back(mantissa_length, exponent_length, 3463246);
    mps_vector.emplace_back(mantissa_length, exponent_length, -0.34346);

    EXPECT_EQ(ira::toString(mps_vector, 4), "45.3400, -32.0000, 3463246.0000, -0.3435");
    EXPECT_EQ(mantissa_length, mps_vector[0].getMantisseLength());
    EXPECT_EQ(exponent_length, mps_vector[0].getExponentLength());
}

