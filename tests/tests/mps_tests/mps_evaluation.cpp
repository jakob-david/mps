//
// Created by Jakob on 18.03.24.
//

#include "gtest/gtest.h"
#include "../../functions/functions.h"

#include "mps.h"


TEST(checkPrecision, exception_mantissa_does_not_match){

    mps MPS_should(7, 4, 3.14);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    bool nix = false;
    EXPECT_ANY_THROW(nix = MPS_is.checkPrecision(MPS_should, 6));
    EXPECT_FALSE(nix);
}

TEST(checkPrecision, exception_exponent_does_not_match){

    mps MPS_should(6, 5, 3.14);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    bool nix = false;
    EXPECT_ANY_THROW(nix = MPS_is.checkPrecision(MPS_should, 6));
    EXPECT_FALSE(nix);
}

TEST(checkPrecision, simple_1){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    EXPECT_FALSE(MPS_is.checkPrecision(MPS_should, 6));
    EXPECT_FALSE(MPS_should.checkPrecision(MPS_is, 6));

    EXPECT_FALSE(MPS_is.checkPrecision(MPS_should, 7));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 0));
}

TEST(checkPrecision, simple_2){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{0, 0, 0, 0, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    EXPECT_FALSE(MPS_is.checkPrecision(MPS_should, 6));
    EXPECT_FALSE(MPS_should.checkPrecision(MPS_is, 6));

    EXPECT_FALSE(MPS_is.checkPrecision(MPS_should, 7));
    EXPECT_FALSE(MPS_is.checkPrecision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 0));
}

TEST(checkPrecision, simple_3){

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

    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 6));
    EXPECT_FALSE(MPS_should.checkPrecision(MPS_is, 6));

    EXPECT_FALSE(MPS_is.checkPrecision(MPS_should, 7));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 0));
}

TEST(checkPrecision, simple_4){

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

    EXPECT_FALSE(MPS_is.checkPrecision(MPS_should, 6));
    EXPECT_TRUE(MPS_should.checkPrecision(MPS_is, 6));

    EXPECT_FALSE(MPS_is.checkPrecision(MPS_should, 7));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 5));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 4));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 3));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 2));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 1));
    EXPECT_TRUE(MPS_is.checkPrecision(MPS_should, 0));
}

TEST(checkPrecision, simple_5){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> should_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);
    MPS_should.setExponent(should_exponent);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{0, 0, 0, 0, 0, 0};     // NOLINT(*-use-bool-literals)
    vector<bool> is_exponent{1 ,0 , 1, 0};          // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);
    MPS_is.setExponent(is_exponent);

    EXPECT_FALSE(MPS_is.checkPrecision(MPS_should, 0));
    EXPECT_FALSE(MPS_should.checkPrecision(MPS_is, 0));
}





TEST(getPrecision, simple_0){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    EXPECT_EQ(7, MPS_is.getPrecision(MPS_should));
}

TEST(getPrecision, simple_1){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    EXPECT_EQ(6, MPS_is.getPrecision(MPS_should));
}

TEST(getPrecision, simple_2){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{0, 0, 0, 0, 1, 0}; // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);

    EXPECT_EQ(5, MPS_is.getPrecision(MPS_should));
}

TEST(getPrecision, simple_3){

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

    EXPECT_EQ(6, MPS_is.getPrecision(MPS_should));
    EXPECT_EQ(5, MPS_should.getPrecision(MPS_is));
}

TEST(getPrecision, simple_4){

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

    EXPECT_EQ(5, MPS_is.getPrecision(MPS_should));
    EXPECT_EQ(6, MPS_should.getPrecision(MPS_is));
}

TEST(getPrecision, simple_5){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    vector<bool> should_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);
    MPS_should.setExponent(should_exponent);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 0, 0, 1, 1, 1};     // NOLINT(*-use-bool-literals)
    vector<bool> is_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);
    MPS_is.setExponent(is_exponent);

    EXPECT_EQ(3, MPS_is.getPrecision(MPS_should));
    EXPECT_EQ(3, MPS_should.getPrecision(MPS_is));
}

TEST(getPrecision, simple_6){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 0, 1, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    vector<bool> should_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);
    MPS_should.setExponent(should_exponent);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{1, 0, 0, 1, 1, 1};     // NOLINT(*-use-bool-literals)
    vector<bool> is_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);
    MPS_is.setExponent(is_exponent);

    EXPECT_EQ(5, MPS_is.getPrecision(MPS_should));
    EXPECT_EQ(5, MPS_should.getPrecision(MPS_is));
}

TEST(getPrecision, negative_precision_1){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> should_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);
    MPS_should.setExponent(should_exponent);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{0, 0, 0, 0, 0, 0};     // NOLINT(*-use-bool-literals)
    vector<bool> is_exponent{1 ,0 , 1, 0};          // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);
    MPS_is.setExponent(is_exponent);

    EXPECT_EQ(-1, MPS_is.getPrecision(MPS_should));
    EXPECT_EQ(0, MPS_should.getPrecision(MPS_is));
}

TEST(getPrecision, negative_precision_2){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    vector<bool> should_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);
    MPS_should.setExponent(should_exponent);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{0, 0, 0, 0, 0, 0};     // NOLINT(*-use-bool-literals)
    vector<bool> is_exponent{1 ,0 , 1, 0};          // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);
    MPS_is.setExponent(is_exponent);

    EXPECT_EQ(-1, MPS_is.getPrecision(MPS_should));
    EXPECT_EQ(0, MPS_should.getPrecision(MPS_is));
}

TEST(getPrecision, negative_precision_3){

    mps MPS_should(6, 4, 3.14);
    vector<bool> should_mantissa{0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    vector<bool> should_exponent{1 ,0 , 0, 0};      // NOLINT(*-use-bool-literals)
    MPS_should.setMantissa(should_mantissa);
    MPS_should.setExponent(should_exponent);

    mps MPS_is(6, 4, 3.14);
    vector<bool> is_mantissa{0, 0, 0, 0, 0, 0};     // NOLINT(*-use-bool-literals)
    vector<bool> is_exponent{1, 0, 1, 1};          // NOLINT(*-use-bool-literals)
    MPS_is.setMantissa(is_mantissa);
    MPS_is.setExponent(is_exponent);

    EXPECT_EQ(-4, MPS_is.getPrecision(MPS_should));
    EXPECT_EQ(0, MPS_should.getPrecision(MPS_is));
}




TEST(getAbsoluteError, exception_mathissa_no_match){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length-1, exponent_length, is_d);

    EXPECT_ANY_THROW(auto tmp = is.getAbsoluteError(should));
}

TEST(getAbsoluteError, exception_exponent_no_match){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length-1, is_d);

    EXPECT_ANY_THROW(auto tmp = is.getAbsoluteError(should));
}

TEST(getAbsoluteError, simple_1){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = is.getAbsoluteError(should);

    EXPECT_EQ(expected_result, actual_result.getValue());
    EXPECT_EQ(should_value(expected_result), actual_result.print());
}

TEST(getAbsoluteError, simple_2){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 10;
    float is_d = 20;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = is.getAbsoluteError(should);

    EXPECT_EQ(expected_result, (float) actual_result.getValue());
    EXPECT_EQ(should_value(expected_result), actual_result.print());
}

TEST(getAbsoluteError, simple_3){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 0.0032;
    double is_d = 0.334;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = is.getAbsoluteError(should);

    EXPECT_EQ(expected_result, actual_result.getValue());
    EXPECT_EQ(should_value(expected_result), actual_result.print());
}

TEST(getAbsoluteError, simple_4){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 0.0003f;
    float is_d = 0.00032f;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = is.getAbsoluteError(should);

    EXPECT_EQ(expected_result, (float) actual_result.getValue());
    EXPECT_EQ(should_value(expected_result), actual_result.print());
}


TEST(getRelativeError, exception_mathissa_no_match){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length-1, exponent_length, is_d);

    EXPECT_ANY_THROW(auto tmp = is.getRelativeError(should));
}

TEST(getRelativeError, exception_exponent_no_match){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length-1, is_d);

    EXPECT_ANY_THROW(auto tmp = is.getRelativeError(should));
}

TEST(getRelativeError, simple_1){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = is.getRelativeError(should);

    EXPECT_EQ(expected_result, actual_result.getValue());
    EXPECT_EQ(should_value(expected_result), actual_result.print());
}

TEST(getRelativeError, simple_2){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 10;
    float is_d = 20;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = is.getRelativeError(should);

    EXPECT_EQ(expected_result, (float) actual_result.getValue());
    EXPECT_EQ(should_value(expected_result), actual_result.print());
}

TEST(getRelativeError, simple_3){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 0.0032;
    double is_d = 0.334;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = is.getRelativeError(should);

    EXPECT_EQ(expected_result, actual_result.getValue());
    EXPECT_EQ(should_value(expected_result), actual_result.print());
}

TEST(getRelativeError, simple_4){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 0.0003f;
    float is_d = 0.00032f;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = is.getRelativeError(should);

    EXPECT_EQ(expected_result, (float) actual_result.getValue());
    EXPECT_EQ(should_value(expected_result), actual_result.print());
}


TEST(getRelativeError_double, simple_1){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = is.getRelativeError_double(should);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getRelativeError_double, simple_2){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 10;
    float is_d = 20;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = (float) is.getRelativeError_double(should);

    EXPECT_EQ(expected_result, (float) actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getRelativeError_double, simple_3){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 0.0032;
    double is_d = 0.334;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = is.getRelativeError_double(should);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getRelativeError_double, simple_4){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 0.0003f;
    float is_d = 0.00032f;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = (float) is.getRelativeError_double(should);

    EXPECT_EQ(expected_result, (float) actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}


TEST(getAbsoluteError_double, simple_1){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = is.getAbsoluteError_double(should);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getAbsoluteError_double, simple_2){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 10;
    float is_d = 20;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = (float) is.getAbsoluteError_double(should);

    EXPECT_EQ(expected_result, (float) actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getAbsoluteError_double, simple_3){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 0.0032;
    double is_d = 0.334;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = is.getAbsoluteError_double(should);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getAbsoluteError_double, simple_4){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 0.0003f;
    float is_d = 0.00032f;

    auto should = mps(mantissa_length, exponent_length, should_d);
    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = (float) is.getAbsoluteError_double(should);

    EXPECT_EQ(expected_result, (float) actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}



TEST(getRelativeError_all_double, simple_1){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = is.getRelativeError_double(should_d);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getRelativeError_all_double, simple_2){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 10;
    float is_d = 20;

    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = (float) is.getRelativeError_double(should_d);

    EXPECT_EQ(expected_result, (float) actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getRelativeError_all_double, simple_3){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 0.0032;
    double is_d = 0.334;

    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = is.getRelativeError_double(should_d);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getRelativeError_all_double, simple_4){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 0.0003f;
    float is_d = 0.00032f;

    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d) / should_d;
    auto actual_result = (float) is.getRelativeError_double(should_d);

    EXPECT_EQ(expected_result, (float) actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}


TEST(getAbsoluteError_all_double, simple_1){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 2;
    double is_d = 1;

    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = is.getAbsoluteError_double(should_d);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getAbsoluteError_all_double, simple_2){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 10;
    float is_d = 20;

    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = (float) is.getAbsoluteError_double(should_d);

    EXPECT_EQ(expected_result, (float) actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getAbsoluteError_all_double, simple_3){

    unsigned long exponent_length = 11;
    unsigned long mantissa_length = 52;

    double should_d = 0.0032;
    double is_d = 0.334;

    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = is.getAbsoluteError_double(should_d);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}

TEST(getAbsoluteError_all_double, simple_4){

    unsigned long exponent_length = 8;
    unsigned long mantissa_length = 23;

    float should_d = 0.0003f;
    float is_d = 0.00032f;

    auto is = mps(mantissa_length, exponent_length, is_d);

    auto expected_result = abs(should_d-is_d);
    auto actual_result = (float) is.getAbsoluteError_double(should_d);

    EXPECT_EQ(expected_result, (float) actual_result);
    EXPECT_EQ(should_value(expected_result), should_value(actual_result));
}