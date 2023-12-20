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

TEST(addition_tests, simple_addition_same_float) {

    float value_1 = 1.05;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_1);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_1+value_1, test.getValue());
}

TEST(addition_tests, simple_addition_float) {

    float value_1 = 1.05;
    float value_2 = 2.1;

    mps MPS(23,8,value_1);
    mps MPS_2(23,8,value_2);

    auto test = MPS + MPS_2;

    EXPECT_EQ(value_2+value_1, test.getValue());
}


