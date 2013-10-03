#ifndef __EIGENLICHT_INTERFACE_COMPONENT_H__
#define __EIGENLICHT_INTERFACE_COMPONENT_H__

#include <IReferenceCounted.h>
#include "EventDispatcher.h"

namespace irr
{
namespace scene
{

class IMesh;
class ISceneNode;

}
}

using namespace irr;
using namespace scene;

using namespace eigen::event;

namespace eigen
{
namespace interactable
{

class IComponent : public IReferenceCounted, public EventDispatcher
{
public:
    IComponent():IReferenceCounted() {}

    virtual IMesh *getMesh() { return NULL; }

    virtual void setSceneNode(ISceneNode*) {}

    virtual ISceneNode *getSceneNode() { return NULL; }
};

}
}

#endif
