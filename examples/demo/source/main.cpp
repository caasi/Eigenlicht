#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class KeyBuffer : public IEventReceiver
{
public:
    KeyBuffer()
    {
        for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
            status[i] = false;
    }

    virtual bool OnEvent(const SEvent &event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            status[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    virtual bool isDown(EKEY_CODE keyCode) const
    {
        return status[keyCode];
    }

private:
    bool status[KEY_KEY_CODES_COUNT];
};

int main(int argc, char *argv[])
{
    KeyBuffer keyBuffer;

    IrrlichtDevice *device = createDevice(
        video::EDT_OPENGL,
        dimension2d<u32>(640, 480),
        16,
        false,
        false,
        false,
        &keyBuffer
    );

    if (!device) return 1;

    device->setWindowCaption(L"demo");

    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();
    IGUIEnvironment *guienv = device->getGUIEnvironment();

    smgr->addCubeSceneNode();
    smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

    while (device->run())
    {
        if (keyBuffer.isDown(KEY_ESCAPE)) device->closeDevice();

        driver->beginScene(true, true, SColor(255, 22, 22, 29));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }

    device->drop();

    return 0;
}
