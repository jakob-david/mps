#include "gtest/gtest.h"
#include <random>

#include "mps.h"
#include "../functions/functions.h"

unsigned long number_of_tests = 10000;

TEST(random, double_pp){

    for(unsigned long i = 0; i < number_of_tests; i++){

        double lower_bound = 0;
        double upper_bound = numeric_limits<double>::max();
        std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
        std::default_random_engine re((unsigned int) rand());

        double one = unif(re);
        double two = unif(re);

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
        }
        if( (one - two) >= numeric_limits<double>::min() ||
            (one - two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        }
        if( (one * two) >= numeric_limits<double>::min() ||
            (one * two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        }
        if( (one / two) >= numeric_limits<double>::min() ||
            (one / two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
            << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        }
    }
}

TEST(random, double_nn){

    for(unsigned long i = 0; i < number_of_tests; i++){

        double lower_bound = 0;
        double upper_bound = numeric_limits<double>::max();
        std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
        std::default_random_engine re((unsigned int) rand());

        double one = unif(re) * -1;
        double two = unif(re) * -1;

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
        }
        if( (one - two) >= numeric_limits<double>::min() ||
            (one - two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        }
        if( (one * two) >= numeric_limits<double>::min() ||
            (one * two) <= (numeric_limits<double>::min() * -1)
            ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;

        }
        if( (one / two) >= numeric_limits<double>::min() ||
            (one / two) <= (numeric_limits<double>::min() * -1)
            ){

            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
            << endl << "one: " << one << "   two: " << two << "   value: " << DIV.getValue() << endl;
        }
    }
}

TEST(random, double_pn){

    for(unsigned long i = 0; i < number_of_tests; i++){

        double lower_bound = 0;
        double upper_bound = numeric_limits<double>::max();
        std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
        std::default_random_engine re((unsigned int) rand());

        double one = unif(re);
        double two = unif(re) * -1;

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
        }
        if( (one - two) >= numeric_limits<double>::min() ||
            (one - two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        }
        if( (one * two) >= numeric_limits<double>::min() ||
            (one * two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        }
        if( (one / two) >= numeric_limits<double>::min() ||
            (one / two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        }
    }
}

TEST(random, double_np){

    for(unsigned long i = 0; i < number_of_tests; i++){

        double lower_bound = 0;
        double upper_bound = numeric_limits<double>::max();
        std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
        std::default_random_engine re((unsigned int) rand());

        double one = unif(re) * -1;
        double two = unif(re);

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
        }
        if( (one - two) >= numeric_limits<double>::min() ||
            (one - two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        }
        if( (one * two) >= numeric_limits<double>::min() ||
            (one * two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        }
        if( (one / two) >= numeric_limits<double>::min() ||
            (one / two) <= (numeric_limits<double>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        }
    }
}


TEST(random, float_pp){

    for(unsigned long i = 0; i < number_of_tests; i++){

        float lower_bound = 0.0f;
        float upper_bound = numeric_limits<float>::max();
        std::uniform_real_distribution<float> unif(lower_bound,upper_bound);
        std::default_random_engine re((unsigned int) rand());

        float one = unif(re);
        float two = unif(re);

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
        }
        if( (one - two) >= numeric_limits<float>::min() ||
            (one - two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        }
        if( (one * two) >= numeric_limits<float>::min() ||
            (one * two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        }
        if( (one / two) >= numeric_limits<float>::min() ||
            (one / two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        }
    }
}

TEST(random, float_nn){

    for(unsigned long i = 0; i < number_of_tests; i++){

        float lower_bound = 0.0f;
        float upper_bound = numeric_limits<float>::max();
        std::uniform_real_distribution<float> unif(lower_bound,upper_bound);
        std::default_random_engine re((unsigned int) rand());

        float one = unif(re) * -1;
        float two = unif(re) * -1;

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
        }
        if( (one - two) >= numeric_limits<float>::min() ||
            (one - two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        }
        if( (one * two) >= numeric_limits<float>::min() ||
            (one * two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        }
        if( (one / two) >= numeric_limits<float>::min() ||
            (one / two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        }
    }
}

TEST(random, float_pn){

    for(unsigned long i = 0; i < number_of_tests; i++){

        float lower_bound = 0.0f;
        float upper_bound = numeric_limits<float>::max();
        std::uniform_real_distribution<float> unif(lower_bound,upper_bound);
        std::default_random_engine re((unsigned int) rand());

        float one = unif(re);
        float two = unif(re) * -1;

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
        }
        if( (one - two) >= numeric_limits<float>::min() ||
            (one - two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        }
        if( (one * two) >= numeric_limits<float>::min() ||
            (one * two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        }
        if( (one / two) >= numeric_limits<float>::min() ||
            (one / two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        }
    }
}

TEST(random, float_np){

    for(unsigned long i = 0; i < number_of_tests; i++){

        float lower_bound = 0.0f;
        float upper_bound = numeric_limits<float>::max();
        std::uniform_real_distribution<float> unif(lower_bound,upper_bound);
        std::default_random_engine re((unsigned int) rand());

        float one = unif(re) * -1;
        float two = unif(re);

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
        }
        if( (one - two) >= numeric_limits<float>::min() ||
            (one - two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one - two, SUB.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one-two), is_mps(SUB.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << SUB.getValue() << endl;
        }
        if( (one * two) >= numeric_limits<float>::min() ||
            (one * two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one * two, MUL.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one*two), is_mps(MUL.getBitArray()))
                                << endl << "one: " << one << "   two: " << two << "   value: " << MUL.getValue() << endl;
        }
        if( (one / two) >= numeric_limits<float>::min() ||
            (one / two) <= (numeric_limits<float>::min() * -1)
                ){
            EXPECT_EQ(one / two, DIV.getValue()) << endl << "one: " << one << "   two: " << two << i;
            EXPECT_EQ(should_value(one/two), is_mps(DIV.getBitArray()))
                                << endl << "one: " << one << "   two: " << two  << "   value: " << DIV.getValue() << endl;
        }
    }
}
