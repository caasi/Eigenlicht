#ifndef __EIGENLICHT_INTERFACE_COMPONENT_H__
#define __EIGENLICHT_INTERFACE_COMPONENT_H__

#include <IReferenceCounted.h>
#include "EventDispatcher.h"

namespace irr
{
namespace scene
{

class IMesh;

}
}

using namespace irr;
using namespace scene;

using namespace eigen::event;

namespace eigen
{
namespace interactable
{

class ComponentContainer;

class IComponent : public IReferenceCounted, public EventDispatcher
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
