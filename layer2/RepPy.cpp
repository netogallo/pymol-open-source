#include "RepPy.h"

#include <iostream>
#include <Python.h>

#include "Base.h"
#include "Rep.h"

std::vector<PyMolRepBase*> py_reps_bad;
void PyMolRepBase::register_bad(){
  py_reps_bad.push_back(this);
  printf("regis");
}

struct RepPy : Rep {
  using Rep::Rep;
  ~RepPy() override;

  cRep_t type() const override { return cRepPy; }
  void render(RenderInfo* info) override;
};

RepPy::~RepPy() { }

void RepPy::render(RenderInfo* info) {
  //std::cout << "pyrep render" << std::endl;
  PyGILState_STATE gilState = PyGILState_Ensure();
  PyRenderContext context;

  for(auto rep : py_reps_bad) {
    rep->render(&context);
  }

  //PyRun_SimpleString("import glfw\nfrom OpenGL.GL import *\nfrom OpenGL.GLUT import *\nprint('Hello from Python!')\nglColor3f(1.0, 0.0, 0.0)\nglBegin(GL_TRIANGLES)\nglVertex2f(-0.5, -5.5)\nglVertex2f( 0.5, -0.5)\nglVertex2f( 0.0,  0.5)\nglEnd()");
  PyGILState_Release(gilState);
}

Rep* RepPyNew(CoordSet * cset, int state) {

  auto repPy = new RepPy(cset, state);
  return (Rep*) repPy;
}