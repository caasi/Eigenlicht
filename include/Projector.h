#ifndef __EIGENLICHT_PROJECTOR_H__
#define __EIGENLICHT_PROJECTOR_H__

#include <ICameraSceneNode.h>

using namespace irr;
using namespace core;
using namespace scene;

namespace eigen
{

class Projector
{
public:
    static vector3df &projectToCameraSpace(vector3df&, ICameraSceneNode&);
    static vector3df &projectToNDCSpace(vector3df&, ICameraSceneNode&);
    static vector3df &unprojectFromCameraSpace(vector3df&, ICameraSceneNode&);
    static vector3df &unprojectFromNDCSpace(vector3df&, ICameraSceneNode&);
private:
    static const matrix4 getViewMatrix(ICameraSceneNode&);
    static void applyMatrix4(vector3df&, const matrix4&);
};

}

#endif
