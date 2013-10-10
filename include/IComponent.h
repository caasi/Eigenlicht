#ifndef __EIGENLICHT_INTERFACE_COMPONENT_H__
#define __EIGENLICHT_INTERFACE_COMPONENT_H__

#include <IReferenceCounted.h>
#include <irrString.h>
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
using namespace io;

using namespace eigen::event;

namespace eigen
{

class GUIManager;

namespace interactable
{

class IComponent : public IReferenceCounted, public EventDispatcher
{
public:
    IComponent():IReferenceCounted() {}

    virtual ~IComponent() {}

    virtual IMesh *getMesh() { return NULL; }

    virtual path getTexturePath() { return ""; }

    virtual void setSceneNode(ISceneNode*) {}

    virtual void setGUIManager(GUIManager*) {}

    virtual ISceneNode *getSceneNode() { return NULL; }
};

}
}

#endif
