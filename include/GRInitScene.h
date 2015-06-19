/* -----------------------------------------------------------------
 * File:    GRInitScene.h
 * Author:  Michael Gharbi <gharbi@mit.edu>
 * Created: 2015-06-19
 * -----------------------------------------------------------------
 * 
 * 
 * 
 * ---------------------------------------------------------------*/


#ifndef GRINIT_H_UVJRK1UO
#define GRINIT_H_UVJRK1UO

#include <irrlicht.h>

#include "GRResourceLoader.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


namespace gr {
void initialize_scene(IrrlichtDevice *device) {
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
    spaceship->setName("spaceship");
    scene::IMeshSceneNode* earth = smgr->addMeshSceneNode(smgr->getMesh("Earth.obj"),0,-1,core::vector3df(0.0f,0.0f,10.0f),
            core::vector3df(0.f,0.f,0.f),core::vector3df(10.0f,10.0f,10.0f));
    earth->setName("planet");

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

}
}

#endif /* end of include guard: GRINIT_H_UVJRK1UO */

