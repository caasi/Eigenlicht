#ifndef __EIGENLICHT_PLANE_H__
#define __EIGENLICHT_PLANE_H__

#include <dimension2d.h>
#include <vector2d.h>
#include <vector3d.h>
#include <irrString.h>

#include "Component.h"

using namespace irr;
using namespace scene;
using namespace io;

namespace eigen
{
namespace interactable
{

class Plane : public Component
{
public:
    Plane(
        core::dimension2df size = core::dimension2df(1280, 800),
        f32 dpi = 72.0,
        path texture = "../media/background_white.png"
    );

    virtual ~Plane();

    core::vector2df getPointFromUV(const core::vector2df &uv);

protected:
    core::dimension2df size;
    f32 dpi;
    path texturePath;

    virtual ISceneNode *createSceneNode(ISceneManager*);
};

}
}

#endif
