#include "gtest/gtest.h"
#include "ira.h"

TEST(vectorNorm_L1, exception_vector_empty) {

    bool should = true;

    vector<mps> mps_vector;

    bool test = false;

    try
    {
        auto ret = ira::vectorNorm_L1(mps_vector);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorNorm_L1, simple_1_float) {

    std::string should = "45.00";

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> double_vector{ 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto mps_vector = ira::double_to_mps(mantissa_length, exponent_length, double_vector);
    auto result = ira::vectorNorm_L1(mps_vector);


    EXPECT_EQ(should, result.to_string(2));
}

TEST(vectorNorm_L1, simple_1_double) {

    std::string should = "45.00000000";

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> double_vector{ 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto mps_vector = ira::double_to_mps(mantissa_length, exponent_length, double_vector);
    auto result = ira::vectorNorm_L1(mps_vector);


    EXPECT_EQ(should, result.to_string(8));
}


TEST(vectorAddition, exception_first_vector_empty) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<mps> first;
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);

    bool test = false;

    try
    {
        auto tmp = ira::vectorAddition(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorAddition, exception_second_vector_empty) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);

    vector<mps> second;

    bool test = false;

    try
    {
        auto tmp = ira::vectorAddition(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorAddition, exception_not_same_size) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);

    bool test = false;

    try
    {
        auto tmp = ira::vectorAddition(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorAddition, exception_exponent_not_same_size) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length-1, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);

    bool test = false;

    try
    {
        auto tmp = ira::vectorAddition(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorAddition, exception_mantissa_not_same_size) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length-1, exponent_length, second_double);

    bool test = false;

    try
    {
        auto tmp = ira::vectorAddition(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorAddition, simple_1_float) {

    std::string should = "4.00, 4.00, 4.00, 4.00";

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);


    auto result = ira::vectorAddition(first, second);


    EXPECT_EQ(should, ira::to_string(result, 2));
}

TEST(vectorAddition, simple_1_double) {

    std::string should = "4.00000000, 4.00000000, 4.00000000, 4.00000000";

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);


    auto result = ira::vectorAddition(first, second);


    EXPECT_EQ(should, ira::to_string(result, 8));
}


TEST(vectorSubtraction, exception_first_vector_empty) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<mps> first;
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);

    bool test = false;

    try
    {
        auto tmp = ira::vectorSubtraction(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorSubtraction, exception_second_vector_empty) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);

    vector<mps> second;

    bool test = false;

    try
    {
        auto tmp = ira::vectorSubtraction(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorSubtraction, exception_not_same_size) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);

    bool test = false;

    try
    {
        auto tmp = ira::vectorSubtraction(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorSubtraction, exception_exponent_not_same_size) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length-1, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);

    bool test = false;

    try
    {
        auto tmp = ira::vectorSubtraction(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorSubtraction, exception_mantissa_not_same_size) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length-1, exponent_length, second_double);

    bool test = false;

    try
    {
        auto tmp = ira::vectorSubtraction(first, second);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(vectorSubtraction, simple_1_float) {

    std::string should = "0.00, 0.00, 0.00, 0.00";

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);


    auto result = ira::vectorSubtraction(first, second);


    EXPECT_EQ(should, ira::to_string(result, 2));
}

TEST(vectorSubtraction, simple_1_double) {

    std::string should = "0.00000000, 0.00000000, 0.00000000, 0.00000000";

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> first_double{2, 2, 2, 2};
    auto first = ira::double_to_mps(mantissa_length, exponent_length, first_double);
    vector<double> second_double{2, 2, 2, 2};
    auto second = ira::double_to_mps(mantissa_length, exponent_length, second_double);


    auto result = ira::vectorSubtraction(first, second);


    EXPECT_EQ(should, ira::to_string(result, 8));
}


TEST(matrixVectorProduct, exception_D_empty) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<mps> D;
    vector<double> x_double{2, 2, 2, 2};
    auto x = ira::double_to_mps(mantissa_length, exponent_length, x_double);

    bool test = false;

    try
    {
        auto tmp = ira::matrixVectorProduct(D, x);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(matrixVectorProduct, exception_x_empty) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> D_double{2, 2, 2, 2};
    auto D = ira::double_to_mps(mantissa_length, exponent_length, D_double);

    vector<mps> x;

    bool test = false;

    try
    {
        auto tmp = ira::matrixVectorProduct(D, x);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(matrixVectorProduct, exception_dimensions_not_the_same) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> D_double{2, 2, 2, 2};
    auto D = ira::double_to_mps(mantissa_length, exponent_length, D_double);
    vector<double> x_double{2, 2, 2, 2};
    auto x = ira::double_to_mps(mantissa_length, exponent_length, x_double);

    bool test = false;

    try
    {
        auto tmp = ira::matrixVectorProduct(D, x);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(matrixVectorProduct, exception_mantissas_not_the_same) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> D_double{2, 2, 2, 2};
    auto D = ira::double_to_mps(mantissa_length-1, exponent_length, D_double);
    vector<double> x_double{2, 2};
    auto x = ira::double_to_mps(mantissa_length, exponent_length, x_double);

    bool test = false;

    try
    {
        auto tmp = ira::matrixVectorProduct(D, x);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(matrixVectorProduct, exception_exponents_not_the_same) {

    bool should = true;

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> D_double{2, 2, 2, 2};
    auto D = ira::double_to_mps(mantissa_length, exponent_length, D_double);
    vector<double> x_double{2, 2};
    auto x = ira::double_to_mps(mantissa_length, exponent_length-1, x_double);

    bool test = false;

    try
    {
        auto tmp = ira::matrixVectorProduct(D, x);
    }

    catch (std::invalid_argument& e)
    {
        test = true;
    }

    EXPECT_EQ(should, test);
}

TEST(matrixVectorProduct, simple_1_float) {

    std::string should = "8.00, 8.00";

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> D_double{2, 2, 2, 2};
    auto D = ira::double_to_mps(mantissa_length, exponent_length, D_double);
    vector<double> x_double{2, 2};
    auto x = ira::double_to_mps(mantissa_length, exponent_length, x_double);

   auto result = ira::matrixVectorProduct(D, x);

    EXPECT_EQ(should, ira::to_string(result, 2));
}

TEST(matrixVectorProduct, simple_1_double) {

    std::string should = "8.00000000, 8.00000000";

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> D_double{2, 2, 2, 2};
    auto D = ira::double_to_mps(mantissa_length, exponent_length, D_double);
    vector<double> x_double{2, 2};
    auto x = ira::double_to_mps(mantissa_length, exponent_length, x_double);

    auto result = ira::matrixVectorProduct(D, x);

    EXPECT_EQ(should, ira::to_string(result, 8));
}

TEST(matrixVectorProduct, simple_2_float) {

    std::string should = "8.00, 18.00";

    unsigned long mantissa_length = 23;
    unsigned long exponent_length = 8;

    vector<double> D_double{1, 2, 3, 4};
    auto D = ira::double_to_mps(mantissa_length, exponent_length, D_double);
    vector<double> x_double{2, 3};
    auto x = ira::double_to_mps(mantissa_length, exponent_length, x_double);

    auto result = ira::matrixVectorProduct(D, x);

    EXPECT_EQ(should, ira::to_string(result, 2));
}

TEST(matrixVectorProduct, simple_2_double) {

    std::string should = "8.00000000, 18.00000000";

    unsigned long mantissa_length = 52;
    unsigned long exponent_length = 11;

    vector<double> D_double{1, 2, 3, 4};
    auto D = ira::double_to_mps(mantissa_length, exponent_length, D_double);
    vector<double> x_double{2, 3};
    auto x = ira::double_to_mps(mantissa_length, exponent_length, x_double);

    auto result = ira::matrixVectorProduct(D, x);

    EXPECT_EQ(should, ira::to_string(result, 8));
}
