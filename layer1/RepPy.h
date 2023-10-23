#ifndef _H_RepPy
#define _H_RepPy

struct PyMOLGlobals;
struct Rep;
struct CoordSet;

class PyMolRep {

    public:
    virtual void render() {}
};

Rep *RepPyNew(CoordSet * cset, int state);

#endif