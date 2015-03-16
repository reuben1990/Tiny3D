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
#include "TinyMemoryAlloc.h"
#include "TinyGBuffer.h"

namespace Tiny
{
    TinyRenderSystem::TinyRenderSystem():
    mActiveViewPort(nullptr),
    mActiveRenderTarget(nullptr),
    mGbuffer(nullptr)
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
            uint32 actualX = vpPosition.x;
            uint32 actualY = vpPosition.y;
            uint32 actualWidth = vpSize.x;
            uint32 actualHeight = vpSize.y;
            glViewport(actualX, actualY, actualWidth, actualHeight);
            glScissor(actualX, actualY, actualWidth, actualHeight);
            TINYLOG("glViewport (%d, %d) (%d, %d)", actualX, actualY, actualWidth, actualHeight);
        }
    }
    
    void TinyRenderSystem::clearBg()
    {
        mActiveRenderTarget->clearBg();
    }
    
    void TinyRenderSystem::setRenderTarget(TinyRenderTarget *target)
    {
        mActiveRenderTarget = target;
        if (target)
        {
            
        }
    }
    
    void TinyRenderSystem::setProjectionMatrix(kmMat4& matrix)
    {
        mProjMatrix = matrix;
    }
    
    void TinyRenderSystem::setViewMatrix(kmMat4& matrix)
    {
        mViewMatrix = matrix;
    }
    
    void TinyRenderSystem::setModelMatrix(kmMat4& matrix)
    {
        mModelMatrix = matrix;
    }
    
    void TinyRenderSystem::updateAllRenderTargets()
    {
        TinyRenderTargetMap::iterator iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            auto target = iter->second;
            TINYLOG("glBindFramebuffer %d", target->getFBO());
            glBindFramebuffer(GL_FRAMEBUFFER, target->getFBO());
            target->update(false);
        }
    }
    
    void TinyRenderSystem::swapAllRenderTargetBuffers()
    {
        TinyRenderTargetMap::iterator iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            //
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
        
        TinyVertexObject* vertexObject = ro->mVertexObject;
        TinyVertexData* vertexData = vertexObject->getVertexData();
        TinyIndexData* indexData = vertexObject->getIndexData();
        GLuint handler = static_cast<GLuint>(vertexObject->getHandler());
        if (!vertexObject->isGeneratedObject())
        {
            glGenVertexArrays(1, &handler);
            glBindVertexArray(handler);
            auto iter = vertexData->getBufferIterator();
            while (iter.hasMoreElements())
            {
                GLuint location = iter.peekNextKey();
                TinyVertexElement* element = iter.getNext();
                TinyHardwareBuffer* hardwareBuffer = element->mBuffer;
                glBindBuffer(GL_ARRAY_BUFFER, hardwareBuffer->getHandler());
                TINYLOG("glBindBuffer vertex %d", hardwareBuffer->getHandler());
                glEnableVertexAttribArray(location);
                TINYLOG("glEnableVertexAttribArray %d", location);
                glVertexAttribPointer(location, element->mVectorSizePerElement, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
                TINYLOG("glVertexAttribPointer %d, %d", location, element->mVectorSizePerElement);
            }
            
            //bind index
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData->getBuffer()->getHandler());
            TINYLOG("glBindBuffer index %d", indexData->getBuffer()->getHandler());
            
            vertexObject->setHandler(handler);
        }
        else
        {
            glBindVertexArray(handler);
        }
        
        //draw
        uint32 vertexNum = indexData->getVertexNum();
        glDrawElements(GL_TRIANGLES, vertexNum, GL_UNSIGNED_INT, 0);
        TINYLOG("glDrawElements vertexNum = %d", vertexNum);
        
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




