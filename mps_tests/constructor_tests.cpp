#include "gtest/gtest.h"

#include "mps.h"
#include <bitset>


TEST(constructor_tests, constructor_sets_values_coorectly){

    mps* MPS = new mps(5, 6, 3.14);

    int mantissa_actual = MPS->getMantisseLength();
    int exponent_actual = MPS->getExponentLength();
    int length_actual = MPS->getBitArrayLength();

    EXPECT_EQ(5, mantissa_actual);
    EXPECT_EQ(6, exponent_actual);
    EXPECT_EQ(12, length_actual);
}

TEST(constructor_tests, constructor_initializes_bit_array_correctly){

    mps* MPS = new mps(20, 12, 3.14);

    int size = MPS->getBitArrayLength();

    EXPECT_EQ(33, size);
}


TEST(converter_tests, test_positive_double) {

    double test_value = 342.45636;

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_positive_double_using_getBitArrayReference) {

    double test_value = 572496.394863845;

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArrayReference();

    string str;
    for(bool bit : *binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_negative_double) {

    double test_value = -38758285.203858387583005867;

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_positive_float) {

    float test_value = 345.3456;

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_negative_float) {

    float test_value = -2354.3456;

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_zero_double) {

    double test_value = 0;

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_zero_float) {

    float test_value = 0;

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_pos_infinity_double) {

    double test_value = numeric_limits<double>::infinity();

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_pos_infinity_float) {

    float test_value = numeric_limits<float>::infinity();

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_neg_infinity_double) {

    double test_value = numeric_limits<double>::infinity() * -1;

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_neg_infinity_float) {

    float test_value = numeric_limits<float>::infinity() * -1;

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_pos_max_double) {

    double test_value = numeric_limits<double>::max();  //- 1 * pow(2, 979);

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_pos_max_float) {

    float test_value = numeric_limits<float>::max();

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }


    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_max_float_in_double) {

    double test_value = numeric_limits<float>::max();

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_pos_min_double) {

    double test_value = numeric_limits<double>::min();

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_pos_min_float) {

    float test_value = numeric_limits<float>::min();

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }


    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_small_difference) {

    double test_value = 1.0 + pow(0.5, 52);

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_neg_max_double) {

    double test_value = numeric_limits<double>::max() * -1;

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_neg_max_float) {

    float test_value = numeric_limits<float>::max() * -1;

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }


    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_neg_min_double) {

    double test_value = numeric_limits<double>::min() * -1;

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_neg_min_float) {

    float test_value = numeric_limits<float>::min() * -1;

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }


    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_NAN_double) {

    double test_value = std::numeric_limits<double>::quiet_NaN();

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_NAN_float) {

    float test_value = std::numeric_limits<float>::quiet_NaN();

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_neg_NAN_double) {

    double test_value = std::numeric_limits<double>::quiet_NaN() * -1;

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_neg_NAN_float) {

    float test_value = std::numeric_limits<float>::quiet_NaN() * -1;

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_null_double) {

    double test_value = 0;

    auto MPS = new mps(52, 11, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(converter_tests, test_null_float) {

    float test_value = 0;

    auto MPS = new mps(23, 8, test_value);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}


TEST(setter_tests, set_pos_inf_double) {

    double test_value = numeric_limits<double>::infinity();

    auto MPS = new mps(52, 11, 345.234);

    MPS->setInf();

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(setter_tests, set_pos_inf_float) {

    float test_value = numeric_limits<float>::infinity();

    auto MPS = new mps(23, 8, 345.234);

    MPS->setInf();

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(setter_tests, set_neg_inf_double) {

    double test_value = numeric_limits<double>::infinity() * -1;

    auto MPS = new mps(52, 11, 345.234);

    MPS->setInf(true);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(setter_tests, set_neg_inf_float) {

    float test_value = numeric_limits<float>::infinity() * -1;

    auto MPS = new mps(23, 8, 345.234);

    MPS->setInf(true);

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(setter_tests, set_zero_double) {

    double test_value = 0;

    auto MPS = new mps(52, 11, 345.234);

    MPS->setZero();

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(setter_tests, set_zero_float) {

    float test_value = 0;

    auto MPS = new mps(23, 8, 345.234);

    MPS->setZero();

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(setter_tests, set_NAN_double) {

    double test_value = numeric_limits<double>::quiet_NaN();

    auto MPS = new mps(52, 11, 345.234);

    MPS->setNAN();

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}

TEST(setter_tests, set_NAN_float) {

    float test_value = numeric_limits<float>::quiet_NaN();

    auto MPS = new mps(23, 8, 345.234);

    MPS->setNAN();

    auto binary = MPS->getBitArray();

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    string compare_str;
    char* bits = reinterpret_cast<char*>(&test_value);
    for(std::size_t n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>(bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
}