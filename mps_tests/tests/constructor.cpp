#include "gtest/gtest.h"

#include "../functions/functions.h"
#include "mps.h"


// ######################
// Constructor Tests
// ######################
TEST(constructor_tests, constructor_sets_values_coorectly){

    mps MPS(5, 6, 3.14);

    unsigned long mantissa_actual = MPS.getMantisseLength();
    unsigned long exponent_actual = MPS.getExponentLength();

    EXPECT_EQ(5, mantissa_actual);
    EXPECT_EQ(6, exponent_actual);

}

TEST(constructor_tests, constructor_initializes_bit_array_correctly){

    mps MPS(20, 12, 3.14);

    unsigned long size = MPS.getBitArrayLength();

    EXPECT_EQ(33, size);
}


// ######################
// converter Tests
// ######################
TEST(converter_tests, test_positive_double) {

    double test_value = 342.45636;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_positive_double_using_getBitArrayReference) {

    double test_value = 572496.394863845;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_negative_double) {

    double test_value = -38758285.203858387583005867;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_positive_float) {

    float test_value = 345.3456f;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_negative_float) {

    float test_value = -2354.3456f;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_zero_double) {

    double test_value = 0;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_zero_float) {

    float test_value = 0;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_pos_infinity_double) {

    double test_value = numeric_limits<double>::infinity();
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_pos_infinity_float) {

    float test_value = numeric_limits<float>::infinity();
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_neg_infinity_double) {

    double test_value = numeric_limits<double>::infinity() * -1;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_neg_infinity_float) {

    float test_value = numeric_limits<float>::infinity() * -1;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_pos_max_double) {

    double test_value = numeric_limits<double>::max();  //- 1 * pow(2, 979);
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_pos_max_float) {

    float test_value = numeric_limits<float>::max();
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_max_float_in_double) {

    double test_value = numeric_limits<float>::max();
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_pos_min_double) {

    double test_value = numeric_limits<double>::min();
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_pos_min_float) {

    float test_value = numeric_limits<float>::min();
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_small_difference) {

    double test_value = 1.0 + pow(0.5, 52);
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_neg_max_double) {

    double test_value = numeric_limits<double>::max() * -1;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_neg_max_float) {

    float test_value = numeric_limits<float>::max() * -1;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_neg_min_double) {

    double test_value = numeric_limits<double>::min() * -1;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_neg_min_float) {

    float test_value = numeric_limits<float>::min() * -1;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_NAN_double) {

    double test_value = std::numeric_limits<double>::quiet_NaN();
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_NAN_float) {

    float test_value = std::numeric_limits<float>::quiet_NaN();
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_neg_NAN_double) {

    double test_value = std::numeric_limits<double>::quiet_NaN() * -1;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_neg_NAN_float) {

    float test_value = std::numeric_limits<float>::quiet_NaN() * -1;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_null_double) {

    double test_value = 0;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(converter_tests, test_null_float) {

    float test_value = 0;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}


// ######################
// Get Value Tests
// ######################
TEST(get_value_tests, get_one_double) {

    double test_value = 1;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_one_float) {

    float test_value = 1;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_double) {

    double test_value = 3455763.3467457;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_float) {

    float test_value = 3455763.3467457f;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_one_double) {

    double test_value = -1;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_one_float) {

    float test_value = -1;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_double) {

    double test_value = -2356345.235643;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_float) {

    float test_value = -2356345.235643f;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_zero_double) {

    double test_value = 0;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_zero_float) {

    float test_value = 0;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_pos_inf_double) {

    double test_value = numeric_limits<double>::infinity();
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_pos_inf_float) {

    float test_value = numeric_limits<float>::infinity();
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_inf_double) {

    double test_value = numeric_limits<double>::infinity() * -1;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_inf_float) {

    float test_value = numeric_limits<float>::infinity() * -1;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_pos_max_double) {

    double test_value = numeric_limits<double>::max();
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_pos_max_float) {

    float test_value = numeric_limits<float>::max();
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_max_double) {

    double test_value = numeric_limits<double>::max() * -1;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_max_float) {

    float test_value = numeric_limits<float>::max() * -1;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_pos_min_double) {

    double test_value = numeric_limits<double>::min();
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_pos_min_float) {

    float test_value = numeric_limits<float>::min();
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_min_double) {

    double test_value = numeric_limits<double>::min() * -1;
    mps MPS(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_neg_min_float) {

    float test_value = numeric_limits<float>::min() * -1;
    mps MPS(23, 8, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
}

TEST(get_value_tests, get_NAN_float) {

    float test_value = numeric_limits<float>::quiet_NaN();
    mps MPS(23, 8, test_value);

    EXPECT_EQ(isnan(test_value), isnan(MPS.getValue()));
}

TEST(get_value_tests, get_NAN_double) {

    double test_value = numeric_limits<double>::quiet_NaN();
    mps MPS(52, 11, test_value);

    EXPECT_EQ(isnan(test_value), isnan(MPS.getValue()));
}

TEST(get_value_tests, exponent_too_large_positive_float) {

    float test_value = numeric_limits<float>::max();
    mps MPS(23, 4, test_value);

    EXPECT_EQ(true, MPS.isInfinity());
    EXPECT_EQ(true, MPS.isPositive());
}

TEST(get_value_tests, exponent_too_large_double) {

    double test_value = numeric_limits<double>::max();
    mps MPS(52, 10, test_value);

    EXPECT_EQ(true, MPS.isInfinity());
    EXPECT_EQ(true, MPS.isPositive());
}

TEST(get_value_tests, exponent_too_large_negative_float) {

    float test_value = numeric_limits<float>::max() * -1;
    mps MPS(23, 4, test_value);

    EXPECT_EQ(true, MPS.isInfinity());
    EXPECT_EQ(false, MPS.isPositive());
}

TEST(get_value_tests, exponent_too_negative_double) {

    double test_value = numeric_limits<double>::max() * -1;
    mps MPS(52, 10, test_value);

    EXPECT_EQ(true, MPS.isInfinity());
    EXPECT_EQ(false, MPS.isPositive());
}


// ######################
// Setter Tests
// ######################
TEST(setter_tests, set_pos_inf_double) {

    double test_value = numeric_limits<double>::infinity();
    mps MPS(52, 11, 345.234);
    MPS.setInf();

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(setter_tests, set_pos_inf_float) {

    float test_value = numeric_limits<float>::infinity();
    mps MPS(23, 8, 345.234);
    MPS.setInf();

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(setter_tests, set_neg_inf_double) {

    double test_value = numeric_limits<double>::infinity() * -1;
    mps MPS(52, 11, 345.234);
    MPS.setInf(true);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(setter_tests, set_neg_inf_float) {

    float test_value = numeric_limits<float>::infinity() * -1;
    mps MPS(23, 8, 345.234);
    MPS.setInf(true);

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(setter_tests, set_zero_double) {

    double test_value = 0;
    mps MPS(52, 11, 345.234);
    MPS.setZero();

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(setter_tests, set_zero_float) {

    float test_value = 0;
    mps MPS(23, 8, 345.234);
    MPS.setZero();

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(setter_tests, set_NAN_double) {

    double test_value = numeric_limits<double>::quiet_NaN();
    mps MPS(52, 11, 345.234);
    MPS.setNaN();

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}

TEST(setter_tests, set_NAN_float) {

    float test_value = numeric_limits<float>::quiet_NaN();
    mps MPS(23, 8, 345.234);
    MPS.setNaN();

    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
}


