#ifndef _H_RepPy
#define _H_RepPy

#include <memory>

struct PyMOLGlobals;
struct Rep;
struct CoordSet;

class PyRenderContextBase {

    public:
    virtual ~PyRenderContextBase();

    /*
    An instance of this object will be exposed to python. There is no
    way to prevent python code from obtaining additional references
    to this object.

    However, methods of this object could potentially rely on references
    that are no longer valid once rendering is completed. To avoid
    segmentation faults, the invalidate method will be called before
    exiting the render function which should make instances of this
    object raise exceptions (on python) if any method of this
    object is called.
    */
    virtual void invalidate();
};

std::shared_ptr<PyRenderContextBase> new_render_context(CoordSet* cset);

class PyMolRep {

    public:
    virtual void render(std::shared_ptr<PyRenderContextBase>) {}
    void register_bad();
};

Rep *RepPyNew(CoordSet * cset, int state);

#endif