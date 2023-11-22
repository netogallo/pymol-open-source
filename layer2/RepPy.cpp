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
}

struct RepPy : Rep {
  using Rep::Rep;
  ~RepPy() override;

  cRep_t type() const override { return cRepPy; }
  void render(RenderInfo* info) override;
};

RepPy::~RepPy() { }

void RepPy::render(RenderInfo* info) {
  PyGILState_STATE gilState = PyGILState_Ensure();
  std::vector<std::weak_ptr<PyMolRep>> coords_reps = getRepsForCoords(cs);
  std::shared_ptr<PyRenderContextBase> context = new_render_context(cs);

  for(auto rep_ptr : coords_reps) {

    if (auto rep = rep_ptr.lock()){
      rep->render(context);
    }
  }

  PyGILState_Release(gilState);
  context->invalidate();
}

Rep* RepPyNew(CoordSet * cset, int state) {

  auto repPy = new RepPy(cset, state);
  return (Rep*) repPy;
}

PyRenderContextBase::~PyRenderContextBase(){}
void PyRenderContextBase::invalidate(){}