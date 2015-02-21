//
//  TinyRenderSystem.cpp
//  proj_mac
//
//  Created by reuben chao on 2/4/15.
//  Copyright (c) 2015 reuben chao. All rights reserved.
//

#include "TinyRenderSystem.h"
#include "kazmath/kazmath.h"
#include "TinyHardwareBuffer.h"
#include "TinyPlatform.h"

namespace Tiny
{
    TinyRenderSystem::TinyRenderSystem():
    mActiveViewPort(nullptr),
    mActiveRenderTarget(nullptr)
    {
    }
    
    TinyRenderSystem::~TinyRenderSystem()
    {
    }
    
    void TinyRenderSystem::setViewPort(TinyViewPort *vp)
    {
        if (!vp)
        {
            mActiveViewPort = nullptr;
            setRenderTarget(nullptr);
        }
        else
        {
            mActiveViewPort = vp;
            TinyRenderTarget *renderTarget;
            renderTarget = vp->getRenderTarget();
            setRenderTarget(renderTarget);
            kmVec2 vpPosition = vp->geViewPortLeftBottom();
            kmVec2 vpSize = vp->getViewPortSize();
            glViewport(vpPosition.x, vpPosition.y, vpSize.x, vpSize.y);
            glScissor(vpPosition.x, vpPosition.y, vpSize.x, vpSize.y);
            TINYLOG("glViewport (%f, %f) (%f, %f)", vpPosition.x, vpPosition.y, vpSize.x, vpSize.y);
        }
    }
    
    void TinyRenderSystem::clearBg()
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        TINYLOG("glClear");
    }
    
    void TinyRenderSystem::setRenderTarget(TinyRenderTarget *target)
    {
        mActiveRenderTarget = target;
        if (target)
        {
            TINYLOG("glBindFramebuffer %d", target->getFBO());
            glBindFramebuffer(GL_FRAMEBUFFER, target->getFBO());
        }
    }
    
    void TinyRenderSystem::setViewMatrix(kmMat4& matrix)
    {
        mViewMatrix = matrix;
    }
    
    void TinyRenderSystem::updateAllRenderTargets()
    {
        TinyRenderTargetMap::iterator iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            iter->second->update(false);
        }
    }
    
    void TinyRenderSystem::swapAllRenderTargetBuffers()
    {
        TinyRenderTargetMap::iterator iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            iter->second->swapBuffer();
        }
    }
    
    void TinyRenderSystem::render(TinyRenderOperation* ro)
    {
        //switch states
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        TINYLOG("glEnable and glDisable");
        
        //bind uniform
        TinyGPUProgram* program = ro->mProgram;
        program->useProgram();
        TINYLOG("glUseProgram");
        
        //bind vertexAttr
        auto iter = ro->mVertexData->getBufferIterator();
        while (iter.hasMoreElements())
        {
            auto key = iter.peekNextKey();
            TinyVertexElement* element = iter.getNext();
            TinyHardwareBuffer* hardwareBuffer = element->mBuffer;
            glBindBuffer(GL_ARRAY_BUFFER, hardwareBuffer->getHandler());
            TINYLOG("glBindBuffer %d", hardwareBuffer->getHandler());
            glEnableVertexAttribArray(key);
            TINYLOG("glEnableVertexAttribArray %d", key);
            glVertexAttribPointer(key, element->mSize, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
            TINYLOG("glVertexAttribPointer %d, %d", key, element->mSize);
        }
        
        //bind index
        TinyIndexData* indexData = ro->mIndexData;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData->getBuffer()->getHandler());
        TINYLOG("glBindBuffer indexbuffer %d", indexData->getBuffer()->getHandler());
        
        //draw
        glDrawElements(GL_TRIANGLES, indexData->getVertexSize(), GL_UNSIGNED_SHORT, 0);
        TINYLOG("glDrawElements");
    }
    
    void TinyRenderSystem::attachRenderTarget(TinyRenderTarget *target)
    {
        std::pair<unsigned char, TinyRenderTarget *> element(target->getPriority(), target);
        mPrioritisedRenderTargets.insert(element);
    }
    
    void TinyRenderSystem::detachRenderTarget(TinyRenderTarget *target)
    {
        if (target == mActiveRenderTarget)
        {
            mActiveRenderTarget = nullptr;
        }
        TinyRenderTargetMap::iterator iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            if (iter->second == target)
            {
                mPrioritisedRenderTargets.erase(iter);
            }
        }
    }
}




