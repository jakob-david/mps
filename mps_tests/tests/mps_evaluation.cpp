//
// Created by Jakob on 18.03.24.
//

#include "gtest/gtest.h"

#include "../functions/functions.h"
#include "mps.h"


TEST(check_precision, constructor_simple_1){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 1, 1, 1, 1, 1};
    MPS_should.setMantissa(should_mantissa);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 0};
    MPS_is.setMantissa(is_mantissa);

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 6));
    EXPECT_FALSE(MPS_should.check_precision(MPS_is, 6));

    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 0));
}

TEST(check_precision, constructor_simple_2){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{0, 0, 0, 0, 0, 0};
    MPS_should.setMantissa(should_mantissa);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{0, 0, 0, 0, 1, 0};
    MPS_is.setMantissa(is_mantissa);

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 6));
    EXPECT_FALSE(MPS_should.check_precision(MPS_is, 6));

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 0));
}

