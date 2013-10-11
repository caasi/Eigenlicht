#ifndef __EIGENLICHT_COMPONENT_H__
#define __EIGENLICHT_COMPONENT_H__

#include <SMesh.h>
#include <ISceneNode.h>

#include "IComponent.h"
#include "GUIManager.h"

using namespace irr;
using namespace scene;

namespace eigen
{
namespace interactable
{

class Component : public IComponent
{
public:
    Component():sceneNode(NULL),mgr(NULL) {}

    virtual ~Component()
    {
        if (sceneNode) sceneNode->drop();
        if (mgr) mgr->drop();
    }

    virtual void dispatchEvent(Event *event)
    {
        if (mgr)
            mgr->bubbleUp(this, event);
        else
            EventDispatcher::dispatchEvent(event);
    }

    virtual IMesh *getMesh() { return mesh; }

    virtual ISceneNode *getSceneNode() { return sceneNode; }

    virtual void setGUIManager(GUIManager *manager)
    {
        if (mgr) mgr->drop();
        (mgr = manager)->grab();
    }

protected:
    SMesh *mesh;
    ISceneNode *sceneNode;
    GUIManager *mgr;
};

}
}

#endif
