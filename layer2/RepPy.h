#ifndef _H_RepPy
#define _H_RepPy

#include <memory>
#include <pybind11/stl.h>

struct PyMOLGlobals;
struct Rep;
struct CoordSet;

class PyRenderContext {

    public:
    virtual std::vector<std::vector<float>> current_scene_coords() {
        return {{}};
    }
};

class PyMolRep {

    public:
    // virtual void render(std::shared_ptr<PyRenderContext>) {}
    virtual void render(PyRenderContext*) {}
    void register_bad();
};

Rep *RepPyNew(CoordSet * cset, int state);

#endif