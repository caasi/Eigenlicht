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

    testNode = smgr->addMeshSceneNode(component->getMesh());
}

bool Manager::remove(IComponent *component)
{
    return ComponentContainer::remove(component);
}

void Manager::update()
{
    dispatchEvent(new Event("update"));
}
