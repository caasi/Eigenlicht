#include <SMesh.h>
#include <SMeshBuffer.h>

using namespace irr;
using namespace scene;
using namespace video;

#include "../include/Plane.h"

using namespace eigen;
using namespace interactable;

/* 1280 x 720 72dpi screen in meters */
Plane::Plane(core::dimension2df size):
    Component(),
    ComponentContainer()
{
    S3DVertex vertices[4];

    vertices[0] = S3DVertex(-size.Width / 2, -size.Height / 2, 1.0f, 1, 1, 0, SColor(255, 255, 255, 255), 0.0f, 0.0f);
    vertices[1] = S3DVertex(-size.Width / 2,  size.Height / 2, 1.0f, 1, 1, 0, SColor(255, 255, 255, 255), 0.0f, 1.0f);
    vertices[2] = S3DVertex( size.Width / 2,  size.Height / 2, 1.0f, 1, 1, 0, SColor(255, 255, 255, 255), 1.0f, 1.0f);
    vertices[3] = S3DVertex( size.Width / 2, -size.Height / 2, 1.0f, 1, 1, 0, SColor(255, 255, 255, 255), 1.0f, 0.0f);

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
