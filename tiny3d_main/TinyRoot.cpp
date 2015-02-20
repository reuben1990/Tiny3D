//
//  TinyRoot.cpp
//  proj_mac
//
//  Created by reuben chao on 2/3/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include <stdio.h>
#include "TinySchedulerManager.h"
#include "TinyRoot.h"
#include "TinyRenderSystem.h"
#include "TinyMemoryAlloc.h"
#include "TinyEntityFactory.h"

namespace Tiny
{
    TinyRoot::TinyRoot():
    mRenderSystem(nullptr),
    mSceneMgr(nullptr)
    {
        mRenderSystem = TINY_NEW TinyRenderSystem();
        addMovableObjectFactory(TINY_NEW TinyEntityFactory());
    }
    
    TinyRoot::~TinyRoot()
    {
        TINY_DELETE mSceneMgr;
        TINY_DELETE mRenderSystem;
    }
    
    TinySceneManager *TinyRoot::createSceneManager()
    {
        if (mSceneMgr)
        {
            TINY_DELETE mSceneMgr;
        }
        mSceneMgr = TINY_NEW TinySceneManager();
        return mSceneMgr;
    }
    
    void TinyRoot::attachRenderTarget(TinyRenderTarget* target)
    {
        mRenderSystem->attachRenderTarget(target);
    }
    
    void TinyRoot::renderOneFrame(float timeInterval)
    {
        //add Time to scheduler.
        Tiny::TinyScheduleManager::getSingleton()->timeStep(timeInterval);
        
        //update all render targets, include render window, render texture, etc.
        updateAllRenderTargets();
        
    }
    
    void TinyRoot::updateAllRenderTargets()
    {
        //render all render target.
        if (mRenderSystem)
        {
            mRenderSystem->updateAllRenderTargets();
            mRenderSystem->swapAllRenderTargetBuffers();
        }
    }
    
    void TinyRoot::addMovableObjectFactory(TinyMovableObjectFactory* factory)
    {
        mMovableObjectFactoryMap[factory->getType()] = factory;
    }
    
    TinyMovableObjectFactory* TinyRoot::getMovableObjectFactory(std::string& name)
    {
        TinyMovableObjectFactory* ret = nullptr;
        auto iter = mMovableObjectFactoryMap.find(name);
        if (iter != mMovableObjectFactoryMap.end())
        {
            ret = iter->second;
        }
        return ret;
    }
}







