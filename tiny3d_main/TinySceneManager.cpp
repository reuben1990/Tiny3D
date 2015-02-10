//
//  TinySceneManager.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySceneManager.h"
#include "TinyMemoryAlloc.h"

namespace Tiny
{
    TinySceneManager::TinySceneManager()
        : mCurrentViewPort(nullptr)
        , mCameraInProgress(nullptr)
        , mSceneRoot(nullptr)
        , mDestRenderSystem(nullptr)
        , mSceneRoot(nullptr)
    {
        mDestRenderSystem = TINY_NEW TinyRenderSystem();
    }
    
    TinySceneManager::~TinySceneManager()
    {
    }
    
    void TinySceneManager::renderScene(TinyCamera *cam)
    {
        setViewPort();
        setViewMatrix(cam->getViewMatrix());
        updateSceneGraph();
        findVisibleObjects();
        renderVisibleObjects();
    }
    
    TinySceneNode* TinySceneManager::getRootSceneNode()
    {
        if (! mSceneRoot)
        {
            mSceneRoot = TINY_NEW TinySceneNode("Tiny/SceneRoot");
        }
        return mSceneRoot;
    }
    
    void TinySceneManager::updateSceneGraph()
    {
        getRootSceneNode()->update();
    }
    
    void TinySceneManager::findVisibleObjects()
    {
        getRootSceneNode()->findVisibleObjects();
    }
    
    void TinySceneManager::setViewPort(TinyViewPort* vp)
    {
        mDestRenderSystem->setViewPort(vp);
    }
    
    void TinySceneManager::renderVisibleObjects()
    {
        
    }
    
    void TinySceneManager::setViewMatrix(kmMat4& matrix)
    {
        mDestRenderSystem->setViewMatrix(matrix);
    }
}



