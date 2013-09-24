#ifndef __EIGEN_PLANE_H__
#define __EIGEN_PLANE_H__

#include "Component.h"
#include "ComponentContainer.h"

namespace eigen
{
namespace interactable
{

class Plane : public Component, public ComponentContainer
{
public:
    Plane();

    ~Plane();
};

}
}

#endif
