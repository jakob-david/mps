//
// Created by Jakob on 18.03.24.
//

#include "gtest/gtest.h"
#include "helper_functions.h"

#include "mps.h"

#include <random>


unsigned long number_of_tests = 10000;

TEST(random, double_pp){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, DBL_MAX);

    for(unsigned long i = 0; i < number_of_tests; i++){

        double one = dist(mt);
        double two = dist(mt);


        if(one < numeric_limits<double>::min() || two < numeric_limits<double>::min()){
            continue;
        }

        mps ONE(52, 11, one);
        mps TWO(52, 11, two);

        auto ADD = ONE + TWO;
        auto SUB = ONE - TWO;
        auto MUL = ONE * TWO;
        auto DIV = ONE / TWO;

        if( (one + two) >= numeric_limits<double>::min() ||
            (one + two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one + two, ADD.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one+two), is_mps(ADD.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << ADD.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one - two) >= numeric_limits<double>::min() ||
            (one - two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one * two) >= numeric_limits<double>::min() ||
            (one * two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one / two) >= numeric_limits<double>::min() ||
            (one / two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
            << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
    }
}

TEST(random, double_nn){


    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, DBL_MAX);

    for(unsigned long i = 0; i < number_of_tests; i++){

        double one = dist(mt) * -1;
        double two = dist(mt) * -1;

        if(one < numeric_limits<double>::min() || two < numeric_limits<double>::min()){
            continue;
        }

        mps ONE(52, 11, one);
        mps TWO(52, 11, two);

        auto ADD = ONE + TWO;
        auto SUB = ONE - TWO;
        auto MUL = ONE * TWO;
        auto DIV = ONE / TWO;

        if( (one + two) >= numeric_limits<double>::min() ||
            (one + two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one + two, ADD.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one+two), is_mps(ADD.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << ADD.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one - two) >= numeric_limits<double>::min() ||
            (one - two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one * two) >= numeric_limits<double>::min() ||
            (one * two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;

        } else {
            cout << "subnormal number" << endl;
        }
        if( (one / two) >= numeric_limits<double>::min() ||
            (one / two) <= (numeric_limits<double>::min() * -1)
            ){

            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << DIV.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
    }
}

TEST(random, double_pn){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, DBL_MAX);

    for(unsigned long i = 0; i < number_of_tests; i++){

        double one = dist(mt);
        double two = dist(mt) * -1;

        if(one < numeric_limits<double>::min() || two < numeric_limits<double>::min()){
            continue;
        }

        mps ONE(52, 11, one);
        mps TWO(52, 11, two);

        auto ADD = ONE + TWO;
        auto SUB = ONE - TWO;
        auto MUL = ONE * TWO;
        auto DIV = ONE / TWO;

        if( (one + two) >= numeric_limits<double>::min() ||
            (one + two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one + two, ADD.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one+two), is_mps(ADD.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << ADD.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one - two) >= numeric_limits<double>::min() ||
            (one - two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one * two) >= numeric_limits<double>::min() ||
            (one * two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one / two) >= numeric_limits<double>::min() ||
            (one / two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
    }
}

TEST(random, double_np){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, DBL_MAX);

    for(unsigned long i = 0; i < number_of_tests; i++){

        double one = dist(mt) * -1;
        double two = dist(mt);

        if(one < numeric_limits<double>::min() || two < numeric_limits<double>::min()){
            continue;
        }

        mps ONE(52, 11, one);
        mps TWO(52, 11, two);

        auto ADD = ONE + TWO;
        auto SUB = ONE - TWO;
        auto MUL = ONE * TWO;
        auto DIV = ONE / TWO;

        if( (one + two) >= numeric_limits<double>::min() ||
            (one + two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one + two, ADD.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one+two), is_mps(ADD.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << ADD.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one - two) >= numeric_limits<double>::min() ||
            (one - two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one * two) >= numeric_limits<double>::min() ||
            (one * two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one / two) >= numeric_limits<double>::min() ||
            (one / two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
    }
}


TEST(random, float_pp){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0, FLT_MAX);

    for(unsigned long i = 0; i < number_of_tests; i++){

        float one = dist(mt);
        float two = dist(mt);

        if(one < numeric_limits<float>::min() || two < numeric_limits<float>::min()){
            continue;
        }

        mps ONE(23, 8, one);
        mps TWO(23, 8, two);

        auto ADD = ONE + TWO;
        auto SUB = ONE - TWO;
        auto MUL = ONE * TWO;
        auto DIV = ONE / TWO;

        if( (one + two) >= numeric_limits<float>::min() ||
            (one + two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one + two, ADD.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one+two), is_mps(ADD.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << ADD.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one - two) >= numeric_limits<float>::min() ||
            (one - two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one * two) >= numeric_limits<float>::min() ||
            (one * two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one / two) >= numeric_limits<float>::min() ||
            (one / two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
    }
}

TEST(random, float_nn){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0, FLT_MAX);

    for(unsigned long i = 0; i < number_of_tests; i++){

        float one = dist(mt) * -1;
        float two = dist(mt) * -1;

        if(one < numeric_limits<float>::min() || two < numeric_limits<float>::min()){
            continue;
        }

        mps ONE(23, 8, one);
        mps TWO(23, 8, two);

        auto ADD = ONE + TWO;
        auto SUB = ONE - TWO;
        auto MUL = ONE * TWO;
        auto DIV = ONE / TWO;

        if( (one + two) >= numeric_limits<float>::min() ||
            (one + two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one + two, ADD.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one+two), is_mps(ADD.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << ADD.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one - two) >= numeric_limits<float>::min() ||
            (one - two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one * two) >= numeric_limits<float>::min() ||
            (one * two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one / two) >= numeric_limits<float>::min() ||
            (one / two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
    }
}

TEST(random, float_pn){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0, FLT_MAX);

    for(unsigned long i = 0; i < number_of_tests; i++){

        float one = dist(mt);
        float two = dist(mt) * -1;

        if(one < numeric_limits<float>::min() || two < numeric_limits<float>::min()){
            continue;
        }

        mps ONE(23, 8, one);
        mps TWO(23, 8, two);

        auto ADD = ONE + TWO;
        auto SUB = ONE - TWO;
        auto MUL = ONE * TWO;
        auto DIV = ONE / TWO;

        if( (one + two) >= numeric_limits<float>::min() ||
            (one + two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one + two, ADD.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one+two), is_mps(ADD.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << ADD.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one - two) >= numeric_limits<float>::min() ||
            (one - two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one * two) >= numeric_limits<float>::min() ||
            (one * two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one / two) >= numeric_limits<float>::min() ||
            (one / two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
    }
}

TEST(random, float_np){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0, FLT_MAX);

    for(unsigned long i = 0; i < number_of_tests; i++){

        float one = dist(mt) * -1;
        float two = dist(mt);

        if(one < numeric_limits<float>::min() || two < numeric_limits<float>::min()){
            continue;
        }

        mps ONE(23, 8, one);
        mps TWO(23, 8, two);

        auto ADD = ONE + TWO;
        auto SUB = ONE - TWO;
        auto MUL = ONE * TWO;
        auto DIV = ONE / TWO;

        if( (one + two) >= numeric_limits<float>::min() ||
            (one + two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one + two, ADD.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one+two), is_mps(ADD.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << ADD.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one - two) >= numeric_limits<float>::min() ||
            (one - two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one * two) >= numeric_limits<float>::min() ||
            (one * two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
        if( (one / two) >= numeric_limits<float>::min() ||
            (one / two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        } else {
            cout << "subnormal number" << endl;
        }
    }
}
