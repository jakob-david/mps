#include "gtest/gtest.h"

#include "ira.h"



TEST(PLU, simple_3x3_float_1) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> new_matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.to_string('L', 2);
        U_result = IRA.to_string('U', 2);
        P_result = IRA.to_string('P', 2);
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

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.to_string('L', 4);
        U_result = IRA.to_string('U', 4);
        P_result = IRA.to_string('P', 4);
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

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.to_string('L', 8);
        U_result = IRA.to_string('U', 8);
        P_result = IRA.to_string('P', 8);
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

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.to_string('L', 8);
        U_result = IRA.to_string('U', 8);
        P_result = IRA.to_string('P', 8);
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

    ira IRA(4);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.to_string('L', 2);
        U_result = IRA.to_string('U', 2);
        P_result = IRA.to_string('P', 2);
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

    ira IRA(4);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.to_string('L', 2);
        U_result = IRA.to_string('U', 2);
        P_result = IRA.to_string('P', 2);
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

    ira IRA(4);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.to_string('L', 8);
        U_result = IRA.to_string('U', 8);
        P_result = IRA.to_string('P', 8);
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

    ira IRA(4);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition(mantissa_length, exponent_length);


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.to_string('L', 8);
        U_result = IRA.to_string('U', 8);
        P_result = IRA.to_string('P', 8);
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