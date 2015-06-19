#include <iostream>
#include <irrlicht.h>
#include <boost/filesystem.hpp>

#include "GREventReceiver.h"
#include "GRInitScene.h"

#include <iostream>

using std::cout;
using std::endl;

namespace fs = boost::filesystem;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
    gr::GREventReceiver receiver;

    SIrrlichtCreationParameters params;
    params.AntiAlias       = 8;
    params.Bits            = 24;
    params.DriverType      = video::EDT_OPENGL;
    params.Vsync           = false;
    params.Fullscreen      = false;
    params.Stencilbuffer               = false;
    params.EventReceiver   = &receiver;
    params.WindowSize = core::dimension2du(480,640);
    IrrlichtDevice *device = createDeviceEx(params);

    if (!device)
        return EXIT_FAILURE;

    device->setWindowCaption(L"Gravity");

    IVideoDriver* driver    = device->getVideoDriver();
    ISceneManager* smgr     = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    guienv->addStaticText(L"Running Gravity Game",
            rect<s32>(10,10,360,62), false);

    gr::initialize_scene(device);

    scene::ISceneNode* spaceship = smgr->getSceneNodeFromName("spaceship");
    // scene::ISceneNode* planet = smgr->getSceneNodeFromName("planet");

    u32 then = device->getTimer()->getTime();

    // This is the movemen speed in units per second.
    const f32 MOVEMENT_SPEED = 20.f;

    // Main game loop
    while(device->run())
    {
        if(receiver.IsKeyDown(irr::KEY_ESCAPE)) {
            printf("out\n");
            break;
        }

        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        // Spaceship controls
        core::vector3df nodePosition = spaceship->getPosition();
        if(receiver.IsKeyDown(irr::KEY_KEY_W))
            nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
        else if(receiver.IsKeyDown(irr::KEY_KEY_S))
            nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
        if(receiver.IsKeyDown(irr::KEY_KEY_A))
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
        else if(receiver.IsKeyDown(irr::KEY_KEY_D))
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

        spaceship->setPosition(nodePosition);

        if (device->isWindowActive())
        {
            driver->beginScene(true, true, video::SColor(255,200,200,200));

            smgr->drawAll();
            driver->endScene();
        }
        else {
            device->yield();
        }

    }

    device->closeDevice();
    device->drop();

    return EXIT_SUCCESS;
}
