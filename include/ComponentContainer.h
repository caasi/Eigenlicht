#ifndef __EIGEN_COMPONENT_CONTAINER_H__
#define __EIGEN_COMPONENT_CONTAINER_H__

#include <vector>
#include <IReferenceCounted.h>

#include "EventDispatcher.h"

namespace eigen
{
namespace interactable
{

class ComponentContainer : public event::EventDispatcher, public irr::IReferenceCounted
{
public:
    ComponentContainer();

    ~ComponentContainer();

    void add(ComponentContainer*);

    bool remove(ComponentContainer*);

private:
    ComponentContainer *parent;
    std::vector<ComponentContainer*> children;
};

}
}

#endif
