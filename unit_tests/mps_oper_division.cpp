//
// Created by Jakob on 09.03.24.
//

#include "gtest/gtest.h"
#include "helper_functions.h"

#include "mps.h"


TEST(division_tests, NAN_left_float) {

    float value_1 = NAN;
    float value_2 = 346346.34f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, isnan(value_1/value_2));
    EXPECT_EQ(true, isnan(value_1));
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, NAN_left_double) {

    double value_1 = NAN;
    double value_2 = 346346.34;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, isnan(value_1/value_2));
    EXPECT_EQ(true, isnan(value_1));
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, NAN_right_float) {

    float value_1 = 346346.34f;
    float value_2 = NAN;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, isnan(value_1/value_2));
    EXPECT_EQ(true, isnan(value_2));
    EXPECT_EQ(value_1, MPS.getValue());
}

TEST(division_tests, NAN_right_double) {

    double value_1 = 346346.34;
    double value_2 = NAN;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, isnan(value_1/value_2));
    EXPECT_EQ(true, isnan(value_2));
    EXPECT_EQ(value_1, MPS.getValue());
}

TEST(division_tests, pos_inf_left_float) {

    float value_1 = numeric_limits<float>::infinity();
    float value_2 = 346346.34f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, pos_inf_left_double) {

    double value_1 = numeric_limits<double>::infinity();
    double value_2 = 346346.34;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, pos_inf_right_float) {

    float value_1 = 346346.34f;
    float value_2 = numeric_limits<float>::infinity();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, pos_inf_right_double) {

    double value_1 = 346346.34;
    double value_2 = numeric_limits<double>::infinity();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_inf_left_float) {

    float value_1 = numeric_limits<float>::infinity() * -1;
    float value_2 = 346346.34f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_inf_left_double) {

    double value_1 = numeric_limits<double>::infinity() * -1;
    double value_2 = 346346.34;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_inf_right_float) {

    float value_1 = 346346.34f;
    float value_2 = numeric_limits<float>::infinity() * -1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_inf_right_double) {

    double value_1 = 346346.34;
    double value_2 = numeric_limits<double>::infinity() * -1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1/value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, zero_left_float) {

    float value_1 = 0;
    float value_2 = 346346.34f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, zero_left_double) {

    double value_1 = 0;
    double value_2 = 346346.34;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, pos_val_zero_right_float) {

    float value_1 = 346346.34f;
    float value_2 = 0;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, pos_val_zero_right_double) {

    double value_1 = 346346.34;
    double value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_val_zero_right_float) {

    float value_1 = -346346.34f;
    float value_2 = 0;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_val_zero_right_double) {

    double value_1 = -346346.34;
    double value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_float_1) {

    float value_1 = 46547.3456f;
    float value_2 = 3463.678f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_double_1) {

    double value_1 = 46547.3456;
    double value_2 = 3463.678;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_float_2) {

    float value_1 = 345.3453f;
    float value_2 = 0.0034534f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_double_2) {

    double value_1 = 345.3453;
    double value_2 = 0.0034534;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_float_3) {

    float value_1 = 0.000643f;
    float value_2 = 234.2352f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_double_3) {

    double value_1 = 0.000643;
    double value_2 = 234.2352;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_float_4) {

    float value_1 = 0.00342f;
    float value_2 = 0.0000456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_double_4) {

    double value_1 = 0.00342;
    double value_2 = 0.0000456;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_float_5) {

    float value_1 = -3563.346f;
    float value_2 = 0.0046646f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_double_5) {

    double value_1 = -3563.346;
    double value_2 = 0.0046646;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_float_6) {

    float value_1 = 3563.346f;
    float value_2 = -0.0046646f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_double_6) {

    double value_1 = 3563.346;
    double value_2 = -0.0046646;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_float_7) {

    float value_1 = -3454;
    float value_2 = -0.00463f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, division_double_7) {

    double value_1 = 3454;
    double value_2 = -0.00463;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, pos_pos_float) {

    float value_1 = 45.2352f;
    float value_2 = 78.5f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, pos_pos_double) {

    double value_1 = 45.2352;
    double value_2 = 78.5;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_neg_float) {

    float value_1 = -74464.5674f;
    float value_2 = -3464.4656f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_neg_double) {

    double value_1 = -74464.5674;
    double value_2 = -3464.4656;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, pos_neg_float) {

    float value_1 = 12854.346345f;
    float value_2 = -48442.559f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, pos_neg_double) {

    double value_1 = 12854.346345;
    double value_2 = -48442.559;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_pos_float) {

    float value_1 = -845.346f;
    float value_2 = 634.7345f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, neg_pos_double) {

    double value_1 = -845.346;
    double value_2 = 634.7345;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, small_small_float) {

    float value_1 = 0.0000034f;
    float value_2 = 0.0000784f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, small_small_double) {

    double value_1 = 0.0000034;
    double value_2 = 0.0000784;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, large_large_float) {

    float value_1 = 456345.456f;
    float value_2 = 853546.34674f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, large_large_double) {

    double value_1 = 456346345.456;
    double value_2 = 853534546.34674;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, large_small_float) {

    float value_1 = 456345.456f;
    float value_2 = 0.00034525f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, large_small_double) {

    double value_1 = 456346345.456;
    double value_2 = 0.0000000034525;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, small_large_float) {

    float value_1 = 0.00034525f;
    float value_2 = 456345.456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, small_large_double) {

    double value_1 = 0.0000000034525;
    double value_2 = 456346345.456;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, max_min_float) {

    float value_1 = numeric_limits<float>::max();
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, max_min_double) {

    double value_1 = numeric_limits<double>::max();
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, min_max_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::max();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, min_max_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::max();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, min_min_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, min_min_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, max_max_float) {

    float value_1 = numeric_limits<float>::max();
    float value_2 = numeric_limits<float>::max();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, max_max_double) {

    double value_1 = numeric_limits<double>::max();
    double value_2 = numeric_limits<double>::max();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, over_max_float) {

    float value_1 = numeric_limits<float>::max();
    float value_2 = 0.5f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(division_tests, over_max_double) {

    double value_1 = numeric_limits<double>::max();
    double value_2 = 0.5;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}


TEST(division_tests, four_seven_double) {

    double value_1 = 4;
    double value_2 = 7;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(value_1/value_2, test.getValue());
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}




TEST(division_tests, coding) {

    float value_1 = 0.000643f;
    float value_2 = 234.2352f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS / MPS_2;

    EXPECT_EQ(should_value(value_1 / value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(should_value(value_1/value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}