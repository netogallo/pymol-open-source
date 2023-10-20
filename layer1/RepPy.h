#ifndef _H_RepPy
#define _H_RepPy

struct PyMOLGlobals;
struct Rep;
struct CoordSet;

Rep *RepPyNew(CoordSet * cset, int state);

#endif