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

namespace Tiny
{
    TinyRoot::TinyRoot():
    mRenderSystem(nullptr),
    mSceneMgr(nullptr)
    {
        //TODO only support one render window and render system now lol...
        mRenderSystem = TINY_NEW TinyRenderSystem();
        mRenderSystem->attachRenderTarget(TINY_NEW TinyRenderWindow());
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
}







