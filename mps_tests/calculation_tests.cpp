#include "gtest/gtest.h"

#include "mps.h"
#include <bitset>

std::string is_mps2(vector<bool> vec){

    string str;
    for(bool bit : vec){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    return str;
}

template <typename T>
std::string should_value2(T fp_number){

    string compare_str;
    char* bits = reinterpret_cast<char*>(&fp_number);
    for(unsigned long n = 0; n < sizeof fp_number; ++n) {
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    return  compare_str;
}



TEST(equality_tests, equality_pos_double){

    double test_value = 234536.34634;

    mps* MPS = new mps(52, 11, test_value);

    mps* MPS_copy = MPS;

    EXPECT_EQ(MPS->getMantisseLength(), MPS_copy->getMantisseLength());
    EXPECT_EQ(MPS->getExponentLength(), MPS_copy->getExponentLength());
    EXPECT_EQ(test_value, MPS_copy->getValue());
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
    EXPECT_EQ(value_1+value_1, test.my_getValue());
}

TEST(addition_tests, addition_same_float) {

    float value_1 = 1.05f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_1);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_1, test.getValue());
    EXPECT_EQ(value_1+value_1, test.my_getValue());
}

TEST(addition_tests, addition_double) {

    double value_1 = 1.05;
    double value_2 = 2.1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, addition_float) {

    float value_1 = 1.05f;
    float value_2 = 2.1f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, addition2_double) {

    double value_1 = 2453.45645;
    double value_2 = 124779.3456;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, addition2_float) {

    float value_1 = 2453.45645f;
    float value_2 = 124779.3456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, addition3_double) {

    double value_1 = 0.0345;
    double value_2 = 0.000435345;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, addition3_float) {

    float value_1 = 0.0345f;
    float value_2 = 0.000435345f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, zero_left_double) {

    double value_1 = 0;
    double value_2 = 346.4367;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, zero_left_float) {

    float value_1 = 0;
    float value_2 = 346.4367f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, zero_right_double) {

    double value_1 = 23456.356;
    double value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, zero_right_float) {

    float value_1 = 23456.356f;
    float value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, additition_negative_double) {

    double value_1 = -345.346;
    double value_2 = -0.00456345;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, addition_negative_float) {

    float value_1 = -345.346f;
    float value_2 = -0.00456345f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_2+value_1, test.my_getValue());
}

TEST(addition_tests, negative_first_number_double) {

    double value_1 = -345.346;
    double value_2 = 238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, negative_first_number_float) {

    float value_1 = -345.346f;
    float value_2 = 238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, negative_second_number_double) {

    double value_1 = 345.346;
    double value_2 = -238683.355;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}

TEST(addition_tests, negative_second_number_float) {

    float value_1 = 345.346f;
    float value_2 = -238683.355f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
    EXPECT_EQ(value_1+value_2, test.my_getValue());
}



TEST(subtraction_tests, coding) {

    float value_1 = -3453.3456f;
    float value_2 = -45456.456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(should_value2(value_1 - value_2), is_mps2(test.getBitArray()));
}

TEST(subtraction_tests, simple_subtractiob_float) {

    float value_1 = 2.1f;
    float value_2 = 1.05f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, simple_subtractiob_double) {

    double value_1 = 2.1;
    double value_2 = 1.05;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, subtractiob_float) {

    float value_1 = 34466.45346f;
    float value_2 = 3453.35f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, subtractiob_double) {

    double value_1 = 34466.45346;
    double value_2 = 3453.35;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, negative_subtractiob_float) {

    float value_1 = -8567.78f;
    float value_2 = -675.67f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, negative_subtractiob2_double) {

    double value_1 = -8567.78;
    double value_2 = -675.67;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, positive_zero_crossing_float) {

    float value_1 = 2345.3345f;
    float value_2 = 356456346.45f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, npositive_zero_crossing_double) {

    double value_1 = 2345.3345;
    double value_2 = 356456346.45;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, negative_zero_crossing_float) {

    float value_1 = -3453.3456f;
    float value_2 = -45456.456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, negative_zero_crossing_double) {

    double value_1 = -3453.3456;
    double value_2 = -45456.456;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, negatave_first_number_float) {

    float value_1 = -46547.3456f;
    float value_2 = 3463.678f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, negatave_first_number_double) {

    double value_1 = -46547.3456;
    double value_2 = 3463.678;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, negatave_second_number_float) {

    float value_1 = 46547.3456f;
    float value_2 = -3463.678f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}

TEST(subtraction_tests, negatave_second_number_double) {

    double value_1 = 46547.3456;
    double value_2 = -3463.678;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS - MPS_2;

    EXPECT_EQ(value_1-value_2, test.getValue());
    EXPECT_EQ(value_1-value_2, test.my_getValue());
}


TEST(multiplication_tests, coding) {

    float value_1 = -0.0000045f;
    float value_2 = 0.000000000000000001f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(should_value2(value_1 * value_2), is_mps2(test.getBitArray()));
}

TEST(multiplication_tests, multiplication_float_1) {

    float value_1 = 46547.3456f;
    float value_2 = 3463.678f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_double_1) {

    double value_1 = 46547.3456;
    double value_2 = 3463.678;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_float_2) {

    float value_1 = 345.3453f;
    float value_2 = 0.0034534f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_double_2) {

    double value_1 = 345.3453;
    double value_2 = 0.0034534;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_float_3) {

    float value_1 = 0.000643f;
    float value_2 = 234.2352f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_double_3) {

    double value_1 = 0.000643;
    double value_2 = 234.2352;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_float_4) {

    float value_1 = 0.00342f;
    float value_2 = 0.0000456f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_double_4) {

    double value_1 = 0.00342;
    double value_2 = 0.0000456;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_float_5) {

    float value_1 = -3563.346f;
    float value_2 = 0.0046646f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_double_5) {

    double value_1 = -3563.346;
    double value_2 = 0.0046646;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_float_6) {

    float value_1 = 3563.346f;
    float value_2 = -0.0046646f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_double_6) {

    double value_1 = 3563.346;
    double value_2 = -0.0046646;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_float_7) {

    float value_1 = -3454;
    float value_2 = -0.00463f;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}

TEST(multiplication_tests, multiplication_double_7) {

    double value_1 = 3454;
    double value_2 = -0.00463;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS * MPS_2;

    EXPECT_EQ(value_1*value_2, test.getValue());
    EXPECT_EQ(value_1*value_2, test.my_getValue());
}