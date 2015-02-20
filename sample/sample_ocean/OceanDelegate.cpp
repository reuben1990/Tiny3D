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
#include "TinyTextureManager.h";
#include "TinyRenderWindow.h"
#include "kazmath/kazmath.h"
#include "TinyEntityFactory.h"
#include "TinyEntity.h";
#include "TinyMath.h"

namespace Tiny
{
    void TinyDelegate::initialize()
    {
        //Create TinyRoot.
        TinyRoot* root = TINY_NEW TinyRoot();
        
        //Create render window.
        TinyRenderWindow* mainWindow = tinyCreateRenderWindow(0, 0);
        root->attachRenderTarget(mainWindow);
        
        //Init scene graph.
        TinySceneManager* sceneMgr = root->createSceneManager();
        TinySceneNode* rootNode = sceneMgr->getRootSceneNode();
        //Entity node.
        TinySceneNode* entityNode = rootNode->createChildSceneNode();
        kmVec3 entityNodePosition = kmVec3Make(0, 0, -0.5);
        entityNode->setPosition(entityNodePosition);
        rootNode->addChild(entityNode);
        //Camera node.
        TinySceneNode* cameraNode = rootNode->createChildSceneNode();
        kmVec3 cameraNodePosition = kmVec3Make(0, 0, 0);
        cameraNode->setPosition(cameraNodePosition);
        rootNode->addChild(cameraNode);
        
        //Create an entity and attach it to our scene graph.
        TinyEntityFactory* factory = root->getMovableObjectFactory("Entity");
        TinyEntity* entity = factory->createInstance();
        entityNode->attachObject(entity);
        
        //Create camera.
        TinyCamera* camera = TINY_NEW TinyCamera();
        mainWindow->addViewPort(camera);
        cameraNode->attachObject(camera);
        
        
        //Create a diffuse texture.
        TinyTexture* texture = TinyTextureManager::getSingleton()->load("first_demo.png");
        
        //Create a gpu program, set diffuse texture to our program as parameter.
        TinyProgram* program = TinyProgramManager::getSingleton()->load("first_demo.vs", "first_demo.fs");
        TinyGPUProgramParameter param;
        param.mName = "diffuseTexture"
        param.mType = GP_SAMPLER
        param.mBindData = texture->getHandlerPtr();
        program->setParameter(const TinyGPUProgramParameter& value);
        
        //Create material with gpu program. TODO assemble program form script.
        TinyMaterial* material = TinyMaterialManager::getSingleton()->load("first_demo.material");
        material->setProgram(program);
        
        //Set the material to entity.
        entity->setMaterial(material);
    }
}