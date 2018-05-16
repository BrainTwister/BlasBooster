#include <pybind11/pybind11.h>
#include "BlasBooster/Core/DenseMatrix.h"

namespace py = pybind11;
using namespace BlasBooster;

PYBIND11_MODULE(blasbooster, m)
{
    m.doc() = "pybind11 blasbooster plugin";

    py::class_<Matrix<Dense, double>>(m, "Matrix")
        .def(py::init<int, int>());
}
