#include "gtest/gtest.h"

#include "mps.h"
#include "mps_side.h"


TEST(constructor_tests, constructor_sets_values_coorectly){

    mps* MPS = new mps(5, 6, 3.14);

    int mantisse_actual = MPS->getMantisseLength();
    int exponent_actual = MPS->getExponentLength();
    int length_actual = MPS->getBitArrayLength();

    EXPECT_EQ(5, mantisse_actual);
    EXPECT_EQ(6, exponent_actual);
    EXPECT_EQ(12, length_actual);
}

TEST(constructor_tests, constructor_initializes_bit_array_correctly){

    mps* MPS = new mps(20, 12, 3.14);

    int size = MPS->getBitArrayLength();

    EXPECT_EQ(33, size);
}

TEST(constructor_tests, sidecalculation_initialisation) {

    auto MPS = new mps_side(20, 12, 3.14159265359);

    auto value_actual = MPS->getSideCalculationValue();

    EXPECT_EQ(3.14159265359, value_actual);

}

TEST(converter_tests, test_intToBit) {

    auto MPS = new mps_side(20, 12, 3.14159265359);

    auto binary = MPS->getIntegerPart(132);

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    EXPECT_EQ("10000100", str);

}

TEST(converter_tests, test_getDecimalPart) {

    auto MPS = new mps_side(20, 12, 3.14159265359);

    auto binary = MPS->getDecimalPart(132.64, 15);

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    EXPECT_EQ("101000111101011", str);

}

TEST(converter_tests, test_getDecimalPart2) {

    auto MPS = new mps_side(20, 12, 3.14159265359);

    auto binary = MPS->getDecimalPart(0.3452, 20);

    string str;
    for(bool bit : binary){
        if(bit){
            str.append("1");
        } else {
            str.append("0");
        }
    }

    EXPECT_EQ("01011000010111110000", str);

}

TEST(converter_tests, test_positive_double) {

    double test_value = 342.45636;

    auto MPS = new mps_side(52, 11, test_value);

    auto binary = MPS->getFloatingPointRepresentation(test_value, 11, 52);

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