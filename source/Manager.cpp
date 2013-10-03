#include <iostream>

#include <IMesh.h>
#include <ITriangleSelector.h>

#include "../include/Manager.h"
#include "../include/Event.h"
#include "../include/Component.h"

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
    component->setSceneNode(node);
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
    event->target = this;
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
        
        event = NULL;

        if (node)
        {
            map<ISceneNode*, IComponent*>::iterator it = components.find(node);

            if (it != components.end())
            {
                event = new Event("intersect");
                event->target = (*it).second;
            }
        }

        /* hit */
        while (node)
        {
            map<ISceneNode*, IComponent*>::iterator it = components.find(node);
            
            /* node belongs to a component */
            if (it != components.end())
            {
                if (event) (*it).second->dispatchEvent(event);
            }

            node = node->getParent();

            /* it's hard to cast ISceneManager to ISceneNode even if CSceneManager is a ISceneNode */
            if (!node && event)
            {
                dispatchEvent(event);
            }

        }
        
        if (event) delete event;
    }
}
