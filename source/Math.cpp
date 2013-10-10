#include "../include/Math.h"

using namespace eigen;

core::matrix4 Math::localMatrix(
    const core::vector3df &axis_x,
    const core::vector3df &axis_y,
    const core::vector3df &axis_z
)
{
    core::matrix4 m;
    m[0] = axis_x.X; m[4] = axis_y.X; m[ 8] = axis_z.X;
    m[1] = axis_x.Y; m[5] = axis_y.Y; m[ 9] = axis_z.Y;
    m[2] = axis_x.Z; m[6] = axis_y.Z; m[10] = axis_z.Z;
    return m;
}
