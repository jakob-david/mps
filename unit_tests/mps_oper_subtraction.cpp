//
// Created by Jakob on 09.03.24.
//

#include "gtest/gtest.h"
#include "helper_functions.h"

#include "mps.h"


TEST(subtraction_tests, coding) {

    float value_1 = 2.0f;
    float value_2 = 3.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, simple_subtractiob_float) {

    float value_1 = 2.1f;
    float value_2 = 1.05f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, simple_subtractiob_double) {

    double value_1 = 2.1;
    double value_2 = 1.05;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, subtractiob_float) {

    float value_1 = 34466.45346f;
    float value_2 = 3453.35f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, subtractiob_double) {

    double value_1 = 34466.45346;
    double value_2 = 3453.35;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, larger_left_exp_double) {

    double value_1 = 4.0;
    double value_2 = 2.0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, larger_left_exp_float) {

    float value_1 = 4.0f;
    float value_2 = 2.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, larger_right_exp_double) {

    double value_1 = 2.0;
    double value_2 = 4.0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, larger_right_exp_float) {

    float value_1 = 2.0f;
    float value_2 = 4.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, same_exp_larger_left_double) {

    double value_1 = 3.0;
    double value_2 = 2.0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, same_exp_larger_left_float) {

    float value_1 = 3.0f;
    float value_2 = 2.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, same_exp_larger_right_double) {

    double value_1 = 2.0;
    double value_2 = 3.0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, same_exp_larger_right_float) {

    float value_1 = 2.0f;
    float value_2 = 3.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negative_subtraction_float) {

    float value_1 = -8567.78f;
    float value_2 = -675.67f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negative_subtraction_double) {

    double value_1 = -8567.78;
    double value_2 = -675.67;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, positive_zero_crossing_float) {

    float value_1 = 2345.3345f;
    float value_2 = 356456346.45f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, npositive_zero_crossing_double) {

    double value_1 = 2345.3345;
    double value_2 = 356456346.45;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negative_zero_crossing_float) {

    float value_1 = -3453.3456f;
    float value_2 = -45456.456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negative_zero_crossing_double) {

    double value_1 = -3453.3456;
    double value_2 = -45456.456;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negatave_first_number_float) {

    float value_1 = -46547.3456f;
    float value_2 = 3463.678f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negatave_first_number_double) {

    double value_1 = -46547.3456;
    double value_2 = 3463.678;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negatave_second_number_float) {

    float value_1 = 46547.3456f;
    float value_2 = -3463.678f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negatave_second_number_double) {

    double value_1 = 46547.3456;
    double value_2 = -3463.678;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, NAN_left_double) {

    double value_1 = NAN;
    double value_2 = -238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, isnan(value_1));
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, NAN_left_float) {

    float value_1 = NAN;
    float value_2 = -238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(isnan(value_2-value_1), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, isnan(value_1));
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, NAN_right_double) {

    double value_1 = 345.346;
    double value_2 = NAN;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(true, isnan(value_2));
}

TEST(subtraction_tests, NAN_right_float) {

    float value_1 = 345.346f;
    float value_2 = NAN;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(isnan(value_2-value_1), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(true, isnan(value_2));
}

TEST(subtraction_tests, inf_left_double) {

    double value_1 = numeric_limits<double>::infinity();
    double value_2 = 238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, inf_left_float) {

    float value_1 = numeric_limits<float>::infinity();
    float value_2 = 238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, inf_right_double) {

    double value_1 = 345.346;
    double value_2 = numeric_limits<double>::infinity();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, inf_right_float) {

    float value_1 = 345.346f;
    float value_2 = numeric_limits<float>::infinity();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, neg_inf_left_double) {

    double value_1 = numeric_limits<double>::infinity() * -1;
    double value_2 = 238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, neg_inf_left_float) {

    float value_1 = numeric_limits<float>::infinity() * -1;
    float value_2 = 238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, neg_inf_right_double) {

    double value_1 = 345.346;
    double value_2 = numeric_limits<double>::infinity() * -1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, neg_inf_right_float) {

    float value_1 = 345.346f;
    float value_2 = numeric_limits<float>::infinity() * -1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, pos_pos_inf_double) {

    double value_1 = numeric_limits<double>::infinity();
    double value_2 = numeric_limits<double>::infinity();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

#ifdef __APPLE__
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
#else
    test.setSign(true);
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
#endif
}

TEST(subtraction_tests, pos_pos_inf_right_float) {

    float value_1 = numeric_limits<float>::infinity();
    float value_2 = numeric_limits<float>::infinity();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

#ifdef __APPLE__
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
#else
    test.setSign(true);
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
#endif
}

TEST(subtraction_tests, neg_neg_inf_double) {

    double value_1 = numeric_limits<double>::infinity() * -1;
    double value_2 = numeric_limits<double>::infinity() * -1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

#ifdef __APPLE__
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
#else
    test.setSign(true);
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
#endif
}

TEST(subtraction_tests, neg_neg_inf_right_float) {

    float value_1 = numeric_limits<float>::infinity() * -1;
    float value_2 = numeric_limits<float>::infinity() * -1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

#ifdef __APPLE__
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
#else
    test.setSign(true);
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
#endif
}

TEST(subtraction_tests, neg_pos_inf_double) {

    double value_1 = numeric_limits<double>::infinity() * -1;
    double value_2 = numeric_limits<double>::infinity();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, neg_pos_inf_float) {

    float value_1 = numeric_limits<float>::infinity() * -1;
    float value_2 = numeric_limits<float>::infinity();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, pos_neg_inf_double) {

    double value_1 = numeric_limits<double>::infinity();
    double value_2 = numeric_limits<double>::infinity() * -1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, pos_neg_inf_right_float) {

    float value_1 = numeric_limits<float>::infinity();
    float value_2 = numeric_limits<float>::infinity() * -1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1-value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, zero_left_double) {

    double value_1 = 0;
    double value_2 = 234534523;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    MPS = 435.35;
    MPS_2 = 435.35;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(435.35, MPS.getValue());
    EXPECT_EQ(435.35, MPS_2.getValue());
}

TEST(subtraction_tests, zero_left_float) {

    float value_1 = 0;
    float value_2 = 3456345.06f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    MPS = 435.35f;
    MPS_2 = 435.35f;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(435.35f, MPS.getValue());
    EXPECT_EQ(435.35f, MPS_2.getValue());
}

TEST(subtraction_tests, zero_right_double) {

    double value_1 = 234534523;
    double value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    MPS = 435.35;
    MPS_2 = 435.35;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(435.35, MPS.getValue());
    EXPECT_EQ(435.35, MPS_2.getValue());
}

TEST(subtraction_tests, zero_right_float) {

    float value_1 = 3456345.06f;
    float value_2 = 0;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    MPS = 435.35f;
    MPS_2 = 435.35f;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(435.35f, MPS.getValue());
    EXPECT_EQ(435.35f, MPS_2.getValue());
}

TEST(subtraction_tests, max_min_double) {

    double value_1 = numeric_limits<double>::max();
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, max_min_float) {

    float value_1 = numeric_limits<float>::max();
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, min_max_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::max();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, min_max_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::max();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, max_exp_diff_left_double) {

    double value_1 = numeric_limits<double>::min()*pow(2, 52);
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, max_exp_diff_left_float) {

    float value_1 = numeric_limits<float>::min() * ((float) pow(2, 23));
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, over_max_exp_diff_left_double) {

    double value_1 = numeric_limits<double>::min()*pow(2, 53);
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, over_max_exp_diff_left_float) {

    float value_1 = numeric_limits<float>::min() * ((float) pow(2, 24));
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, max_exp_diff_right_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::min()*pow(2, 52);

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, max_exp_diff_right_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::min() * ((float) pow(2, 23));

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, over_max_exp_diff_right_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::min()*pow(2, 53);

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, over_max_exp_diff_right_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::min() * ((float) pow(2, 24));

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, spezial_1) {

    mps one(52,11);
    one.setSign(false);
    vector<bool> exponent_one{0, 1,1,1,1,1,1,1,1,1,1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_one{0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,1,1,0,0}; // NOLINT(*-use-bool-literals)
    one.setSign(false);
    one.setExponent(exponent_one);
    one.setMantissa(mantissa_one);

    mps two(52,11);
    two.setSign(false);
    vector<bool> exponent_two{0,1,1,1,1,0,0,1,0,1,0}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_two{1,0,1,0,1,1,0,1,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // NOLINT(*-use-bool-literals)
    two.setSign(false);
    two.setExponent(exponent_two);
    two.setMantissa(mantissa_two);


    auto result = one - two;

    EXPECT_EQ(one.getValue()-two.getValue(), result.getValue());
    EXPECT_EQ(should_value(one.getValue()-two.getValue()), is_mps(result.getBitArray()));
}

TEST(subtraction_tests, spezial_2) {

    mps one(52,11);
    one.setSign(false);
    vector<bool> exponent_one{0, 1,1,1,1,1,1,1,1,1,1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_one{0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,1,1,0,0}; // NOLINT(*-use-bool-literals)
    one.setSign(false);
    one.setExponent(exponent_one);
    one.setMantissa(mantissa_one);

    mps two(52,11);
    two.setSign(false);
    vector<bool> exponent_two{0,1,1,1,1,0,0,1,0,1,0}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_two{1,0,1,0,1,1,0,1,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // NOLINT(*-use-bool-literals)
    two.setSign(false);
    two.setExponent(exponent_two);
    two.setMantissa(mantissa_two);


    auto result = two - one;

    EXPECT_EQ(two.getValue()-one.getValue(), result.getValue());
    EXPECT_EQ(should_value(two.getValue()-one.getValue()), is_mps(result.getBitArray()));
}

TEST(subtraction_tests, subtractio_to_zero_double) {

    double value_1 = 2;
    double value_2 = 2;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, subtractio_to_zero_float) {

    float value_1 = 2.0f;
    float value_2 = 2.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 - value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}


TEST(subtraction, rounding_float) {

    vector<bool> exponent_one{1, 1, 1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_one{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}; // NOLINT(*-use-bool-literals)
    mps MPS_one(23,8);
    MPS_one.setSign(false);
    MPS_one.setExponent(exponent_one);
    MPS_one.setMantissa(mantissa_one);

    vector<bool> exponent_two{1, 1, 1, 0, 0, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_two{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    mps MPS_two(23,8);
    MPS_two.setSign(false);
    MPS_two.setExponent(exponent_two);
    MPS_two.setMantissa(mantissa_two);

    auto MPS_result = MPS_one - MPS_two;

    EXPECT_EQ(((float) MPS_one.getValue()) - ((float) MPS_two.getValue()), (float) MPS_result.getValue());
    EXPECT_EQ(should_value( ((float) MPS_one.getValue()) - ((float) MPS_two.getValue())), MPS_result.print());
}
