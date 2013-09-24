#ifndef __EIGEN_COMPONENT_H__
#define __EIGEN_COMPONENT_H__

#include <SMesh.h>

#include "IComponent.h"

using namespace irr;
using namespace scene;

namespace eigen
{
namespace interactable
{

class Component : public IComponent
{
public:
    Component();

    ~Component();

    IMesh *getMesh() const { return planeMesh; }

private:
    /**
     * Let Manager handles SceneManager, and maps between SceneNodes and
     * Components, because we can get SceneNode and collision point
     * from ray
     **/
    SMesh *planeMesh;
};

}
}

#endif
