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

class IComponent : public IReferenceCounted
{
public:
    IComponent():IReferenceCounted() {};

    ~IComponent();

    virtual IMesh *getMesh() const;
};

}
}

#endif
