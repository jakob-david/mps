import unittest

import mps_library
from mps_library import *
import numpy as np

#print(dir(mps_lib))

class TestStringMethods(unittest.TestCase):

    value_1 = 3
    value_2 = 4

    fpn_1 = mps(52, 11, value_1)
    fpn_2 = mps(52, 11, value_2)

    ###################################
    # general
    ###################################
    def test_constructor(self):
        value = 3.14
        mantissa_length = 52
        exponent_length = 11
        fpn = mps(mantissa_length, exponent_length, value)
        message = "Constructor not working propperly."
        self.assertTrue(fpn.getValue() == value, message)
        self.assertTrue(fpn.mantissa_length == mantissa_length, message)
        self.assertTrue(fpn.exponent_length == exponent_length, message)
        self.assertTrue(fpn.bit_array_length == mantissa_length + exponent_length + 1, message)

    def test_copy_and_cast(self):
        value = 3.14
        mantissa_length = 52
        exponent_length = 11
        fpn = mps(mantissa_length, exponent_length, value)
        casted = fpn.copy()
        casted.cast(10, 5)
        message = "Cast or copy not working propperly."
        self.assertFalse(casted.exponent_length == fpn.exponent_length, message)
        casted.cast(mantissa_length, exponent_length)
        self.assertTrue(fpn.check_precision(casted, 2))

    def test_bit_array(self):
        mantissa_length = 4
        exponent_length = 2
        fpn = mps(mantissa_length, exponent_length)
        te = np.array([0, 1, 1, 1, 0, 0, 0])
        testValue = (te == fpn.bit_array).all()
        message = "Bit array not returned correctly."
        self.assertTrue(testValue, message)
    ###################################

    ###################################
    # getter and setters
    ###################################
    def test_zero(self):
        fpn = mps(52,11,3)
        fpn.setZero(False)
        testValue = fpn.isZero()
        message = "Set zero not working."
        self.assertTrue(testValue, message)

    def test_NaN(self):
        fpn = mps(52,11,3)
        fpn.setNaN(False)
        testValue = fpn.isNaN()
        message = "Set NaN not working."
        self.assertTrue(testValue, message)

    def test_infinity(self):
        fpn = mps(52,11,3)
        fpn.setInf(False)
        testValue = fpn.isInfinity()
        message = "Set infinity not working."
        self.assertTrue(testValue, message)

    def test_NaN(self):
        fpn = mps(52,11,3)
        fpn.setSign(True)
        testValue = fpn.isPositive()
        message = "Set sign not working."
        self.assertFalse(testValue, message)

    def test_set_exponent(self):
        mantissa_length = 4
        exponent_length = 2
        fpn = mps(mantissa_length, exponent_length)
        fpn.setExponent([1, 0])
        fpn.setMantissa([1, 1, 0, 1])
        fpn.setSign(False)

        te = np.array([0, 1, 0, 1, 1, 0, 1])
        testValue = (te == fpn.bit_array).all()
        message = "Setting exponent or mantissa not working correctly."
        self.assertTrue(testValue, message)
    ###################################

    ###################################
    # oparators: +, -, *, /
    ###################################
    def test_plus(self):
        fpn_3 = self.fpn_1 + self.fpn_2
        testValue = ((self.value_1  + self.value_2) == fpn_3.getValue())
        message = "Operator + not working."
        self.assertTrue(testValue, message)

    def test_minus(self):
        fpn_3 = self.fpn_1 - self.fpn_2
        testValue = ((self.value_1  - self.value_2) == fpn_3.getValue())
        message = "Operator - not working."
        self.assertTrue(testValue, message)

    def test_multiply(self):
        fpn_3 = self.fpn_1 * self.fpn_2
        testValue = ((self.value_1  * self.value_2) == fpn_3.getValue())
        message = "Operator * not working."
        self.assertTrue(testValue, message)

    def test_divide(self):
        fpn_3 = self.fpn_1 / self.fpn_2
        testValue = ((self.value_1  / self.value_2) == fpn_3.getValue())
        message = "Operator / not working."
        self.assertTrue(testValue, message)
    ###################################

    ###################################
    # oparators: ==, !=, <, <=, >, >=
    ###################################
    def test_equal(self):
        testValue = self.fpn_2 == self.fpn_1
        message = "Operator == not working."
        self.assertFalse(testValue, message)

    def test_not_equal(self):
        testValue = self.fpn_2 != self.fpn_1
        message = "Operator != not working."
        self.assertTrue(testValue, message)

    def test_smaller(self):
        testValue = self.fpn_1 < self.fpn_2
        message = "Operator < not working."
        self.assertTrue(testValue, message)

    def test_smaller_equal(self):
        testValue = self.fpn_1 <= self.fpn_2
        message = "Operator <= not working."
        self.assertTrue(testValue, message)

    def test_larger(self):
        testValue = self.fpn_2 > self.fpn_1
        message = "Operator > not working."
        self.assertTrue(testValue, message)

    def test_larger_equal(self):
        testValue = self.fpn_2 >= self.fpn_1
        message = "Operator >= not working."
        self.assertTrue(testValue, message)
    ###################################


if __name__ == '__main__':
    unittest.main()
