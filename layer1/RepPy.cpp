#include "RepPy.h"

#include <iostream>

#include "Base.h"
#include "Rep.h"

struct RepPy : Rep {
  using Rep::Rep;
  ~RepPy() override;

  cRep_t type() const override { return cRepPy; }
  void render(RenderInfo* info) override;
};

RepPy::~RepPy() { }

void RepPy::render(RenderInfo* info) {
  //std::cout << "pyrep render" << std::endl;
}

Rep* RepPyNew(CoordSet * cset, int state) {

  auto repPy = new RepPy(cset, state);
  return (Rep*) repPy;
}