//
// Created by Jakob on 18.03.24.
//

#include "gtest/gtest.h"
#include "helper_functions.h"

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
TEST(get_value_tests, sign){

    mps MPS(52, 11, 8);
    MPS.setSign(true);
    EXPECT_EQ(true, MPS.getSign());
    MPS.setSign(false);
    EXPECT_EQ(false, MPS.getSign());
}

TEST(get_value_tests, mantissa){

    mps MPS(5, 11, 8);

    vector<bool> new_mantissa = {0,0,1,1,0};
    MPS.setMantissa(new_mantissa);
    EXPECT_EQ(new_mantissa, MPS.getMantissa());

    new_mantissa = {0,1,0,1,1};
    MPS.setMantissa(new_mantissa);
    EXPECT_EQ(new_mantissa, MPS.getMantissa());
}

TEST(get_value_tests, exponent){

    mps MPS(52, 5, 5);

    vector<bool> new_exponent = {0,0,1,1,0};
    MPS.setExponent(new_exponent);
    EXPECT_EQ(new_exponent, MPS.getExponent());

    new_exponent = {0,1,0,1,1};
    MPS.setExponent(new_exponent);
    EXPECT_EQ(new_exponent, MPS.getExponent());
}

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

TEST(get_value_tests, mantissa_all_zero) {

    double test_value = pow(2, 128);
    mps MPS2(52, 11, test_value);

    EXPECT_EQ(test_value, MPS2.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS2.getBitArray()));
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

    EXPECT_EQ(true, MPS.isInf());
    EXPECT_EQ(true, MPS.isPositive());
}

TEST(get_value_tests, exponent_too_large_double) {

    double test_value = numeric_limits<double>::max();
    mps MPS(52, 10, test_value);

    EXPECT_EQ(true, MPS.isInf());
    EXPECT_EQ(true, MPS.isPositive());
}

TEST(get_value_tests, exponent_too_large_negative_float) {

    float test_value = numeric_limits<float>::max() * -1;
    mps MPS(23, 4, test_value);

    EXPECT_EQ(true, MPS.isInf());
    EXPECT_EQ(false, MPS.isPositive());
}

TEST(get_value_tests, exponent_too_large_negative_double) {

    double test_value = numeric_limits<double>::max() * -1;
    mps MPS(52, 10, test_value);

    EXPECT_EQ(true, MPS.isInf());
    EXPECT_EQ(false, MPS.isPositive());
}

TEST(get_value_tests, value_too_large_positive) {

    double test_value = pow(2, 128);
    mps MPS(23, 8, test_value);
    mps MPS2(52, 11, test_value);

    EXPECT_EQ((float) test_value, MPS.getValue());
    EXPECT_EQ(should_value((float) test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS2.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS2.getBitArray()));
}

TEST(get_value_tests, value_too_large_negative) {

    double test_value = pow(2, 127) * -1;
    mps MPS(23, 8, test_value);
    mps MPS2(52, 11, test_value);

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value((float) test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(should_value(test_value), is_mps(MPS2.getBitArray()));
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



// ######################
// Exception Tests
// ######################
TEST(exception, different_length_exponent){


    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    EXPECT_ANY_THROW(ONE + TWO);
    EXPECT_ANY_THROW(ONE - TWO);
    EXPECT_ANY_THROW(ONE * TWO);
    EXPECT_ANY_THROW(ONE / TWO);

    bool useless = true;
    EXPECT_ANY_THROW(useless = (ONE == TWO));
    EXPECT_ANY_THROW(useless = (ONE != TWO));
    EXPECT_ANY_THROW(useless = (ONE > TWO));
    EXPECT_ANY_THROW(useless = (ONE < TWO));
    EXPECT_ANY_THROW(useless = (ONE >= TWO));
    EXPECT_ANY_THROW(useless = (ONE <= TWO));

    EXPECT_TRUE(useless);
}

TEST(exception, different_length_mantissa){

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    EXPECT_ANY_THROW(ONE + TWO);
    EXPECT_ANY_THROW(ONE - TWO);
    EXPECT_ANY_THROW(ONE * TWO);
    EXPECT_ANY_THROW(ONE / TWO);

    bool useless = true;
    EXPECT_ANY_THROW(useless = (ONE == TWO));
    EXPECT_ANY_THROW(useless = (ONE != TWO));
    EXPECT_ANY_THROW(useless = (ONE > TWO));
    EXPECT_ANY_THROW(useless = (ONE < TWO));
    EXPECT_ANY_THROW(useless = (ONE >= TWO));
    EXPECT_ANY_THROW(useless = (ONE <= TWO));

    EXPECT_TRUE(useless);
}


TEST(exception, cast_too_small_mantissa){

    mps ONE(20, 8, 345.234);

    EXPECT_ANY_THROW(ONE.cast(0, 13));
}

TEST(exception, cast_too_small_exponent){

    mps ONE(20, 8, 345.234);

    EXPECT_ANY_THROW(ONE.cast(13, 1));
}

TEST(exception, constructor_too_small_mantissa){

    EXPECT_ANY_THROW(mps ONE(0, 8));
    EXPECT_ANY_THROW(mps ONE(0, 8, 345.234));
}

TEST(exception, constructor_too_small_exponent){

    EXPECT_ANY_THROW(mps ONE(20, 1));
    EXPECT_ANY_THROW(mps ONE(20, 1, 345.234));
}




TEST(cast, float_to_double_pos_large){

    float value = 2356345.345f;

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_pos_large){

    double value = 2356345.345;

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, float_to_double_neg_large){

    float value = -2356345.345f;

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_neg_large){

    double value = -2356345.345;

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, float_to_double_pos_small){

    float value = 0.00004536f;

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_pos_small){

    double value = 0.00004536;

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, float_to_double_neg_small){

    float value = -0.00004536f;

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_neg_small){

    double value = -0.00004536;

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, float_to_double_zero){

    float value = 0.0f;

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_zero){

    double value = 0;

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, float_to_double_one){

    float value = 1.0f;

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_one){

    double value = 1;

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, float_to_double_min){

    float value = numeric_limits<float>::min();

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_min){

    double value = numeric_limits<float>::min();

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, float_to_double_max){

    float value = numeric_limits<float>::max();

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_max){

    double value = numeric_limits<float>::max();

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, double_to_float_exponent_too_large){

    double value = numeric_limits<double>::max();

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(true, MPS.isInf());
    EXPECT_EQ(true, isinf((float) value));
}

TEST(cast, double_to_float_exponent_too_large_2){

    double value = 2 * (double) numeric_limits<float>::max();

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(true, MPS.isInf());
    EXPECT_EQ(true, isinf((float) value));
}

TEST(cast, double_to_float_exponent_too_small){

    double value = numeric_limits<double>::min();

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(true, MPS.isZero());
    EXPECT_EQ(0, (float) value);
}

TEST(cast, double_to_float_exponent_too_small_2){

    double value = (double) numeric_limits<float>::min() / 2;

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    // cannot be tested directly since the system uses subnormal numbers.
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(true, MPS.isZero());
}

TEST(cast, float_to_double_NAN){

    float value = NAN;

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_NAN){

    double value = NAN;

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, float_to_double_pos_inf){

    float value = numeric_limits<float>::infinity();

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_pos_inf){

    double value = numeric_limits<double>::infinity();

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(cast, float_to_double_neg_inf){

    float value = numeric_limits<float>::infinity() * -1;

    mps MPS(23, 8, value);

    MPS.cast(52, 11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(cast, double_to_float_neg_inf){

    double value = numeric_limits<double>::infinity() * -1;

    mps MPS(52, 11, value);

    MPS.cast(23, 8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}



TEST(print, simple_print_1){

    double value = 345634.3453;

    mps MPS(52, 11, value);

    EXPECT_EQ(should_value(value), MPS.print());
}

TEST(print, simple_print_2){

    double value = -345634.3453;

    mps MPS(52, 11, value);

    EXPECT_EQ(should_value(value), MPS.print());
}

TEST(print, simple_print_3){

    double value = 0.0000345;

    mps MPS(52, 11, value);

    EXPECT_EQ(should_value(value), MPS.print());
}

TEST(print, simple_print_4){

    double value = -0.0000345;

    mps MPS(52, 11, value);

    EXPECT_EQ(should_value(value), MPS.print());
}

TEST(to_string, simple_to_string_1){

    double value = 355345.000;

    mps MPS(52, 11, value);

    EXPECT_EQ(std::to_string(value), MPS.toString());
}

TEST(to_string, simple_to_string_2){

    double value = -355345.000;

    mps MPS(52, 11, value);

    EXPECT_EQ(std::to_string(value), MPS.toString());
}

TEST(to_string, simple_to_string_3){

double value = 0.0000345;

mps MPS(52, 11, value);

EXPECT_EQ(std::to_string(value), MPS.toString());
}

TEST(to_string, simple_to_string_4){

    double value = -0.0000345;

    mps MPS(52, 11, value);

    EXPECT_EQ(std::to_string(value), MPS.toString());
}

TEST(to_string, round_to_string_1){

    double value = 355345.344;

    mps MPS(52, 11, value);

    EXPECT_EQ("355345.34", MPS.toString(2));
}

TEST(to_string, round_to_string_2){

    double value = -355345.344;

    mps MPS(52, 11, value);

    EXPECT_EQ("-355345.34", MPS.toString(2));
}



TEST(setSign, positive_to_negative){

    double value = 355345.344;

    mps MPS(52, 11, value);
    MPS.setSign(true);

    value *= -1;

    EXPECT_EQ(value, MPS.getValue());
}

TEST(setSign, negative_to_positve){

    double value = -355345.344;

    mps MPS(52, 11, value);
    MPS.setSign(false);

    value *= -1;

    EXPECT_EQ(value, MPS.getValue());
}

TEST(setCustom, simple_1_flaot){

    mps MPS(23, 8);

    bool sign = false;
    vector<bool> exp{1,0,0,0,0,0,0,0};
    vector<bool> mant{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    MPS.setSign(sign);
    MPS.setExponent(exp);
    MPS.setMantissa(mant);

    std::string should = "";
    if(sign){
        should += "1";
    } else {
        should += "0";
    }

    for(bool bit : exp){
        if(bit){
            should += "1";
        } else {
            should += "0";
        }
    }

    for(bool bit : mant){
        if(bit){
            should += "1";
        } else {
            should += "0";
        }
    }

    EXPECT_EQ(should, MPS.print());
}

TEST(setCustom, simple_2_flaot){

    mps MPS(23, 8);

    bool sign = false;
    vector<bool> exp{1,0,1,0,1,0,0,0};
    vector<bool> mant{1,1,1,1,1,0,1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1};

    MPS.setSign(sign);
    MPS.setExponent(exp);
    MPS.setMantissa(mant);

    std::string should = "";
    if(sign){
        should += "1";
    } else {
        should += "0";
    }

    for(bool bit : exp){
        if(bit){
            should += "1";
        } else {
            should += "0";
        }
    }

    for(bool bit : mant){
        if(bit){
            should += "1";
        } else {
            should += "0";
        }
    }

    EXPECT_EQ(should, MPS.print());
}

TEST(setCustom, simple_3_flaot){

    mps MPS(23, 8);

    bool sign = false;
    vector<bool> exp{0,0,0,0,1,0,0,1};
    vector<bool> mant{1,1,1,1,0,0,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1};

    MPS.setSign(sign);
    MPS.setExponent(exp);
    MPS.setMantissa(mant);

    std::string should = "";
    if(sign){
        should += "1";
    } else {
        should += "0";
    }

    for(bool bit : exp){
        if(bit){
            should += "1";
        } else {
            should += "0";
        }
    }

    for(bool bit : mant){
        if(bit){
            should += "1";
        } else {
            should += "0";
        }
    }

    EXPECT_EQ(should, MPS.print());
}

TEST(setCustom, mantissa_too_small_flaot){

    mps MPS(23, 8);

    bool sign = false;
    vector<bool> exp{1,0,0,0,0,0,0,0};
    vector<bool> mant{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    MPS.setSign(sign);
    MPS.setExponent(exp);

    EXPECT_ANY_THROW(MPS.setMantissa(mant));
}

TEST(setCustom, mantissa_too_large_flaot){

    mps MPS(23, 8);

    bool sign = false;
    vector<bool> exp{1,0,0,0,0,0,0,0};
    vector<bool> mant{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    MPS.setSign(sign);
    MPS.setExponent(exp);

    EXPECT_ANY_THROW(MPS.setMantissa(mant));
}

TEST(setCustom, exponent_too_small_flaot){

    mps MPS(23, 8);

    bool sign = false;
    vector<bool> exp{1,0,0,0,0,0,0};
    vector<bool> mant{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    MPS.setSign(sign);
    MPS.setMantissa(mant);

    EXPECT_ANY_THROW(MPS.setExponent(exp));
}

TEST(setCustom, exponent_too_large_flaot){

    mps MPS(23, 8);

    bool sign = false;
    vector<bool> exp{1,0,0,0,0,0,0,0,0};
    vector<bool> mant{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    
    MPS.setSign(sign);
    MPS.setMantissa(mant);

    EXPECT_ANY_THROW(MPS.setExponent(exp));
}



