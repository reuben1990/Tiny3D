//
//  TinySceneManager.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinySceneManager.h"
#include "TinyMemoryAlloc.h"
#include "TinyIteratorWrapper.h"
#include "TinyRenderOperation.h"

namespace Tiny
{
    TinySceneManager::TinySceneManager()
        : mCurrentViewPort(nullptr)
        , mCameraInProgress(nullptr)
        , mSceneRoot(nullptr)
        , mDestRenderSystem(nullptr)
        , mSceneRoot(nullptr)
        , mRenderQueue(nullptr)
    {
        mDestRenderSystem = TINY_NEW TinyRenderSystem();
    }
    
    TinySceneManager::~TinySceneManager()
    {
        if (nullptr != mRenderQueue)
        {
            TINY_DELETE mRenderQueue;
        }
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
        getRootSceneNode()->findVisibleObjects(mCameraInProgress, getRenderQueue());
    }
    
    void TinySceneManager::setViewPort(TinyViewPort* vp)
    {
        mDestRenderSystem->setViewPort(vp);
    }
    
    void TinySceneManager::renderVisibleObjects()
    {
        MapIterator<RenderQueueGroupMap > iter = getRenderQueue()->getQueueGroupIterator();
        
        while (iter.hasMoreElements())
        {
            //uint8 qId = queueIt.peekNextKey();
            TinyRenderQueueGroup* pGroup = iter.getNext();
            renderQueueGroupObjects(pGroup);
        }
    }
    void TinySceneManager::renderQueueGroupObjects(TinyRenderQueueGroup* group)
    {
        MapIterator<RenderPriorityGroupMap > iter = group->getPriorityGroupIterator();
        
        while (iter.hasMoreElements())
        {
            //uint8 priority = iter.peekNextKey();
            TinyRenderPriorityGroup* pPriorityGroup = iter.getNext();
            renderObjects(pPriorityGroup->getSolidCollection());
            renderObjects(pPriorityGroup->getTransParentCollection());
        }
    }
    
    void TinySceneManager::renderObjects(TinyRenderableCollection* collection)
    {
        VectorIterator<RenderableArray > iter = collection->getRenderableIterator();
        while (iter.hasMoreElements())
        {
            TinyRenderable pRenderable = iter.getNext();
            renderSingleObject(pRenderable);
        }
    }
    
    void TinySceneManager::renderSingleObject(TinyRenderable* renderable)
    {
        TinyRenderOperation ro;
        renderable->getRenderOperation(&ro);
        mDestRenderSystem->render(&ro);
    }
    
    void TinySceneManager::setViewMatrix(kmMat4& matrix)
    {
        mDestRenderSystem->setViewMatrix(matrix);
    }
    
    TinyRenderQueue* TinyRenderQueue::getRenderQueue()
    {
        if (nullptr == mRenderQueue)
        {
            mRenderQueue = TINY_NEW TinyRenderQueue();
        }
        return mRenderQueue;
    }
}



