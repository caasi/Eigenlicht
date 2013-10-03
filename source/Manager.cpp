#include <iostream>

#include <IMesh.h>
#include <ITriangleSelector.h>

#include "../include/Manager.h"
#include "../include/Event.h"

Manager::Manager(ISceneManager *mgr):
    IComponent(),
    smgr(mgr),
    collmgr(smgr->getSceneCollisionManager())
{
    smgr->grab();
    collmgr->grab();
}

Manager::~Manager()
{
    for (map<ISceneNode*, IComponent*>::iterator it = components.begin(); it != components.end(); ++it)
    {
        it->first->drop();
        it->second->drop();
    }
    if (collmgr) collmgr->drop();
    if (smgr) smgr->drop();
}

void Manager::add(IComponent *component)
{
    IMesh *mesh = component->getMesh();
    ISceneNode *node = smgr->addMeshSceneNode(mesh, 0, Manager::ID_COMPONENT);
    ITriangleSelector *selector = smgr->createTriangleSelector(mesh, node);

    node->setTriangleSelector(selector);
    selector->drop();

    components.insert(pair<ISceneNode*, IComponent*>(node, component));
    component->grab();
}

bool Manager::remove(IComponent *component)
{
    /* TODO */
    return false;
}

void Manager::add(core::line3df *line)
{
    lines.push_back(line);
}

void Manager::update()
{
    Event *event = new Event("update");
    dispatchEvent(event);
    delete event;
    
    core::vector3df intersection;
    core::triangle3df hitTriangle;

    for (vector<core::line3df*>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        core::line3df &line = **it;

        ISceneNode *node = collmgr->getSceneNodeAndCollisionPointFromRay(
            line,
            intersection,
            hitTriangle,
            Manager::ID_COMPONENT
        );

        /* hit */
        while (node)
        {
            event = new Event("intersect");

            map<ISceneNode*, IComponent*>::iterator itComponent = components.find(node);
            
            /* node belongs to a component */
            if (itComponent != components.end())
            {
                (*itComponent).second->dispatchEvent(event);
            }

            node = node->getParent();

            /* it's hard to cast ISceneManager to ISceneNode even if CSceneManager is a ISceneNode */
            if (!node)
            {
                dispatchEvent(event);
                delete event;
            }
        }
    }
}
