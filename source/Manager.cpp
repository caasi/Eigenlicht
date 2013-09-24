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
    if (smgr) smgr->drop();
}

void Manager::add(IComponent *component)
{
    ComponentContainer::add(component);
}

bool Manager::remove(IComponent *component)
{
    return ComponentContainer::remove(component);
}

void Manager::update()
{
    dispatchEvent(new Event("update"));
}
