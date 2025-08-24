//
// Created by Jakob on 09.03.24.
//

#include "gtest/gtest.h"

#include "mps.h"


TEST(equal_tests, small_large_pp_float) {

    float small = 353.4532f;
    float large = 35620493.405f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, large_small_pp_float) {

    float small = 353.4532f;
    float large = 35620493.405f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(large == small, LARGE == SMALL);
}

TEST(equal_tests, small_large_nn_float) {

    float small = -35620493.405f;
    float large = -353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, large_small_nn_float) {

    float small = -35620493.405f;
    float large = -353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(large == small, LARGE == SMALL);
}

TEST(equal_tests, small_large_np_float) {

    float small = -35620493.405f;
    float large = 353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, large_small_np_float) {

    float small = -35620493.405f;
    float large = 353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(large == small, LARGE == SMALL);
}

TEST(equal_tests, same_n_float) {

    float same = -35620493.405f;

    mps SAME_1(23, 8, same);
    mps SAME_2(23, 8, same);

    EXPECT_EQ(same == same, SAME_1 == SAME_2);
}

TEST(equal_tests, same_p_float) {

    float same = 35620493.405f;

    mps SAME_1(23, 8, same);
    mps SAME_2(23, 8, same);

    EXPECT_EQ(same == same, SAME_1 == SAME_2);
}

TEST(equal_tests, zero_left_float) {

    float small = 0;
    float large = 353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, zero_right_float) {

    float small = -353.4532f;
    float large = 0;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, zero_both_float) {

    float same = 0;

    mps SAME_1(23, 8, same);
    mps SAME_2(23, 8, same);

    EXPECT_EQ(same == same, SAME_1 == SAME_2);
}

TEST(equal_tests, inf_left_float) {

    float left = numeric_limits<float>::infinity();
    float right = 35620493.405f;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, inf_right_float) {

    float left = 35620493.405f;
    float right = numeric_limits<float>::infinity();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, inf_inf_float) {

    float left = numeric_limits<float>::infinity();
    float right = numeric_limits<float>::infinity();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, NAN_left_float) {

    float left = NAN;
    float right = 35620493.405f;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, NAN_right_float) {

    float left = 35620493.405f;
    float right = NAN;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, NAN_NAN_float) {

    float left = NAN;
    float right = NAN;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_left_float) {

    float left = numeric_limits<float>::max();
    float right = 35620493.405f;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_right_float) {

    float left = 35620493.405f;
    float right = numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_max_float) {

    float left = numeric_limits<float>::max();
    float right = numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_left_float) {

    float left = numeric_limits<float>::min();
    float right = 35620493.405f;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_right_float) {

    float left = 35620493.405f;
    float right = numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_min_float) {

    float left = numeric_limits<float>::min();
    float right = numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_max_float) {

    float left = numeric_limits<float>::min();
    float right = numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_min_float) {

    float left = numeric_limits<float>::max();
    float right = numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_max_nn_float) {

    float left = -numeric_limits<float>::max();
    float right = -numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_max_pn_float) {

    float left = numeric_limits<float>::max();
    float right = -numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_max_np_float) {

    float left = -numeric_limits<float>::max();
    float right = numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_min_nn_float) {

    float left = -numeric_limits<float>::min();
    float right = -numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_min_pn_float) {

    float left = numeric_limits<float>::min();
    float right = -numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_min_np_float) {

    float left = -numeric_limits<float>::min();
    float right = numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}


TEST(equal_tests, small_large_pp_double) {

    double small = 353.4532;
    double large = 35620493.405;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, large_small_pp_double) {

    double small = 353.4532;
    double large = 35620493.405;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(large == small, LARGE == SMALL);
}

TEST(equal_tests, small_large_nn_double) {

    double small = -35620493.405;
    double large = -353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, large_small_nn_double) {

    double small = -35620493.405;
    double large = -353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(large == small, LARGE == SMALL);
}

TEST(equal_tests, small_large_np_double) {

    double small = -35620493.405;
    double large = 353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, large_small_np_double) {

    double small = -35620493.405;
    double large = 353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(large == small, LARGE == SMALL);
}

TEST(equal_tests, same_n_double) {

    double same = -35620493.405;

    mps SAME_1(52, 11, same);
    mps SAME_2(52, 11, same);

    EXPECT_EQ(same == same, SAME_1 == SAME_2);
}

TEST(equal_tests, same_p_double) {

    double same = 35620493.405;

    mps SAME_1(52, 11, same);
    mps SAME_2(52, 11, same);

    EXPECT_EQ(same == same, SAME_1 == SAME_2);
}

TEST(equal_tests, zero_left_double) {

    double small = 0;
    double large = 353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, zero_right_double) {

    double small = -353.4532;
    double large = 0;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small == large, SMALL == LARGE);
}

TEST(equal_tests, zero_both_double) {

    double same = 0;

    mps SAME_1(52, 11, same);
    mps SAME_2(52, 11, same);

    EXPECT_EQ(same == same, SAME_1 == SAME_2);
}

TEST(equal_tests, inf_left_double) {

    double left = numeric_limits<double>::infinity();
    double right = 35620493.405;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, inf_right_double) {

    double left = 35620493.405;
    double right = numeric_limits<double>::infinity();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, inf_inf_double) {

    double left = numeric_limits<double>::infinity();
    double right = numeric_limits<double>::infinity();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, NAN_left_double) {

    double left = NAN;
    double right = 35620493.405;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, NAN_right_double) {

    double left = 35620493.405;
    double right = NAN;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, NAN_NAN_double) {

    double left = NAN;
    double right = NAN;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_left_double) {

    double left = numeric_limits<double>::max();
    double right = 35620493.405;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_right_double) {

    double left = 35620493.405;
    double right = numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_max_double) {

    double left = numeric_limits<double>::max();
    double right = numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_left_double) {

    double left = numeric_limits<double>::min();
    double right = 35620493.405;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_right_double) {

    double left = 35620493.405;
    double right = numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_min_double) {

    double left = numeric_limits<double>::min();
    double right = numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_max_double) {

    double left = numeric_limits<double>::min();
    double right = numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_min_double) {

    double left = numeric_limits<double>::max();
    double right = numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_max_nn_double) {

    double left = -numeric_limits<double>::max();
    double right = -numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_max_pn_double) {

    double left = numeric_limits<double>::max();
    double right = -numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, max_max_np_double) {

    double left = -numeric_limits<double>::max();
    double right = numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_min_nn_double) {

    double left = -numeric_limits<double>::min();
    double right = -numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_min_pn_double) {

    double left = numeric_limits<double>::min();
    double right = -numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}

TEST(equal_tests, min_min_np_double) {

    double left = -numeric_limits<double>::min();
    double right = numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left == right, LEFT == RIGHT);
}




TEST(not_equal_tests, small_large_pp_float) {

    float small = 353.4532f;
    float large = 35620493.405f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, large_small_pp_float) {

    float small = 353.4532f;
    float large = 35620493.405f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(large != small, LARGE != SMALL);
}

TEST(not_equal_tests, small_large_nn_float) {

    float small = -35620493.405f;
    float large = -353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, large_small_nn_float) {

    float small = -35620493.405f;
    float large = -353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(large != small, LARGE != SMALL);
}

TEST(not_equal_tests, small_large_np_float) {

    float small = -35620493.405f;
    float large = 353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, large_small_np_float) {

    float small = -35620493.405f;
    float large = 353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(large != small, LARGE != SMALL);
}

TEST(not_equal_tests, same_n_float) {

    float same = -35620493.405f;

    mps SAME_1(23, 8, same);
    mps SAME_2(23, 8, same);

    EXPECT_EQ(same != same, SAME_1 != SAME_2);
}

TEST(not_equal_tests, same_p_float) {

    float same = 35620493.405f;

    mps SAME_1(23, 8, same);
    mps SAME_2(23, 8, same);

    EXPECT_EQ(same != same, SAME_1 != SAME_2);
}

TEST(not_equal_tests, zero_left_float) {

    float small = 0;
    float large = 353.4532f;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, zero_right_float) {

    float small = -353.4532f;
    float large = 0;

    mps SMALL(23, 8, small);
    mps LARGE(23, 8, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, zero_both_float) {

    float same = 0;

    mps SAME_1(23, 8, same);
    mps SAME_2(23, 8, same);

    EXPECT_EQ(same != same, SAME_1 != SAME_2);
}

TEST(not_equal_tests, inf_left_float) {

    float left = numeric_limits<float>::infinity();
    float right = 35620493.405f;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, inf_right_float) {

    float left = 35620493.405f;
    float right = numeric_limits<float>::infinity();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, inf_inf_float) {

    float left = numeric_limits<float>::infinity();
    float right = numeric_limits<float>::infinity();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, NAN_left_float) {

    float left = NAN;
    float right = 35620493.405f;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, NAN_right_float) {

    float left = 35620493.405f;
    float right = NAN;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, NAN_NAN_float) {

    float left = NAN;
    float right = NAN;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_left_float) {

    float left = numeric_limits<float>::max();
    float right = 35620493.405f;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_right_float) {

    float left = 35620493.405f;
    float right = numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_max_float) {

    float left = numeric_limits<float>::max();
    float right = numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_left_float) {

    float left = numeric_limits<float>::min();
    float right = 35620493.405f;

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_right_float) {

    float left = 35620493.405f;
    float right = numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_min_float) {

    float left = numeric_limits<float>::min();
    float right = numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_max_float) {

    float left = numeric_limits<float>::min();
    float right = numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_min_float) {

    float left = numeric_limits<float>::max();
    float right = numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_max_nn_float) {

    float left = -numeric_limits<float>::max();
    float right = -numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_max_pn_float) {

    float left = numeric_limits<float>::max();
    float right = -numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_max_np_float) {

    float left = -numeric_limits<float>::max();
    float right = numeric_limits<float>::max();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_min_nn_float) {

    float left = -numeric_limits<float>::min();
    float right = -numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_min_pn_float) {

    float left = numeric_limits<float>::min();
    float right = -numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_min_np_float) {

    float left = -numeric_limits<float>::min();
    float right = numeric_limits<float>::min();

    mps LEFT(23, 8, left);
    mps RIGHT(23, 8, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}


TEST(not_equal_tests, small_large_pp_double) {

    double small = 353.4532;
    double large = 35620493.405;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, large_small_pp_double) {

    double small = 353.4532;
    double large = 35620493.405;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(large != small, LARGE != SMALL);
}

TEST(not_equal_tests, small_large_nn_double) {

    double small = -35620493.405;
    double large = -353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, large_small_nn_double) {

    double small = -35620493.405;
    double large = -353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(large != small, LARGE != SMALL);
}

TEST(not_equal_tests, small_large_np_double) {

    double small = -35620493.405;
    double large = 353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, large_small_np_double) {

    double small = -35620493.405;
    double large = 353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(large != small, LARGE != SMALL);
}

TEST(not_equal_tests, same_n_double) {

    double same = -35620493.405;

    mps SAME_1(52, 11, same);
    mps SAME_2(52, 11, same);

    EXPECT_EQ(same != same, SAME_1 != SAME_2);
}

TEST(not_equal_tests, same_p_double) {

    double same = 35620493.405;

    mps SAME_1(52, 11, same);
    mps SAME_2(52, 11, same);

    EXPECT_EQ(same != same, SAME_1 != SAME_2);
}

TEST(not_equal_tests, zero_left_double) {

    double small = 0;
    double large = 353.4532;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, zero_right_double) {

    double small = -353.4532;
    double large = 0;

    mps SMALL(52, 11, small);
    mps LARGE(52, 11, large);

    EXPECT_EQ(small != large, SMALL != LARGE);
}

TEST(not_equal_tests, zero_both_double) {

    double same = 0;

    mps SAME_1(52, 11, same);
    mps SAME_2(52, 11, same);

    EXPECT_EQ(same != same, SAME_1 != SAME_2);
}

TEST(not_equal_tests, inf_left_double) {

    double left = numeric_limits<double>::infinity();
    double right = 35620493.405;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, inf_right_double) {

    double left = 35620493.405;
    double right = numeric_limits<double>::infinity();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, inf_inf_double) {

    double left = numeric_limits<double>::infinity();
    double right = numeric_limits<double>::infinity();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, NAN_left_double) {

    double left = NAN;
    double right = 35620493.405;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, NAN_right_double) {

    double left = 35620493.405;
    double right = NAN;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, NAN_NAN_double) {

    double left = NAN;
    double right = NAN;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_left_double) {

    double left = numeric_limits<double>::max();
    double right = 35620493.405;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_right_double) {

    double left = 35620493.405;
    double right = numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_max_double) {

    double left = numeric_limits<double>::max();
    double right = numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_left_double) {

    double left = numeric_limits<double>::min();
    double right = 35620493.405;

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_right_double) {

    double left = 35620493.405;
    double right = numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_min_double) {

    double left = numeric_limits<double>::min();
    double right = numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_max_double) {

    double left = numeric_limits<double>::min();
    double right = numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_min_double) {

    double left = numeric_limits<double>::max();
    double right = numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_max_nn_double) {

    double left = -numeric_limits<double>::max();
    double right = -numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_max_pn_double) {

    double left = numeric_limits<double>::max();
    double right = -numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, max_max_np_double) {

    double left = -numeric_limits<double>::max();
    double right = numeric_limits<double>::max();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_min_nn_double) {

    double left = -numeric_limits<double>::min();
    double right = -numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_min_pn_double) {

    double left = numeric_limits<double>::min();
    double right = -numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}

TEST(not_equal_tests, min_min_np_double) {

    double left = -numeric_limits<double>::min();
    double right = numeric_limits<double>::min();

    mps LEFT(52, 11, left);
    mps RIGHT(52, 11, right);

    EXPECT_EQ(left != right, LEFT != RIGHT);
}
