#ifndef __EIGENLICHT_COMPONENT_CONTAINER_H__
#define __EIGENLICHT_COMPONENT_CONTAINER_H__

#include <vector>
#include <IReferenceCounted.h>

#include "IComponent.h"
#include "EventDispatcher.h"

namespace eigen
{
namespace interactable
{

/* TODO: remove this class */
class ComponentContainer : virtual public IComponent
{
public:
    ComponentContainer();

    ~ComponentContainer();

    virtual void add(IComponent*);

    virtual bool remove(IComponent*);

private:
    std::vector<IComponent*> children;
};

}
}

#endif
