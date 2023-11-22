#ifndef PY_RENDER_CONTEXT_H
#define PY_RENDER_CONTEXT_H

#include <pybind11/stl.h>

#include "RepPy.h"

class PyAtomInfo {

    public:
    PyAtomInfo(int pdbId);

    int pdbId();

    private:
    int vPdbId;
};

class PyRenderContext : public PyRenderContextBase {

    public:
    PyRenderContext();
    PyRenderContext(CoordSet* cs);

    ~PyRenderContext() override;

    std::vector<std::shared_ptr<PyAtomInfo>> atoms();

    std::vector<std::vector<float>> current_scene_coords();

    void invalidate() override;

    private:
    CoordSet* cs;
};

#endif