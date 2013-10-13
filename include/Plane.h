#ifndef __EIGENLICHT_PLANE_H__
#define __EIGENLICHT_PLANE_H__

#include <dimension2d.h>
#include <vector2d.h>
#include <vector3d.h>
#include <irrString.h>

#include "Component.h"

using namespace irr;
using namespace core;
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
        dimension2df size = dimension2df(1280, 800),
        f32 dpi = 72.0,
        path texture = "../media/background_white.png"
    );

    virtual ~Plane();

    vector2df getPointFromUV(const vector2df &uv);

protected:
    virtual ISceneNode *createSceneNode(ISceneManager*);

private:
    dimension2df size;
    f32 dpi;
    path texturePath;
};

}
}

#endif
