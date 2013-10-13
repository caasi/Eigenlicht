#include <iostream>

#include <S3DVertex.h>
#include <IMesh.h>
#include <IMeshBuffer.h>
#include <IMeshSceneNode.h>
#include <ITriangleSelector.h>

#include "../include/Math.h"
#include "../include/GUIManager.h"
#include "../include/Event.h"
#include "../include/IntersectEvent.h"
#include "../include/Component.h"

using namespace irr::video;

GUIManager::GUIManager(ISceneManager *mgr):
    IComponent(),
    smgr(mgr),
    collmgr(smgr->getSceneCollisionManager())
{
    smgr->grab();
    collmgr->grab();
}

GUIManager::~GUIManager()
{
    for (map<ISceneNode*, IComponent*>::iterator it = components.begin(); it != components.end(); ++it)
    {
        (*it).first->drop();
        (*it).second->drop();
    }
    if (collmgr) collmgr->drop();
    if (smgr) smgr->drop();
}

void GUIManager::add(IComponent *component)
{
    component->addTo(this);
}

bool GUIManager::remove(IComponent *component)
{
    /* TODO */
    return false;
}

void GUIManager::insert(ISceneNode *node, IComponent *comp)
{
    if (!node && !comp) return;
    components.insert(pair<ISceneNode*, IComponent*>(node, comp));
    node->grab();
    comp->grab();
}

void GUIManager::add(core::line3df *line)
{
    lines.push_back(line);
}

IComponent *GUIManager::getComponentForSceneNode(ISceneNode *node)
{
    map<ISceneNode*, IComponent*>::iterator it = components.find(node);
    if (it != components.end()) return (*it).second;
    return NULL;
}

void GUIManager::bubbleUp(IComponent *comp, Event *event)
{
    if (!event) return;

    ISceneNode *node = comp ? comp->getSceneNode() : NULL;

    do
    {
        if (comp)
            comp->EventDispatcher::dispatchEvent(event);
        
        node = node->getParent();
        comp = getComponentForSceneNode(node);
    } while (node);

    /* it's hard to cast ISceneManager to ISceneNode even if CSceneManager is a ISceneNode */
    dispatchEvent(event);
}

void GUIManager::update()
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
            GUIManager::ID_COMPONENT
        );
        
        if (node)
        {
            map<ISceneNode*, IComponent*>::iterator it = components.find(node);

            if (it != components.end())
            {
                IComponent *comp = (*it).second;
                S3DVertex v_a, v_b, v_c;

                IMesh *mesh = comp->getMesh();

                /**
                 * TODO
                 **
                 * can't down cast scene node to mesh scene node now,
                 * may get NULL if component has multiple components or scene nodes.
                 **/
                if (mesh)
                {
                    s32 buffer_len = mesh->getMeshBufferCount();
                    for (int i = 0; i < buffer_len; ++i)
                    {
                        IMeshBuffer *buffer = mesh->getMeshBuffer(i);

                        s32 vertices_len = buffer->getVertexCount();
                        S3DVertex *vertices = static_cast<S3DVertex*>(buffer->getVertices());

                        for (int j = 0; j < vertices_len; ++j)
                        {
                            core::vector3df pos = vertices[j].Pos;
                            node->getAbsoluteTransformation().transformVect(pos);

                            if (pos == hitTriangle.pointA) v_a = vertices[j];
                            if (pos == hitTriangle.pointB) v_b = vertices[j];
                            if (pos == hitTriangle.pointC) v_c = vertices[j];
                        }
                    }

                    intersect_event = new IntersectEvent();
                    intersect_event->target = comp;
                    intersect_event->intersection = intersection;

                    // caculate intersection in uv coords
                    intersection -= hitTriangle.pointA;
                    core::vector3df vx = hitTriangle.pointB - hitTriangle.pointA;
                    core::vector3df vy = hitTriangle.pointC - hitTriangle.pointA;
                    core::vector3df vz = vx.crossProduct(vy).normalize();
                    core::matrix4 m = Math::localMatrix(vx, vy, vz), inverted;
                    m.getInverse(inverted);
                    inverted.transformVect(intersection);
                    core::vector3df ta = core::vector3df(v_a.TCoords.X, v_a.TCoords.Y, 0);
                    core::vector3df tb = core::vector3df(v_b.TCoords.X, v_b.TCoords.Y, 0);
                    core::vector3df tc = core::vector3df(v_c.TCoords.X, v_c.TCoords.Y, 0);
                    vx = tb - ta;
                    vy = tc - ta;
                    vz = vx.crossProduct(vy).normalize();
                    Math::localMatrix(vx, vy, vz).transformVect(intersection);
                    intersect_event->uv = core::vector2df(intersection.X, intersection.Y);

                    intersect_event->hitTriangle = hitTriangle;
                
                    bubbleUp(comp, intersect_event);
                }
            }

            if (intersect_event) delete intersect_event;
        }

        /* TODO: bounding box and near event */
    }
}
