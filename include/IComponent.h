#ifndef __EIGENLICHT_INTERFACE_COMPONENT_H__
#define __EIGENLICHT_INTERFACE_COMPONENT_H__

#include <IReferenceCounted.h>

namespace irr
{
namespace scene
{

class IMesh;

}
}

using namespace irr;
using namespace scene;

namespace eigen
{
namespace interactable
{

class ComponentContainer;

class IComponent : public IReferenceCounted
{
    friend class ComponentContainer;

public:
    IComponent():IReferenceCounted(),parent(NULL) {}

    virtual IMesh *getMesh() const { return NULL; }
protected:
    ComponentContainer *parent;
};

}
}

#endif
