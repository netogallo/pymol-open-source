#ifndef _H_RepPy
#define _H_RepPy

#include <pybind11/stl.h>

struct PyMOLGlobals;
struct Rep;
struct CoordSet;

class PyRenderContext {

    public:
    std::vector<std::vector<float>> current_scene_coords() {
        return {{1.1f, 2.2f, 3.3f, 4.4f}};
    }
};

class PyMolRepBase {

    public:
    virtual void render(PyRenderContext*) {}
    void register_bad();
};

Rep *RepPyNew(CoordSet * cset, int state);

#endif