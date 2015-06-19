#include <iostream>
#include <irrlicht.h>

#include "GREventHandler.h"
#include "GRResourceLoader.h"
#include <boost/filesystem.hpp>

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
    IrrlichtDevice *device = createDeviceEx(params);

    if (!device)
        return EXIT_FAILURE;

    device->setWindowCaption(L"Gravity");


    IVideoDriver* driver    = device->getVideoDriver();
    ISceneManager* smgr     = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    fs::path map_path = get_resource_path("map-20kdm2.pk3");
    device->getFileSystem()->addFileArchive("../../media/map-20kdm2.pk3");

    scene::IAnimatedMesh* mesh = smgr->getMesh("20kdm2.bsp");
    scene::ISceneNode* node = 0;

    if (mesh)
        node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);

    if (node)
            node->setPosition(core::vector3df(-1300,-144,-1249));

    smgr->addCameraSceneNodeFPS();

    device->getCursorControl()->setVisible(false);

    int lastFPS = -1;

    while(device->run())
    {
        if(receiver.IsKeyDown(irr::KEY_ESCAPE)) {
            printf("out\n");
            break;
        }
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, video::SColor(255,200,200,200));
            smgr->drawAll();
            driver->endScene();

            int fps = driver->getFPS();

            if (lastFPS != fps)
            {
                core::stringw str = L"Irrlicht Engine - Quake 3 Map example [";
                str += driver->getName();
                str += "] FPS:";
                str += fps;

                device->setWindowCaption(str.c_str());
                lastFPS = fps;
            }
        }
        else
            device->yield();

    }

    device->closeDevice();
    device->drop();

    return EXIT_SUCCESS;
}
