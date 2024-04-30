//
// Created by Jakob on 30.04.24.
//

#include "gtest/gtest.h"

#include "../../functions/functions.h"
#include "../../../iras_lib/iras.cpp"


// generateRandomVector
//-------------------------------
TEST(gRV, simple_double_1){

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

TEST(gRV, simple_float_1){

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
//-------------------------------


// generateRandomMatrix
//-------------------------------
TEST(gRM, simple_double_1){

    unsigned long size = 4;
    double lower_bound = -10;
    double upper_bound = 10;


    auto matrix = generateRandomMatrix<double>(size, lower_bound, upper_bound);


    string type = typeid(matrix[0][0]).name();

    EXPECT_EQ("d", type);
    EXPECT_EQ(size, matrix.size());

    for(const auto& row : matrix){

        EXPECT_EQ(size, row.size());

        for(const auto& element : row){
            EXPECT_TRUE(element <= upper_bound);
            EXPECT_TRUE(element >= lower_bound);
        }
    }
}

TEST(gRM, simple_float_1){

    unsigned long size = 4;
    float lower_bound = -10;
    float upper_bound = 10;


    auto matrix = generateRandomMatrix<float>(size, lower_bound, upper_bound);


    string type = typeid(matrix[0][0]).name();

    EXPECT_EQ("f", type);
    EXPECT_EQ(size, matrix.size());

    for(const auto& row : matrix){

        EXPECT_EQ(size, row.size());

        for(const auto& element : row){
            EXPECT_TRUE(element <= upper_bound);
            EXPECT_TRUE(element >= lower_bound);
        }
    }
}

TEST(gRM, sparcity_1){

    unsigned long size = 15;
    double lower_bound = -10;
    double upper_bound = 10;
    double sparsity_rate = 0.25;


    auto matrix = generateRandomMatrix<double>(size, lower_bound, upper_bound, sparsity_rate);

    unsigned long sum = 0;
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        for(unsigned long col_idx = 0; col_idx < size; col_idx++){
            if(0.0 == matrix[row_idx][col_idx]){
            sum++;
            }
        }
    }

    double actual_rate = (double) sum / ((double)(size*size));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.1);

    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < size; column_idx++){
            if(0 != matrix[row_idx][column_idx]){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < size; column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < size; row_idx++){
            if(0 != matrix[row_idx][column_idx]){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(gRM, sparcity_2){

    unsigned long size = 15;
    double lower_bound = -10;
    double upper_bound = 10;
    double sparsity_rate = 0.5;


    auto matrix = generateRandomMatrix<double>(size, lower_bound, upper_bound, sparsity_rate);

    unsigned long sum = 0;
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        for(unsigned long col_idx = 0; col_idx < size; col_idx++){
            if(0.0 == matrix[row_idx][col_idx]){
                sum++;
            }
        }
    }

    double actual_rate = (double) sum / ((double)(size*size));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.1);

    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < size; column_idx++){
            if(0 != matrix[row_idx][column_idx]){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < size; column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < size; row_idx++){
            if(0 != matrix[row_idx][column_idx]){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}

TEST(gRM, sparcity_3){

    unsigned long size = 15;
    double lower_bound = -10;
    double upper_bound = 10;
    double sparsity_rate = 0.75;


    auto matrix = generateRandomMatrix<double>(size, lower_bound, upper_bound, sparsity_rate);

    unsigned long sum = 0;
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        for(unsigned long col_idx = 0; col_idx < size; col_idx++){
            if(0.0 == matrix[row_idx][col_idx]){
                sum++;
            }
        }
    }

    double actual_rate = (double) sum / ((double)(size*size));

    EXPECT_NEAR(sparsity_rate, actual_rate, 0.1);

    //check if matrix is invertible
    // check rows
    for(unsigned long row_idx = 0; row_idx < size; row_idx++){
        bool only_zero_entries = true;
        for(unsigned long column_idx = 0; column_idx < size; column_idx++){
            if(0 != matrix[row_idx][column_idx]){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }

    // check columns
    for(unsigned long column_idx = 0; column_idx < size; column_idx++){
        bool only_zero_entries = true;
        for(unsigned long row_idx = 0; row_idx < size; row_idx++){
            if(0 != matrix[row_idx][column_idx]){
                only_zero_entries = false;
                continue;
            }
        }
        EXPECT_FALSE(only_zero_entries);
    }
}
//-------------------------------

// matrix vector product
//-------------------------------
TEST(dP, matrix_vector){

    vector<double> vec = {1, 2, 3};
    vector<vector<double>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    auto result = dotProduct(matrix, vec);

    EXPECT_EQ(14, result[0]);
    EXPECT_EQ(32, result[1]);
    EXPECT_EQ(50, result[2]);
}

TEST(dP, matrix_matrix){

    vector<vector<double>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<double>> B = {{2, 3, 4}, {5, 6, 7}, {8, 9, 1}};

    auto result = dotProduct(A, B);

    EXPECT_EQ(36, result[0][0]);
    EXPECT_EQ(42, result[0][1]);
    EXPECT_EQ(21, result[0][2]);

    EXPECT_EQ(81, result[1][0]);
    EXPECT_EQ(96, result[1][1]);
    EXPECT_EQ(57, result[1][2]);

    EXPECT_EQ(126, result[2][0]);
    EXPECT_EQ(150, result[2][1]);
    EXPECT_EQ(93, result[2][2]);
}
//-------------------------------

// converter
//-------------------------------
TEST(c, vector){

    vector<double> from = {1,2,3};

    auto to = convert<double, float>(from);

    string type = typeid(to[0]).name();
    EXPECT_EQ("f", type);

    EXPECT_EQ(3, to.size());

    for(unsigned long idx = 0; idx < from.size(); idx++){
        EXPECT_EQ((float) from[idx], to[idx]);
    }
}

TEST(c, matrix){

    vector<vector<double>> from = {{1,2,3}, {2,3,1}, {3,1,2}};

    auto to = convert<double, float>(from);

    string type = typeid(to[0][0]).name();
    EXPECT_EQ("f", type);

    EXPECT_EQ(3, to.size());

    for(unsigned long row_idx = 0; row_idx < from.size(); row_idx++){
        for(unsigned long col_idx = 0; col_idx < from.size(); col_idx++){
            EXPECT_EQ((float) from[row_idx][col_idx], to[row_idx][col_idx]);
        }
    }
}
//-------------------------------