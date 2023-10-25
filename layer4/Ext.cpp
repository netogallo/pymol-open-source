#include <pybind11/pybind11.h>
#include "RepPy.h"

namespace py = pybind11;

class PyMolRepTrampoline : public PyMolRep {
    using PyMolRep::PyMolRep;

    public:
    // void render(std::shared_ptr<PyRenderContext> ctx) override {
    void render(PyRenderContext* ctx) override {
        PYBIND11_OVERRIDE_PURE(
            void,
            PyMolRep,
            render,
            ctx
        );
    }
};

PYBIND11_MODULE(ext, m) {
    py::class_<PyRenderContext>(m, "PyRenderContext")
        .def(py::init<>())
        .def("current_scene_coords", &PyRenderContext::current_scene_coords);

    py::class_<PyMolRep, PyMolRepTrampoline>(m, "PyMolRep")
        .def(py::init<>())
        .def("render", &PyMolRep::render)
        .def("register_bad", &PyMolRep::register_bad);
}