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

void intersect(Event *event)
{
    IntersectEvent *e = dynamic_cast<IntersectEvent*>(event);
    Plane *p = static_cast<Plane*>(e->target);

    if (e)
    {
        cout << "uv: " << e->uv << endl;
        cout << "hit: " << p->getPointFromUV(e->uv) << endl;
    }
}

int main(int argc, char *argv[])
{
    InputBuffer inputBuffer;

    IrrlichtDevice *device = createDevice(
        video::EDT_OPENGL,
        dimension2d<u32>(800, 600),
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

    ILightSceneNode * light = smgr->addLightSceneNode(
                                0,
                                vector3df(0, 2, -2),
                                SColorf(1.0f, 1.0f, 1.0f, 1.0f),
                                500.f
                              );


    GUIManager *gui3d = new GUIManager(smgr);
    gui3d->addEventListener("update", &update);
    gui3d->removeEventListener("update", &update);
    gui3d->addEventListener("update", &update);
    gui3d->addEventListener("intersect", &intersect);
    if (gui3d->hasEventListener("update", &update))
    {
        cout << "ready" << endl;
    }

    Plane *plane = new Plane;
    gui3d->add(plane);
    plane->getSceneNode()->setPosition(vector3df(0, 0, 0.25));
    plane->drop();

    Plane *another = new Plane(dimension2df(640, 480));
    gui3d->add(another);
    // you can only get valid scene node after component added to the GUI manager */
    another->getSceneNode()->setPosition(vector3df(0.25, 0, -0.25));
    another->getSceneNode()->setRotation(vector3df(0, 90, 0));
    another->drop();

    //smgr->addCubeSceneNode();
    ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(-0.5, 0.2, -0.5));
    camera->setTarget(vector3df(0, 0, -0.25));

    line3df ray;
    gui3d->add(&ray);

    while (device->run())
    {
        if (inputBuffer.isDown(KEY_ESCAPE)) device->closeDevice();
        
        ray.setLine(collMan->getRayFromScreenCoordinates(inputBuffer.mouse, camera));

        driver->beginScene(true, true, SColor(255, 22, 22, 29));

        smgr->drawAll();
        guienv->drawAll();
        gui3d->update();

        driver->endScene();
    }

    gui3d->drop();
    device->drop();

    return 0;
}
