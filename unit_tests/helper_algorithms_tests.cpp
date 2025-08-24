//
// Created by Jakob on 30.04.24.
//

#include "gtest/gtest.h"

#include "helper_functions.h"
#include "helper_algorithms.h"



// round
//-------------------------------
TEST(round, number){

    double expected = 1.12;

    double number = 1.12345;
    EXPECT_NE(expected, number);

    number = round(number, 0.01);
    EXPECT_EQ(expected, number);
}

TEST(round, vector){

    vector<double> expected = {1.12, -1.23, 100.02, 0.02, 0.03};
    vector vec = {1.123542, -1.233523, 100.023523, 0.0235235, 0.027};

    EXPECT_NE(expected, vec);

    vec = round(vec, 0.01);
    EXPECT_EQ(expected, vec);
}
//-------------------------------

// to string
//-------------------------------
TEST(tS, vector){

    vector<double> test = {1, 2, 3};

    auto result = toString<double>(test, 2);

    EXPECT_EQ("1.00, 2.00, 3.00", result);
}

TEST(tS, matrix){

    vector<vector<double>> test = {{1,2}, {3,4}};

    auto result = toString<double>(test, 2);

    EXPECT_EQ("1.00, 2.00\n3.00, 4.00\n", result);
}
//-------------------------------

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

// operators
//-------------------------------
TEST(add, simple_1){

    vector<double> a = {1, 2, 3, 4};
    vector<double> b = {2, 3, -4, -5};

    vector<double> x_should = {3, 5, -1, -1};

    auto x = add<double>(a, b);

    EXPECT_EQ(x_should, x);
}

TEST(sub, simple_1){

    vector<double> a = {1, 2, 3, 4};
    vector<double> b = {2, 3, -4, -5};

    vector<double> x_should = {-1, -1, 7, 9};

    auto x = subtract<double>(a, b);

    EXPECT_EQ(x_should, x);
}

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


// PLU decomposition
//-------------------------------
TEST(interRow, simple_1){

    vector<vector<double>> matrix = {{1,2}, {3,4}};

    EXPECT_EQ("1.00, 2.00\n3.00, 4.00\n", toString(matrix, 2));

    interchangeRow(matrix, 0, 1, 1, 2);

    EXPECT_EQ("1.00, 4.00\n3.00, 2.00\n", toString(matrix, 2));
}

TEST(gMU_idx, simple_1){

    vector<double> row = {19, 18, 1, 10, 2, 3};

   auto result = get_max_U_idx(row, 2);

    EXPECT_EQ(3, result);
}

TEST(plu, simple_1) {


    vector<vector<double>> A {{1,2,3},{4,5,6},{7,8,9}};
    vector<unsigned long> P;
    auto LU = PLU<double, float>(A, P);

    auto L_result = toString(LU[0],2);
    auto U_result = toString(LU[1],2);

    vector<unsigned long> P_expected = {2, 0, 1};

    EXPECT_EQ(L_result, "1.00, 0.00, 0.00\n0.14, 1.00, 0.00\n0.57, 0.50, 1.00\n");
    EXPECT_EQ(U_result, "7.00, 8.00, 9.00\n0.00, 0.86, 1.71\n0.00, 0.00, 0.00\n");
    EXPECT_EQ(P, P_expected);

}
//-------------------------------


// fw and bw substitution
//-------------------------------
TEST(fS, simple_1){

    vector<vector<double>> L = {{-4.3, 0, 0, 0}, {2, -5.2, 0, 0}, {-18, 7.4, -1, 0}, {3, -0.34, 4.2321, 1.98}};
    vector<double> b = {34.2, 2.4, 24.3, -0.034};

    vector<double> x_should = {-7.9534883720930241, -3.5205724508050094, 92.810554561717368, -186.94650377658519};

    auto x = fS<double>(L, b);

    EXPECT_EQ(x_should, x);
}

TEST(bS, simple_1){

    vector<vector<double>> U = {{3, -0.34, 4.2321, 1.98}, {0, 7.4, -1, -18}, {0, 0, -5.2, 2}, {0, 0, 0, -4.3}};
    vector<double> b = {3.2, 2.4, 24.3, -0.034};

    vector<double> x_should = {7.6168809817241199, -0.28752840497026538, -4.670035778175313, 0.0079069767441860474};

    auto x = bS<double>(U, b);

    EXPECT_EQ(x_should, x);
}
//-------------------------------


// solver
//-------------------------------
TEST(pV, simple_1){

    vector<unsigned long> P = {0, 2, 1, 3};
    vector<double> b = {2, 3, 4, 5};

    vector<double> x_should = {2, 4, 3, 5};

    auto x = permuteVector<double>(P, b);

    EXPECT_EQ(x_should, x);
}


TEST(directPLU, simple_1){

    vector<vector<double>> A = {{5, 1, 3, 4}, {1, 1, 1, 2}, {1, 2, 1, 3}, {4, 2, -1, 3}};
    vector<double> b = {32, 14, 20, 17};

    vector<double> x_should = {1, 2, 3, 4};

    auto x = directPLU(A, b);

    EXPECT_EQ(x_should, round(x, 0.0001));
}

TEST(irPLU, simple_1){

    vector<vector<long double>> A = {{5, 1, 3, 4}, {1, 1, 1, 2}, {1, 2, 1, 3}, {4, 2, -1, 3}};
    vector<long double> b = {32, 14, 20, 17};

    vector<double> x_should = {1, 2, 3, 4};

    auto x = irPLU<float, double, long double>(A, b, 10);

    EXPECT_EQ(x_should, round(x, 0.0001));
}
//-------------------------------