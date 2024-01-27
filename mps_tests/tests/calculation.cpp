#include "gtest/gtest.h"

#include "mps.h"
#include "../functions/functions.h"


TEST(equality_tests, equality_pos_double){

    double test_value = 234536.34634;
    mps MPS(52, 11, test_value);

    mps MPS_copy = MPS;

    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());
}

TEST(equality_tests, equality_pos_float){

    float test_value = 234536.34634f;

    mps* MPS = new mps(23, 8, test_value);

    mps* MPS_copy = MPS;

    EXPECT_EQ(MPS->getMantisseLength(), MPS_copy->getMantisseLength());
    EXPECT_EQ(MPS->getExponentLength(), MPS_copy->getExponentLength());
    EXPECT_EQ(test_value, MPS_copy->getValue());
}

TEST(equality_tests, equality_neg_double){

    double test_value = -234536.34634;

    mps* MPS = new mps(52, 11, test_value);

    mps* MPS_copy = MPS;

    EXPECT_EQ(MPS->getMantisseLength(), MPS_copy->getMantisseLength());
    EXPECT_EQ(MPS->getExponentLength(), MPS_copy->getExponentLength());
    EXPECT_EQ(test_value, MPS_copy->getValue());
}

TEST(equality_tests, equality_neg_float){

    float test_value = -234536.34634f;

    mps* MPS = new mps(23, 8, test_value);

    mps* MPS_copy = MPS;

    EXPECT_EQ(MPS->getMantisseLength(), MPS_copy->getMantisseLength());
    EXPECT_EQ(MPS->getExponentLength(), MPS_copy->getExponentLength());
    EXPECT_EQ(test_value, MPS_copy->getValue());
}




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
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_1, MPS_2.getValue());
}

TEST(addition_tests, addition_same_float) {

    float value_1 = 1.05f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_1);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_1, test.getValue());
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
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(addition_tests, zero_right_float) {

    float value_1 = 23456.356f;
    float value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
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
    EXPECT_EQ(true, test.isInfinity());
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
    EXPECT_EQ(true, test.isInfinity());
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
    EXPECT_EQ(true, test.isInfinity());
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
    EXPECT_EQ(true, test.isInfinity());
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
    EXPECT_EQ(435.35f, MPS.getValue());
    EXPECT_EQ(435.35f, MPS_2.getValue());
}



TEST(subtraction_tests, coding) {

    float value_1 = -3453.3456f;
    float value_2 = -45456.456f;

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
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negative_subtractiob_float) {

    float value_1 = -8567.78f;
    float value_2 = -675.67f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(subtraction_tests, negative_subtractiob2_double) {

    double value_1 = -8567.78;
    double value_2 = -675.67;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
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
}

TEST(subtraction_tests, neg_pos_inf_double) {

    double value_1 = numeric_limits<double>::infinity() * -1;
    double value_2 = numeric_limits<double>::infinity();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
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
    EXPECT_EQ(435.35f, MPS.getValue());
    EXPECT_EQ(435.35f, MPS_2.getValue());
}


TEST(multiplication_tests, coding) {

    float value_1 = -0.0000045f;
    float value_2 = 0.000000000000000001f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(should_value(value_1 * value_2), is_mps(test.getBitArray()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_float_1) {

    float value_1 = 46547.3456f;
    float value_2 = 3463.678f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_double_1) {

    double value_1 = 46547.3456;
    double value_2 = 3463.678;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_float_2) {

    float value_1 = 345.3453f;
    float value_2 = 0.0034534f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_double_2) {

    double value_1 = 345.3453;
    double value_2 = 0.0034534;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_float_3) {

    float value_1 = 0.000643f;
    float value_2 = 234.2352f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_double_3) {

    double value_1 = 0.000643;
    double value_2 = 234.2352;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_float_4) {

    float value_1 = 0.00342f;
    float value_2 = 0.0000456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_double_4) {

    double value_1 = 0.00342;
    double value_2 = 0.0000456;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_float_5) {

    float value_1 = -3563.346f;
    float value_2 = 0.0046646f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_double_5) {

    double value_1 = -3563.346;
    double value_2 = 0.0046646;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_float_6) {

    float value_1 = 3563.346f;
    float value_2 = -0.0046646f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_double_6) {

    double value_1 = 3563.346;
    double value_2 = -0.0046646;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_float_7) {

    float value_1 = -3454;
    float value_2 = -0.00463f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, multiplication_double_7) {

    double value_1 = 3454;
    double value_2 = -0.00463;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, pos_pos_float) {

    float value_1 = 45.2352f;
    float value_2 = 78.5f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, pos_pos_double) {

    double value_1 = 45.2352;
    double value_2 = 78.5;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, neg_neg_float) {

    float value_1 = -74464.5674f;
    float value_2 = -3464.4656f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, neg_neg_double) {

    double value_1 = -74464.5674;
    double value_2 = -3464.4656;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, pos_neg_float) {

    float value_1 = 12854.346345f;
    float value_2 = -48442.559f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, pos_neg_double) {

    double value_1 = 12854.346345;
    double value_2 = -48442.559;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, neg_pos_float) {

    float value_1 = -845.346f;
    float value_2 = 634.7345f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, neg_pos_double) {

    double value_1 = -845.346;
    double value_2 = 634.7345;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, small_small_float) {

float value_1 = 0.0000034f;
float value_2 = 0.0000784f;

mps MPS(23,8,value_1);
mps MPS_2(23,8,value_2);

auto test = MPS * MPS_2;

EXPECT_EQ(value_1*value_2, test.getValue());
EXPECT_EQ(value_1, MPS.getValue());
EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, small_small_double) {

    double value_1 = 0.0000034;
    double value_2 = 0.0000784;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, large_large_float) {

    float value_1 = 456345.456f;
    float value_2 = 853546.34674f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, large_large_double) {

    double value_1 = 456346345.456;
    double value_2 = 853534546.34674;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, large_small_float) {

    float value_1 = 456345.456f;
    float value_2 = 0.00034525f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, large_small_double) {

    double value_1 = 456346345.456;
    double value_2 = 0.0000000034525;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, small_large_float) {

    float value_1 = 0.00034525f;
    float value_2 = 456345.456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, small_large_double) {

    double value_1 = 0.0000000034525;
    double value_2 = 456346345.456;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, max_min_float) {

    float value_1 = numeric_limits<float>::max();
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, max_min_double) {

    double value_1 = numeric_limits<double>::max();
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, min_max_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::max();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, min_max_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::max();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, min_min_float) {

    float value_1 = numeric_limits<float>::min();
    float value_2 = numeric_limits<float>::min();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, min_min_double) {

    double value_1 = numeric_limits<double>::min();
    double value_2 = numeric_limits<double>::min();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, max_max_float) {

    float value_1 = numeric_limits<float>::max();
    float value_2 = numeric_limits<float>::max();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, max_max_double) {

    double value_1 = numeric_limits<double>::max();
    double value_2 = numeric_limits<double>::max();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, very_small_float) {

    float value_1 = 0.000000000000000000000000000000000006f;
    float value_2 = 0.00000000000000000000000000000000000004f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, very_small_double) {

    double value_1 = 0.0000000000000000000000000000000000000000000000000000006;
    double value_2 = 0.00000000000000000000000000000000000000000000000000004;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, one_one_float) {

    float value_1 = 1.0f;
    float value_2 = 1.0f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, one_one_double) {

    double value_1 = 1.0;
    double value_2 = 1.0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, NAN_left_float) {

    float value_1 = NAN;
    float value_2 = 346346.34f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(value_1*value_2));
    EXPECT_EQ(true, isnan(value_1));
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, NAN_left_double) {

    double value_1 = NAN;
    double value_2 = 346346.34;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(value_1*value_2));
    EXPECT_EQ(true, isnan(value_1));
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, NAN_right_float) {

    float value_1 = 346346.34f;
    float value_2 = NAN;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(value_1*value_2));
    EXPECT_EQ(true, isnan(value_2));
    EXPECT_EQ(value_1, MPS.getValue());
}

TEST(multiplication_tests, NAN_right_double) {

    double value_1 = 346346.34;
    double value_2 = NAN;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(true, isnan(value_1*value_2));
    EXPECT_EQ(true, isnan(value_2));
    EXPECT_EQ(value_1, MPS.getValue());
}

TEST(multiplication_tests, pos_inf_left_float) {

    float value_1 = numeric_limits<float>::infinity();
    float value_2 = 346346.34f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, pos_inf_left_double) {

    double value_1 = numeric_limits<double>::infinity();
    double value_2 = 346346.34;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, pos_inf_right_float) {

    float value_1 = 346346.34f;
    float value_2 = numeric_limits<float>::infinity();

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, pos_inf_right_double) {

    double value_1 = 346346.34;
    double value_2 = numeric_limits<double>::infinity();

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, neg_inf_left_float) {

    float value_1 = numeric_limits<float>::infinity() * -1;
    float value_2 = 346346.34f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, neg_inf_left_double) {

    double value_1 = numeric_limits<double>::infinity() * -1;
    double value_2 = 346346.34;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, neg_inf_right_float) {

    float value_1 = 346346.34f;
    float value_2 = numeric_limits<float>::infinity() * -1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, neg_inf_right_double) {

    double value_1 = 346346.34;
    double value_2 = numeric_limits<double>::infinity() * -1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(isnan(value_1*value_2), isnan(test.getValue()));
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, zero_left_float) {

    float value_1 = 0;
    float value_2 = 346346.34f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, zero_left_double) {

    double value_1 = 0;
    double value_2 = 346346.34;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, zero_right_float) {

    float value_1 = 346346.34f;
    float value_2 = 0;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}

TEST(multiplication_tests, zero_right_double) {

    double value_1 = 346346.34;
    double value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1, MPS.getValue());
    EXPECT_EQ(value_2, MPS_2.getValue());
}


