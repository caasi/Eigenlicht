#include <iostream>
#include <iomanip>

using namespace std;

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

ostream &operator<< (ostream &out, const matrix4 &m)
{
    out << "{" << endl;

    for (int i = 0; i < 16; ++i)
    {
        out << setw(10) << setfill(' ') << m[i];
        if (i % 4 != 3) out << ", ";
        if (i % 4 == 3) out << endl;
    }

    out << "}";

    return out;
}

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

    //smgr->addCubeSceneNode();
    ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(0, 1, -1), vector3df(0, 0.25, 0));

    while (device->run())
    {
        if (inputBuffer.isDown(KEY_ESCAPE)) device->closeDevice();

        driver->beginScene(true, true, SColor(255, 22, 22, 29));

        smgr->drawAll();
        guienv->drawAll();
        gui3d->update();

        driver->endScene();

        const SViewFrustum *frustum = camera->getViewFrustum();
        cout << "projection: " << frustum->getTransform(ETS_PROJECTION) << endl;
        cout << "view: "<< frustum->getTransform(ETS_VIEW) << endl;
    }

    gui3d->drop();
    device->drop();

    return 0;
}
