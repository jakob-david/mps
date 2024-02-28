#include "gtest/gtest.h"

#include "ira.h"


TEST(PLU, simple_3x3_1) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    IRA.PLU_decomposition();


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
