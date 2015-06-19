#include <iostream>
#include <irrlicht.h>
#include <boost/filesystem.hpp>

#include "GREventHandler.h"
#include "GRResourceLoader.h"

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
    MyEventReceiver receiver;

    SIrrlichtCreationParameters params;
    params.AntiAlias       = 8;
    params.Bits            = 24;
    params.DriverType      = video::EDT_OPENGL;
    params.Vsync           = false;
    params.Fullscreen      = false;
    params.EventReceiver   = &receiver;
    params.WindowSize = core::dimension2du(480,640);
    IrrlichtDevice *device = createDeviceEx(params);

    if (!device)
        return EXIT_FAILURE;

    device->setWindowCaption(L"Gravity");


    IVideoDriver* driver    = device->getVideoDriver();
    ISceneManager* smgr     = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    // IO
    fs::path spaceship_path = get_resource_path("spaceship.zip");
    fs::path earth_path     = get_resource_path("Earth.zip");
    device->getFileSystem()->addFileArchive(spaceship_path.c_str());
    device->getFileSystem()->addFileArchive(earth_path.c_str());

    // Scene setup
    scene::IMeshSceneNode* spaceship = smgr->addMeshSceneNode(smgr->getMesh("spaceship.obj"),0,-1,core::vector3df(0.0f,0.0f,-10.0f),
            core::vector3df(0.f,0.f,0.f),core::vector3df(.01f,.01f,.01f));
    scene::IMeshSceneNode* earth = smgr->addMeshSceneNode(smgr->getMesh("Earth.obj"),0,-1,core::vector3df(0.0f,0.0f,10.0f),
            core::vector3df(0.f,0.f,0.f),core::vector3df(10.0f,10.0f,10.0f));

    spaceship->setMaterialFlag(video::EMF_LIGHTING, false);
    earth->setMaterialFlag(video::EMF_LIGHTING, false);

    // smgr->setAmbientLight(video::SColorf(0.3,0.3,0.3,1));
    // ILightSceneNode* light1 = smgr->addLightSceneNode( 0, core::vector3df(0,500,0), video::SColorf(0.3f,0.3f,0.3f), 200.0f, 1 ); 


    // View setup
    smgr->addCameraSceneNode(
        0,
        core::vector3df(0, 20, -20),
        core::vector3df(0, 0, 0)
    );

    device->getCursorControl()->setVisible(false);

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
