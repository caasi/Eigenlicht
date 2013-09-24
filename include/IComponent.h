#ifndef __EIGEN_INTERFACE_COMPONENT_H__
#define __EIGEN_INTERFACE_COMPONENT_H__

#include <IReferenceCounted.h>

namespace irr
{
namespace scene
{

class IMesh;

}
}

using namespace irr;
using namespace scene;

namespace eigen
{
namespace interactable
{

class ComponentContainer;

class IComponent : public IReferenceCounted
{
    friend class ComponentContainer;

public:
    IComponent():IReferenceCounted(),parent(NULL) {};

    ~IComponent();

    virtual IMesh *getMesh() const;
protected:
    ComponentContainer *parent;
};

}
}

#endif
