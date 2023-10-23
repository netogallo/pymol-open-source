#include <pybind11/pybind11.h>
#include "RepPy.h"

namespace py = pybind11;

PYBIND11_MODULE(ext, m) {
    py::class_<PyMolRep>(m, "PyMolRep")
        .def(py::init<>())
        .def("render", &PyMolRep::render);
}