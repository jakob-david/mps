#include "gtest/gtest.h"

#include "../functions/functions.h"
#include "ira.h"

TEST(constructor, init_2x2_unitary_matrix) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(2);
    IRA.unitary(mantissa_length, exponent_length);

    EXPECT_EQ(IRA.to_string(), "1.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.matrix[0].mantissa_length);
    EXPECT_EQ(exponent_length, IRA.matrix[0].exponent_length);
}

TEST(constructor, init_3x3_unitary_matrix) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(3);
    IRA.unitary(mantissa_length, exponent_length);

    EXPECT_EQ(IRA.to_string(), "1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.matrix[0].mantissa_length);
    EXPECT_EQ(exponent_length, IRA.matrix[0].exponent_length);
}