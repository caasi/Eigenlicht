#include "../include/ComponentContainer.h"

using namespace eigen;
using namespace interactable;

ComponentContainer::ComponentContainer():
    IComponent(),
    parent(NULL)
{
}

ComponentContainer::~ComponentContainer()
{
    for (
        vector< IComponent* >::iterator it = children.begin();
        it != children.end();
        ++it
    )
    {
        ComponentContainer *container = dynamic_cast<ComponentContainer*>(*it);

        if (container)
        {
            container->parent->drop();
            container->parent = NULL;
            container->drop();
        }
    }

    if (parent) parent->remove(this);
}

void ComponentContainer::add(IComponent *component)
{
    ComponentContainer *container = dynamic_cast<ComponentContainer*>(component);

    if (container && container->parent != this)
    {
        if (container->parent) container->parent->remove(container);
        container->parent = this;
        container->parent->grab();
    }

    children.push_back(component);
    component->grab();
}

bool ComponentContainer::remove(IComponent *component)
{
    vector< IComponent* >::iterator it = children.begin();

    for (; it != children.end(); (*it)->drop(), ++it)
    {
        if (*it == component) break;
    }

    if (it != children.end())
    {
        ComponentContainer *container = dynamic_cast<ComponentContainer*>(component);

        if (container)
        {
            container->parent->drop();
            container->parent = NULL;
        }

        component->drop();
        children.erase(it);
        return true;
    }

    return false;
}
