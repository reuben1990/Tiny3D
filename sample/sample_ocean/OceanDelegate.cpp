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

namespace Tiny
{
    void TinyDelegate::initialize()
    {
        TinyRoot* root = TINY_NEW TinyRoot();
        TinySceneManager* sceneMgr = root->createSceneManager();
        TinyNode* rootNode = sceneMgr->getRootSceneNode();
        TinySceneNode* secondNode = rootNode->createChildSceneNode();
        secondNode->setPosition(kmVec2(0.1, 0.1));
        rootNode->addChild(secondNode);
        
        TinyEntityFactory* factory = root->getMovableObjectFactory("Entity");
        TinyEntity* entity = factory->createInstance();
        secondNode->attachObject(entity);
        
        TinyTexture* texture = TinyTextureManager::getSingleton()->load("abc.png");
        
        TinyProgram* program = TinyProgramManager::getSingleton()->load("abc.vs", "abc.fs");
        TinyGPUProgramParameter param;
        param.mName = "diffuseTexture"
        param.mType = GP_SAMPLER
        param.mBindData = texture->getHandlerPtr();
        program->setParameter(const TinyGPUProgramParameter& value);
        
        TinyMaterial* material = TinyMaterialManager::getSingleton()->load("abc.material");
        material->setProgram(program);
        
        entity->setMaterial(material);
    }
}