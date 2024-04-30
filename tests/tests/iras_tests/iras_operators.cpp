//
// Created by Jakob on 30.04.24.
//

#include "gtest/gtest.h"

#include "../../functions/functions.h"
#include "../../../iras_lib/iras.cpp"

TEST(iras_generateRandomVector, simple_double_1){

    unsigned long size = 4;
    double lower_bound = -10;
    double upper_bound = 10;


    auto vec = generateRandomVector<double>(size, lower_bound, upper_bound);


    string type = typeid(vec[0]).name();

    EXPECT_EQ("d", type);
    EXPECT_EQ(size, vec.size());

    for(const auto& element : vec){
        EXPECT_TRUE(element <= upper_bound);
        EXPECT_TRUE(element >= lower_bound);
    }
}

TEST(iras_generateRandomVector, simple_float_1){

    unsigned long size = 4;
    float lower_bound = -10;
    float upper_bound = 10;


    auto vec = generateRandomVector<float>(size, lower_bound, upper_bound);


    string type = typeid(vec[0]).name();

    EXPECT_EQ("f", type);
    EXPECT_EQ(size, vec.size());

    for(const auto& element : vec){
        EXPECT_TRUE(element <= upper_bound);
        EXPECT_TRUE(element >= lower_bound);
    }
}