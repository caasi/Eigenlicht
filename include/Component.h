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

class Component : virtual public IComponent
{
public:
    Component():mesh(NULL) {}

    virtual IMesh *getMesh() const { return mesh; }

protected:
    /**
     * Let Manager handles SceneManager, and maps between SceneNodes and
     * Components, because we can get SceneNode and collision point
     * from ray
     **/
    SMesh *mesh;
};

}
}

#endif
