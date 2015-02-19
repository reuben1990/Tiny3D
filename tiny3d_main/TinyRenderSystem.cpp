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
            glViewport(vpPosition.x, vpPosition.y vpSize.x, vpSize.y);
            glScissor(vpPosition.x, vpPosition.y vpSize.x, vpSize.y);
        }
    }
    
    void TinyRenderSystem::setRenderTarget(TinyRenderTarget *target)
    {
        mActiveRenderTarget = target;
        if (target)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, target->getFBO());
        }
    }
    
    void TinyRenderSystem::setViewMatrix(kmMat4& matrix)
    {
        kmMat4Fill(&mViewMatrix, matrix.kmScalar);
    }
    
    void TinyRenderSystem::updateAllRenderTargets()
    {
        std::map<unsigned char, TinyRenderTarget *> iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            iter->second->update(false);
        }
    }
    
    void TinyRenderSystem::swapAllRenderTargetBuffers()
    {
        std::map<unsigned char, TinyRenderTarget *> iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            iter->second->swapBuffers();
        }
    }
    
    void TinyRenderSystem::render(TinyRenderOperation* ro)
    {
        glUseProgram(ro->mProgram->getHandler());
        
        //bind vertexAttr
        auto iter = ro->mVertexData->getBufferIterator();
        while (iter.hasMoreElements())
        {
            auto key = iter->first;
            TinyVertexElement* element = iter->second;
            TinyHardwareBuffer* hardwareBuffer = element->mBuffer;
            glBindBuffer(GL_ARRAY_BUFFER, hardwareBuffer->getHandler());
            glEnableVertexAttribArray(key);
            glVertexAttribPointer(key, element->mSize, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        }
        
        //bind index
        TinyIndexData indexData = ro->mIndexData;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexData->getBuffer());
        
        //bind uniform
        TinyGPUProgram* program = ro->mProgram;
        program->useProgram();
        
        //draw
        glDrawElements(GL_TRIANGLES, indexData->getVertexSize(), GL_UNSIGNED_SHORT, 0);
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
        std::map<unsigned char, TinyRenderTarget *> iter = mPrioritisedRenderTargets.begin();
        for (; iter != mPrioritisedRenderTargets.end(); iter ++)
        {
            if (iter->second == target)
            {
                mPrioritisedRenderTargets.erase(iter);
            }
        }
    }
}




