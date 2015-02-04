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

namespace Tiny
{
    TinyRoot *TinyRoot::sSingleton = nullptr;
    
    TinyRoot *TinyRoot::getSingleton()
    {
        if (nullptr == sSingleton)
        {
            sSingleton = new TinyRoot();
        }
        return sSingleton;
    }
    
    TinyRoot::TinyRoot()
    {
    }
    
    TinyRoot::~TinyRoot()
    {
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
        Tiny::TinyRenderSystem::getSingleton()->updateAllRenderTargets();
        Tiny::TinyRenderSystem::getSingleton()->swapAllRenderTargetBuffers();
    }
    
    void TinyRoot::onWindowUpdate(float width, float height)
    {
        //set all render target dirty.
    }
}




