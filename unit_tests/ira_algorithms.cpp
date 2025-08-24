//
// Created by Jakob on 12.03.24.
//

#include "gtest/gtest.h"

#include "ira.h"
#include "helper_functions.h"


TEST(PLU, exception_mantissa_too_small) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> new_matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_ANY_THROW(IRA.decompPLU(0, exponent_length));
}

TEST(PLU, exception_exponent_too_small) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> new_matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);

    EXPECT_ANY_THROW(IRA.decompPLU(mantissa_length, 1));
}

TEST(PLU, simple_3x3_float_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> new_matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);
    IRA.decompPLU(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.toString('L', 2);
        U_result = IRA.toString('U', 2);
        P_result = IRA.toString('P', 2);
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }


    EXPECT_EQ(L_result, "1.00, 0.00, 0.00, 0.14, 1.00, 0.00, 0.57, 0.50, 1.00");
    EXPECT_EQ(U_result, "7.00, 8.00, 9.00, 0.00, 0.86, 1.71, 0.00, 0.00, 0.00");
    EXPECT_EQ(P_result, "0.00, 0.00, 1.00, 1.00, 0.00, 0.00, 0.00, 1.00, 0.00");
    EXPECT_EQ(true, test);
}

TEST(PLU, simple_3x3_float_2) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> new_matrix{ 4, -7, 2, -3, 1, -6, 3.5, 3, -8.4};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);
    IRA.decompPLU(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.toString('L', 4);
        U_result = IRA.toString('U', 4);
        P_result = IRA.toString('P', 4);
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }


    EXPECT_EQ(L_result, "1.0000, 0.0000, 0.0000, 0.8750, 1.0000, 0.0000, -0.7500, -0.4658, 1.0000");
    EXPECT_EQ(U_result, "4.0000, -7.0000, 2.0000, 0.0000, 9.1250, -10.1500, 0.0000, 0.0000, -9.2274");
    EXPECT_EQ(P_result, "1.0000, 0.0000, 0.0000, 0.0000, 0.0000, 1.0000, 0.0000, 1.0000, 0.0000");
    EXPECT_EQ(true, test);
}

TEST(PLU, simple_3x3_double_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);
    IRA.decompPLU(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.toString('L', 8);
        U_result = IRA.toString('U', 8);
        P_result = IRA.toString('P', 8);
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }


    EXPECT_EQ(L_result, "1.00000000, 0.00000000, 0.00000000, 0.14285714, 1.00000000, 0.00000000, 0.57142857, 0.50000000, 1.00000000");
    EXPECT_EQ(U_result, "7.00000000, 8.00000000, 9.00000000, 0.00000000, 0.85714286, 1.71428571, 0.00000000, 0.00000000, 0.00000000");
    EXPECT_EQ(P_result, "0.00000000, 0.00000000, 1.00000000, 1.00000000, 0.00000000, 0.00000000, 0.00000000, 1.00000000, 0.00000000");
    EXPECT_EQ(true, test);
}

TEST(PLU, simple_3x3_double_2) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 4, -7, 2, -3, 1, -6, 3.5, 3, -8.4};

    ira IRA(3, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);
    IRA.decompPLU(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.toString('L', 8);
        U_result = IRA.toString('U', 8);
        P_result = IRA.toString('P', 8);
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }


    EXPECT_EQ(L_result, "1.00000000, 0.00000000, 0.00000000, 0.87500000, 1.00000000, 0.00000000, -0.75000000, -0.46575342, 1.00000000");
    EXPECT_EQ(U_result, "4.00000000, -7.00000000, 2.00000000, 0.00000000, 9.12500000, -10.15000000, 0.00000000, 0.00000000, -9.22739726");
    EXPECT_EQ(P_result, "1.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 1.00000000, 0.00000000, 1.00000000, 0.00000000");
    EXPECT_EQ(true, test);
}

TEST(PLU, simple_4x4_float_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> new_matrix{ 2, 5, 8, 7, 5, 2, 2, 8, 7, 5, 6, 6, 5, 4, 4, 8};

    ira IRA(4, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);
    IRA.decompPLU(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.toString('L', 2);
        U_result = IRA.toString('U', 2);
        P_result = IRA.toString('P', 2);
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }


    EXPECT_EQ(L_result, "1.00, 0.00, 0.00, 0.00, 0.29, 1.00, 0.00, 0.00, 0.71, 0.12, 1.00, 0.00, 0.71, -0.44, -0.46, 1.00");
    EXPECT_EQ(U_result, "7.00, 5.00, 6.00, 6.00, 0.00, 3.57, 6.29, 5.29, 0.00, 0.00, -1.04, 3.08, 0.00, 0.00, 0.00, 7.46");
    EXPECT_EQ(P_result, "0.00, 0.00, 1.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 1.00, 0.00, 0.00");
    EXPECT_EQ(true, test);
}

TEST(PLU, simple_4x4_float_2) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> new_matrix{ 5, -2, 0, -6, 2, 8, 2, -4, 2, 12, 3, 5, 2, 33, -32, 3};

    ira IRA(4, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);
    IRA.decompPLU(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.toString('L', 2);
        U_result = IRA.toString('U', 2);
        P_result = IRA.toString('P', 2);
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }


    EXPECT_EQ(L_result, "1.00, 0.00, 0.00, 0.00, 0.40, 1.00, 0.00, 0.00, 0.40, 0.38, 1.00, 0.00, 0.40, 0.26, 0.68, 1.00");
    EXPECT_EQ(U_result, "5.00, -2.00, 0.00, -6.00, 0.00, 33.80, -32.00, 5.40, 0.00, 0.00, 15.12, 5.36, 0.00, -0.00, 0.00, -6.67");
    EXPECT_EQ(P_result, "1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 1.00, 0.00, 0.00, 1.00, 0.00, 0.00");
    EXPECT_EQ(true, test);
}

TEST(PLU, simple_4x4_double_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 2, 5, 8, 7, 5, 2, 2, 8, 7, 5, 6, 6, 5, 4, 4, 8};

    ira IRA(4, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);
    IRA.decompPLU(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.toString('L', 8);
        U_result = IRA.toString('U', 8);
        P_result = IRA.toString('P', 8);
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }


    EXPECT_EQ(L_result, "1.00000000, 0.00000000, 0.00000000, 0.00000000, 0.28571429, 1.00000000, 0.00000000, 0.00000000, 0.71428571, 0.12000000, 1.00000000, 0.00000000, 0.71428571, -0.44000000, -0.46153846, 1.00000000");
    EXPECT_EQ(U_result, "7.00000000, 5.00000000, 6.00000000, 6.00000000, 0.00000000, 3.57142857, 6.28571429, 5.28571429, 0.00000000, 0.00000000, -1.04000000, 3.08000000, 0.00000000, 0.00000000, 0.00000000, 7.46153846");
    EXPECT_EQ(P_result, "0.00000000, 0.00000000, 1.00000000, 0.00000000, 1.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 1.00000000, 0.00000000, 1.00000000, 0.00000000, 0.00000000");
    EXPECT_EQ(true, test);
}

TEST(PLU, simple_4x4_double_2) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 5, -2, 0, -6, 2, 8, 2, -4, 2, 12, 3, 5, 2, 33, -32, 3};

    ira IRA(4, mantissa_length, exponent_length);
    IRA.setMatrix(new_matrix);
    IRA.decompPLU(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.toString('L', 8);
        U_result = IRA.toString('U', 8);
        P_result = IRA.toString('P', 8);
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }


    EXPECT_EQ(L_result, "1.00000000, 0.00000000, 0.00000000, 0.00000000, 0.40000000, 1.00000000, 0.00000000, 0.00000000, 0.40000000, 0.37869822, 1.00000000, 0.00000000, 0.40000000, 0.26035503, 0.68336595, 1.00000000");
    EXPECT_EQ(U_result, "5.00000000, -2.00000000, 0.00000000, -6.00000000, 0.00000000, 33.80000000, -32.00000000, 5.40000000, 0.00000000, 0.00000000, 15.11834320, 5.35502959, 0.00000000, 0.00000000, 0.00000000, -6.66536204");
    EXPECT_EQ(P_result, "1.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 1.00000000, 0.00000000, 0.00000000, 1.00000000, 0.00000000, 0.00000000, 1.00000000, 0.00000000, 0.00000000");
    EXPECT_EQ(true, test);
}



TEST(FS, exception_L_empty) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(4, mantissa_length, exponent_length);

    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);

    EXPECT_ANY_THROW(auto x = IRA.forwardSubstitution(b));
}

TEST(FS, exception_b_empty) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(4, mantissa_length, exponent_length);

    vector<double> new_L{ 3, 0, 0, 0, 2, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1};
    IRA.setL(new_L);

    vector<mps> b;

    EXPECT_ANY_THROW(auto x = IRA.forwardSubstitution(b));
}

TEST(FS, simple_4x4_float_1){

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(4, mantissa_length, exponent_length);


    vector<double> new_L{ 3, 0, 0, 0, 2, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1};
    IRA.setL(new_L);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);

    auto x = IRA.forwardSubstitution(b);

    std::string solution = x[0].toString(2);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(2);
    }

    EXPECT_EQ(solution, "1.33, -0.67, 2.67, -1.33");
}

TEST(FS, simple_4x4_float_2) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(4, mantissa_length, exponent_length);


    vector<double> new_L{-4.3, 0, 0, 0, 2, -5.2, 0, 0, -18, 7.4, -1, 0, 3, -0.34, 4.2321, 1.98};
    IRA.setL(new_L);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 34.2);
    b.emplace_back(mantissa_length, exponent_length, 2.4);
    b.emplace_back(mantissa_length, exponent_length, 24.3);
    b.emplace_back(mantissa_length, exponent_length, -0.034);

    auto x = IRA.forwardSubstitution(b);

    std::string solution = x[0].toString(2);
    for (unsigned long i = 1; i < b.size(); i++) {
        solution += ", ";
        solution += x[i].toString(2);
    }

    EXPECT_EQ(solution, "-7.95, -3.52, 92.81, -186.95");
}

TEST(FS, simple_4x4_double_1){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(4, mantissa_length, exponent_length);


    vector<double> new_L{ 3, 0, 0, 0, 2, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1};
    IRA.setL(new_L);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);

    auto x = IRA.forwardSubstitution(b);

    std::string solution = x[0].toString(8);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(8);
    }

    EXPECT_EQ(solution, "1.33333333, -0.66666667, 2.66666667, -1.33333333");
}

TEST(FS, simple_4x4_double_2){


    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(4, mantissa_length, exponent_length);


    vector<double> new_L{-4.3, 0, 0, 0, 2, -5.2, 0, 0, -18, 7.4, -1, 0, 3, -0.34, 4.2321, 1.98};
    IRA.setL(new_L);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 34.2);
    b.emplace_back(mantissa_length, exponent_length, 2.4);
    b.emplace_back(mantissa_length, exponent_length, 24.3);
    b.emplace_back(mantissa_length, exponent_length, -0.034);

    auto x = IRA.forwardSubstitution(b);

    std::string solution = x[0].toString(8);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(8);
    }

    EXPECT_EQ(solution, "-7.95348837, -3.52057245, 92.81055456, -186.94650378");
}

TEST(FS, simple_5x5_float_1){

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(5, mantissa_length, exponent_length);

    vector<double> new_L{3, 0, 0, 0, 0, 2, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 3, 5, 1, 3, 2};
    IRA.setL(new_L);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);

    auto x = IRA.forwardSubstitution(b);

    std::string solution = x[0].toString(2);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(2);
    }

    EXPECT_EQ(solution, "1.33, -0.67, 2.67, -1.33, 2.33");
}

TEST(FS, simple_5x5_float_2){

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(5, mantissa_length, exponent_length);

    vector<double> new_L{-4.3, 0, 0, 0, 0, 2, -5.2, 0, 0, 0, -18, 7.4, -1, 0, 0, 3, -0.34, 4.2321, 1.98, 0, 3.64, -2.4, -14.7, 2, 9.3};
    IRA.setL(new_L);

    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 34.2);
    b.emplace_back(mantissa_length, exponent_length, 2.4);
    b.emplace_back(mantissa_length, exponent_length, 24.3);
    b.emplace_back(mantissa_length, exponent_length, -0.034);
    b.emplace_back(mantissa_length, exponent_length, 8.6);

    auto x = IRA.forwardSubstitution(b);

    std::string solution = x[0].toString(2);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(2);
    }

    EXPECT_EQ(solution, "-7.95, -3.52, 92.81, -186.95, 190.03");
}

TEST(FS, simple_5x5_double_1){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(5, mantissa_length, exponent_length);

    vector<double> new_L{3, 0, 0, 0, 0, 2, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 3, 5, 1, 3, 2};
    IRA.setL(new_L);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);

    auto x = IRA.forwardSubstitution(b);

    std::string solution = x[0].toString(8);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(8);
    }

    EXPECT_EQ(solution, "1.33333333, -0.66666667, 2.66666667, -1.33333333, 2.33333333");
}

TEST(FS, simple_5x5_double_2){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(5, mantissa_length, exponent_length);

    vector<double> new_L{-4.3, 0, 0, 0, 0, 2, -5.2, 0, 0, 0, -18, 7.4, -1, 0, 0, 3, -0.34, 4.2321, 1.98, 0, 3.64, -2.4, -14.7, 2, 9.3};
    IRA.setL(new_L);

    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 34.2);
    b.emplace_back(mantissa_length, exponent_length, 2.4);
    b.emplace_back(mantissa_length, exponent_length, 24.3);
    b.emplace_back(mantissa_length, exponent_length, -0.034);
    b.emplace_back(mantissa_length, exponent_length, 8.6);

    auto x = IRA.forwardSubstitution(b);

    std::string solution = x[0].toString(8);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(8);
    }

    EXPECT_EQ(solution, "-7.95348837, -3.52057245, 92.81055456, -186.94650378, 190.03327779");
}



TEST(BS, exception_L_empty) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(4, mantissa_length, exponent_length);

    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);

    EXPECT_ANY_THROW(auto x = IRA.backwardSubstitution(b));
}

TEST(BS, exception_b_empty) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(4, mantissa_length, exponent_length);

    vector<double> new_U{ 1, 1, 2, 1, 0, 4, 1, 1, 0, 0, 2, 1, 0, 0, 0, 3};
    IRA.setU(new_U);

    vector<mps> b;

    EXPECT_ANY_THROW(auto x = IRA.backwardSubstitution(b));
}

TEST(BS, simple_4x4_float_1){

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(4, mantissa_length, exponent_length);

    vector<double> new_U{ 1, 1, 2, 1, 0, 4, 1, 1, 0, 0, 2, 1, 0, 0, 0, 3};
    IRA.setU(new_U);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);

    auto x = IRA.backwardSubstitution(b);

    std::string solution = x[0].toString(2);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(2);
    }

    EXPECT_EQ(solution, "0.08, -0.08, 1.67, 0.67");

}

TEST(BS, simple_4x4_float_2){

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(4, mantissa_length, exponent_length);

    vector<double> new_U{3, -0.34, 4.2321, 1.98, 0, 7.4, -1, -18, 0, 0, -5.2, 2, 0, 0, 0, -4.3};
    IRA.setU(new_U);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 3.2);
    b.emplace_back(mantissa_length, exponent_length, 2.4);
    b.emplace_back(mantissa_length, exponent_length, 24.3);
    b.emplace_back(mantissa_length, exponent_length, -0.034);

    auto x = IRA.backwardSubstitution(b);

    std::string solution = x[0].toString(2);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(2);
    }

    EXPECT_EQ(solution, "7.62, -0.29, -4.67, 0.01");

}

TEST(BS, simple_4x4_double_1){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(4, mantissa_length, exponent_length);

    vector<double> new_U{ 1, 1, 2, 1, 0, 4, 1, 1, 0, 0, 2, 1, 0, 0, 0, 3};
    IRA.setU(new_U);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);

    auto x = IRA.backwardSubstitution(b);

    std::string solution = x[0].toString(8);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(8);
    }

    EXPECT_EQ(solution, "0.08333333, -0.08333333, 1.66666667, 0.66666667");

}

TEST(BS, simple_4x4_double_2){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(4, mantissa_length, exponent_length);

    vector<double> new_U{3, -0.34, 4.2321, 1.98, 0, 7.4, -1, -18, 0, 0, -5.2, 2, 0, 0, 0, -4.3};
    IRA.setU(new_U);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 3.2);
    b.emplace_back(mantissa_length, exponent_length, 2.4);
    b.emplace_back(mantissa_length, exponent_length, 24.3);
    b.emplace_back(mantissa_length, exponent_length, -0.034);

    auto x = IRA.backwardSubstitution(b);

    std::string solution = x[0].toString(8);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(8);
    }

    EXPECT_EQ(solution, "7.61688098, -0.28752840, -4.67003578, 0.00790698");

}

TEST(BS, simple_5x5_float_1){

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(5, mantissa_length, exponent_length);

    vector<double> new_U{3, 0.5, 1, 3, 2, 0, 1, -1, 1, 3, 0, 0, 1, 0.1, -3, 0, 0, 0, 3, -1, 0, 0, 0, 0, -4};
    IRA.setU(new_U);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 3);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);

    auto x = IRA.backwardSubstitution(b);

    std::string solution = x[0].toString(2);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(2);
    }

    EXPECT_EQ(solution, "0.91, 4.63, -0.03, 0.33, -1.00");

}

TEST(BS, simple_5x5_float_2){

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(5, mantissa_length, exponent_length);

    vector<double> new_U{2.4, 0.5, 3.253, 7, 9.23, 0, 3.2, -1.53, 2.21, 4.23, 0, 0, 7.8, 0.64, -0.321, 0, 0, 0, 7.3, -14, 0, 0, 0, 0, -4.85};
    IRA.setU(new_U);

    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 3.64);
    b.emplace_back(mantissa_length, exponent_length, 8.45);
    b.emplace_back(mantissa_length, exponent_length, -4);
    b.emplace_back(mantissa_length, exponent_length, 15.332);
    b.emplace_back(mantissa_length, exponent_length, -7.6);

    auto x = IRA.backwardSubstitution(b);

    std::string solution = x[0].toString(2);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(2);
    }

    EXPECT_EQ(solution, "-17.52, -3.37, -0.87, 5.11, 1.57");

}

TEST(BS, simple_5x5_double_1){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(5, mantissa_length, exponent_length);

    vector<double> new_U{3, 0.5, 1, 3, 2, 0, 1, -1, 1, 3, 0, 0, 1, 0.1, -3, 0, 0, 0, 3, -1, 0, 0, 0, 0, -4};
    IRA.setU(new_U);


    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 4);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 3);
    b.emplace_back(mantissa_length, exponent_length, 2);
    b.emplace_back(mantissa_length, exponent_length, 4);

    auto x = IRA.backwardSubstitution(b);

    std::string solution = x[0].toString(8);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(8);
    }

    EXPECT_EQ(solution, "0.90555556, 4.63333333, -0.03333333, 0.33333333, -1.00000000");

}

TEST(BS, simple_5x5_double_2){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(5, mantissa_length, exponent_length);

    vector<double> new_U{2.4, 0.5, 3.253, 7, 9.23, 0, 3.2, -1.53, 2.21, 4.23, 0, 0, 7.8, 0.64, -0.321, 0, 0, 0, 7.3, -14, 0, 0, 0, 0, -4.85};
    IRA.setU(new_U);

    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 3.64);
    b.emplace_back(mantissa_length, exponent_length, 8.45);
    b.emplace_back(mantissa_length, exponent_length, -4);
    b.emplace_back(mantissa_length, exponent_length, 15.332);
    b.emplace_back(mantissa_length, exponent_length, -7.6);

    auto x = IRA.backwardSubstitution(b);

    std::string solution = x[0].toString(8);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(8);
    }

    EXPECT_EQ(solution, "-17.52297946, -3.37140356, -0.86724477, 5.10549922, 1.56701031");

}



TEST(solve_LU, simple_3x3_float_1){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 3;    // the extra mantissa bits which are needed to achieve double precision.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {23 + precision, 8};

    ira IRA(3, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 1, 1 ,1, 1, 2 ,1};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], 16);
    b.emplace_back(u[0], u[1], 6);
    b.emplace_back(u[0], u[1], 8);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_float(x);

    vector<float> x_should{1.0f, 2.0f, 3.0f};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value((float) x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value((float) x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value((float) x_result[2]));
}

TEST(solve_LU, simple_3x3_double_1){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 3;    // the extra mantissa bits which are needed to achieve double precision.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {52 + precision, 11};

    ira IRA(3, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 1, 1 ,1, 1, 2 ,1};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], 16);
    b.emplace_back(u[0], u[1], 6);
    b.emplace_back(u[0], u[1], 8);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_double(x);

    vector<double> x_should{1, 2, 3};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value(x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value(x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value(x_result[2]));
}

TEST(solve_LU, simple_3x3_float_2){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 1;    // the extra mantissa bits which are needed to achieve double precision.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {23 + precision, 8};

    ira IRA(3, u[0], u[1]);


    vector<double> new_A{-34.23, 4.2 ,0.43, 3.2, 8.45 ,12.45, -7, 2.45 ,-4.35};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], -62.92316);
    b.emplace_back(u[0], u[1], 194.1884);
    b.emplace_back(u[0], u[1], -21.37);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_float(x);

    vector<float> x_should{3.432f, 12.34f, 6.34f};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value((float) x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value((float) x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value((float) x_result[2]));
}

TEST(solve_LU, simple_3x3_double_2){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 4;    // the extra mantissa bits which are needed to achieve double precision.
    // one value (3.432) needed to be fitted.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {52 + precision, 11};

    ira IRA(3, u[0], u[1]);

    vector<double> new_A{-34.23, 4.2 ,0.43, 3.2, 8.45 ,12.45, -7, 2.45 ,-4.35};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], -62.92316);
    b.emplace_back(u[0], u[1], 194.1884);
    b.emplace_back(u[0], u[1], -21.37);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_double(x);

    vector<double> x_should{3.4320000000000004, 12.34, 6.34};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value(x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value(x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value(x_result[2]));
}

TEST(solve_LU, simple_4x4_float_1){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 7;    // the extra mantissa bits which are needed to achieve double precision.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {23 + precision, 8};

    ira IRA(4, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 4, 1, 1 ,1, 2, 1, 2 ,1, 3, 4, 2 ,-1, 3};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], 32);
    b.emplace_back(u[0], u[1], 14);
    b.emplace_back(u[0], u[1], 20);
    b.emplace_back(u[0], u[1], 17);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_float(x);

    vector<float> x_should{1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value((float) x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value((float) x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value((float) x_result[2]));
    EXPECT_EQ(should_value(x_should[3]), should_value((float) x_result[3]));
}

TEST(solve_LU, simple_4x4_double_1){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 6;    // the extra mantissa bits which are needed to achieve double precision.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {52 + precision, 11};

    ira IRA(4, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 4, 1, 1 ,1, 2, 1, 2 ,1, 3, 4, 2 ,-1, 3};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], 32);
    b.emplace_back(u[0], u[1], 14);
    b.emplace_back(u[0], u[1], 20);
    b.emplace_back(u[0], u[1], 17);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_double(x);

    vector<double> x_should{1, 2, 3, 4};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value(x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value(x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value(x_result[2]));
    EXPECT_EQ(should_value(x_should[3]), should_value(x_result[3]));
}

TEST(solve_LU, simple_5x5_float_1){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 5;    // the extra mantissa bits which are needed to achieve double precision.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {23 + precision, 8};

    ira IRA(5, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 4,2, 1, 1 ,1, 2,5, 1, 2 ,1, 3,2, 4, 2 ,-1, 3, 3, 2, 2 ,-3, 3,-6};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], 42);
    b.emplace_back(u[0], u[1], 39);
    b.emplace_back(u[0], u[1], 30);
    b.emplace_back(u[0], u[1], 32);
    b.emplace_back(u[0], u[1], -21);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_float(x);

    vector<float> x_should{1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value((float) x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value((float) x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value((float) x_result[2]));
    EXPECT_EQ(should_value(x_should[3]), should_value((float) x_result[3]));
    EXPECT_EQ(should_value(x_should[4]), should_value((float) x_result[4]));
}

TEST(solve_LU, simple_5x5_double_1){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 5;    // the extra mantissa bits which are needed to achieve double precision.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {52 + precision, 11};

    ira IRA(5, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 4,2, 1, 1 ,1, 2,5, 1, 2 ,1, 3,2, 4, 2 ,-1, 3, 3, 2, 2 ,-3, 3,-6};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], 42);
    b.emplace_back(u[0], u[1], 39);
    b.emplace_back(u[0], u[1], 30);
    b.emplace_back(u[0], u[1], 32);
    b.emplace_back(u[0], u[1], -21);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_double(x);

    vector<double> x_should{1.0, 2.0, 3.0, 4.0, 5.0};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value(x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value(x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value(x_result[2]));
    EXPECT_EQ(should_value(x_should[3]), should_value(x_result[3]));
    EXPECT_EQ(should_value(x_should[4]), should_value(x_result[4]));
}

TEST(solve_LU, simple_6x6_float_1){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 5;    // the extra mantissa bits which are needed to achieve double precision.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {23 + precision, 8};

    ira IRA(6, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 4, 2, -3, 1, 1 ,1, 2, 5, -2, 1, 2 ,1, 3, 2, 5, 4, 2 ,-1, 3, 3, -4, 2, 2 ,-3, 3,-6, 1, 2, 4 ,-1, 7,-6, -1.5};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], 24);
    b.emplace_back(u[0], u[1], 27);
    b.emplace_back(u[0], u[1], 60);
    b.emplace_back(u[0], u[1], 8);
    b.emplace_back(u[0], u[1], -15);
    b.emplace_back(u[0], u[1], -4);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_float(x);

    vector<float> x_should{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value((float) x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value((float) x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value((float) x_result[2]));
    EXPECT_EQ(should_value(x_should[3]), should_value((float) x_result[3]));
    EXPECT_EQ(should_value(x_should[4]), should_value((float) x_result[4]));
}

TEST(solve_LU, simple_6x6_double_1){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 5;    // the extra mantissa bits which are needed to achieve double precision.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {52 + precision, 11};

    ira IRA(6, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 4, 2, -3, 1, 1 ,1, 2, 5, -2, 1, 2 ,1, 3, 2, 5, 4, 2 ,-1, 3, 3, -4, 2, 2 ,-3, 3,-6, 1, 2, 4 ,-1, 7,-6, -1.5};
    IRA.setMatrix(new_A);

    vector<mps> b;
    b.emplace_back(u[0], u[1], 24);
    b.emplace_back(u[0], u[1], 27);
    b.emplace_back(u[0], u[1], 60);
    b.emplace_back(u[0], u[1], 8);
    b.emplace_back(u[0], u[1], -15);
    b.emplace_back(u[0], u[1], -4);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_double(x);

    vector<double> x_should{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value(x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value(x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value(x_result[2]));
    EXPECT_EQ(should_value(x_should[3]), should_value(x_result[3]));
    EXPECT_EQ(should_value(x_should[4]), should_value(x_result[4]));
}

TEST(solve_LU, exception_b_empty){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 4;    // the extra mantissa bits which are needed to achieve double precision.
    // one value (3.432) needed to be fitted.
    //------------------------------------------------------------------------------------------------------

    unsigned long u[2] = {52 + precision, 11};

    ira IRA(3, u[0], u[1]);

    vector<double> new_A{-34.23, 4.2 ,0.43, 3.2, 8.45 ,12.45, -7, 2.45 ,-4.35};
    IRA.setMatrix(new_A);

    vector<mps> b;
    EXPECT_ANY_THROW(auto tmp = IRA.directPLU(b));

    b.emplace_back(u[0], u[1], -62.92316);
    b.emplace_back(u[0], u[1], 194.1884);
    b.emplace_back(u[0], u[1], -21.37);

    auto x = IRA.directPLU(b);
    auto x_result = ira::mps_to_double(x);

    vector<double> x_should{3.4320000000000004, 12.34, 6.34};

    EXPECT_EQ(x_should, x_result);
    EXPECT_EQ(should_value(x_should[0]), should_value(x_result[0]));
    EXPECT_EQ(should_value(x_should[1]), should_value(x_result[1]));
    EXPECT_EQ(should_value(x_should[2]), should_value(x_result[2]));
}


TEST(solve_LU_double, simple_3x3_1){

    unsigned long u[2] = {52, 11};

    ira IRA(3, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 1, 1 ,1, 1, 2 ,1};
    IRA.setMatrix(new_A);

    vector<double> b;
    b.push_back(16);
    b.push_back(6);
    b.push_back(8);

    auto x_result = IRA.solveLU_double(b);

    vector<double> x_should{1, 2, 3};

    for(unsigned long i = 0; i < b.size(); i++){
        EXPECT_EQ(to_string(x_should[i]), to_string(x_result[i]));
    }
}

TEST(solve_LU_double, simple_3x3_2){

    unsigned long u[2] = {52, 11};

    ira IRA(3, u[0], u[1]);

    vector<double> new_A{-34.23, 4.2 ,0.43, 3.2, 8.45 ,12.45, -7, 2.45 ,-4.35};
    IRA.setMatrix(new_A);

    vector<double> b;
    b.push_back(-62.92316);
    b.push_back(194.1884);
    b.push_back(-21.37);

    auto x_result = IRA.solveLU_double(b);

    vector<double> x_should{3.4320000000000004, 12.34, 6.34};

    for(unsigned long i = 0; i < b.size(); i++){
        EXPECT_EQ(to_string(x_should[i]), to_string(x_result[i]));
    }
}

TEST(solve_LU_double, simple_6x6_1){

    unsigned long u[2] = {52, 11};

    ira IRA(6, u[0], u[1]);

    vector<double> new_A{5, 1 ,3, 4, 2, -3, 1, 1 ,1, 2, 5, -2, 1, 2 ,1, 3, 2, 5, 4, 2 ,-1, 3, 3, -4, 2, 2 ,-3, 3,-6, 1, 2, 4 ,-1, 7,-6, -1.5};
    IRA.setMatrix(new_A);

    vector<double> b;
    b.push_back(24);
    b.push_back(27);
    b.push_back( 60);
    b.push_back( 8);
    b.push_back( -15);
    b.push_back( -4);

    auto x_result = IRA.solveLU_double(b);

    vector<double> x_should{1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    for(unsigned long i = 0; i < b.size(); i++){
        EXPECT_EQ(to_string(x_should[i]), to_string(x_result[i]));
    }
}





TEST(IR, simple_3x3_double_1){

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    unsigned long ul[2] = {52, 11};
    unsigned long u[2] = {52, 11};

    ira IRA(3, mantissa_length, exponent_length);

    vector<double> new_A{5, 1 ,3, 1, 1 ,1, 1, 2 ,1};
    IRA.setMatrix(new_A);
    IRA.setWorkingPrecision(u[0], u[1]);
    IRA.setLowerPrecision(ul[0], ul[1]);

    vector<mps> b;
    b.emplace_back(mantissa_length, exponent_length, 16);
    b.emplace_back(mantissa_length, exponent_length, 6);
    b.emplace_back(mantissa_length, exponent_length, 8);

    auto x = IRA.irPLU(b);


    std::string solution = x[0].toString(8);
    for(unsigned long i = 1; i < b.size(); i++){
        solution += ", ";
        solution += x[i].toString(8);
    }

    EXPECT_EQ(solution, "1.00000000, 2.00000000, 3.00000000");
}

TEST(IR, simple_3x3_double_2){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 51;                // the number of  mantissa bits which should be checked.
    unsigned long ur[2] = {52, 11};     // precision: A
    unsigned long ul[2] = { 23, 11};    // precision: LU
    unsigned long u[2] = {52, 11};      // precision: working
    //------------------------------------------------------------------------------------------------------


    ira IRA(3, ur[0], ur[1]);

    vector<double> new_A{563.46, 634.346, 575.346, 694.3453, 573.234, 4638.67, 985.456, 575.56, 978.56};
    IRA.setMatrix(new_A);
    IRA.setWorkingPrecision(u[0], u[1]);
    IRA.setLowerPrecision(ul[0], ul[1]);

    vector<mps> b;
    b.emplace_back(ur[0], ur[1], 463.56);
    b.emplace_back(ur[0], ur[1], 875.357);
    b.emplace_back(ur[0], ur[1], 235.5745);

    auto x = IRA.irPLU(b);

    auto x_should = IRA.directPLU(b);

    // perform tests
    //--------------------------------
    for(unsigned long i = 0; i < x.size(); i++){

        auto result = x[i].checkPrecision(x_should[i], precision);
        EXPECT_TRUE(result);

        if(!result){
            cout << "x_i:   " << x[i].print() << endl;
            cout << "x_i_s  " << x_should[i].print() << endl;
        }
    }
    //--------------------------------
}

TEST(IR, get_evaluation_value_IR_area){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 51;                // the number of  mantissa bits which should be checked.
    unsigned long ur[2] = {52, 11};     // precision: A
    unsigned long ul[2] = { 23, 11};    // precision: LU
    unsigned long u[2] = {52, 11};      // precision: working
    //------------------------------------------------------------------------------------------------------


    ira IRA(3, ur[0], ur[1]);

    vector<double> new_A{563.46, 634.346, 575.346, 694.3453, 573.234, 4638.67, 985.456, 575.56, 978.56};
    IRA.setMatrix(new_A);
    IRA.setWorkingPrecision(u[0], u[1]);
    IRA.setLowerPrecision(ul[0], ul[1]);

    vector<mps> b;
    b.emplace_back(ur[0], ur[1], 463.56);
    b.emplace_back(ur[0], ur[1], 875.357);
    b.emplace_back(ur[0], ur[1], 235.5745);

    auto x_should = IRA.directPLU(b);
    IRA.setExpectedResult(x_should);

    auto x = IRA.irPLU(b);

    // perform tests
    //--------------------------------
    for(unsigned long i = 0; i < x.size(); i++){

        auto result = x[i].checkPrecision(x_should[i], precision);
        EXPECT_TRUE(result);

        if(!result){
            cout << "x_i:   " << x[i].print() << endl;
            cout << "x_i_s  " << x_should[i].print() << endl;
        }
    }
    //--------------------------------

    EXPECT_TRUE(IRA.evaluation.IR_relativeError_sum > 0);

}

TEST(IR, get_evaluation_value_milliseconds){

    //------------------------------------------------------------------------------------------------------
    unsigned long precision = 51;       // the number of  mantissa bits which should be checked.
    unsigned long ur[2] = {52, 11};     // precision: A
    unsigned long ul[2] = { 23, 11};    // precision: LU
    unsigned long u[2] = {52, 11};      // precision: working
    //------------------------------------------------------------------------------------------------------


    ira IRA(3, ur[0], ur[1]);

    vector<double> new_A{563.46, 634.346, 575.346, 694.3453, 573.234, 4638.67, 985.456, 575.56, 978.56};
    IRA.setMatrix(new_A);
    IRA.setWorkingPrecision(u[0], u[1]);
    IRA.setLowerPrecision(ul[0], ul[1]);

    vector<mps> b;
    b.emplace_back(ur[0], ur[1], 463.56);
    b.emplace_back(ur[0], ur[1], 875.357);
    b.emplace_back(ur[0], ur[1], 235.5745);

    auto x_should = IRA.directPLU(b);
    IRA.setExpectedResult(x_should);

    auto x = IRA.irPLU(b);

    // perform tests
    //--------------------------------
    for(unsigned long i = 0; i < x.size(); i++){

        auto result = x[i].checkPrecision(x_should[i], precision);
        EXPECT_TRUE(result);

        if(!result){
            cout << "x_i:   " << x[i].print() << endl;
            cout << "x_i_s  " << x_should[i].print() << endl;
        }
    }
    //--------------------------------

    EXPECT_TRUE(IRA.evaluation.milliseconds > 0);
}