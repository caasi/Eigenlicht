#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char *argv[])
{
    IrrlichtDevice *device = createDevice(
        video::EDT_SOFTWARE,
        dimension2d<u32>(640, 480),
        16,
        false,
        false,
        false,
        0
    );

    if (!device) return 1;

    device->drop();

    return 0;
}
