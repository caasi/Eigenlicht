#ifndef __EIGENLICHT_MATH_H__
#define __EIGENLICHT_MATH_H__

#include <matrix4.h>
#include <vector3d.h>

using namespace irr;

namespace eigen
{

class Math
{
public:
    static core::matrix4 localMatrix(const core::vector3df&, const core::vector3df&, const core::vector3df&);
};

}

#endif
