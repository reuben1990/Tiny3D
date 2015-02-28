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

void OceanApplication::initialize()
{

    //Create TinyRoot.
    TinyRoot* root = TinyRoot::getSingleton();
    
    Tiny::TinyInputManager::getSingleton()->createInputObject(Tiny::InputDevice::Mouse);
    Tiny::TinyInputManager::getSingleton()->createInputObject(Tiny::InputDevice::Keyboard);
    
    //Create render window.
    TinyRenderWindow* mainWindow = tinyCreateRenderWindow(800, 480);
    root->attachRenderTarget(mainWindow);
    
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
    std::string entityFactoryNameStr("Entity");
    TinyEntityFactory* factory = dynamic_cast<TinyEntityFactory*>(root->getMovableObjectFactory(entityFactoryNameStr));
    TinyNameValuePairList params;
    const int8* meshName = "assets/suzanne.obj";
    params["mesh"] = meshName;
    std::string entityNameStr("first_entity");
    TinyEntity* entity = dynamic_cast<TinyEntity*>(factory->createInstance(entityNameStr, params));
    entityNode->attachObject(entity);
    
    //Create camera.
    std::string cameraNameStr("camera");
    mCamera = TINY_NEW Tiny::TinyCamera(cameraNameStr, sceneMgr);
    mainWindow->addViewPort(mCamera, 0, 0, 0, 1, 1);
    cameraNode->attachObject(mCamera);
    
    //Create a diffuse texture.
    std::string textureName("assets/uvmap.tga");
    TinyTexture* texture = TinyTextureManager::getSingleton()->load(textureName);
    
    //Create a gpu program, set diffuse texture to our program as parameter.
    TinyGPUProgram* program = TinyGPUProgramManager::getSingleton()->load("assets/first_demo.vs", "assets/first_demo.fs");
    program->setParameter(TinyGPUProgramParameter("diffuse_sampler", GP_SAMPLER, &texture->getHandler()));
    
    //Create material with gpu program.
    TinyMaterial* material = TinyMaterialManager::getSingleton()->load("assets/first_demo.material");
    material->setProgram(program);
    
    //Set the material to entity.
    entity->setMaterial(material);
    
    TinyInputObject *inputObject_mouse = Tiny::TinyInputManager::getSingleton()->getInputObject(Tiny::InputDevice::Mouse);
    mMouse = (Tiny::TinyMouse *)inputObject_mouse;
    TinyInputObject *inputObject_keyboard = Tiny::TinyInputManager::getSingleton()->getInputObject(Tiny::InputDevice::Keyboard);
    mKeyBoard = (Tiny::TinyKeyboard *)inputObject_keyboard;
    
    mMouse->addEventCallBack(this);
}

void OceanApplication::keyPressed(TinyKeyEvent* event)
{
    
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
        mCamera->yaw(state.deltaX * sensity);
    }
    if (state.deltaY != 0)
    {
        mCamera->roll(state.deltaY * sensity);
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


