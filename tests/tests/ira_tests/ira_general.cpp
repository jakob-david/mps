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

    EXPECT_EQ(mantissa_length, result_1[0]);
    EXPECT_EQ(exponent_length, result_1[1]);
    EXPECT_EQ(dimension, result_2);
    EXPECT_EQ(dimension * dimension, result_3);
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
    ira::castVectorElements(u_m_l, u_m_e, &expected_result_mps);
    ira::castVectorElements(mantissa_length, exponent_length, &expected_result_mps);

    EXPECT_EQ(expected_result_mps, IRA.getExpectedResult_mps());
    EXPECT_EQ(expected_result_double, IRA.getExpectedResult_double());
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

    EXPECT_EQ(IRA.to_string('A'), "1.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(unitary_matrix, init_3x3) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setUnitaryMatrix();

    EXPECT_EQ(IRA.to_string('A'), "1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(custom_matrix, init_2x2) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40 };

    ira IRA(2, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_EQ(IRA.to_string('A'), "10.000000, 20.000000, 30.000000, 40.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(custom_matrix, init_3x3) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_EQ(IRA.to_string('A'), "10.000000, 20.000000, 30.000000, 40.000000, 50.000000, 60.000000, 70.000000, 80.000000, 90.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
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

    EXPECT_EQ("90.00", tmp.to_string(2));
}

TEST(setL, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_L{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);

    IRA.setL(new_L);


    EXPECT_EQ("10, 20, 30, 40, 50, 60, 70, 80, 90", IRA.to_string('L', 0));
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


    EXPECT_EQ("10, 20, 30, 40, 50, 60, 70, 80, 90", IRA.to_string('U', 0));
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

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(mantissa_length, mps_vector[0].mantissa_length);
    EXPECT_EQ(exponent_length, mps_vector[0].exponent_length);
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

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(mantissa_length, mps_vector[0].mantissa_length);
    EXPECT_EQ(exponent_length, mps_vector[0].exponent_length);
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

TEST(castVectorElements, exception_vector_empty) {

    vector<mps> mps_vector;

    EXPECT_ANY_THROW(ira::castVectorElements(52, 11, &mps_vector));
}

TEST(castVectorElements, exception_mantissa_too_small) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(23, 8, double_vector);

    EXPECT_ANY_THROW(ira::castVectorElements(0, 11, &mps_vector));
}

TEST(castVectorElements, exception_exponent_too_small) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(23, 8, double_vector);

    EXPECT_ANY_THROW(ira::castVectorElements(52, 1, &mps_vector));
}

TEST(castVectorElements, float_to_double_1) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(23, 8, double_vector);
    ira::castVectorElements(52, 11, &mps_vector);

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(52, mps_vector[0].mantissa_length);
    EXPECT_EQ(11, mps_vector[0].exponent_length);
}

TEST(castVectorElements, double_to_float_1) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(52, 11, double_vector);
    ira::castVectorElements(23, 8, &mps_vector);

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(23, mps_vector[0].mantissa_length);
    EXPECT_EQ(8, mps_vector[0].exponent_length);
}

TEST(castSystemMatrix, simple_1) {

    unsigned long wanted_mantissa = 12;
    unsigned long wanted_exponent = 5;

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();

    IRA.castSystemMatrix(wanted_mantissa, wanted_exponent);

    EXPECT_EQ(wanted_mantissa, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(wanted_exponent, IRA.getMatrixElement(0).exponent_length);
}

TEST(castSystemMatrix, simple_2) {

    unsigned long wanted_mantissa = 52;
    unsigned long wanted_exponent = 11;

    ira IRA(5, 23, 8);
    IRA.setRandomMatrix();

    IRA.castSystemMatrix(wanted_mantissa, wanted_exponent);

    EXPECT_EQ(wanted_mantissa, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(wanted_exponent, IRA.getMatrixElement(0).exponent_length);
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

    EXPECT_EQ(wanted_mantissa, x[0].mantissa_length);
    EXPECT_EQ(wanted_exponent, x[0].exponent_length);
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

    EXPECT_EQ(wanted_mantissa, x[0].mantissa_length);
    EXPECT_EQ(wanted_exponent, x[0].exponent_length);
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

    EXPECT_EQ(wanted_mantissa, IRA.getExpectedError().mantissa_length);
    EXPECT_EQ(wanted_exponent, IRA.getExpectedError().exponent_length);
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

    EXPECT_EQ(wanted_mantissa, IRA.getExpectedError().mantissa_length);
    EXPECT_EQ(wanted_exponent, IRA.getExpectedError().exponent_length);
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




// printing
// -------------------------------------
TEST(to_string, exception_nullptr) {

    ira IRA(3, 53, 11);

    EXPECT_ANY_THROW(auto tmp = IRA.to_string('A'));
    EXPECT_ANY_THROW(auto tmp = IRA.to_string('L'));
    EXPECT_ANY_THROW(auto tmp = IRA.to_string('U'));
    EXPECT_ANY_THROW(auto tmp = IRA.to_string('P'));
}

TEST(to_string, exception_invalid_argument) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_ANY_THROW(auto tmp = IRA.to_string('Z'));
}

TEST(to_string, round_to_precision_zero) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_EQ(IRA.to_string('A', 0), "10, 20, 30, 40, 50, 60, 70, 80, 90");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(to_string, round_to_precision_two) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_EQ(IRA.to_string('A', 2), "10.00, 20.00, 30.00, 40.00, 50.00, 60.00, 70.00, 80.00, 90.00");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(to_string_vector, exception_vector_empty) {

    vector<mps> mps_vector;

    EXPECT_ANY_THROW(auto ret = ira::to_string(mps_vector));
}

TEST(to_string_vector, simple_float) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, 45.34);
    mps_vector.emplace_back(mantissa_length, exponent_length, -32);
    mps_vector.emplace_back(mantissa_length, exponent_length, 3463246);
    mps_vector.emplace_back(mantissa_length, exponent_length, -0.34345);

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(mantissa_length, mps_vector[0].mantissa_length);
    EXPECT_EQ(exponent_length, mps_vector[0].exponent_length);
}

TEST(to_string_vector, simple_double) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, 45.34);
    mps_vector.emplace_back(mantissa_length, exponent_length, -32);
    mps_vector.emplace_back(mantissa_length, exponent_length, 3463246);
    mps_vector.emplace_back(mantissa_length, exponent_length, -0.34346);

    EXPECT_EQ(ira::to_string(mps_vector, 4), "45.3400, -32.0000, 3463246.0000, -0.3435");
    EXPECT_EQ(mantissa_length, mps_vector[0].mantissa_length);
    EXPECT_EQ(exponent_length, mps_vector[0].exponent_length);
}

