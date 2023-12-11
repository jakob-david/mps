#include "gtest/gtest.h"

#include "mps.h"

TEST(genertal_tests, constructor_test){

    int mantisse_actual = 0;

    mps* MPS = new mps(5);

    mantisse_actual = MPS->getMantisseLength();

    EXPECT_EQ(5, mantisse_actual);
}