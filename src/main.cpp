#include <iostream>
#include <irrlicht.h>

#include "GREventHandler.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
    MyEventReceiver receiver;

    SIrrlichtCreationParameters params;
    params.AntiAlias       = 8;
    params.Bits            = 24;
    params.DriverType      = video::EDT_OPENGL;
    params.Vsync           = false;
    params.Fullscreen      = false;
    params.EventReceiver   = &receiver;
    IrrlichtDevice *device = createDeviceEx(params);

    if (!device)
        return EXIT_FAILURE;

    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

    IVideoDriver* driver    = device->getVideoDriver();
    ISceneManager* smgr     = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
            rect<s32>(10,10,260,22), true);

    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    while(device->run())
    {
        if(receiver.IsKeyDown(irr::KEY_ESCAPE)) {
            printf("out\n");
            break;
        }

        driver->beginScene(true, true, SColor(255,100,101,140));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }

    device->closeDevice();
    device->drop();

    return EXIT_SUCCESS;
}
