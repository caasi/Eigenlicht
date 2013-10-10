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
    Component(path texture = ""):mesh(NULL),sceneNode(NULL),mgr(NULL),texturePath(texture) {}

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

    virtual path getTexturePath() { return texturePath; }

    virtual void setSceneNode(ISceneNode *node)
    {
        if (sceneNode) sceneNode->drop();
        (sceneNode = node)->grab();
    }

    virtual void setGUIManager(GUIManager *manager)
    {
        if (mgr) mgr->drop();
        (mgr = manager)->grab();
    }

    virtual ISceneNode *getSceneNode() { return sceneNode; }

protected:
    /**
     * Let Manager handles SceneManager, and maps between SceneNodes and
     * Components, because we can get SceneNode and collision point
     * from ray
     **/
    SMesh *mesh;
    path texturePath;
    ISceneNode *sceneNode;
    GUIManager *mgr;
};

}
}

#endif
