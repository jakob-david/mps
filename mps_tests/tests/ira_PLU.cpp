#include "gtest/gtest.h"

#include "ira.h"


TEST(PLU, simple_3x3_1) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition();


    bool test = true;
    std::string L_result;
    std::string U_result;
    std::string P_result;

    try
    {
        L_result = IRA.to_string('L', 0);
        U_result = IRA.to_string('L', 0);
        P_result = IRA.to_string('L', 0);
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }

    EXPECT_EQ(L_result, "1, 0, 0, 4, 1, 0, 7, 2, 1");
    EXPECT_EQ(U_result, "1, 2, 3, 0, -3, -6, 0, 0, 0");
    EXPECT_EQ(P_result, "1, 0, 0, 0, 1, 0, 0, 0, 1");
    EXPECT_EQ(true, test);
}
