#ifndef __EIGEN_COMPONENT_CONTAINER_H__
#define __EIGEN_COMPONENT_CONTAINER_H__

#include <vector>
#include <IReferenceCounted.h>

#include "IComponent.h"
#include "EventDispatcher.h"

namespace eigen
{
namespace interactable
{

class ComponentContainer : virtual public IComponent, public event::EventDispatcher
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
