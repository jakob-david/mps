//
// Created by Jakob on 30.03.24.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>

#include "mps_lib/mps.h"

namespace py = pybind11;
PYBIND11_MODULE(mps_library, handle) {
    handle.doc() = "Framework for mixed precision floating point simulation.";

    py::class_<mps>(handle, "mps")
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

            .def("isZero", &mps::isZero)
            .def("isInfinity", &mps::isInfinity)
            .def("isPositive", &mps::isPositive)
            .def("isNaN", &mps::isNaN)
            .def("setInf", &mps::setInf)
            .def("setZero", &mps::setZero)
            .def("setNaN", &mps::setNaN)
            .def("setSign", &mps::setSign)
            .def("setMantissa", &mps::setMantissa)
            .def("setExponent", &mps::setExponent)

            .def("cast", &mps::cast)
            .def("check_precision", &mps::check_precision)

            .def("getValue", &mps::getValue)
            .def("print", &mps::print)
            .def("to_string", &mps::to_string)
            ;
}