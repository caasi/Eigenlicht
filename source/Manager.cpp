#include <IMesh.h>
#include <ITriangleSelector.h>

#include "../include/Manager.h"
#include "../include/Event.h"

using namespace eigen;
using namespace event;

Manager::Manager(ISceneManager *mgr):
    ComponentContainer(),
    smgr(mgr)
{
    smgr->grab();
}

Manager::~Manager()
{
    if (testNode) testNode->drop();
    if (smgr) smgr->drop();
}

void Manager::add(IComponent *component)
{
    ComponentContainer::add(component);

    IMesh *mesh = component->getMesh();

    testNode = smgr->addMeshSceneNode(mesh, 0, Manager::ID_COMPONENT);

    ITriangleSelector *selector = smgr->createTriangleSelector(mesh, testNode);
    testNode->setTriangleSelector(selector);
    selector->drop();
}

bool Manager::remove(IComponent *component)
{
    return ComponentContainer::remove(component);
}

void Manager::update()
{
    dispatchEvent(new Event("update"));
}
