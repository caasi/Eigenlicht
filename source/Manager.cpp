#include <iostream>

#include <S3DVertex.h>
#include <IMesh.h>
#include <IMeshBuffer.h>
#include <ITriangleSelector.h>

#include "../include/Manager.h"
#include "../include/Event.h"
#include "../include/IntersectEvent.h"
#include "../include/Component.h"

using namespace irr::video;

Manager::Manager(ISceneManager *mgr):
    IComponent(),
    smgr(mgr),
    collmgr(smgr->getSceneCollisionManager())
{
    smgr->grab();
    collmgr->grab();
}

Manager::~Manager()
{
    for (map<ISceneNode*, IComponent*>::iterator it = components.begin(); it != components.end(); ++it)
    {
        it->first->drop();
        it->second->drop();
    }
    if (collmgr) collmgr->drop();
    if (smgr) smgr->drop();
}

void Manager::add(IComponent *component)
{
    IMesh *mesh = component->getMesh();
    ISceneNode *node = smgr->addMeshSceneNode(mesh, 0, Manager::ID_COMPONENT);
    ITriangleSelector *selector = smgr->createTriangleSelector(mesh, node);

    node->setTriangleSelector(selector);
    selector->drop();

    components.insert(pair<ISceneNode*, IComponent*>(node, component));
    component->grab();
    component->setSceneNode(node);
}

bool Manager::remove(IComponent *component)
{
    /* TODO */
    return false;
}

void Manager::add(core::line3df *line)
{
    lines.push_back(line);
}

void Manager::update()
{
    IntersectEvent *intersect_event = NULL;

    Event *event = new Event("update");
    event->target = this;
    dispatchEvent(event);
    delete event;
    event = NULL;
    
    core::vector3df intersection;
    core::triangle3df hitTriangle;

    for (vector<core::line3df*>::iterator it = lines.begin(); it != lines.end(); ++it)
    {
        core::line3df &line = **it;

        ISceneNode *node = collmgr->getSceneNodeAndCollisionPointFromRay(
            line,
            intersection,
            hitTriangle,
            Manager::ID_COMPONENT
        );
        
        if (node)
        {
            map<ISceneNode*, IComponent*>::iterator it = components.find(node);

            if (it != components.end())
            {
                S3DVertex v_a, v_b, v_c;

                IMesh *mesh = (*it).second->getMesh();
                s32 buffer_len = mesh->getMeshBufferCount();
                for (int i = 0; i < buffer_len; ++i)
                {
                    IMeshBuffer *buffer = mesh->getMeshBuffer(i);

                    s32 vertices_len = buffer->getVertexCount();
                    S3DVertex *vertices = static_cast<S3DVertex*>(buffer->getVertices());

                    for (int j = 0; j < vertices_len; ++j)
                    {
                        core::vector3df pos = vertices[j].Pos;
                        (*it).first->getAbsoluteTransformation().transformVect(pos);

                        if (pos == hitTriangle.pointA) v_a = vertices[j];
                        if (pos == hitTriangle.pointB) v_b = vertices[j];
                        if (pos == hitTriangle.pointC) v_c = vertices[j];
                    }
                }

                //std::cout << v_c.TCoords.X << ", " << v_c.TCoords.Y << std::endl;

                intersect_event = new IntersectEvent();
                intersect_event->target = (*it).second;
                intersect_event->intersection = intersection;

                // caculate intersection in uv coords
                intersection = intersection - hitTriangle.pointA;
                core::vector3df vc = hitTriangle.pointB - hitTriangle.pointA;
                core::vector3df vb = hitTriangle.pointC - hitTriangle.pointA;
                core::vector3df vn = vc.crossProduct(vb).normalize();
                core::matrix4 m, inverted;
                m[0] = vc.X; m[4] = vb.X; m[ 8] = vn.X;
                m[1] = vc.Y; m[5] = vb.Y; m[ 9] = vn.Y;
                m[2] = vc.Z; m[6] = vb.Z; m[10] = vn.Z;
                m.getInverse(inverted);
                inverted.transformVect(intersection);
                core::vector3df ta = core::vector3df(v_a.TCoords.X, v_a.TCoords.Y, 0);
                core::vector3df tb = core::vector3df(v_b.TCoords.X, v_b.TCoords.Y, 0);
                core::vector3df tc = core::vector3df(v_c.TCoords.X, v_c.TCoords.Y, 0);
                vc = tb - ta;
                vb = tc - ta;
                vn = vc.crossProduct(vb).normalize();
                m.makeIdentity();
                m[0] = vc.X; m[4] = vb.X; m[ 8] = vn.X;
                m[1] = vc.Y; m[5] = vb.Y; m[ 9] = vn.Y;
                m[2] = vc.Z; m[6] = vb.Z; m[10] = vn.Z;
                m.transformVect(intersection);
                intersect_event->uv = core::vector2df(intersection.X, intersection.Y);

                intersect_event->hitTriangle = hitTriangle;
            }
        }

        /* hit */
        while (node)
        {
            map<ISceneNode*, IComponent*>::iterator it = components.find(node);
            
            /* node belongs to a component */
            if (it != components.end())
            {
                if (intersect_event) (*it).second->dispatchEvent(intersect_event);
            }

            node = node->getParent();

            /* it's hard to cast ISceneManager to ISceneNode even if CSceneManager is a ISceneNode */
            if (!node && intersect_event)
            {
                dispatchEvent(intersect_event);
            }

        }
        
        if (intersect_event) delete intersect_event;
    }
}
