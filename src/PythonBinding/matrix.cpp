#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/DynamicMatrix.h"
#include "BlasBooster/Utilities/Version.h"

PYBIND11_MODULE(blasbooster, m)
{
    namespace py = pybind11;
    namespace bb = BlasBooster;

    m.doc() = "BlasBooster";
    m.attr("__version__") = std::string(PROJECT_VERSION) + " revision " + std::string(GIT_REVISION);

    py::class_<bb::DynamicMatrix>(m, "Matrix", py::buffer_protocol())
		.def(py::init([](py::buffer b)
		{
			py::buffer_info info = b.request();
			return new bb::DynamicMatrix;
		}));
//		.def_buffer([](bb::DynamicMatrix &m) -> py::buffer_info
//		{
//			return py::buffer_info();
//		});
}
