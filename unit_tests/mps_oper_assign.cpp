//
// Created by Jakob on 09.03.24.
//

#include "gtest/gtest.h"
#include "helper_functions.h"

#include "mps.h"


TEST(implicit_equal, pos_double){

    double test_value = 234536.34634;
    mps MPS(52, 11, test_value);

    mps MPS_copy = MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
    EXPECT_EQ(52, MPS_copy.getMantisseLength());
    EXPECT_EQ(11, MPS_copy.getExponentLength());

    EXPECT_EQ(52, MPS.getMantissa().size());
    EXPECT_EQ(11, MPS.getExponent().size());
    EXPECT_EQ(52, MPS_copy.getMantissa().size());
    EXPECT_EQ(11, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0;
    MPS_copy = 5.0;

    EXPECT_EQ(6.0, MPS.getValue());
    EXPECT_EQ(should_value(6.0), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0), is_mps(MPS_copy.getBitArray()));
}

TEST(implicit_equal, equality_pos_float){

    float test_value = 234536.34634f;
    mps MPS(23, 8, test_value);

    mps MPS_copy = MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(23, MPS_copy.getMantisseLength());
    EXPECT_EQ(8, MPS_copy.getExponentLength());

    EXPECT_EQ(23, MPS.getMantissa().size());
    EXPECT_EQ(8, MPS.getExponent().size());
    EXPECT_EQ(23, MPS_copy.getMantissa().size());
    EXPECT_EQ(8, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0f;
    MPS_copy = 5.0f;

    EXPECT_EQ(6.0f, MPS.getValue());
    EXPECT_EQ(should_value(6.0f), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0f, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0f), is_mps(MPS_copy.getBitArray()));
}

TEST(implicit_equal, equality_neg_double){

    double test_value = 234536.34634;
    mps MPS(52, 11, test_value);

    mps MPS_copy = MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
    EXPECT_EQ(52, MPS_copy.getMantisseLength());
    EXPECT_EQ(11, MPS_copy.getExponentLength());

    EXPECT_EQ(52, MPS.getMantissa().size());
    EXPECT_EQ(11, MPS.getExponent().size());
    EXPECT_EQ(52, MPS_copy.getMantissa().size());
    EXPECT_EQ(11, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0;
    MPS_copy = 5.0;

    EXPECT_EQ(6.0, MPS.getValue());
    EXPECT_EQ(should_value(6.0), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0), is_mps(MPS_copy.getBitArray()));
}

TEST(implicit_equal, equality_neg_float){

    float test_value = -234536.34634f;
    mps MPS(23, 8, test_value);

    mps MPS_copy = MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(23, MPS_copy.getMantisseLength());
    EXPECT_EQ(8, MPS_copy.getExponentLength());

    EXPECT_EQ(23, MPS.getMantissa().size());
    EXPECT_EQ(8, MPS.getExponent().size());
    EXPECT_EQ(23, MPS_copy.getMantissa().size());
    EXPECT_EQ(8, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0f;
    MPS_copy = 5.0f;

    EXPECT_EQ(6.0f, MPS.getValue());
    EXPECT_EQ(should_value(6.0f), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0f, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0f), is_mps(MPS_copy.getBitArray()));
}



TEST(equal, pos_double){

    double test_value = 234536.34634;
    mps MPS(52, 11, test_value);


    mps MPS_copy(52, 11);
    MPS_copy = MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
    EXPECT_EQ(52, MPS_copy.getMantisseLength());
    EXPECT_EQ(11, MPS_copy.getExponentLength());

    EXPECT_EQ(52, MPS.getMantissa().size());
    EXPECT_EQ(11, MPS.getExponent().size());
    EXPECT_EQ(52, MPS_copy.getMantissa().size());
    EXPECT_EQ(11, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0;
    MPS_copy = 5.0;

    EXPECT_EQ(6.0, MPS.getValue());
    EXPECT_EQ(should_value(6.0), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0), is_mps(MPS_copy.getBitArray()));
}

TEST(equal, pos_float){

    float test_value = 234536.34634f;
    mps MPS(23, 8, test_value);

    mps MPS_copy(23, 8);
    MPS_copy = MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(23, MPS_copy.getMantisseLength());
    EXPECT_EQ(8, MPS_copy.getExponentLength());

    EXPECT_EQ(23, MPS.getMantissa().size());
    EXPECT_EQ(8, MPS.getExponent().size());
    EXPECT_EQ(23, MPS_copy.getMantissa().size());
    EXPECT_EQ(8, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0f;
    MPS_copy = 5.0f;

    EXPECT_EQ(6.0f, MPS.getValue());
    EXPECT_EQ(should_value(6.0f), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0f, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0f), is_mps(MPS_copy.getBitArray()));
}

TEST(equal, neg_double){

    double test_value = 234536.34634;
    mps MPS(52, 11, test_value);

    mps MPS_copy(52, 11);
    MPS_copy = MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
    EXPECT_EQ(52, MPS_copy.getMantisseLength());
    EXPECT_EQ(11, MPS_copy.getExponentLength());

    EXPECT_EQ(52, MPS.getMantissa().size());
    EXPECT_EQ(11, MPS.getExponent().size());
    EXPECT_EQ(52, MPS_copy.getMantissa().size());
    EXPECT_EQ(11, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0;
    MPS_copy = 5.0;

    EXPECT_EQ(6.0, MPS.getValue());
    EXPECT_EQ(should_value(6.0), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0), is_mps(MPS_copy.getBitArray()));
}

TEST(equal, neg_float){

    float test_value = -234536.34634f;
    mps MPS(23, 8, test_value);

    mps MPS_copy(23, 8);
    MPS_copy = MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(23, MPS_copy.getMantisseLength());
    EXPECT_EQ(8, MPS_copy.getExponentLength());

    EXPECT_EQ(23, MPS.getMantissa().size());
    EXPECT_EQ(8, MPS.getExponent().size());
    EXPECT_EQ(23, MPS_copy.getMantissa().size());
    EXPECT_EQ(8, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0f;
    MPS_copy = 5.0f;

    EXPECT_EQ(6.0f, MPS.getValue());
    EXPECT_EQ(should_value(6.0f), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0f, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0f), is_mps(MPS_copy.getBitArray()));
}

TEST(equal, exception_exponent_length){


    mps ONE(23, 9, 345.234);
    mps TWO(23, 8, 345.234);

    EXPECT_ANY_THROW(ONE = TWO);
}

TEST(equal, exception_mantissa_length){

    mps ONE(20, 8, 345.234);
    mps TWO(23, 8, 345.234);

    EXPECT_ANY_THROW(ONE = TWO);
}



TEST(assign, pos_double){

    double test_value = 234536.34634;
    mps MPS(52, 11, test_value);

    mps MPS_copy;
    MPS_copy |= MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
    EXPECT_EQ(52, MPS_copy.getMantisseLength());
    EXPECT_EQ(11, MPS_copy.getExponentLength());

    EXPECT_EQ(52, MPS.getMantissa().size());
    EXPECT_EQ(11, MPS.getExponent().size());
    EXPECT_EQ(52, MPS_copy.getMantissa().size());
    EXPECT_EQ(11, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0;
    MPS_copy = 5.0;

    EXPECT_EQ(6.0, MPS.getValue());
    EXPECT_EQ(should_value(6.0), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0), is_mps(MPS_copy.getBitArray()));
}

TEST(assign, pos_float){

    float test_value = 234536.34634f;
    mps MPS(23, 8, test_value);

    mps MPS_copy;
    MPS_copy |= MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(23, MPS_copy.getMantisseLength());
    EXPECT_EQ(8, MPS_copy.getExponentLength());

    EXPECT_EQ(23, MPS.getMantissa().size());
    EXPECT_EQ(8, MPS.getExponent().size());
    EXPECT_EQ(23, MPS_copy.getMantissa().size());
    EXPECT_EQ(8, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0f;
    MPS_copy = 5.0f;

    EXPECT_EQ(6.0f, MPS.getValue());
    EXPECT_EQ(should_value(6.0f), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0f, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0f), is_mps(MPS_copy.getBitArray()));
}

TEST(assign, neg_double){

    double test_value = 234536.34634;
    mps MPS(52, 11, test_value);

    mps MPS_copy;
    MPS_copy |= MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
    EXPECT_EQ(52, MPS_copy.getMantisseLength());
    EXPECT_EQ(11, MPS_copy.getExponentLength());

    EXPECT_EQ(52, MPS.getMantissa().size());
    EXPECT_EQ(11, MPS.getExponent().size());
    EXPECT_EQ(52, MPS_copy.getMantissa().size());
    EXPECT_EQ(11, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0;
    MPS_copy = 5.0;

    EXPECT_EQ(6.0, MPS.getValue());
    EXPECT_EQ(should_value(6.0), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0), is_mps(MPS_copy.getBitArray()));
}

TEST(assign, neg_float){

    float test_value = -234536.34634f;
    mps MPS(23, 8, test_value);

    mps MPS_copy;
    MPS_copy |= MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(23, MPS_copy.getMantisseLength());
    EXPECT_EQ(8, MPS_copy.getExponentLength());

    EXPECT_EQ(23, MPS.getMantissa().size());
    EXPECT_EQ(8, MPS.getExponent().size());
    EXPECT_EQ(23, MPS_copy.getMantissa().size());
    EXPECT_EQ(8, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0f;
    MPS_copy = 5.0f;

    EXPECT_EQ(6.0f, MPS.getValue());
    EXPECT_EQ(should_value(6.0f), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0f, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0f), is_mps(MPS_copy.getBitArray()));
}

TEST(assign, different_mantissa_double){

    double test_value = 234536.34634;
    mps MPS(52, 11, test_value);

    mps MPS_copy(23, 11, 5.0);
    MPS_copy |= MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
    EXPECT_EQ(52, MPS_copy.getMantisseLength());
    EXPECT_EQ(11, MPS_copy.getExponentLength());

    EXPECT_EQ(52, MPS.getMantissa().size());
    EXPECT_EQ(11, MPS.getExponent().size());
    EXPECT_EQ(52, MPS_copy.getMantissa().size());
    EXPECT_EQ(11, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0;
    MPS_copy = 5.0;

    EXPECT_EQ(6.0, MPS.getValue());
    EXPECT_EQ(should_value(6.0), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0), is_mps(MPS_copy.getBitArray()));
}

TEST(assign, different_mantissa_float){

    float test_value = 234536.34634f;
    mps MPS(23, 8, test_value);

    mps MPS_copy(52, 8, 5.0);
    MPS_copy |= MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(23, MPS_copy.getMantisseLength());
    EXPECT_EQ(8, MPS_copy.getExponentLength());

    EXPECT_EQ(23, MPS.getMantissa().size());
    EXPECT_EQ(8, MPS.getExponent().size());
    EXPECT_EQ(23, MPS_copy.getMantissa().size());
    EXPECT_EQ(8, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0f;
    MPS_copy = 5.0f;

    EXPECT_EQ(6.0f, MPS.getValue());
    EXPECT_EQ(should_value(6.0f), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0f, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0f), is_mps(MPS_copy.getBitArray()));
}

TEST(assign, different_exponent_double){

    double test_value = 234536.34634;
    mps MPS(52, 11, test_value);

    mps MPS_copy(52, 8, 5.0);
    MPS_copy |= MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(52, MPS.getMantisseLength());
    EXPECT_EQ(11, MPS.getExponentLength());
    EXPECT_EQ(52, MPS_copy.getMantisseLength());
    EXPECT_EQ(11, MPS_copy.getExponentLength());

    EXPECT_EQ(52, MPS.getMantissa().size());
    EXPECT_EQ(11, MPS.getExponent().size());
    EXPECT_EQ(52, MPS_copy.getMantissa().size());
    EXPECT_EQ(11, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0;
    MPS_copy = 5.0;

    EXPECT_EQ(6.0, MPS.getValue());
    EXPECT_EQ(should_value(6.0), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0), is_mps(MPS_copy.getBitArray()));
}

TEST(assign, different_exponent_float){

    float test_value = 234536.34634f;
    mps MPS(23, 8, test_value);

    mps MPS_copy(23, 11, 5.0);
    MPS_copy |= MPS;


    EXPECT_NE(&MPS, &MPS_copy);

    EXPECT_EQ(MPS.print(), MPS_copy.print());
    EXPECT_EQ(MPS.getMantisseLength(), MPS_copy.getMantisseLength());
    EXPECT_EQ(MPS.getExponentLength(), MPS_copy.getExponentLength());
    EXPECT_EQ(test_value, MPS_copy.getValue());

    EXPECT_EQ(23, MPS.getMantisseLength());
    EXPECT_EQ(8, MPS.getExponentLength());
    EXPECT_EQ(23, MPS_copy.getMantisseLength());
    EXPECT_EQ(8, MPS_copy.getExponentLength());

    EXPECT_EQ(23, MPS.getMantissa().size());
    EXPECT_EQ(8, MPS.getExponent().size());
    EXPECT_EQ(23, MPS_copy.getMantissa().size());
    EXPECT_EQ(8, MPS_copy.getExponent().size());

    EXPECT_EQ(test_value, MPS.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS.getBitArray()));
    EXPECT_EQ(test_value, MPS_copy.getValue());
    EXPECT_EQ(should_value(test_value), is_mps(MPS_copy.getBitArray()));

    MPS = 6.0f;
    MPS_copy = 5.0f;

    EXPECT_EQ(6.0f, MPS.getValue());
    EXPECT_EQ(should_value(6.0f), is_mps(MPS.getBitArray()));
    EXPECT_EQ(5.0f, MPS_copy.getValue());
    EXPECT_EQ(should_value(5.0f), is_mps(MPS_copy.getBitArray()));
}

