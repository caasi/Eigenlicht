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
    applyMatrix4(vector, camera.getProjectionMatrix());
    return vector;
}

vector3df &Projector::unprojectFromCameraSpace(vector3df &vector, ICameraSceneNode &camera)
{
    matrix4 inversed;
    getViewMatrix(camera).getInversePrimitive(inversed);
    inversed.transformVect(vector);
    return vector;
}

vector3df &Projector::unprojectFromNDCSpace(vector3df &vector, ICameraSceneNode &camera)
{
    matrix4 inversed;
    camera.getProjectionMatrix().getInverse(inversed);
    applyMatrix4(vector, inversed);
    unprojectFromCameraSpace(vector, camera);
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

/**
 * like applyProjection() in three.js, but I think it should be done
 * automatically when we cast vector4d to vector3d
 */
void Projector::applyMatrix4(vector3df &vector, const matrix4 &matrix)
{
    float w = vector.X * matrix[3] + vector.Y * matrix[7] + vector.Z * matrix[11] + matrix[15];

    matrix.transformVect(vector);

    vector.X /= w;
    vector.Y /= w;
    vector.Z /= w;
}
