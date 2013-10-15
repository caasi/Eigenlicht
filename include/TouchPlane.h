#ifndef __EIGENLICHT_TOUCH_PLANE_H__
#define __EIGENLICHT_TOUCH_PLANE_H__

#include "Event.h"
#include "Component.h"
#include "Plane.h"

namespace eigen
{
namespace interactable
{

class TouchPlane : public Component
{
public:
    TouchPlane(
        core::dimension2df size = core::dimension2df(1280, 800),
        f32 dpi = 72.0,
        path texture = "../media/background_white.png",
        f32 d = 0.1
    );

    virtual ~TouchPlane();

    virtual IMesh *getMesh() { return NULL; }

    virtual void addTo(GUIManager *);

protected:
    virtual ISceneNode *createSceneNode(ISceneManager*);

private:
    core::dimension2df size;
    f32 dpi;
    path texturePath;
    f32 distance;
    Plane *display;
    Plane *near;
};

}
}

#endif
