#ifndef __EIGEN_PROJECTOR_H__
#define __EIGEN_PROJECTOR_H__

#include <ICameraSceneNode.h>

using namespace irr;
using namespace scene;
using namespace core;

namespace eigen
{
namespace core
{

class Projector
{
public:
    static vector3df &projectToCameraSpace(vector3df&, ICameraSceneNode&);
    static vector3df &projectToNDCSpace(vector3df&, ICameraSceneNode&);
private:
    static const matrix4 getViewMatrix(ICameraSceneNode&);
};

}
}

#endif
