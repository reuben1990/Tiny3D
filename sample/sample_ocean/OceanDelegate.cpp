//
//  OceanDelegate.cpp
//  proj_mac
//
//  Created by reuben chao on 2/20/15.
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

namespace Tiny
{
    void TinyDelegate::initialize()
    {
        //Create TinyRoot.
        TinyRoot* root = TinyRoot::getSingleton();
        
        Tiny::TinyInputManager::getSingleton()->createInputObject(Tiny::InputDevice::Mouse);
        Tiny::TinyInputManager::getSingleton()->createInputObject(Tiny::InputDevice::Keyboard);
        
        //Create render window.
        TinyRenderWindow* mainWindow = tinyCreateRenderWindow(800, 480);
        root->attachRenderTarget(mainWindow);
        
        //Init scene graph.
        TinySceneManager* sceneMgr = root->createSceneManager();
        TinySceneNode* rootNode = sceneMgr->getRootSceneNode();
        //Entity node.
        TinySceneNode* entityNode = rootNode->createChildSceneNode();
        kmVec3 entityNodePosition = kmVec3Make(0, 0, -0.5);
        entityNode->setPosition(entityNodePosition);
        //Camera node.
        TinySceneNode* cameraNode = rootNode->createChildSceneNode();
        kmVec3 cameraNodePosition = kmVec3Make(0, 0, 0);
        cameraNode->setPosition(cameraNodePosition);
        
        //Create an entity and attach it to our scene graph.
        std::string entityFactoryNameStr("Entity");
        TinyEntityFactory* factory = dynamic_cast<TinyEntityFactory*>(root->getMovableObjectFactory(entityFactoryNameStr));
        TinyNameValuePairList params;
        const int8* meshName = "first_mesh.obj";
        params["mesh"] = meshName;
        std::string entityNameStr("first_entity");
        TinyEntity* entity = dynamic_cast<TinyEntity*>(factory->createInstance(entityNameStr, params));
        entityNode->attachObject(entity);
        
        //Create camera.
        std::string cameraNameStr("camera");
        TinyCamera* camera = TINY_NEW TinyCamera(cameraNameStr, sceneMgr);
        mainWindow->addViewPort(camera, 0, 0, 0, 1, 1);
        cameraNode->attachObject(camera);
        
        
        //Create a diffuse texture.
        //std::string textureName("first_demo.png");
        //TinyTexture* texture = TinyTextureManager::getSingleton()->load(textureName);
        
        //Create a gpu program, set diffuse texture to our program as parameter.
        TinyGPUProgram* program = TinyGPUProgramManager::getSingleton()->load("first_demo.vs", "first_demo.fs");
        //TinyGPUProgramParameter param;
        //param.mName = "diffuseTexture";
        //param.mType = GP_SAMPLER;
        //param.mBindData = texture->getHandlerPtr();
        //program->setParameter(param);
        
        //Create material with gpu program. TODO assemble program form script.
        TinyMaterial* material = TinyMaterialManager::getSingleton()->load("first_demo.material");
        material->setProgram(program);
        
        //Set the material to entity.
        entity->setMaterial(material);
    }
}