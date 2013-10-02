#ifndef __EIGENLICHT_PLANE_H__
#define __EIGENLICHT_PLANE_H__

#include <dimension2d.h>
#include <vector3d.h>

#include "Component.h"
#include "ComponentContainer.h"

using namespace irr;
using namespace core;

namespace eigen
{
namespace interactable
{

class Plane : public Component, public ComponentContainer
{
public:
    Plane(dimension2df size = dimension2df(0.451555, 0.282222));

    ~Plane();

    vector3df getUpVector() { return upVector; }

    vector3df getTargetVector() { return targetVector; }

private:
    vector3df upVector;
    vector3df targetVector;
};

}
}

#endif
