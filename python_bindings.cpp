//
// Created by Jakob on 30.03.24.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>

#include "./mps/mps.h"

namespace py = pybind11;


PYBIND11_MODULE(mps_lib, mps_handle) {
    mps_handle.doc() = "Framework for mixed precision floating point simulation.";

    py::class_<mps>(mps_handle, "mps")
            .def(py::init<unsigned long, unsigned long, double>())
            .def(py::init<unsigned long, unsigned long>())
            .def(py::init<>())

            .def("copy", [](mps &self){
                const mps& out = self;
                return out;
            })
            .def(py::self + py::self)
            .def(py::self - py::self)
            .def(py::self * py::self)
            .def(py::self / py::self)
            .def(py::self < py::self)
            .def(py::self <= py::self)
            .def(py::self > py::self)
            .def(py::self >= py::self)
            .def(py::self == py::self)
            .def(py::self != py::self)

            .def_property_readonly("mantissa_length", &mps::getMantisseLength)
            .def_property_readonly("exponent_length", &mps::getExponentLength)
            .def_property_readonly("bit_array_length", &mps::getBitArrayLength)
            .def_property_readonly("bit_array", [](mps &self){
                py::array out = py::cast(self.getBitArray());
                return out;
            })

            .def("is_zero", &mps::isZero)
            .def("is_infinity", &mps::isInf)
            .def("is_positive", &mps::isPositive)
            .def("is_NaN", &mps::isNaN)
            .def("set_infinity", &mps::setInf)
            .def("set_zero", &mps::setZero)
            .def("set_NaN", &mps::setNaN)
            .def("set_sign", &mps::setSign)
            .def("set_mantissa", &mps::setMantissa)
            .def("set_exponent", &mps::setExponent)

            .def("cast", &mps::cast)
            .def("check_precision", &mps::checkPrecision)

            .def("get_value", &mps::getValue)
            .def("print", &mps::print)
            .def("to_string", &mps::toString)
            ;
}
