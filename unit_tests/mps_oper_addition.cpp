//
// Created by Jakob on 09.03.24.
//

#include "gtest/gtest.h"
#include "helper_functions.h"

#include "mps.h"


TEST(addition_tests, conversion_empty_object_double){

    double test_value = 234536.34634;

    mps MPS(52, 11, test_value);
    mps MPS_2(52, 11, test_value);

    mps result = MPS + MPS_2;

    EXPECT_EQ(MPS.getMantisseLength(), result.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), result.getExponentLength());
}

TEST(addition_tests, conversion_empty_object_float){

    float test_value = 234536.34634f;

    mps MPS(23, 8, test_value);
    mps MPS_2(23, 8, test_value);

    mps result = MPS + MPS_2;

    EXPECT_EQ(MPS_2.getMantisseLength(), result.getMantisseLength());
    EXPECT_EQ(MPS_2.getExponentLength(), result.getExponentLength());
}

TEST(addition_tests, addition_same_double) {

    double value_1 = 1.05;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_1);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_1), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_1, MPS_2.getValue());
}

TEST(addition_tests, addition_same_float) {

    float value_1 = 1.05f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_1);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_1), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_1, MPS_2.getValue());
}

TEST(addition_tests, addition_double) {

    double value_1 = 1.05;
    double value_2 = 2.1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, addition_float) {

    float value_1 = 1.05f;
    float value_2 = 2.1f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, addition2_double) {

    double value_1 = 2453.45645;
    double value_2 = 124779.3456;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, addition2_float) {

    float value_1 = 2453.45645f;
    float value_2 = 124779.3456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, addition3_double) {

    double value_1 = 0.0345;
    double value_2 = 0.000435345;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, addition3_float) {

    float value_1 = 0.0345f;
    float value_2 = 0.000435345f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, zero_left_double) {

    double value_1 = 0;
    double value_2 = 346.4367;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, zero_left_float) {

    float value_1 = 0;
    float value_2 = 346.4367f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, zero_right_double) {

    double value_1 = 23456.356;
    double value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, zero_right_float) {

    float value_1 = 23456.356f;
    float value_2 = 0;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, additition_negative_double) {

    double value_1 = -345.346;
    double value_2 = -0.00456345;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, addition_negative_float) {

    float value_1 = -345.346f;
    float value_2 = -0.00456345f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, negative_first_number_double) {

    double value_1 = -345.346;
    double value_2 = 238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1+value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, negative_first_number_float) {

    float value_1 = -345.346f;
    float value_2 = 238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, negative_second_number_double) {

    double value_1 = 345.346;
    double value_2 = -238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, negative_second_number_float) {

    float value_1 = 345.346f;
    float value_2 = -238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, over_max_double) {

    double value_1 = numeric_limits<double>::max();
    double value_2 = pow(2, 1000);

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, test.isInf());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, over_max_float) {

    float value_1 = numeric_limits<float>::max();
    auto value_2 = (float) pow(2, 110);

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, test.isInf());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, over_max_negative_double) {

    double value_1 = numeric_limits<double>::max() * -1;
    double value_2 = pow(2, 1000) * -1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, test.isInf());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, over_max_negative_float) {

    float value_1 = numeric_limits<float>::max() * -1;
    float value_2 = (float) pow(2, 110) * -1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, test.isInf());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, NAN_left_double) {

    double value_1 = NAN;
    double value_2 = -238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(isnan(value_1+value_2), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, isnan(MPS.getValue()));
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, NAN_left_float) {

    float value_1 = NAN;
    float value_2 = -238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(isnan(value_2+value_1), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(true, isnan(MPS.getValue()));
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, NAN_right_double) {

    double value_1 = 345.346;
    double value_2 = NAN;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(isnan(value_1+value_2), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(true, isnan(MPS_2.getValue()));
}

TEST(addition_tests, NAN_right_float) {

    float value_1 = 345.346f;
    float value_2 = NAN;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(isnan(value_2+value_1), isnan(test.getValue()));
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(true, isnan(MPS_2.getValue()));
}

TEST(addition_tests, inf_left_double) {

    double value_1 = numeric_limits<double>::infinity();
    double value_2 = 238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

}

TEST(addition_tests, inf_left_float) {

    float value_1 = numeric_limits<float>::infinity();
    float value_2 = 238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, inf_right_double) {

    double value_1 = 345.346;
    double value_2 = numeric_limits<double>::infinity();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, inf_right_float) {

    float value_1 = 345.346f;
    float value_2 = numeric_limits<float>::infinity();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, neg_inf_left_double) {

    double value_1 = numeric_limits<double>::infinity() * -1;
    double value_2 = 238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, neg_inf_left_float) {

    float value_1 = numeric_limits<float>::infinity() * -1;
    float value_2 = 238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, neg_inf_right_double) {

    double value_1 = 345.346;
    double value_2 = numeric_limits<double>::infinity() * -1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, neg_inf_right_float) {

    float value_1 = 345.346f;
    float value_2 = numeric_limits<float>::infinity() * -1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, pos_pos_inf_double) {

    double value_1 = numeric_limits<double>::infinity();
    double value_2 = numeric_limits<double>::infinity();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1+value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, pos_pos_inf_right_float) {

    float value_1 = numeric_limits<float>::infinity();
    float value_2 = numeric_limits<float>::infinity();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1+value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, neg_neg_inf_double) {

    double value_1 = numeric_limits<double>::infinity() * -1;
    double value_2 = numeric_limits<double>::infinity() * -1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1+value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, neg_neg_inf_right_float) {

    float value_1 = numeric_limits<float>::infinity() * -1;
    float value_2 = numeric_limits<float>::infinity() * -1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2,test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(isnan(value_1+value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, neg_pos_inf_double) {

    double value_1 = numeric_limits<double>::infinity() * -1;
    double value_2 = numeric_limits<double>::infinity();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(isnan(value_1+value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

#ifdef __APPLE__
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
#else
    test.setSign(true);
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
#endif
}

TEST(addition_tests, neg_pos_inf_float) {

    float value_1 = numeric_limits<float>::infinity() * -1;
    float value_2 = numeric_limits<float>::infinity();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(isnan(value_2+value_1), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

#ifdef __APPLE__
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
#else
    test.setSign(true);
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
#endif
}

TEST(addition_tests, pos_neg_inf_double) {

    double value_1 = numeric_limits<double>::infinity();
    double value_2 = numeric_limits<double>::infinity() * -1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(isnan(value_1+value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

#ifdef __APPLE__
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
#else
    test.setSign(true);
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
#endif
}

TEST(addition_tests, pos_neg_inf_right_float) {

    float value_1 = numeric_limits<float>::infinity();
    float value_2 = numeric_limits<float>::infinity() * -1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(isnan(value_1+value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

#ifdef __APPLE__
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
#else
    test.setSign(true);
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
#endif
}

TEST(addition_tests, zero_left_adv_double) {

    double value_1 = 0;
    double value_2 = 234534523;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

    MPS = 435.35;
    MPS_2 = 435.35;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(435.35, MPS.getValue());
    EXPECT_EQ(435.35, MPS_2.getValue());
}

TEST(addition_tests, zero_left_adv_float) {

    float value_1 = 0;
    float value_2 = 3456345.06f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

    MPS = 435.35f;
    MPS_2 = 435.35f;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(435.35f, MPS.getValue());
    EXPECT_EQ(435.35f, MPS_2.getValue());
}

TEST(addition_tests, zero_right_adv_double) {

    double value_1 = 234534523;
    double value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

    MPS = 435.35;
    MPS_2 = 435.35;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(435.35, MPS.getValue());
    EXPECT_EQ(435.35, MPS_2.getValue());
}

TEST(addition_tests, zero_right_adv_float) {

    float value_1 = 3456345.06f;
    float value_2 = 0;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());

    MPS = 435.35f;
    MPS_2 = 435.35f;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(435.35f, MPS.getValue());
    EXPECT_EQ(435.35f, MPS_2.getValue());
}

TEST(addition_tests, larger_left_exp_double) {

    double value_1 = 4.0;
    double value_2 = 2.0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, larger_left_exp_float) {

    float value_1 = 4.0f;
    float value_2 = 2.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, larger_right_exp_double) {

    double value_1 = 2.0;
    double value_2 = 4.0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, larger_right_exp_float) {

    float value_1 = 2.0f;
    float value_2 = 4.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, same_exp_larger_left_double) {

    double value_1 = 3.0;
    double value_2 = 2.0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, same_exp_larger_left_float) {

    float value_1 = 3.0f;
    float value_2 = 2.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, same_exp_larger_right_double) {

    double value_1 = 2.0;
    double value_2 = 3.0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, same_exp_larger_right_float) {

    float value_1 = 2.0f;
    float value_2 = 3.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, max_min_double) {

    double value_1 = numeric_limits<double>::max();
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, max_min_float) {

    float value_1 = numeric_limits<float>::max();
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, min_max_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::max();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, min_max_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::max();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, max_exp_diff_left_double) {

    double value_1 = numeric_limits<double>::min()*pow(2, 52);
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, max_exp_diff_left_float) {

    float value_1 = numeric_limits<float>::min() * ((float) pow(2, 23));
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, over_max_exp_diff_left_double) {

    double value_1 = numeric_limits<double>::min()*pow(2, 53);
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, over_max_exp_diff_left_float) {

    float value_1 = numeric_limits<float>::min() * ((float) pow(2, 24));
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, max_exp_diff_right_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::min()*pow(2, 52);

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, max_exp_diff_right_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::min() * ((float) pow(2, 23));

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, over_max_exp_diff_right_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::min()*pow(2, 53);

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, over_max_exp_diff_right_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::min() * ((float) pow(2, 24));

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, addition_special_float) {

    float value_1 = 2.0f / 3.0f;
    float value_2 = 3.0f + (1.0f/3.0f);

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(should_value(value_1 + value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}



TEST(addition, rounding_exponent_overflow_float) {

vector<bool> exponent_one{1, 1, 1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
vector<bool> mantissa_one{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
mps MPS_one(23,8);
MPS_one.setSign(false);
MPS_one.setExponent(exponent_one);
MPS_one.setMantissa(mantissa_one);

vector<bool> exponent_two{1, 1, 1, 1, 1, 1, 0, 0}; // NOLINT(*-use-bool-literals)
vector<bool> mantissa_two{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}; // NOLINT(*-use-bool-literals)
mps MPS_two(23,8);
MPS_two.setSign(false);
MPS_two.setExponent(exponent_two);
MPS_two.setMantissa(mantissa_two);

auto MPS_result = MPS_one + MPS_two;

EXPECT_EQ(((float) MPS_one.getValue()) + ((float) MPS_two.getValue()), (float) MPS_result.getValue());
EXPECT_EQ(should_value( ((float) MPS_one.getValue()) + ((float) MPS_two.getValue())), MPS_result.print());
}

// rounding when the exponent_diff is equal than mantissa.size() +1
TEST(addition, special_left_float) {

    vector<bool> exponent_one{0, 1, 1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_one{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}; // NOLINT(*-use-bool-literals)
    mps MPS_one(23,8);
    MPS_one.setSign(false);
    MPS_one.setExponent(exponent_one);
    MPS_one.setMantissa(mantissa_one);

    vector<bool> exponent_two{0, 1, 1, 0, 0, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_two{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    mps MPS_two(23,8);
    MPS_two.setSign(false);
    MPS_two.setExponent(exponent_two);
    MPS_two.setMantissa(mantissa_two);

    auto MPS_result = MPS_one + MPS_two;

    EXPECT_EQ(((float) MPS_one.getValue()) + ((float) MPS_two.getValue()), (float) MPS_result.getValue());
    EXPECT_EQ(should_value( ((float) MPS_one.getValue()) + ((float) MPS_two.getValue())), MPS_result.print());
}

TEST(addition, special_left_overflow_float) {

    vector<bool> exponent_one{0, 1, 1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_one{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    mps MPS_one(23,8);
    MPS_one.setSign(false);
    MPS_one.setExponent(exponent_one);
    MPS_one.setMantissa(mantissa_one);

    vector<bool> exponent_two{0, 1, 1, 0, 0, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_two{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    mps MPS_two(23,8);
    MPS_two.setSign(false);
    MPS_two.setExponent(exponent_two);
    MPS_two.setMantissa(mantissa_two);

    auto MPS_result = MPS_one + MPS_two;

    EXPECT_EQ(((float) MPS_one.getValue()) + ((float) MPS_two.getValue()), (float) MPS_result.getValue());
    EXPECT_EQ(should_value( ((float) MPS_one.getValue()) + ((float) MPS_two.getValue())), MPS_result.print());
}

TEST(addition, special_left_overflow_overflow_float) {

    vector<bool> exponent_one{1, 1, 1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_one{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    mps MPS_one(23,8);
    MPS_one.setSign(false);
    MPS_one.setExponent(exponent_one);
    MPS_one.setMantissa(mantissa_one);

    vector<bool> exponent_two{1, 1, 1, 0, 0, 1, 1, 0};// NOLINT(*-use-bool-literals)
    vector<bool> mantissa_two{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};// NOLINT(*-use-bool-literals)
    mps MPS_two(23,8);
    MPS_two.setSign(false);
    MPS_two.setExponent(exponent_two);
    MPS_two.setMantissa(mantissa_two);

    auto MPS_result = MPS_one + MPS_two;

    EXPECT_EQ(((float) MPS_one.getValue()) + ((float) MPS_two.getValue()), (float) MPS_result.getValue());
    EXPECT_EQ(should_value( ((float) MPS_one.getValue()) + ((float) MPS_two.getValue())), MPS_result.print());
}

TEST(addition, special_right_float) {

    vector<bool> exponent_one{0, 1, 1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_one{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}; // NOLINT(*-use-bool-literals)
    mps MPS_one(23,8);
    MPS_one.setSign(false);
    MPS_one.setExponent(exponent_one);
    MPS_one.setMantissa(mantissa_one);

    vector<bool> exponent_two{0, 1, 1, 0, 0, 1, 1, 1};// NOLINT(*-use-bool-literals)
    vector<bool> mantissa_two{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};// NOLINT(*-use-bool-literals)
    mps MPS_two(23,8);
    MPS_two.setSign(false);
    MPS_two.setExponent(exponent_two);
    MPS_two.setMantissa(mantissa_two);

    auto MPS_result = MPS_two + MPS_one;

    EXPECT_EQ(((float) MPS_one.getValue()) + ((float) MPS_two.getValue()), (float) MPS_result.getValue());
    EXPECT_EQ(should_value( ((float) MPS_one.getValue()) + ((float) MPS_two.getValue())), MPS_result.print());
}

TEST(addition, special_right_overflow_float) {

    vector<bool> exponent_one{0, 1, 1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_one{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    mps MPS_one(23,8);
    MPS_one.setSign(false);
    MPS_one.setExponent(exponent_one);
    MPS_one.setMantissa(mantissa_one);

    vector<bool> exponent_two{0, 1, 1, 0, 0, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_two{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // NOLINT(*-use-bool-literals)
    mps MPS_two(23,8);
    MPS_two.setSign(false);
    MPS_two.setExponent(exponent_two);
    MPS_two.setMantissa(mantissa_two);

    auto MPS_result = MPS_two + MPS_one;

    EXPECT_EQ(((float) MPS_one.getValue()) + ((float) MPS_two.getValue()), (float) MPS_result.getValue());
    EXPECT_EQ(should_value( ((float) MPS_one.getValue()) + ((float) MPS_two.getValue())), MPS_result.print());
}

TEST(addition, special_right_overflow_overflow_float) {

    vector<bool> exponent_one{1, 1, 1, 1, 1, 1, 1, 0}; // NOLINT(*-use-bool-literals)
    vector<bool> mantissa_one{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // NOLINT(*-use-bool-literals)
    mps MPS_one(23,8);
    MPS_one.setSign(false);
    MPS_one.setExponent(exponent_one);
    MPS_one.setMantissa(mantissa_one);

    vector<bool> exponent_two{1, 1, 1, 0, 0, 1, 1, 0};// NOLINT(*-use-bool-literals)
    vector<bool> mantissa_two{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};// NOLINT(*-use-bool-literals)
    mps MPS_two(23,8);
    MPS_two.setSign(false);
    MPS_two.setExponent(exponent_two);
    MPS_two.setMantissa(mantissa_two);

    auto MPS_result = MPS_two + MPS_one;

    EXPECT_EQ(((float) MPS_one.getValue()) + ((float) MPS_two.getValue()), (float) MPS_result.getValue());
    EXPECT_EQ(should_value( ((float) MPS_one.getValue()) + ((float) MPS_two.getValue())), MPS_result.print());
}


