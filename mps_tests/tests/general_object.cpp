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

TEST(get_value_tests, exponent_too_large_negative_double) {

    double test_value = numeric_limits<double>::max() * -1;
    mps MPS(52, 10, test_value);

    EXPECT_EQ(true, MPS.isInfinity());
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





TEST(exception, different_length_exponent_assign){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE = TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_assign){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE = TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_addition){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE + TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_addition){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE + TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_subtraction){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE - TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_subtraction){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE - TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_multiplication){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE * TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_multiplication){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE * TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_division){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE / TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_division){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        ONE / TWO;
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_equal){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE == TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_equal){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE == TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_notequal){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE != TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_notequal){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE != TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_larger){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE > TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_larger){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE > TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_smaller){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE < TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_smaller){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE < TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_larger_equal){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE >= TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_larger_equal){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE >= TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_exponent_smaller_equal){

    bool test = false;

    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE <= TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(exception, different_length_mantissa_smaller_equal){

    bool test = false;

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    try
    {
        if(ONE <= TWO){
            test = false;
        }
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}




TEST(round, float_to_double_pos_large){

    float value = 2356345.345f;

    mps MPS(23, 8, value);

    MPS.round(52,11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(round, double_to_float_pos_large){

    double value = 2356345.345;

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(round, float_to_double_neg_large){

    float value = -2356345.345f;

    mps MPS(23, 8, value);

    MPS.round(52,11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(round, double_to_float_neg_large){

    double value = -2356345.345;

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(round, float_to_double_pos_small){

    float value = 0.00004536f;

    mps MPS(23, 8, value);

    MPS.round(52,11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(round, double_to_float_pos_small){

    double value = 0.00004536;

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(round, float_to_double_neg_small){

    float value = -0.00004536f;

    mps MPS(23, 8, value);

    MPS.round(52,11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(round, double_to_float_neg_small){

    double value = -0.00004536;

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(round, float_to_double_zero){

    float value = 0.0f;

    mps MPS(23, 8, value);

    MPS.round(52,11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(round, double_to_float_zero){

    double value = 0;

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(round, float_to_double_one){

    float value = 1.0f;

    mps MPS(23, 8, value);

    MPS.round(52,11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(round, double_to_float_one){

    double value = 1;

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(round, float_to_double_min){

    float value = numeric_limits<float>::min();

    mps MPS(23, 8, value);

    MPS.round(52,11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(round, double_to_float_min){

    double value = numeric_limits<float>::min();

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}

TEST(round, float_to_double_max){

    float value = numeric_limits<float>::max();

    mps MPS(23, 8, value);

    MPS.round(52,11);

    EXPECT_EQ(should_value((double) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
}

TEST(round, double_to_float_max){

    double value = numeric_limits<float>::max();

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
}



TEST(round, double_to_float_exponent_too_large){

    double value = numeric_limits<double>::max();

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(true, MPS.isInfinity());
    EXPECT_EQ(true, isinf((float) value));
}

TEST(round, double_to_float_exponent_too_large_2){

    double value = 2 * (double) numeric_limits<float>::max();

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(true, MPS.isInfinity());
    EXPECT_EQ(true, isinf((float) value));
}

TEST(round, double_to_float_exponent_too_small){

    double value = numeric_limits<double>::min();

    mps MPS(52, 11, value);

    MPS.round(23,8);

    EXPECT_EQ(should_value((float) value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(true, MPS.isZero());
    EXPECT_EQ(0, (float) value);
}

TEST(round, double_to_float_exponent_too_small_2){

    double value = (double) numeric_limits<float>::min() / 2;

    mps MPS(52, 11, value);

    MPS.round(23,8);

    // cannot be tested directly since the system uses subnormal numbers.
    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(true, MPS.isZero());
}

