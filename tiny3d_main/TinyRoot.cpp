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
        //const GLubyte* vendor = glGetString( GL_VENDOR );
        //TINYLOG("GL_VENDOR:   %s", glGetString( GL_VENDOR ) );
        //TINYLOG("GL_RENDERER: %s", glGetString( GL_RENDERER ) );
        //TINYLOG("GL_VERSION:  %s", glGetString( GL_VERSION ) );
        
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
        
        //fire render event
        fireRenderStartEvent();
        
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
    
    TinyMovableObjectFactory* TinyRoot::getMovableObjectFactory(const std::string& name)
    {
        TinyMovableObjectFactory* ret = nullptr;
        auto iter = mMovableObjectFactoryMap.find(name);
        if (iter != mMovableObjectFactoryMap.end())
        {
            ret = iter->second;
        }
        return ret;
    }
    
    void TinyRoot::addFrameListener(TinyFrameListener* listener)
    {
        auto iter = mRemovedListenerSet.find(listener);
        if (iter != mRemovedListenerSet.end())
            mRemovedListenerSet.erase(*iter);
        else
            mListenerSet.insert(listener);
    }
    
    void TinyRoot::removeFrameListener(TinyFrameListener* listener)
    {
        if (mRemovedListenerSet.find(listener) != mRemovedListenerSet.end())
            mRemovedListenerSet.insert(listener);
    }
    
    void TinyRoot::fireRenderStartEvent()
    {
        auto removedIter = mRemovedListenerSet.begin();
        for (; removedIter != mRemovedListenerSet.end(); removedIter ++)
        {
            mListenerSet.erase(*removedIter);
        }
        mRemovedListenerSet.clear();
        
        
        auto iter = mListenerSet.begin();
        for (; iter != mListenerSet.end(); iter ++)
        {
            (*iter)->onFrameStarted();
        }
    }
}







