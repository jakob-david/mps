#include "gtest/gtest.h"

#include "ira.h"



// setter and getter
// -------------------------------------
TEST(unitary_matrix, init_2x2) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(2);
    IRA.setUnitaryMatrix(mantissa_length, exponent_length);

    EXPECT_EQ(IRA.to_string('A'), "1.000000, 0.000000, 0.000000, 1.000000");
    EXPECT_EQ(mantissa_length, IRA.getMatrixElement(0).mantissa_length);
    EXPECT_EQ(exponent_length, IRA.getMatrixElement(0).exponent_length);
}

TEST(unitary_matrix, init_3x3) {

    unsigned long mantissa_length = 53;
    unsigned long exponent_length = 11;

    ira IRA(3);
    IRA.setUnitaryMatrix(mantissa_length, exponent_length);

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

TEST(setRandomMatrix, exception_exponent_too_small) {

    unsigned long n = 3;

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 0;

    ira IRA(n);

    bool test = false;
    try
    {
        IRA.setRandomMatrix(mantissa_length, exponent_length);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_TRUE(test);
}

TEST(setRandomMatrix, simple_1) {

    unsigned long n = 3;

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    ira IRA(n);
    IRA.setRandomMatrix(mantissa_length, exponent_length);

    for(unsigned long i = 0; i < n * n; i++){
        EXPECT_TRUE(IRA.getMatrixElement(i).getValue() <= 10);
        EXPECT_TRUE(IRA.getMatrixElement(i).getValue() >= -10);
    }

    bool test = false;
    try
    {
        auto tmp = IRA.getMatrixElement(n*n+1);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_TRUE(test);
}

TEST(setRandomMatrix, simple_2) {

    unsigned long n = 6;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    ira IRA(n);
    IRA.setRandomMatrix(mantissa_length, exponent_length);

    for(unsigned long i = 0; i < n * n; i++){
        EXPECT_TRUE(IRA.getMatrixElement(i).getValue() <= 10);
        EXPECT_TRUE(IRA.getMatrixElement(i).getValue() >= -10);
    }

    bool test = false;
    try
    {
        auto tmp = IRA.getMatrixElement(n*n+1);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_TRUE(test);
}

TEST(getMatrixElement, idx_too_large) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    bool test = false;

    try
    {
        auto tmp = IRA.getMatrixElement(9);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(getMatrixElement, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> new_matrix{ 10, 20, 30, 40, 50, 60, 70, 80, 90};

    ira IRA(3);
    IRA.setMatrix(mantissa_length, exponent_length, new_matrix);

    auto tmp = IRA.getMatrixElement(8);

    EXPECT_EQ("90.00", tmp.to_string(2));
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



// casts
// -------------------------------------
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

TEST(mps_to_double, exception_vector_empty) {

    vector<mps> mps_vector;


    bool test = false;

    try
    {
        auto double_vector = ira::mps_to_double(mps_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_TRUE(test);
}

TEST(mps_to_double, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;
    vector<double> should_vector{45.34, -32, 3463246, -0.34345};

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[0]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[1]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[2]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[3]);

    auto double_vector = ira::mps_to_double(mps_vector);


    std::string tmp = "";
    for(unsigned long i = 0; i < should_vector.size(); i++){
        EXPECT_EQ(should_vector[i], double_vector[i]);
    }
}

TEST(mps_to_float, exception_vector_empty) {

    vector<mps> mps_vector;


    bool test = false;

    try
    {
        auto double_vector = ira::mps_to_float(mps_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_TRUE(test);
}

TEST(mps_to_float, simple_1) {

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;
    vector<float> should_vector{45.34f, -32, 3463246, -0.34345f};

    vector<mps> mps_vector;
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[0]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[1]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[2]);
    mps_vector.emplace_back(mantissa_length, exponent_length, should_vector[3]);

    auto float_vector = ira::mps_to_float(mps_vector);


    std::string tmp = "";
    for(unsigned long i = 0; i < should_vector.size(); i++){
        EXPECT_EQ(should_vector[i], float_vector[i]);
    }
}

TEST(castVectorElements, exception_vector_empty) {

    vector<mps> mps_vector;

    bool test = false;

    try
    {
        ira::castVectorElements(52, 11, &mps_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(castVectorElements, exception_mantissa_too_small) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(23, 8, double_vector);

    bool test = false;

    try
    {
        ira::castVectorElements(0, 11, &mps_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(castVectorElements, exception_exponent_too_small) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(23, 8, double_vector);

    bool test = false;

    try
    {
        ira::castVectorElements(52, 1, &mps_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(true, test);
}

TEST(castVectorElements, float_to_double_1) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(23, 8, double_vector);
    ira::castVectorElements(52, 11, &mps_vector);

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(52, mps_vector[0].mantissa_length);
    EXPECT_EQ(11, mps_vector[0].exponent_length);
}

TEST(castVectorElements, double_to_float_1) {

    vector<double> double_vector;
    double_vector.push_back(45.34);
    double_vector.push_back(-32);
    double_vector.push_back(3463246);
    double_vector.push_back(-0.34345);

    auto mps_vector = ira::double_to_mps(52, 11, double_vector);
    ira::castVectorElements(23, 8, &mps_vector);

    EXPECT_EQ(ira::to_string(mps_vector, 2), "45.34, -32.00, 3463246.00, -0.34");
    EXPECT_EQ(23, mps_vector[0].mantissa_length);
    EXPECT_EQ(8, mps_vector[0].exponent_length);
}



// printing
// -------------------------------------
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



