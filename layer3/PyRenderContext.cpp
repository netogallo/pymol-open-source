#include "PyRenderContext.h"

#include "CoordSet.h"
#include "ObjectMolecule.h"
#include "RepPy.h"

PyRenderContext::PyRenderContext() : cs(nullptr) {}

PyRenderContext::PyRenderContext(CoordSet* cs) : cs(cs) { }

PyRenderContext::~PyRenderContext() {}

std::vector<std::vector<float>> PyRenderContext::current_scene_coords() {
    ObjectMolecule* obj = cs->Obj;
    pymol::vla<AtomInfoType>& atomInfo = obj->AtomInfo;
    std::vector<std::vector<float>> result;

    for(int i = 0; i < atomInfo.size(); i++) {
    float* coords = cs->coordPtr(cs->atmToIdx(i));
    result.push_back({ coords[0], coords[1], coords[2] });
    }

    return result;
}

void PyRenderContext::invalidate() {

}

std::shared_ptr<PyRenderContextBase> new_render_context(CoordSet* cset) {
    return std::make_shared<PyRenderContext>(cset);
}