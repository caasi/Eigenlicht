#include <SMesh.h>
#include <SMeshBuffer.h>
#include <IVideoDriver.h>
#include "../include/Math.h"
#include "../include/Plane.h"

using namespace irr;
using namespace scene;
using namespace video;

using namespace eigen;
using namespace interactable;

Plane::Plane(core::dimension2df size, f32 dpi, path texture):
    Component(texture),
    size(size),
    dpi(dpi)
{
    f32 width  = size.Width  / dpi * Math::INCH_PER_METER,
        height = size.Height / dpi * Math::INCH_PER_METER;

    S3DVertex vertices[4];

    vertices[0] = S3DVertex(   0.0,    0.0, 0.0f, 0, 0, -1, SColor(255, 255, 255, 255), 0.0f, 0.0f);
    vertices[1] = S3DVertex( width,    0.0, 0.0f, 0, 0, -1, SColor(255, 255, 255, 255), 1.0f, 0.0f);
    vertices[2] = S3DVertex( width, -height, 0.0f, 0, 0, -1, SColor(255, 255, 255, 255), 1.0f, 1.0f);
    vertices[3] = S3DVertex(   0.0, -height, 0.0f, 0, 0, -1, SColor(255, 255, 255, 255), 0.0f, 1.0f);

    u16 indicies[6];

    indicies[0] = 0;
    indicies[1] = 1;
    indicies[2] = 2;
    indicies[3] = 0;
    indicies[4] = 2;
    indicies[5] = 3;

    IMeshBuffer *mesh_buffer = new SMeshBuffer;
    mesh_buffer->append(vertices, 4, indicies, 6);

    mesh = new SMesh;
    mesh->addMeshBuffer(mesh_buffer);
    mesh->recalculateBoundingBox();

    mesh_buffer->drop();
}

Plane::~Plane()
{
    if (mesh) mesh->drop();
}

ISceneNode *Plane::createSceneNode(ISceneManager *smgr)
{
    sceneNode = smgr->addMeshSceneNode(mesh, 0, GUIManager::ID_COMPONENT);
    sceneNode->grab();

    ITriangleSelector *selector = smgr->createTriangleSelector(mesh, sceneNode);
    sceneNode->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
    sceneNode->setMaterialTexture(0, smgr->getVideoDriver()->getTexture(getTexturePath()));
    sceneNode->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
    sceneNode->setTriangleSelector(selector);
    selector->drop();

    return sceneNode;
}

vector2df Plane::getPointFromUV(const vector2df &uv)
{
    return vector2df(uv.X * size.Width, uv.Y * size.Height);
}
