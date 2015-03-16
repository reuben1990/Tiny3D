//
//  OceanApplication.cpp
//  proj_mac
//
//  Created by reuben chao on 2/23/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <stdio.h>
#include "TinyRoot.h"
#include "TinyMemoryAlloc.h"
#include "TinySceneManager.h"
#include "TinyDelegate.h"
#include "TinyPlatform.h"
#include "TinyTextureManager.h"
#include "TinyRenderWindow.h"
#include "kazmath/kazmath.h"
#include "TinyEntityFactory.h"
#include "TinyEntity.h"
#include "TinyMath.h"
#include "TinyGPUProgramManager.h"
#include "TinyMaterialManager.h"
#include "TinyInputManager.h"
#include "OceanApplication.h"
#include "TinySceneNode.h"
#include "TinyCamera.h"
#include "TinyGBuffer.h"

void OceanApplication::initialize()
{

    //Create TinyRoot.
    TinyRoot* root = TinyRoot::getSingleton();
    
    Tiny::TinyInputManager::getSingleton()->createInputObject(Tiny::InputDevice::Mouse);
    Tiny::TinyInputManager::getSingleton()->createInputObject(Tiny::InputDevice::Keyboard);
    
    //Create render window.
    TinyRenderWindow* mainWindow = tinyCreateRenderWindow(800, 480);
    root->attachRenderTarget(mainWindow);
    
    //Create gbuffer.
    TinyGBuffer* gBuffer = TINY_NEW TinyGBuffer(800, 480);
    root->attachRenderTarget(gBuffer);
    
    //Init scene graph.
    Tiny::TinySceneManager* sceneMgr = root->createSceneManager();
    TinySceneNode* rootNode = sceneMgr->getRootSceneNode();
    //Entity node.
    TinySceneNode* entityNode = rootNode->createChildSceneNode();
    kmVec3 entityNodePosition = kmVec3Make(0, 0, -5);
    entityNode->setPosition(entityNodePosition);
    //Camera node.
    TinySceneNode* cameraNode = rootNode->createChildSceneNode();
    kmVec3 cameraNodePosition = kmVec3Make(0, 0, 0);
    cameraNode->setPosition(cameraNodePosition);
    
    //Create an entity and attach it to our scene graph.
    TinyEntityFactory* factory = dynamic_cast<TinyEntityFactory*>(root->getMovableObjectFactory("Entity"));
    TinyNameValuePairList params;
    params["mesh"] = "assets/example1.obj";
    mEntity = dynamic_cast<TinyEntity*>(factory->createInstance("", params));
    entityNode->attachObject(mEntity);
    
    //Create camera.
    mCamera = sceneMgr->createCamera("main_camera");
    mainWindow->addViewPort(mCamera, 0, 0, 0, 1, 1);
    cameraNode->attachObject(mCamera);
    
    //Create a diffuse texture.
    TinyTexture* texture = TinyTextureManager::getSingleton()->load("assets/example1.tga");
    
    //Create a gpu program, set diffuse texture to our program as parameter.
    TinyGPUProgram* program = TinyGPUProgramManager::getSingleton()->load("assets/example1.vs", "assets/example1.fs");
    program->setParameter(TinyGPUProgramParameter("diffuse_sampler", GP_SAMPLER, &texture->getHandler()));
    
    //Create material with gpu program.
    TinyMaterial* material = TinyMaterialManager::getSingleton()->load("assets/example1.material");
    material->setProgram(program);
    
    //Set the material to entity.
    mEntity->setMaterial(material);
    
    TinyInputObject *inputObject_mouse = Tiny::TinyInputManager::getSingleton()->getInputObject(Tiny::InputDevice::Mouse);
    mMouse = (Tiny::TinyMouse *)inputObject_mouse;
    TinyInputObject *inputObject_keyboard = Tiny::TinyInputManager::getSingleton()->getInputObject(Tiny::InputDevice::Keyboard);
    mKeyBoard = (Tiny::TinyKeyboard *)inputObject_keyboard;
    
    light_direction = kmVec3Make(0, 0, -1);
    light_color = kmVec3Make(1, 1, 1);
    light_ambient_power = 0.1;
    light_diffuse_power = 0.5;
    light_specular_power = 0.4;
    material_shininess = 100;
    
    mMouse->addEventCallBack(this);
    mKeyBoard->addEventCallBack(this);
    root->addFrameListener(this);
}

void OceanApplication::keyPressed(TinyKeyEvent* event)
{
    uint8 keyCode = event->mKeyCode;
    float sensity = 0.1;
    switch (keyCode) {
        case 'w':
        {
            kmVec3 vec;
            kmVec3Fill(&vec, 0, 0, -sensity);
            mCamera->moveRelative(vec);
            break;
        }
        case 's':
        {
            kmVec3 vec;
            kmVec3Fill(&vec, 0, 0, sensity);
            mCamera->moveRelative(vec);
            break;
        }
        case 'a':
        {
            kmVec3 vec;
            kmVec3Fill(&vec, -sensity, 0, 0);
            mCamera->moveRelative(vec);
            break;
        }
        case 'd':
        {
            kmVec3 vec;
            kmVec3Fill(&vec, sensity, 0, 0);
            mCamera->moveRelative(vec);
            break;
        }
        default:
            break;
    }
}

void OceanApplication::keyReleased(TinyKeyEvent* event)
{
    
}

void OceanApplication::mouseDraged(TinyMouseEvent* event)
{
    float sensity = 0.01f;
    TinyMouseState& state = event->state;
    if (state.deltaX != 0)
    {
        mCamera->yaw(-state.deltaX * sensity);
    }
    if (state.deltaY != 0)
    {
        mCamera->roll(-state.deltaY * sensity);
    }
}

void OceanApplication::mouseMoved(TinyMouseEvent* event)
{
    
}

void OceanApplication::mousePressed(TinyMouseEvent* event, TinyMouseButtonID id)
{
    
}

void OceanApplication::mouseReleased(TinyMouseEvent* event, TinyMouseButtonID id)
{
    
}

void OceanApplication::onFrameStarted()
{
    auto program = mEntity->getSubEntity(0)->getMaterial()->getProgram();
    program->setParameter(TinyGPUProgramParameter("light_direction", GP_FLOAT3, &light_direction));
    program->setParameter(TinyGPUProgramParameter("light_color", GP_FLOAT3, &light_color));
    program->setParameter(TinyGPUProgramParameter("light_ambient_power", GP_FLOAT1, &light_ambient_power));
    program->setParameter(TinyGPUProgramParameter("light_diffuse_power", GP_FLOAT1, &light_diffuse_power));
    program->setParameter(TinyGPUProgramParameter("light_specular_power", GP_FLOAT1, &light_specular_power));
    program->setParameter(TinyGPUProgramParameter("material_shininess", GP_FLOAT1, &material_shininess));
}


