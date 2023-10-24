#include <pybind11/pybind11.h>
#include "RepPy.h"

namespace py = pybind11;

class PyMolRep : public PyMolRepBase {
    using PyMolRepBase::PyMolRepBase;

    public:
    void render(PyRenderContext* ctx) override {
        /*
        PYBIND11_OVERRIDE(
            void,
            PymolRepBase,
            render
        );
        */
    }
};

PYBIND11_MODULE(ext, m) {
    py::class_<PyRenderContext>(m, "PyRenderContext")
        .def(py::init<>())
        .def("current_scene_coords", &PyRenderContext::current_scene_coords);

    py::class_<PyMolRepBase, PyMolRep>(m, "PyMolRep")
        .def(py::init<>())
        .def("render", &PyMolRepBase::render)
        .def("register_bad", &PyMolRepBase::register_bad);
}