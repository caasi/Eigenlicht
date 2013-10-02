#ifndef __EIGENLICHT_PLANE_H__
#define __EIGENLICHT_PLANE_H__

#include <dimension2d.h>
#include <vector3d.h>

#include "Component.h"

using namespace irr;
using namespace core;

namespace eigen
{
namespace interactable
{

class Plane : public Component
{
public:
    Plane(dimension2df size = dimension2df(1920, 1080), f32 dpi = 72.0);

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
