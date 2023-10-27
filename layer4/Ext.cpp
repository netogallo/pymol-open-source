#include <pybind11/pybind11.h>

#include "PyRenderContext.h"

namespace py = pybind11;

class PyMolRepTrampoline : public PyMolRep {
    using PyMolRep::PyMolRep;

    public:
    // void render(std::shared_ptr<PyRenderContext> ctx) override {
    void render(std::shared_ptr<PyRenderContextBase> ctx) override {

        try{
            PYBIND11_OVERRIDE_PURE(
                void,
                PyMolRep,
                render,
                ctx
            );
        } catch(py::error_already_set &e) {
            /*
            Todo: decide what to do with the C++ exception. If we don't
            catch it, pymol crashes.

            Possibly also disable the renderer
            */
            // printf("python is angry");
        }
    }
};

PYBIND11_MODULE(ext, m) {
    py::class_<PyRenderContext, std::shared_ptr<PyRenderContext>>(m, "PyRenderContext")
        .def("current_scene_coords", &PyRenderContext::current_scene_coords);

    py::class_<PyMolRep, PyMolRepTrampoline>(m, "PyMolRep")
        .def(py::init<>())
        .def("render", &PyMolRep::render)
        .def("register_bad", &PyMolRep::register_bad);
}