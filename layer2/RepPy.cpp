#include "RepPy.h"

#include <iostream>
#include <Python.h>

#include "Base.h"
#include "CoordSet.h"
#include "ObjectMolecule.h"
#include "Rep.h"
#include "vla.h"

std::vector<PyMolRep*> py_reps_bad;
void PyMolRep::register_bad(){
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

class PyRenderContextImplementation : public PyRenderContext {

  public:
  PyRenderContextImplementation(CoordSet* cs) : cs(cs) {

  }

  std::vector<std::vector<float>> current_scene_coords() override {
    ObjectMolecule* obj = cs->Obj;
    pymol::vla<AtomInfoType>& atomInfo = obj->AtomInfo;
    std::vector<std::vector<float>> result;

    for(int i = 0; i < atomInfo.size(); i++) {
      float* coords = cs->coordPtr(cs->atmToIdx(i));
      result.push_back({ coords[0], coords[1], coords[2] });
    }

    return result;
  }

  private:
  CoordSet* cs;
};

void RepPy::render(RenderInfo* info) {
  //std::cout << "pyrep render" << std::endl;
  PyGILState_STATE gilState = PyGILState_Ensure();
  //std::shared_ptr<PyRenderContextImplementation> context = std::make_shared<PyRenderContextImplementation>(cs);
  PyRenderContextImplementation context(cs);

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