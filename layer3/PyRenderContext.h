#ifndef PY_RENDER_CONTEXT_H
#define PY_RENDER_CONTEXT_H

#include <pybind11/stl.h>

#include "RepPy.h"

class PyRenderContext : public PyRenderContextBase {

    public:
    PyRenderContext();
    PyRenderContext(CoordSet* cs);

    ~PyRenderContext() override;

    std::vector<std::vector<float>> current_scene_coords();

    void invalidate() override;

    private:
    CoordSet* cs;
};

#endif