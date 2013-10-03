#ifndef __EIGENLICHT_COMPONENT_H__
#define __EIGENLICHT_COMPONENT_H__

#include <SMesh.h>
#include <ISceneNode.h>

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
    Component():mesh(NULL),sceneNode(NULL) {}

    virtual IMesh *getMesh() { return mesh; }

    virtual void setSceneNode(ISceneNode *node) { (sceneNode = node)->grab(); }

    virtual ISceneNode *getSceneNode() { return sceneNode; }

protected:
    /**
     * Let Manager handles SceneManager, and maps between SceneNodes and
     * Components, because we can get SceneNode and collision point
     * from ray
     **/
    SMesh *mesh;
    ISceneNode *sceneNode;
};

}
}

#endif
