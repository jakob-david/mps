//
// Created by Jakob on 18.03.24.
//

#include "gtest/gtest.h"

#include "mps.h"


TEST(check_precision, exception_mantissa_does_not_match){

    mps MPS_should(7, 4, 3.14);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    bool nix = false;
    EXPECT_ANY_THROW(nix = MPS_is.check_precision(MPS_should, 6));
    EXPECT_FALSE(nix);
}

TEST(check_precision, exception_exponent_does_not_match){

    mps MPS_should(6, 5, 3.14);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    bool nix = false;
    EXPECT_ANY_THROW(nix = MPS_is.check_precision(MPS_should, 6));
    EXPECT_FALSE(nix);
}

TEST(check_precision, simple_1){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 6));
    EXPECT_FALSE(MPS_should.check_precision(MPS_is, 6));

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 7));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 0));
}

TEST(check_precision, simple_2){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{0, 0, 0, 0, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 6));
    EXPECT_FALSE(MPS_should.check_precision(MPS_is, 6));

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 7));
    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 0));
}

TEST(check_precision, simple_3){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    vector<bool> should_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);
    MPS_should.setExponent(should_exponent);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 1};     // NOLINT(*-use-bool-literals)
    vector<bool> is_exponent{0 ,1 , 1, 1};      // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);
    MPS_is.setExponent(is_exponent);

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 6));
    EXPECT_FALSE(MPS_should.check_precision(MPS_is, 6));

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 7));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 0));
}

TEST(check_precision, simple_4){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> should_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);
    MPS_should.setExponent(should_exponent);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{0, 0, 0, 0, 0, 0};     // NOLINT(*-use-bool-literals)
    vector<bool> is_exponent{1 ,0 , 0, 1};      // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);
    MPS_is.setExponent(is_exponent);

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 6));
    EXPECT_FALSE(MPS_should.check_precision(MPS_is, 6));

    EXPECT_FALSE(MPS_is.check_precision(MPS_should, 7));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.check_precision(MPS_should, 0));
}

