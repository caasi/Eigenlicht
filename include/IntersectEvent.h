#ifndef __EIGENLICHT_INTERSECT_EVENT_H__
#define __EIGENLICHT_INTERSECT_EVENT_H__

#include <vector3d.h>
#include <triangle3d.h>
#include "Event.h"

namespace eigen
{
namespace event
{

struct IntersectEvent : public Event
{
    IntersectEvent():Event("intersect") {}
    irr::core::vector3df intersection;
    irr::core::vector2df uv;
    irr::core::triangle3df hitTriangle;
};

}
}

#endif
