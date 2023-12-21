#include "gtest/gtest.h"

#include "mps.h"
#include <bitset>


TEST(equality_tests, equality_pos_double){

    double test_value = 234536.34634;

    mps* MPS = new mps(52, 11, test_value);

    mps* MPS_copy = MPS;

    EXPECT_EQ(MPS->getMantisseLength(), MPS_copy->getMantisseLength());
    EXPECT_EQ(MPS->getExponentLength(), MPS_copy->getExponentLength());
    EXPECT_EQ(test_value, MPS_copy->getValue());
}

TEST(equality_tests, equality_pos_float){

    float test_value = 234536.34634;

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

    float test_value = -234536.34634;

    mps* MPS = new mps(23, 8, test_value);

    mps* MPS_copy = MPS;

    EXPECT_EQ(MPS->getMantisseLength(), MPS_copy->getMantisseLength());
    EXPECT_EQ(MPS->getExponentLength(), MPS_copy->getExponentLength());
    EXPECT_EQ(test_value, MPS_copy->getValue());
}

TEST(equality_tests, equality_same_object_double){

    double test_value = 234536.34634;

    mps* MPS = new mps(52, 11, test_value);

    MPS = MPS;

    EXPECT_EQ(&MPS, &MPS);
}

TEST(equality_tests, equality_same_object_float){

    double test_value = 234536.34634;

    mps* MPS = new mps(23, 8, test_value);

    MPS = MPS;

    EXPECT_EQ(&MPS, &MPS);
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

    float test_value = 234536.34634;

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
}

TEST(addition_tests, addition_same_float) {

    float value_1 = 1.05;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_1);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_1, test.getValue());
}

TEST(addition_tests, addition_double) {

    double value_1 = 1.05;
    double value_2 = 2.1;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
}

TEST(addition_tests, addition_float) {

    float value_1 = 1.05;
    float value_2 = 2.1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
}

TEST(addition_tests, addition2_double) {

    double value_1 = 2453.45645;
    double value_2 = 124779.3456;

    mps MPS(53,11,value_1);
    mps MPS_2(53,11,value_2);

    auto test = MPS + MPS_2;

    string str1;
    for(bool bit : MPS.getBitArray()){
        if(bit){
            str1.append("1");
        } else {
            str1.append("0");
        }
    }
    cout << "MPS   : " << str1 << endl;

    string str2;
    for(bool bit : MPS_2.getBitArray()){
        if(bit){
            str2.append("1");
        } else {
            str2.append("0");
        }
    }
    cout << "MPS_2 : " << str2 << endl;

    string str;
    for(bool bit : test.getBitArray()){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    double test_value = value_1 + value_2;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(addition_tests, addition2_float) {

    float value_1 = 2453.45645;
    float value_2 = 124779.3456;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
}

TEST(addition_tests, addition3_double) {

    double value_1 = 0.0345;
    double value_2 = 0.000435345;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_2, test.getValue());
}

TEST(addition_tests, addition3_float) {

    float value_1 = 0.0345;
    float value_2 = 0.000435345;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
}

TEST(addition_tests, zero_left_double) {

    double value_1 = 0;
    double value_2 = 346.4367;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
}

TEST(addition_tests, zero_left_float) {

    float value_1 = 0;
    float value_2 = 346.4367;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
}

TEST(addition_tests, zero_right_double) {

    double value_1 = 23456.356;
    double value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
}

TEST(addition_tests, zero_right_float) {

    float value_1 = 23456.356;
    float value_2 = 0;

    mps MPS(52,11,value_1);
    mps MPS_2(52,11,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
}



