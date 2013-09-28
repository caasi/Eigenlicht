#include <iostream>

#include <irrlicht.h>
#include <eigenlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace eigen;
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
    std::cout << event->type << std::endl;
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

    Manager *gui3d = new Manager(smgr);
    gui3d->addEventListener("update", &update);
    gui3d->removeEventListener("update", &update);
    gui3d->addEventListener("update", &update);
    if (gui3d->hasEventListener("update", &update))
    {
        std::cout << "ready" << std::endl;
    }

    Plane *plane = new Plane;
    gui3d->add(plane);
    plane->drop();

    //smgr->addCubeSceneNode();
    ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(0, 1, -3), vector3df(0, 1, 0));
    // need helpers for matrix4, again
    /*
    camera->getProjectionMatrix();
    camera->getViewMatrix();
    camera->getViewMatrixAffector();
    */

    while (device->run())
    {
        if (inputBuffer.isDown(KEY_ESCAPE)) device->closeDevice();

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
