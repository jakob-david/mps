#include "gtest/gtest.h"

#include "mps.h"

TEST(genertal_tests, constructor_test){

    int mantisse_actual = 0;
    int exponent_actual = 0;
    long double value_actual = 0.0;

    mps* MPS = new mps(5, 6, 3.14);

    mantisse_actual = MPS->getMantisseLength();
    exponent_actual = MPS->getExponentLength();
    value_actual = MPS->getDoubleValue();

    EXPECT_EQ(5, mantisse_actual);
    EXPECT_EQ(6, exponent_actual);
    EXPECT_EQ(3.14, value_actual);
}