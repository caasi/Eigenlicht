#include <iostream>

using namespace std;

#include <irrlicht.h>
#include <eigenlicht.h>
#include <utils.h>

using namespace irr;
using namespace irr::core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace eigen;
using namespace eigen::core;
using namespace event;
using namespace interactable;

class InputBuffer : public IEventReceiver
{
public:
    InputBuffer()
    {
        for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
            status[i] = false;
    }

    virtual bool OnEvent(const SEvent &event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            status[event.KeyInput.Key] = event.KeyInput.PressedDown;

        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            switch (event.MouseInput.Event)
            {
                case EMIE_MOUSE_MOVED:
                    mouse.X = event.MouseInput.X;
                    mouse.Y = event.MouseInput.Y;
            }
        }

        return false;
    }

    virtual bool isDown(EKEY_CODE keyCode) const
    {
        return status[keyCode];
    }

    position2di mouse;

private:
    bool status[KEY_KEY_CODES_COUNT];
};

void update(Event *event)
{
    //cout << event->type << endl;
}

int main(int argc, char *argv[])
{
    InputBuffer inputBuffer;

    IrrlichtDevice *device = createDevice(
        video::EDT_OPENGL,
        dimension2d<u32>(640, 480),
        16,
        false,
        false,
        false,
        &inputBuffer
    );

    if (!device) return 1;

    device->setWindowCaption(L"demo");

    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();
    IGUIEnvironment *guienv = device->getGUIEnvironment();
    ISceneCollisionManager *collMan = smgr->getSceneCollisionManager();

    Manager *gui3d = new Manager(smgr);
    gui3d->addEventListener("update", &update);
    gui3d->removeEventListener("update", &update);
    gui3d->addEventListener("update", &update);
    if (gui3d->hasEventListener("update", &update))
    {
        cout << "ready" << endl;
    }

    Plane *plane = new Plane;
    gui3d->add(plane);
    plane->drop();

    ISceneNode *planeNode = gui3d->getTestNode();
    cout << "aabbox3df: " << endl
         << planeNode->getBoundingBox().MinEdge << endl
         << planeNode->getBoundingBox().MaxEdge << endl;
    if (planeNode->getTriangleSelector())
    {
        cout << "has triangle selector" << endl;
    }

    matrix4 planeMatrix;
    planeMatrix.buildCameraLookAtMatrixLH(
        planeNode->getAbsolutePosition(),
        plane->getTargetVector(),
        plane->getUpVector()
    );

    //smgr->addCubeSceneNode();
    ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(0, 1, -1));
    /**
     * TODO
     **
     * Projector should get frustum from camera,
     * update view matrix, then project or unproject.
     * There are two types of useful projections/unprojections,
     *  1. world space to view space
     *  2. world space to ndc space
     * Because I can't extend CCameraSceneNode,
     * Projector will be a new class.
     * Projector will change the vector to prevent temp objects.
     */
    camera->setTarget(vector3df(0, 0, 0));
    vector3df point = vector3df(0, 0, 0);
    cout << "to from camera: "
         << Projector::unprojectFromCameraSpace(Projector::projectToCameraSpace(point, *camera), *camera)
         << endl;
    point = vector3df(0, 0, 0);
    cout << "to from NDC: "
         << Projector::unprojectFromNDCSpace(Projector::projectToNDCSpace(point, *camera), *camera)
         << endl;

    line3df ray;
    line3df collRay;
    vector3df intersection;
    triangle3df hitTriangle;

    while (device->run())
    {
        if (inputBuffer.isDown(KEY_ESCAPE)) device->closeDevice();

        driver->beginScene(true, true, SColor(255, 22, 22, 29));

        vector3df mouse = vector3df(
            2 * (inputBuffer.mouse.X / 640.0 - 0.5),
            2 * ((480.0 - inputBuffer.mouse.Y) / 480.0 - 0.5),
            1.0
        );
        
        ray.start = camera->getAbsolutePosition();
        ray.end = Projector::unprojectFromNDCSpace(mouse, *camera);

        //collRay = collMan->getRayFromScreenCoordinates(inputBuffer.mouse, camera);

        ISceneNode *selectedSceneNode =
            collMan->getSceneNodeAndCollisionPointFromRay(
                ray,
                intersection,
                hitTriangle,
                Manager::ID_COMPONENT
            );

        if (selectedSceneNode)
        {
            /* collision is performed by bounding box, so the result is very strange */
            cout << "intersect: " << intersection << endl;
            cout << "triangle: " << hitTriangle << endl;
            planeMatrix.transformVect(intersection);
            intersection.X = intersection.X / 0.677333 * 1920;
            intersection.Y = intersection.Y / 0.381 * 1080;
            cout << "view space: " << intersection << endl;
        }

        smgr->drawAll();
        guienv->drawAll();
        gui3d->update();

        driver->endScene();
    }

    gui3d->drop();
    device->drop();

    return 0;
}
