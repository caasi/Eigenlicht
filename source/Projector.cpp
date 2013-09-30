#include "../include/Projector.h"

using namespace irr::scene;
using namespace irr::core;

using namespace eigen::core;

vector3df &Projector::projectToCameraSpace(vector3df &vector, ICameraSceneNode &camera)
{
    getViewMatrix(camera).transformVect(vector);
    return vector;
}

vector3df &Projector::projectToNDCSpace(vector3df &vector, ICameraSceneNode &camera)
{
    getViewMatrix(camera).transformVect(vector);
    camera.getProjectionMatrix().transformVect(vector);
    return vector;
}

const matrix4 Projector::getViewMatrix(ICameraSceneNode &camera)
{
    vector3df pos = camera.getAbsolutePosition();
    vector3df target = camera.getTarget() - pos;
    target.normalize();

    vector3df up = camera.getUpVector();
    up.normalize();

    matrix4 viewMatrix;
    viewMatrix.buildCameraLookAtMatrixLH(pos, target, up);
    viewMatrix *= camera.getViewMatrixAffector();

    return viewMatrix;
}
