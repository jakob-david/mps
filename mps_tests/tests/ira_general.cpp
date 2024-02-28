#include "gtest/gtest.h"

#include "../functions/functions.h"
#include "ira.h"

TEST(unitary_matrix, init_2x2) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(2);
    IRA.unitary(mantissa_length, exponent_length);

    EXPECT_EQ(IRA.to_string(), "1.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.matrix[0].mantissa_length);
    EXPECT_EQ(exponent_length, IRA.matrix[0].exponent_length);
}

TEST(unitary_matrix, init_3x3) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(3);
    IRA.unitary(mantissa_length, exponent_length);

    EXPECT_EQ(IRA.to_string(), "1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.matrix[0].mantissa_length);
    EXPECT_EQ(exponent_length, IRA.matrix[0].exponent_length);
}

TEST(custom_matrix, init_2x2) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40 };

    ira IRA(2);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    EXPECT_EQ(IRA.to_string(), "10.000000, 20.000000, 30.000000, 40.000000");
    EXPECT_EQ(mantissa_length, IRA.matrix[0].mantissa_length);
    EXPECT_EQ(exponent_length, IRA.matrix[0].exponent_length);
}

TEST(custom_matrix, init_3x3) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    EXPECT_EQ(IRA.to_string(), "10.000000, 20.000000, 30.000000, 40.000000, 50.000000, 60.000000, 70.000000, 80.000000, 90.000000");
    EXPECT_EQ(mantissa_length, IRA.matrix[0].mantissa_length);
    EXPECT_EQ(exponent_length, IRA.matrix[0].exponent_length);
}

TEST(custom_matrix, new_matrix_too_large) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    ira IRA(3);

    bool test = false;

    try
    {
        IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(custom_matrix, new_matrix_too_small) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80};

    ira IRA(3);

    bool test = false;

    try
    {
        IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}