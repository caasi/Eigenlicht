#include "../include/ComponentContainer.h"

using namespace eigen;
using namespace interactable;

ComponentContainer::ComponentContainer():
    IReferenceCounted(),
    parent(NULL)
{
}

ComponentContainer::~ComponentContainer()
{
    for (
        vector< ComponentContainer* >::iterator it = children.begin();
        it != children.end();
        ++it
    )
    {
        (*it)->parent->drop();
        (*it)->parent = NULL;
        (*it)->drop();
    }

    if (parent) parent->remove(this);
}

void ComponentContainer::add(ComponentContainer *component)
{
    if (component->parent != this)
    {
        if (component->parent) component->parent->remove(component);
        component->parent = this;
        component->parent->grab();
    }
    children.push_back(component);
    component->grab();
}

bool ComponentContainer::remove(ComponentContainer *component)
{
    vector< ComponentContainer* >::iterator it = children.begin();

    for (; it != children.end(); (*it)->drop(), ++it)
    {
        if (*it == component) break;
    }

    if (it != children.end())
    {
        component->parent->drop();
        component->parent = NULL;
        component->drop();
        children.erase(it);
        return true;
    }

    return false;
}
