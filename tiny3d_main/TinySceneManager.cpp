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
#include "TinyRenderSystem.h"

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
        mCameraInProgress = cam;
        
        kmMat4 projMatrix;
        cam->getProjectionMatrix(projMatrix);
        setProjectionMatrix(projMatrix);
        
        kmMat4 viewMatrix;
        cam->getViewMatrix(viewMatrix);
        setViewMatrix(viewMatrix);
        
        setViewPort(cam->getViewPort());
        clearBg();
        updateSceneGraph();
        findVisibleObjects(cam);
        renderVisibleObjects();
    }
    
    void TinySceneManager::clearBg()
    {
        mDestRenderSystem->clearBg();
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
        getRenderQueue()->clear();
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
        
        kmMat4 modelMatrix;
        renderable->getModelMatrix(modelMatrix);
        setModelMatrix(modelMatrix);
        
        const kmVec3& cameraPositionWorld = mCameraInProgress->getDerivedPosition();
        kmVec3 cameraPositionModel;
        kmMat4 modelMatrixTranspose;
        kmMat4Transpose(&modelMatrixTranspose, &modelMatrix);
        kmVec3MultiplyMat4(&cameraPositionModel, &cameraPositionWorld, &modelMatrixTranspose);
        setEyePositionModelSpace(cameraPositionModel);
        
        
        updateGpuProgramParameters(ro);
        
        mDestRenderSystem->render(&ro);
    }
    
    void TinySceneManager::updateGpuProgramParameters(TinyRenderOperation& ro)
    {
        //update auto parameters
        TinyGPUProgram* program = ro.mProgram;
        TinyGPUProgramParameters* params = program->getGPUProgramParameters();
        params->updateAutoParams(&mAutoParamDataSource);
    }
    
    void TinySceneManager::setProjectionMatrix(kmMat4& matrix)
    {
        mDestRenderSystem->setProjectionMatrix(matrix);
        mAutoParamDataSource.setProjectionMatrix(matrix);
    }
    
    void TinySceneManager::setViewMatrix(kmMat4& matrix)
    {
        mDestRenderSystem->setViewMatrix(matrix);
        mAutoParamDataSource.setViewMatrix(matrix);
    }
    
    void TinySceneManager::setModelMatrix(kmMat4& matrix)
    {
        mDestRenderSystem->setModelMatrix(matrix);
        mAutoParamDataSource.setModelMatrix(matrix);
    }
    
    void TinySceneManager::setEyePositionModelSpace(const kmVec3& position)
    {
        mAutoParamDataSource.setEyePositionModelSpace(position);
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



