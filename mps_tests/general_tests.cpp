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

    bool error = false;


    mps* MPS = new mps(20, 12, 3.14);

    int total_length = MPS->getBitArrayLength();

    bool* array = MPS->getBitArray();

    for(int i = 0; i < total_length; i++){
        if(array[i] != 0){
            error = true;
            break;
        }
    }

    EXPECT_EQ(33, total_length);
    EXPECT_EQ(error, false);
}

TEST(constructor_tests, sidecalculation_initialisation) {

    auto MPS = new mps_side(20, 12, 3.14159265359);

    auto value_actual = MPS->getSideCalculationValue();

    EXPECT_EQ(3.14159265359, value_actual);

}