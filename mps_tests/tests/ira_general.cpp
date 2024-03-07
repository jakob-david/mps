#include "gtest/gtest.h"

#include "ira.h"

TEST(unitary_matrix, init_2x2) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(2);
    IRA.unitary(mantissa_length, exponent_length);

    EXPECT_EQ(IRA.to_string('A'), "1.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(unitary_matrix, init_3x3) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(3);
    IRA.unitary(mantissa_length, exponent_length);

    EXPECT_EQ(IRA.to_string('A'), "1.000000, 0.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}


TEST(custom_matrix, init_2x2) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40 };

    ira IRA(2);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    EXPECT_EQ(IRA.to_string('A'), "10.000000, 20.000000, 30.000000, 40.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(custom_matrix, init_3x3) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    EXPECT_EQ(IRA.to_string('A'), "10.000000, 20.000000, 30.000000, 40.000000, 50.000000, 60.000000, 70.000000, 80.000000, 90.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(custom_matrix, new_matrix_too_large) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    ira IRA(3);

    bool test = false;

    try
    {
        IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(custom_matrix, new_matrix_too_small) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80};

    ira IRA(3);

    bool test = false;

    try
    {
        IRA.setMatrix(mantissa_length, exponent_length, new_matrix);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}


TEST(to_string, exception_L_nullptr) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    bool test = true;

    try
    {
        auto tmp = IRA.to_string('L');
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }

    EXPECT_EQ(true, test);
}

TEST(to_string, exception_U_nullptr) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    bool test = true;

    try
    {
        auto tmp = IRA.to_string('U');
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }

    EXPECT_EQ(true, test);
}

TEST(to_string, exception_P_nullptr) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    bool test = true;

    try
    {
        auto tmp = IRA.to_string('P');
    }

    catch (std::invalid_argument& e)
    {
        test = false;
    }

    EXPECT_EQ(true, test);
}

TEST(to_string, exception_invalid_argument) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    bool test = false;

    try
    {
        auto tmp = IRA.to_string('Z');
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(to_string, round_to_precision_zero) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    EXPECT_EQ(IRA.to_string('A', 0), "10, 20, 30, 40, 50, 60, 70, 80, 90");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(to_string, round_to_precision_two) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    EXPECT_EQ(IRA.to_string('A', 2), "10.00, 20.00, 30.00, 40.00, 50.00, 60.00, 70.00, 80.00, 90.00");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}


TEST(to_string_vector, exception_vector_empty) {

    vector<mps> mps_vector;

    bool test = false;

    try
    {
        auto ret = ira::to_string(mps_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(to_string_vector, simple_float) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, 45.34);
    mps_vector.emplace_back(mantissa_length, exponent_length, -32);
    mps_vector.emplace_back(mantissa_length, exponent_length, 3463246);
    mps_vector.emplace_back(mantissa_length, exponent_length, -0.34345);

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(mantissa_length, mps_vector[0].mantissa_length);
    EXPECT_EQ(exponent_length, mps_vector[0].exponent_length);
}

TEST(to_string_vector, simple_double) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, 45.34);
    mps_vector.emplace_back(mantissa_length, exponent_length, -32);
    mps_vector.emplace_back(mantissa_length, exponent_length, 3463246);
    mps_vector.emplace_back(mantissa_length, exponent_length, -0.34346);

    EXPECT_EQ(ira::to_string(mps_vector, 4), "45.3400, -32.0000, 3463246.0000, -0.3435");
    EXPECT_EQ(mantissa_length, mps_vector[0].mantissa_length);
    EXPECT_EQ(exponent_length, mps_vector[0].exponent_length);
}


TEST(setL, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_L{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);

    IRA.setL(mantissa_length, exponent_length, new_L);


    EXPECT_EQ("10, 20, 30, 40, 50, 60, 70, 80, 90", IRA.to_string('L', 0));
}

TEST(setL, exception_L_too_large) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_L{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    ira IRA(3);

    bool test = false;

    try
    {
        IRA.setL(mantissa_length, exponent_length, new_L);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(setL, exception_L_too_small) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_L{ 10, 20, 30, 40, 50, 60, 70, 80};

    ira IRA(3);

    bool test = false;

    try
    {
        IRA.setL(mantissa_length, exponent_length, new_L);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(setU, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_U{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);

    IRA.setU(mantissa_length, exponent_length, new_U);


    EXPECT_EQ("10, 20, 30, 40, 50, 60, 70, 80, 90", IRA.to_string('U', 0));
}

TEST(setL, exception_U_too_large) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_U{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    ira IRA(3);

    bool test = false;

    try
    {
        IRA.setU(mantissa_length, exponent_length, new_U);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(setL, exception_U_too_small) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_U{ 10, 20, 30, 40, 50, 60, 70, 80};

    ira IRA(3);

    bool test = false;

    try
    {
        IRA.setU(mantissa_length, exponent_length, new_U);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}


TEST(double_to_mps, exception_vector_empty) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> double_vector;

    bool test = false;

    try
    {
        auto ret = ira::double_to_mps(mantissa_length, exponent_length, double_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(double_to_mps, exception_mantissa_too_small) {

    unsigned long mantissa_length = 0;
    unsigned long exponent_length = 11;

    vector<double> double_vector;

    bool test = false;

    try
    {
        auto ret = ira::double_to_mps(mantissa_length, exponent_length, double_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(double_to_mps, exception_exponent_too_small) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 0;

    vector<double> double_vector;

    bool test = false;

    try
    {
        auto ret = ira::double_to_mps(mantissa_length, exponent_length, double_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(double_to_mps, simple_float) {

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(mantissa_length, exponent_length, double_vector);

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(mantissa_length, mps_vector[0].mantissa_length);
    EXPECT_EQ(exponent_length, mps_vector[0].exponent_length);
}

TEST(double_to_mps, simple_double) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(mantissa_length, exponent_length, double_vector);

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(mantissa_length, mps_vector[0].mantissa_length);
    EXPECT_EQ(exponent_length, mps_vector[0].exponent_length);
}



