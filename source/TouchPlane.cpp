#include "../include/TouchPlane.h"

using namespace eigen::interactable;

TouchPlane::TouchPlane
(
    core::dimension2df size,
    f32 dpi,
    path texture,
    f32 d
):
    Component(),
    size(size),
    dpi(dpi),
    texturePath(texture),
    distance(d),
    display(NULL),
    near(NULL)
{
    //addEventListener("intersect", &TouchPlane::onNear);
}

TouchPlane::~TouchPlane()
{
    //removeEventListener("intersect", &TouchPlane::onNear);

    if (near) near->drop();
    if (display) display->drop();
}

void TouchPlane::addTo(GUIManager *mgr)
{
    display = new Plane(size, dpi, texturePath);
    display->addTo(mgr);

    near = new Plane(size, dpi, texturePath);
    near->addTo(mgr);

    Component::addTo(mgr);
}

ISceneNode *TouchPlane::createSceneNode(ISceneManager *smgr)
{
    ISceneNode *displayNode = display->getSceneNode();

    ISceneNode *nearNode = near->getSceneNode();
    nearNode->setPosition(core::vector3df(0.0, 0.0, -distance));

    sceneNode = smgr->addEmptySceneNode(NULL, GUIManager::ID_COMPONENT);
    sceneNode->addChild(displayNode);
    sceneNode->addChild(nearNode);

    return sceneNode;
}
