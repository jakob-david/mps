#include "gtest/gtest.h"

#include "mps.h"
#include <bitset>

std::string is_mps(vector<bool> vec){

    string str;
    for(bool bit : vec){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    return str;
}

template <typename T>
std::string should_value(T fp_number){

    string compare_str;
    char* bits = reinterpret_cast<char*>(&fp_number);
    for(unsigned long n = 0; n < sizeof fp_number; ++n) {
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    return  compare_str;
}


TEST(constructor_tests, constructor_sets_values_coorectly){

    mps MPS(5, 6, 3.14);

    unsigned long mantissa_actual = MPS.getMantisseLength();
    unsigned long exponent_actual = MPS.getExponentLength();

    EXPECT_EQ(5, mantissa_actual);
    EXPECT_EQ(6, exponent_actual);

}

TEST(constructor_tests, constructor_initializes_bit_array_correctly){

    mps MPS(20, 12, 3.14);

    unsigned long size = MPS.getBitArrayLength();
    unsigned long my_size = MPS.my_getBitArrayLength();

    EXPECT_EQ(33, size);
    EXPECT_EQ(33, my_size);
}


TEST(converter_tests, test_positive_double) {

    double test_value = 342.45636;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
    for(unsigned long n = 0; n < sizeof test_value; ++n) {
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_positive_double_using_getBitArrayReference) {

    double test_value = 572496.394863845;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArrayReference();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_negative_double) {

    double test_value = -38758285.203858387583005867;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long)bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_positive_float) {

    float test_value = 345.3456f;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_negative_float) {

    float test_value = -2354.3456f;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_zero_double) {

    double test_value = 0;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_zero_float) {

    float test_value = 0;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long)bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_pos_infinity_double) {

    double test_value = numeric_limits<double>::infinity();

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_pos_infinity_float) {

    float test_value = numeric_limits<float>::infinity();

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_neg_infinity_double) {

    double test_value = numeric_limits<double>::infinity() * -1;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_neg_infinity_float) {

    float test_value = numeric_limits<float>::infinity() * -1;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_pos_max_double) {

    double test_value = numeric_limits<double>::max();  //- 1 * pow(2, 979);

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_pos_max_float) {

    float test_value = numeric_limits<float>::max();

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }


    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_max_float_in_double) {

    double test_value = numeric_limits<float>::max();

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_pos_min_double) {

    double test_value = numeric_limits<double>::min();

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_pos_min_float) {

    float test_value = numeric_limits<float>::min();

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }


    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_small_difference) {

    double test_value = 1.0 + pow(0.5, 52);

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_neg_max_double) {

    double test_value = numeric_limits<double>::max() * -1;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_neg_max_float) {

    float test_value = numeric_limits<float>::max() * -1;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }


    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_neg_min_double) {

    double test_value = numeric_limits<double>::min() * -1;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_neg_min_float) {

    float test_value = numeric_limits<float>::min() * -1;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }


    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_NAN_double) {

    double test_value = std::numeric_limits<double>::quiet_NaN();

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_NAN_float) {

    float test_value = std::numeric_limits<float>::quiet_NaN();

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_neg_NAN_double) {

    double test_value = std::numeric_limits<double>::quiet_NaN() * -1;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_neg_NAN_float) {

    float test_value = std::numeric_limits<float>::quiet_NaN() * -1;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_null_double) {

    double test_value = 0;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(converter_tests, test_null_float) {

    float test_value = 0;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}


TEST(setter_tests, set_pos_inf_double) {

    double test_value = numeric_limits<double>::infinity();

    mps MPS(52, 11, 345.234);

    MPS.setInf();

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(setter_tests, set_pos_inf_float) {

    float test_value = numeric_limits<float>::infinity();

    mps MPS(23, 8, 345.234);

    MPS.setInf();

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(setter_tests, set_neg_inf_double) {

    double test_value = numeric_limits<double>::infinity() * -1;

    mps MPS(52, 11, 345.234);

    MPS.setInf(true);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(setter_tests, set_neg_inf_float) {

    float test_value = numeric_limits<float>::infinity() * -1;

    mps MPS(23, 8, 345.234);

    MPS.setInf(true);

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(setter_tests, set_zero_double) {

    double test_value = 0;

    mps MPS(52, 11, 345.234);

    MPS.setZero();

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(setter_tests, set_zero_float) {

    float test_value = 0;

    mps MPS(23, 8, 345.234);

    MPS.setZero();

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(setter_tests, set_NAN_double) {

    double test_value = numeric_limits<double>::quiet_NaN();

    mps MPS(52, 11, 345.234);

    MPS.setNaN();

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}

TEST(setter_tests, set_NAN_float) {

    float test_value = numeric_limits<float>::quiet_NaN();

    mps MPS(23, 8, 345.234);

    MPS.setNaN();

    auto binary = MPS.getBitArray();

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
        string tmp = std::bitset<8>((unsigned long long) bits[n]).to_string();
        compare_str.insert (0, tmp);
    }

    EXPECT_EQ(compare_str, str);
    EXPECT_EQ(should_value(test_value), is_mps(MPS.my_getBitArray()));
}


TEST(get_value_tests, get_one_double) {

    double test_value = 1;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_one_float) {

    float test_value = 1;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_double) {

    double test_value = 3455763.3467457;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_float) {

    float test_value = 3455763.3467457f;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_one_double) {

    double test_value = -1;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_one_float) {

    float test_value = -1;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_double) {

    double test_value = -2356345.235643;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_float) {

    float test_value = -2356345.235643f;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_zero_double) {

    double test_value = 0;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_zero_float) {

    float test_value = 0;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_pos_inf_double) {

    double test_value = numeric_limits<double>::infinity();

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_pos_inf_float) {

    float test_value = numeric_limits<float>::infinity();

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_inf_double) {

    double test_value = numeric_limits<double>::infinity() * -1;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_inf_float) {

    float test_value = numeric_limits<float>::infinity() * -1;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_pos_max_double) {

    double test_value = numeric_limits<double>::max();

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_pos_max_float) {

    float test_value = numeric_limits<float>::max();

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_max_double) {

    double test_value = numeric_limits<double>::max() * -1;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_max_float) {

    float test_value = numeric_limits<float>::max() * -1;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_pos_min_double) {

    double test_value = numeric_limits<double>::min();

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_pos_min_float) {

    float test_value = numeric_limits<float>::min();

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_min_double) {

    double test_value = numeric_limits<double>::min() * -1;

    mps MPS(52, 11, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}

TEST(get_value_tests, get_neg_min_float) {

    float test_value = numeric_limits<float>::min() * -1;

    mps MPS(23, 8, test_value);

    auto binary = MPS.getBitArray();

    double get_value = MPS.getValue();

    EXPECT_EQ(test_value, get_value);
    EXPECT_EQ(test_value, MPS.my_getValue());
}