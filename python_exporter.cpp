//
// Created by Jakob on 30.03.24.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>

#include "mps_lib/mps.h"
#include "mpe_lib/mpe.h"

namespace py = pybind11;



PYBIND11_MODULE(mpe_library, mpe_handle) {
    mpe_handle.doc() = "Class to evaluate the multiprecision simulator";

    py::class_<mpe>(mpe_handle, "mpe")
            .def(py::init<>())

            // setters
            //-------------------------------
            .def("setRandomLimits", &mpe::setRandomLimits)
            .def("setUpperRandomLimit", &mpe::setUpperRandomLimit)
            .def("setLowerRandomLimit", &mpe::setLowerRandomLimit)
            .def("setSparsityRate", &mpe::setSparsityRate)
            .def("setSparsityPointsAmount", &mpe::setSparsityPointsAmount)

            .def("setMatrixSizeRange", &mpe::setMatrixSizeRange)

            .def("setDimension", &mpe::setDimension)
            .def("setIterations", &mpe::setIterations)
            .def("setMaxIter", &mpe::setMaxIter)

            .def("setLowerPrecision", &mpe::setLowerPrecision)
            .def("setWorkingPrecision", &mpe::setWorkingPrecision)
            .def("setUpperPrecision", &mpe::setUpperPrecision)
            .def("setLowerPrecisionExponent", &mpe::setLowerPrecisionExponent)
            .def("setWorkingPrecisionExponent", &mpe::setWorkingPrecisionExponent)
            .def("setUpperPrecisionExponent", &mpe::setUpperPrecisionExponent)

            .def("setLowerPrecisionMantissaRange", &mpe::setLowerPrecisionMantissaRange)
            .def("setWorkingPrecisionMantissaRange", &mpe::setWorkingPrecisionMantissaRange)
            .def("setUpperPrecisionMantissaRange", &mpe::setUpperPrecisionMantissaRange)

            .def("setWorkingPrecisionExponentRange", &mpe::setWorkingPrecisionExponentRange)

            .def("setExpectedError", &mpe::setExpectedError)
            .def("setExpectedPrecision", &mpe::setExpectedPrecision)

            .def("setMatrixSizes", &mpe::setMatrixSizes)
            .def("setMantissaStepSize", &mpe::setMantissaStepSize)
            //-------------------------------


            // getters
            //-------------------------------
            .def_property_readonly("iterations", &mpe::getIterations)

            .def("getIterationAxis", [](mpe &self){
                py::array out = py::cast(self.getIterationAxis());
                return out;
            })

            .def("getLowerPrecisionMantissaAxis", [](mpe &self){
                py::array out = py::cast(self.getLowerPrecisionMantissaAxis());
                return out;
            })
            .def("getWorkingPrecisionMantissaAxis", [](mpe &self){
                py::array out = py::cast(self.getWorkingPrecisionMantissaAxis());
                return out;
            })
            .def("getUpperPrecisionMantissaAxis", [](mpe &self){
                py::array out = py::cast(self.getUpperPrecisionMantissaAxis());
                return out;
            })

            .def("getWorkingPrecisionExponentAxis", [](mpe &self){
                py::array out = py::cast(self.getWorkingPrecisionExponentAxis());
                return out;
            })

            .def("getSparsityAxis", [](mpe &self){
                py::array out = py::cast(self.getSparsityAxis());
                return out;
            })

            .def("getMatrixSizesAxis", [](mpe &self){
                py::array out = py::cast(self.getMatrixSizesAxis());
                return out;
            })
            //-------------------------------


            // operator evaluation
            //-------------------------------
            .def("evaluateAddition", &mpe::evaluateAddition)
            .def("evaluateSubtraction", &mpe::evaluateSubtraction)
            .def("evaluateMultiplication", &mpe::evaluateMultiplication)
            .def("evaluateDivision", &mpe::evaluateDivision)

            .def("evaluateAdditionExponent", &mpe::evaluateAdditionExponent)
            .def("evaluateSubtractionExponent", &mpe::evaluateSubtractionExponent)
            .def("evaluateMultiplicationExponent", &mpe::evaluateMultiplicationExponent)
            .def("evaluateDivisionExponent", &mpe::evaluateDivisionExponent)
            //-------------------------------


            // operator evaluation system
            //-------------------------------
            .def("evaluateAdditionDouble", &mpe::evaluateAdditionDouble)
            .def("evaluateSubtractionDouble", &mpe::evaluateSubtractionDouble)
            .def("evaluateMultiplicationDouble", &mpe::evaluateMultiplicationDouble)
            .def("evaluateDivisionDouble", &mpe::evaluateDivisionDouble)
            //-------------------------------


            // evaluate sparsity
            //-------------------------------
            .def("evaluateSparsity", &mpe::evaluateSparsity)
            .def("evaluateSparsity_2D", &mpe::evaluateSparsity_2D)
            //-------------------------------


            // compare
            //-------------------------------
            .def("compareMVM", &mpe::compareMVM)
            .def("compareMMM", &mpe::compareMMM)
            .def("comparePLU", &mpe::comparePLU)
            .def("compareIR", &mpe::compareIR)
            .def("compareMultipleIR", &mpe::compareMultipleIR)
            //-------------------------------


            // iterative refinement evaluation
            //-------------------------------
            .def("evaluateArea", [](mpe &self, bool output = false){
                py::array out = py::cast(self.evaluateArea(output));
                return out;
            })

            .def("evaluateArea_2D", [](mpe &self, bool output = false){
                py::array out = py::cast(self.evaluateArea_2D(output));
                return out;
            })

            .def("evaluateConvergence_2D", [](mpe &self, bool output = false){
                py::array out = py::cast(self.evaluateConvergence_2D(output));
                return out;
            })
            //-------------------------------

            ;
}














PYBIND11_MODULE(mps_library, mps_handle) {
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

            .def("isZero", &mps::isZero)
            .def("isInf", &mps::isInf)
            .def("isPositive", &mps::isPositive)
            .def("isNaN", &mps::isNaN)
            .def("setInf", &mps::setInf)
            .def("setZero", &mps::setZero)
            .def("setNaN", &mps::setNaN)
            .def("setSign", &mps::setSign)
            .def("setMantissa", &mps::setMantissa)
            .def("setExponent", &mps::setExponent)

            .def("cast", &mps::cast)
            .def("checkPrecision", &mps::checkPrecision)

            .def("getValue", &mps::getValue)
            .def("print", &mps::print)
            .def("toString", &mps::toString)
            ;
}
