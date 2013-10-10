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
    Component(path texture = ""):mesh(NULL),sceneNode(NULL),texturePath(texture) {}

    virtual IMesh *getMesh() { return mesh; }

    virtual path getTexturePath() { return texturePath; }

    virtual void setSceneNode(ISceneNode *node) { (sceneNode = node)->grab(); }

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
};

}
}

#endif
