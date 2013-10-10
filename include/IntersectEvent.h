#ifndef __EIGENLICHT_INTERSECT_EVENT_H__
#define __EIGENLICHT_INTERSECT_EVENT_H__

#include <vector3d.h>
#include <triangle3d.h>
#include "Event.h"

using namespace irr;

namespace eigen
{
namespace event
{

struct IntersectEvent : public Event
{
    IntersectEvent():Event("intersect") {}
    core::vector3df intersection;
    core::vector2df uv;
    core::triangle3df hitTriangle;
};

}
}

#endif
