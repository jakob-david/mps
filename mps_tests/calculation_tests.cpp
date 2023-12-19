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
