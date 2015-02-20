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
        kmMat4 viewMatrix;
        cam->getViewMatrix(viewMatrix);
        setViewPort(cam->getViewPort());
        setViewMatrix(viewMatrix);
        updateSceneGraph();
        findVisibleObjects(cam);
        renderVisibleObjects();
    }
    
    TinySceneNode* TinySceneManager::getRootSceneNode()
    {
        if (! mSceneRoot)
        {
            std::string name = "Tiny/SceneRoot";
            mSceneRoot = TINY_NEW TinySceneNode(name);
        }
        return mSceneRoot;
    }
    
    void TinySceneManager::updateSceneGraph()
    {
        getRootSceneNode()->update();
    }
    
    void TinySceneManager::findVisibleObjects(TinyCamera *cam)
    {
        getRootSceneNode()->findVisibleObjects(cam, getRenderQueue());
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
            TinyRenderable* pRenderable = iter.getNext();
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
    
    TinyRenderQueue* TinySceneManager::getRenderQueue()
    {
        if (nullptr == mRenderQueue)
        {
            mRenderQueue = TINY_NEW TinyRenderQueue();
        }
        return mRenderQueue;
    }
}



